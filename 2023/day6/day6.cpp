#include "../util/util.h"


// Part 1 function
void part1(const std::vector<std::string>& lines) {
    std::vector<std::string> times = aoc_util::splitString(lines[0], "[:\\s]+");
    std::vector<std::string> distances = aoc_util::splitString(lines[1], "[:\\s]+");

    int permutations = 1;

    for (int race = 1; race < times.size(); race++)
    {
        int time = std::stoi(times[race]);
        int recordDistance = std::stoi(distances[race]);
        int waysToBeatRecord = 0;
        for (int holdTime = 0; holdTime <= time; holdTime++)
        {
            if (holdTime * (time - holdTime) > recordDistance) waysToBeatRecord++;
        }

        if (waysToBeatRecord > 0) permutations *= waysToBeatRecord;

    }

    std::cout << permutations << std::endl;
}

// Part 2 function
void part2(const std::vector<std::string>& lines) {
    std::vector<std::string> timeParts = aoc_util::splitString(lines[0], "[:\\s]+");
    std::vector<std::string> distanceParts = aoc_util::splitString(lines[1], "[:\\s]+");


    long long time = std::stoll(timeParts[1] + timeParts[2] + timeParts[3] + timeParts [4]);
    long long recordDistance = std::stoll(distanceParts[1] + distanceParts[2] + distanceParts[3] + distanceParts[4]);

    long long waysToBeatRecord = 0;
    for (long long holdTime = 0; holdTime <= time; holdTime++)
    {
        if (holdTime * (time - holdTime) > recordDistance) waysToBeatRecord++;
    }

    std::cout << waysToBeatRecord << std::endl;


}

int main() {
    std::vector<std::string> lines = aoc_util::readFile("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day6\\input.txt");
    part1(lines); // 1731600
    part2(lines); // 40087680
    return 0;
}
