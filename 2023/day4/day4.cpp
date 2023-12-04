#include "../util/util.h"
#include <numeric>


int getGameWinCount(const std::string& line)
{
    const std::vector<std::string> game = aoc_util::splitString(line, "[:|]+");
    const std::vector<std::string> winningNumbers = aoc_util::splitString(game[1], "[\\s]+");
    const std::vector<std::string> myNumbers = aoc_util::splitString(game[2], "[\\s]+");

    int winningCount = 0;

    for (auto num : myNumbers)
    {
        if (std::find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end())
        {
            winningCount += 1;
        }
    }

    return winningCount;

}

// Part 1 function
void part1(const std::vector<std::string>& lines) {

    int winningsTotal = 0;

    for (const std::string& line : lines)
    {
        const int winningCount = getGameWinCount(line);
        if (winningCount>0) winningsTotal += (std::pow(2, winningCount - 1));
        

    }
    std::cout << winningsTotal << std::endl;
}

// Part 2 function
void part2(const std::vector<std::string>& lines) {

    std::vector<int> cardCounts(lines.size(), 1);

    for (int i = 0; i<lines.size(); i++)
    {
        const int winningCount = getGameWinCount(lines[i]);
        const int currentIdxCardCount = cardCounts[i];

        for (int winningCard = i + 1; winningCard <= i + winningCount; winningCard++)
        {
            cardCounts[winningCard] += currentIdxCardCount;
        }
    }

    std::cout << std::reduce(cardCounts.begin(), cardCounts.end()) << std::endl;
}

int main() {
    std::vector<std::string> lines = aoc_util::readFile("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day4\\input.txt");
    part1(lines); //19855
    part2(lines); //10378710
    return 0;
}
