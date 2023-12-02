#include "../util/util.h"


// Part 1 function
void part1(const std::vector<std::string>& lines) {

    int idsSum = 0;
    constexpr int maxRed = 12, maxGreen = 13, maxBlue = 14;

    for (const auto& line : lines) {
        //std::cout << line << std::endl;
        const std::vector<std::string> games = aoc_util::splitString(line, "[;,:\\s]+");
        int gameId = std::stoi(games[1]);
        bool impossibleGame = false;

        for (int j = 3; j < games.size(); j += 2) // Just itterate over the colours
        {
            const int numCubes= std::stoi(games[j - 1]);
            if ((games[j] == "red" && numCubes > maxRed) ||
                (games[j] == "green" && numCubes > maxGreen) ||
                (games[j] == "blue" && numCubes > maxBlue))
            {
                impossibleGame = true;
                break;
            }
        }
        if (!impossibleGame)
        {
            idsSum += gameId;
        }
    }
    std::cout << idsSum << std::endl;

}

// Part 2 function
void part2(const std::vector<std::string>& lines) {
    int powerSetSum = 0;

    for (const auto& line : lines) {
        //std::cout << line << std::endl;
        const std::vector<std::string> games = aoc_util::splitString(line, "[;,:\\s]+");
        int minRequiredRedCubes = 0, minRequiredGreenCubes = 0, minRequiredBlueCubes = 0;

        for (int j = 3; j < games.size(); j += 2) // Just itterate over the colours
        {
            const int numCubes = std::stoi(games[j - 1]);
            if (games[j] == "red" && numCubes > minRequiredRedCubes)
            {
                minRequiredRedCubes = numCubes;
            }
            if (games[j] == "green" && numCubes > minRequiredGreenCubes)
            {
                minRequiredGreenCubes = numCubes;
            }
            if (games[j] == "blue" && numCubes > minRequiredBlueCubes)
            {
                minRequiredBlueCubes = numCubes;
            }

        }
        powerSetSum += minRequiredRedCubes * minRequiredGreenCubes * minRequiredBlueCubes;
    }
    std::cout << powerSetSum << std::endl;
}

int main() {
    const std::vector<std::string> lines = aoc_util::readFile("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day2\\input.txt");

    part1(lines);
    part2(lines);
    return 0;
}
