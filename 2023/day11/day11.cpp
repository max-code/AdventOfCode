#include "../util/util.h"


void solve(const std::vector<std::string>& lines, const int& expansionMultiplier)
{
    std::vector<aoc_util::datastructures::Point<int>> galaxyCoordinates;
    std::vector<int> emptyRows(lines.size(), 1);
    std::vector<int> emptyCols(lines[0].size(), 1);

    for (int y = 0; y < lines.size(); y++) // Find non empty rows with 1 pass 
    {
        for (int x = 0; x < lines[y].size(); x++)
        {
            if (lines[y][x] == '#') {
                emptyCols[x] = 0;
                emptyRows[y] = 0;
                continue;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < emptyRows.size(); i++) // Accumulate amount of empty rows seen
    {
        if (emptyRows[i] == 1) count++;
        emptyRows[i] = count;
    }

    count = 0;
    for (int i = 0; i < emptyCols.size(); i++) // Accumulate amount of empty columns seen
    {
        if (emptyCols[i] == 1) count++;
        emptyCols[i] = count;
    }

    for (int y = 0; y < lines.size(); y++) // Fill coordinates
    {
        for (int x = 0; x < lines[y].size(); x++)
        {
            if (lines[y][x] == '#') {
                galaxyCoordinates.emplace_back(x + (emptyCols[x] * (expansionMultiplier-1)), y + (emptyRows[y] * (expansionMultiplier - 1)));
            }
        }
    }

    uint64_t distanceSum = 0;
    for (int first = 0; first < galaxyCoordinates.size() - 1; first++)
    {
        for (int second = first + 1; second < galaxyCoordinates.size(); second++)
        {
            distanceSum += std::abs(galaxyCoordinates[first].x - galaxyCoordinates[second].x) + std::abs(galaxyCoordinates[first].y - galaxyCoordinates[second].y);
        }
    }

    std::cout << distanceSum << std::endl;
}

// Part 1 function
void part1(const std::vector<std::string>& lines) {

    solve(lines, 2);
    
}

// Part 2 function
void part2(const std::vector<std::string>& lines) 
{
    solve(lines, 1000000);
}
int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day11\\input.txt");

    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines); // 9274989
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines); // 357134560737
    return 0;
}
