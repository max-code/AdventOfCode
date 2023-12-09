#include "../util/util.h"

#include <unordered_map>
#include <numeric>


std::unordered_map<std::string, std::pair<std::string, std::string>> mapLines(std::vector<std::string>& lines)
{
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;

    for (auto& line : lines)
    {
        aoc_util::string::removeFromString<std::string>(line, "=", "\\(", ",", "\\)");
        const std::vector<std::string> lineSplit = aoc_util::string::splitString<std::string>(line, "\\s");
        if (lineSplit.size() > 1) 
        {
            map.insert({ lineSplit[0], {lineSplit[1], lineSplit[2]} });
        }
    }
    return map;
}

// Part 1 function
void part1(std::vector<std::string>& lines) {

    std::unordered_map<std::string, std::pair<std::string, std::string>> map = mapLines(lines);

    aoc_util::string::removeFromString<std::string>(lines[0], "\\s");
    const std::string& instructions = lines[0];
    const int instructionCount = instructions.size();
    std::string currentPos = "AAA";
    int moves = 0;

    while (currentPos != "ZZZ")
    {
        auto instruction = instructions[moves % instructionCount];
        if (instruction == 'L')
        {
            currentPos = map[currentPos].first;
        } 
        else
        {
            currentPos = map[currentPos].second;
        }
        moves += 1;
    }

    std::cout << moves << std::endl;


}

// Part 2 function
void part2(std::vector<std::string>& lines) {
    std::unordered_map<std::string, std::pair<std::string, std::string>> map = mapLines(lines);

    aoc_util::string::removeFromString<std::string>(lines[0], "\\s");
    const std::string& instructions = lines[0];
    const int instructionCount = instructions.size();

    std::vector<std::string> currentPositions;

    for (const auto& [key, val] : map)
    {
        if (key[2] == 'A')
        {
            currentPositions.emplace_back(key);
        }
    }

    std::vector<int64_t> currentPositionsToZZZ{};

    for (int i = 0; i < currentPositions.size(); i++) {
        std::string currentPos = currentPositions[i];
        int64_t moves = 0;


        while (currentPos[2] != 'Z')
        {
            auto instruction = instructions[moves % instructionCount];
            if (instruction == 'L')
            {
                currentPos = map[currentPos].first;
            }
            else
            {
                currentPos = map[currentPos].second;
            }
            moves += 1;
        }
        currentPositionsToZZZ.push_back(moves);

    }

    long long result = std::accumulate(currentPositionsToZZZ.begin(), currentPositionsToZZZ.end(), 1LL, [](long long a, int b) {
        return (a / std::gcd(a, static_cast<long long>(b))) * b;
        });

    std::cout << result << std::endl;


}

int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day8\\input.txt");

    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines); // 13771
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines); // 13129439557681

    return 0;
}
