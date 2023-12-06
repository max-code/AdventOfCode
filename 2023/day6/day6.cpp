#include "../util/util.h"


// Part 1 function
void part1(std::vector<std::string>& lines) {


    aoc_util::string::removeFromString(lines[0], "Time:");
    const std::vector<int> times = aoc_util::string::splitString<int>(lines[0], "\\s");

    aoc_util::string::removeFromString(lines[1], "Distance:");
    const std::vector<int> distances = aoc_util::string::splitString<int>(lines[1], "\\s");

    int permutations = 1;

    for (int race = 0; race < times.size(); race++)
    {
        int time = times[race];
        int recordDistance = distances[race];
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
void part2(std::vector<std::string>& lines) {
    const std::vector<std::string> timeParts = aoc_util::string::splitString<std::string>(lines[0], "\\s");
    const std::vector<std::string> distanceParts = aoc_util::string::splitString<std::string>(lines[1], "\\s");

    /*
    t = total time
    x = time held for
    y = t - x = time remaining
    r = record distance

    Solve for when r+1:
    r+1 = x(t-x)

    r+1 = tx - x^2

    x^2 - tx + (r + 1) = 0

    a = 1, b = -t, c = r+1
    */

    std::string timeStr, recordDistanceStr;
    // Reserve enough space in advance to avoid reallocations
    timeStr.reserve(timeParts[0].size() + timeParts[1].size() + timeParts[2].size() + timeParts[3].size());
    recordDistanceStr.reserve(distanceParts[0].size() + distanceParts[1].size() + distanceParts[2].size() + distanceParts[3].size());

    // Append parts directly
    timeStr.append(timeParts[0]).append(timeParts[1]).append(timeParts[2]).append(timeParts[3]);
    recordDistanceStr.append(distanceParts[0]).append(distanceParts[1]).append(distanceParts[2]).append(distanceParts[3]);

    // Convert to long long
    const long long time = std::stoll(timeStr);
    const long long recordDistance = std::stoll(recordDistanceStr);

    const double discriminant = sqrt((time * time) - (4 * (recordDistance)));
    const long long x1 = (time + discriminant) / 2;
    const long long x2 = (time - discriminant) / 2;


    std::cout << x1 - x2  << std::endl;
}


int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day6\\input.txt");

    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines); // 1731600
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines); // 40087680

    return 0;
}
