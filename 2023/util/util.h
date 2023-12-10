#pragma once

#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <regex>
#include <chrono>
#include <functional>
#include <ranges>
#include <numeric>

namespace aoc_util
{

namespace string {

    using MultipleLines = std::vector<std::string>;
    using SingleLine = std::string;

    template<typename... Args>
    inline std::string buildPattern(Args... args) {
        std::ostringstream patternStream;
        // Use fold expression with comma operator to concatenate arguments with '|'
        ((patternStream << args << '|'), ...);
        std::string pattern = patternStream.str();
        pattern.pop_back(); // Remove the trailing '|'
        return pattern;
    }

    template <typename T, typename... Args>
    requires (std::is_arithmetic_v<T> || std::is_same_v<T, std::string>)
    inline std::vector<T> splitString(const std::string& input, Args... args) {
        std::string pattern = buildPattern(args...);
        std::regex regexPattern(pattern);

        std::sregex_token_iterator iter(input.begin(), input.end(), regexPattern, -1);
        std::sregex_token_iterator end;

        std::vector<T> result;
        while (iter != end) {
            if (iter->first != iter->second) { // Check if the sub_match is not empty
                if constexpr (std::is_arithmetic_v<T>) { // Check if T is numeric
                    std::stringstream ss(*iter);
                    T value;
                    ss >> value;
                    result.push_back(value);
                }
                else {
                    result.push_back(*iter);
                }
            }
            ++iter;
        }
        return result;

    }

    template <typename... Args>
    inline void removeFromString(std::string& input, Args... args) {
        std::string pattern = buildPattern(args...);
        std::regex regexPattern(pattern);

        input = std::regex_replace(input, regexPattern, "");
    }

    template<typename T>
    requires (std::is_same_v<std::remove_cvref_t<T>, SingleLine> || std::is_same_v<std::remove_cvref_t<T>, MultipleLines>)
    inline T readFile(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open file: " + filePath);
        }

        if constexpr (std::is_same_v<T, SingleLine>) {
            SingleLine content;
            file.seekg(0, std::ios::end);
            content.reserve(file.tellg());
            file.seekg(0, std::ios::beg);

            content.assign((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());

            content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
            return content;
        }
        else {
            std::vector<std::string> lines;
            std::string line;
            while (std::getline(file, line)) {
                if(line[0] == '\r') continue;
                aoc_util::string::removeFromString(line, "\\r", "\\n", "\\t");
                if(!line.empty()) lines.push_back(line);
            }
            return lines;
        }
    }

} //namespace string

namespace time {

    template<typename Resolution>
    concept isChronoType = requires {
        typename Resolution::rep;
        typename Resolution::period;
        { Resolution::zero() } -> std::same_as<Resolution>;
    };

    template<typename Resolution>
    requires isChronoType<Resolution>
    constexpr inline std::string getDurationUnit() {
        if constexpr (std::is_same_v<std::remove_cvref_t<Resolution>, std::chrono::nanoseconds>) return "nanoseconds";
        if constexpr (std::is_same_v<std::remove_cvref_t<Resolution>, std::chrono::microseconds>) return "microseconds";
        if constexpr (std::is_same_v<std::remove_cvref_t<Resolution>, std::chrono::milliseconds>) return "milliseconds";
        if constexpr (std::is_same_v<std::remove_cvref_t<Resolution>, std::chrono::seconds>) return "seconds";
        if constexpr (std::is_same_v<std::remove_cvref_t<Resolution>, std::chrono::minutes>) return "minutes";
        if constexpr (std::is_same_v<std::remove_cvref_t<Resolution>, std::chrono::hours>) return "hours";
        return "unknown units";
    }

    template<typename Resolution = std::chrono::microseconds, typename Func, typename... Args>
    requires std::invocable<Func, Args...> && isChronoType<Resolution>
    inline void timeCall(const std::string& funcName, Func func, Args&&... args) {
        std::cout << std::flush;
        auto t1 = std::chrono::high_resolution_clock::now();
        std::invoke(func, std::forward<Args>(args)...);
        auto t2 = std::chrono::high_resolution_clock::now();

        /* Getting number of milliseconds as an integer. */
        auto ms_int = std::chrono::duration_cast<Resolution>(t2 - t1);

        std::cout << "Function " << funcName << "() took " << ms_int.count() << " " << getDurationUnit<Resolution>() << "\n";


    }

} // namespace time

namespace maths
{

    template<typename T>
    concept isIntegralContainer = requires(T a) {
        typename T::value_type;
            requires std::is_integral_v<typename T::value_type>;
    };

    template<typename T>
    requires std::is_integral_v<T>
    bool isPrime(T x) {
        if (x <= 1) return false;
        if (x == 2 || x == 3) return true;
        if (x % 2 == 0 || x % 3 == 0) return false;
        if ((x - 1) % 6 != 0 && (x + 1) % 6 != 0) return false;
        for (int i = 5; i * i <= x; i += 6)
        {
            if (x % i == 0 || x % (i + 2) == 0) return false;
        }
        return true;
    }

    // LCM with N integral types passed in
    template<typename ResultType = uint64_t, typename... Numbers>
        requires ((std::is_integral_v<Numbers> && !std::is_same_v<Numbers, bool>) && ...) && std::is_integral_v<ResultType>
    ResultType lcm(Numbers... args) {
        ResultType initialValue{ 1 };
        return ((initialValue = std::lcm(initialValue, args)), ...);
    }

    // LCM with a container of integral types passed in
    template<typename ResultType = uint64_t, typename Container>
        requires isIntegralContainer<Container>
    ResultType lcm(const Container& container) {
        ResultType initialValue{1};
        return std::accumulate(container.begin(), container.end(), initialValue, [](auto a, auto b) { return std::lcm(a, b); });
    }


    // GCD with N integral types passed in
    template<typename ResultType = uint64_t, typename First, typename... Numbers>
        requires ((std::is_integral_v<Numbers> && !std::is_same_v<Numbers, bool>) && ...) && std::is_integral_v<ResultType> && std::is_integral_v<First>
    ResultType gcd(First first, Numbers... args) {
        return ((first = std::gcd(first, args)), ...);
    }

    // GCD with a container of integral types passed in
    template<typename ResultType = uint64_t, typename Container>
        requires isIntegralContainer<Container>
    ResultType gcd(const Container& container) {
        return std::accumulate(container.begin(), container.end(), container[0], [](auto a, auto b) { return std::gcd(a, b); });
    }


} // namespace maths

}
