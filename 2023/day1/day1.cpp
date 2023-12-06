#include "../util/util.h"

#include <unordered_map>
#include <unordered_set>


// Part 1 function
void part1(const std::vector<std::string>& lines) {
    int total = 0;

    for (const auto& str : lines) {
        int firstDigit = -1, lastDigit = -1;

        for (char ch : str) {
            if (std::isdigit(ch)) {
                if (firstDigit == -1) firstDigit = ch - '0';
                lastDigit = ch - '0';
            }
        }
        
        total += firstDigit * 10 + lastDigit;
    }
    std::cout << total << std::endl;
}

inline int convertToDigit(const std::string& s, const std::unordered_map<std::string, int>& numberMap) {
    if (s.length() == 1) {
        return s[0] - '0';
    }
    else if (numberMap.find(s) != numberMap.end()) {
        return numberMap.at(s);
    }
    return 0;
}

std::pair<std::string, std::string> findFirstAndLastOccurrence(const std::string& mainStr, const std::unordered_set<std::string>& searchStrs) {
    size_t firstPos = std::string::npos;
    size_t lastPos = 0;
    std::string firstOccurrence, lastOccurrence;

    for (const auto& str : searchStrs) {
        size_t currentFirstPos = mainStr.find(str);
        size_t currentLastPos = mainStr.rfind(str);

        if (firstPos != 0 && currentFirstPos != std::string::npos && (currentFirstPos < firstPos)) {
            firstPos = currentFirstPos;
            firstOccurrence = str;
        }

        if (lastPos != mainStr.length() -1 && currentLastPos != std::string::npos && (currentLastPos >= lastPos)) {
            lastPos = currentLastPos;
            lastOccurrence = str;
        }
    }

    return { firstOccurrence, lastOccurrence };
}

// Part 2 function
void part2(const std::vector<std::string>& lines) {
    int total = 0;
    std::unordered_set<std::string> searchStrs = { "one", "1", "two", "2", "three", "3", "four", "4", "five", "5", "six", "6", "seven", "7", "eight", "8", "nine", "9"};
    std::unordered_map<std::string, int> numberMap = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3},
        {"four", 4}, {"five", 5}, {"six", 6},
        {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    for (auto line : lines)
    {
        auto [first, last] = findFirstAndLastOccurrence(line, searchStrs);
        total += convertToDigit(first, numberMap)*10 + convertToDigit(last, numberMap);
    }
    std::cout << total << std::endl;
}

int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day1\\input.txt");
    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines);//54561
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines);//54076
    return 0;
}
