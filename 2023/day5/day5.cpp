#include "../util/util.h"
#include <unordered_map>
#include <limits>

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

    long long closestLocation = std::numeric_limits<long long>::max();

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

using SeedBounds = std::pair<long long, long long>;

// Part 2 function
void part2(const std::vector<std::string>& lines) {

    auto [mapping, seeds] = buildMappingsAndSeeds(lines);
    std::vector<SeedBounds> seedBounds;
    seedBounds.reserve(1000);

    for (int i = 0; i < seeds.size(); i += 2)
    {
        long long seed = seeds[i];
        long long seedRange = seeds[i+1];
        seedBounds.emplace_back(seed, seed+seedRange-1);
    }

    for (const auto& map : mapping) // This is layer by layer, e.g. seed-to-soil map, soil-to-fertilizer map etc
    {
        std::vector<SeedBounds> newSeedBounds;
        for (const auto& seedBound : seedBounds) { // <3, 10> etc
            const long long& seedLowerBound = seedBound.first; // 3
            const long long& seedUpperBound = seedBound.second; // 10
            bool foundSeedInSource = false;
            for (const auto& sourceBound : map) // (<8,12>, 4) etc
            {

                const auto& sourceLowerBound = sourceBound.first.first;
                const auto& sourceUpperBound = sourceBound.first.second;
                const auto& destOffset = sourceBound.second;
                
                if (seedLowerBound <= sourceLowerBound && seedUpperBound >= sourceUpperBound) // seedBound covers the entire range
                {
                    newSeedBounds.emplace_back(seedLowerBound, sourceLowerBound-1);
                    newSeedBounds.emplace_back(sourceLowerBound+destOffset, sourceUpperBound+destOffset);
                    newSeedBounds.emplace_back(sourceUpperBound+1, seedUpperBound);
                    foundSeedInSource = true;

                }
                else if (seedLowerBound >= sourceLowerBound && seedUpperBound <= sourceUpperBound) // seedBound entirely inside sourceBound
                {
                    newSeedBounds.emplace_back(seedLowerBound+destOffset, seedUpperBound+destOffset);
                    foundSeedInSource = true;
                }
                else if (seedLowerBound <= sourceUpperBound && seedLowerBound >= sourceLowerBound && seedUpperBound >= sourceUpperBound) // left half of seedBound inside sourceBound. If seedBound = <3,10> and sourceBound = (<1,5>,2) need to add <5,7> and <6,10> to newSeedBounds
                {
                    newSeedBounds.emplace_back(sourceUpperBound+1, seedUpperBound); // Part (right half) of the seedBound outside the sourceBound
                    newSeedBounds.emplace_back(seedLowerBound + destOffset, sourceUpperBound+destOffset);
                    foundSeedInSource = true;

                }
                else if (seedUpperBound >= sourceLowerBound && seedUpperBound <= sourceUpperBound && seedLowerBound <= sourceLowerBound) // right half of seedBound inside sourceBound. If seedBound = <3,10> and sourceBound = (<7,12>,2) need to add <3,6> and <9,12> to newSeedBounds
                {
                    newSeedBounds.emplace_back(seedLowerBound, sourceLowerBound-1); // Part (left half) of the seedBound outside the sourceBound
                    newSeedBounds.emplace_back(sourceLowerBound + destOffset, seedUpperBound+destOffset);
                    foundSeedInSource = true;

                }

                if (foundSeedInSource) break;

            }

            if(!foundSeedInSource) newSeedBounds.emplace_back(seedBound);
        }
        seedBounds = newSeedBounds;
    }

    long long closestLocation = std::numeric_limits<long long>::max();;
    for (const auto& sb : seedBounds)
    {
        if (sb.first < closestLocation) closestLocation = sb.first;
    }

    std::cout << closestLocation << std::endl;
}

int main() {
    std::vector<std::string> lines = aoc_util::readFileSplitOnBlankLines("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day5\\input.txt");
    part1(lines); // 340994526
    part2(lines); // 52210644


    return 0;
}
