#include "../util/util.h"


std::vector<std::vector<int>> builSequencesOfDifferences(const auto& line)
{
    const std::vector<int> lineSplit = aoc_util::string::splitString<int>(line, " ");

    std::vector<std::vector<int>> sequencesOfDifferences = { lineSplit };

    while (!std::all_of(sequencesOfDifferences.back().begin(), sequencesOfDifferences.back().end(), [](int i) { return i == 0; }))
    {

        std::vector<int> tmpSequence;
        for (int i = 0; i < sequencesOfDifferences.back().size() - 1; i++)
        {
            tmpSequence.push_back(sequencesOfDifferences.back()[i + 1] - sequencesOfDifferences.back()[i]);
        }
        sequencesOfDifferences.push_back(tmpSequence);

    }
    return sequencesOfDifferences;
}

// Part 1 function
void part1(const std::vector<std::string>& lines) 
{
    int totalSum = 0;

    for(const auto& line : lines)
    {
        std::vector<std::vector<int>> sequencesOfDifferences = builSequencesOfDifferences(line);
        int lineSum = 0;

        for (int i = 0; i < sequencesOfDifferences.size(); i++)
        {
            lineSum += sequencesOfDifferences[i].back();
        }
        totalSum += lineSum;

    }
    std::cout << totalSum << std::endl;

}

// Part 2 function
void part2(const std::vector<std::string>& lines) {

    int totalSum = 0;

    for (const auto& line : lines)
    {
        std::vector<std::vector<int>> sequencesOfDifferences = builSequencesOfDifferences(line);
        int lineSum = 0;

        for (int i = sequencesOfDifferences.size() - 2; i >= 0; i--)
        {
            lineSum = sequencesOfDifferences[i][0] - lineSum;
        }
        totalSum += lineSum;
    }
    std::cout << totalSum << std::endl;
}

int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day9\\input.txt");

    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines); // 1782868781
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines); // 1057

    return 0;
}
