#include "../util/util.h"
#include <unordered_map>


using RangeMapping = std::vector<std::vector<std::pair<std::pair<long long, long long>, long long>>>;
using SeedVector = std::vector<long long>;

std::pair<RangeMapping, SeedVector> buildMappingsAndSeeds(const std::vector<std::string>& lines)
{
    RangeMapping mapping;
    SeedVector seeds;

    // build mapping
    for (const std::string& line : lines)
    {
        std::vector<std::string> parts = aoc_util::splitString(line, "[\\n:]+");

        if (parts[0] == "seeds")
        {
            std::vector<std::string> seedsSplit = aoc_util::splitString(parts[1], "[\\s]+");
            for (auto seed : seedsSplit)
            {

                seeds.emplace_back(std::stoll(seed));
            }
            continue;
        }

        std::vector<std::pair<std::pair<long long, long long>, long long>> currentMapping;

        for (int partNum = 1; partNum < parts.size(); partNum++)
        {
            std::vector<std::string> rangesSplit = aoc_util::splitString(parts[partNum], "[\\s]+");
            long long destinationRange = std::stoll(rangesSplit[0]), sourceRange = std::stoll(rangesSplit[1]), rangeLength = std::stoll(rangesSplit[2]);
            currentMapping.push_back({ {sourceRange,sourceRange + rangeLength}, destinationRange - sourceRange });

        }

        mapping.push_back(currentMapping);
    }

    return std::pair<RangeMapping, SeedVector>({ mapping, seeds });
}

// Part 1 function
void part1(const std::vector<std::string>& lines) {
    auto [mapping, seeds] = buildMappingsAndSeeds(lines);

    long long closestLocation = INT_MAX;
    const int num_maps = mapping.size();

    long long currentPos;
    bool foundRange;
    int rangeIdx;

    for (const auto& seed : seeds)
    {

        currentPos = seed;

        for (const auto& map : mapping) 
        {

            foundRange = false;
            rangeIdx = 0;
            while (rangeIdx < map.size() && !foundRange)
            {
                const std::pair<long long, long long>& sourceRange = map[rangeIdx].first;
                const long long& change = map[rangeIdx].second;

                if (currentPos >= sourceRange.first && currentPos <= sourceRange.second)
                {
                    foundRange = true;
                    currentPos += change;
                    break;

                }
                rangeIdx++;
            }
        }
        if (currentPos < closestLocation) closestLocation = currentPos;

    }

    std::cout << closestLocation << std::endl;
}

// Part 2 function
void part2(const std::vector<std::string>& lines) {

    auto [mapping, seeds] = buildMappingsAndSeeds(lines);

    long long closestLocation = INT_MAX;
    const int num_maps = mapping.size();

    long long currentSeed;
    bool foundRange;
    int rangeIdx;
    long long startSeed;
    long long seedRange;

    for (int seedIdx = 0; seedIdx <seeds.size(); seedIdx +=2) // Get the startSeed and ranges
    {
        startSeed = seeds[seedIdx];
        seedRange = seeds[seedIdx + 1];

        for (; startSeed < seeds[seedIdx] + seedRange; startSeed++) {
            currentSeed = startSeed;
            //std::cout << "Checking currentSeed " << currentSeed << std::endl;
            for (const auto& map : mapping)
            {

                foundRange = false;
                rangeIdx = 0;
                while (rangeIdx < map.size() && !foundRange)
                {
                    const std::pair<long long, long long>& sourceRange = map[rangeIdx].first;
                    const long long& change = map[rangeIdx].second;

                    if (currentSeed >= sourceRange.first && currentSeed <= sourceRange.second)
                    {
                        foundRange = true;
                        currentSeed += change;
                        break;

                    }
                    rangeIdx++;
                }
            }
            if (currentSeed < closestLocation) closestLocation = currentSeed;

        }

    }

    std::cout << closestLocation << std::endl;
}

int main() {
    std::vector<std::string> lines = aoc_util::readFileSplitOnBlankLines("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day5\\input.txt");

    auto start = std::chrono::high_resolution_clock::now();
    part1(lines); // 340994526
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Part1 Time taken: " << duration << " nanoseconds" << std::endl;


    auto start2 = std::chrono::high_resolution_clock::now();
    part2(lines); // 52210644
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - start2).count();
    std::cout << "Part2 Time taken: " << duration2 << " seconds" << std::endl;


    return 0;
}
