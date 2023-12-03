#include "../util/util.h"

// A lot of this is ridiculous as i treated it as one large string, so accessing elements requires some maths

// Part 1 function
void part1(const std::string& line) {

    int enginePartsSum = 0;
    int lineWidth = 140;
    int lineCount = 140;

    for (int charNum = 0; charNum < line.size(); charNum++)
    {
        const char character = line[charNum];
        int lineNum = charNum / lineWidth;
        int lineCharIdx = charNum % lineWidth;

        auto checkCharIsSymbol = [&](const int& pos) {
            return (line[pos] != '.' && !std::isdigit(line[pos]));
        };


        if (std::isdigit(character))
        {
            int currentCharNum = charNum;
            int currentLineCharIdx = lineCharIdx;
            std::string number;
            bool symbolAdjacent = false;
            while (currentCharNum < line.size() && std::isdigit(line[currentCharNum]))
            {
                if (!symbolAdjacent)
                {

                    symbolAdjacent |= (lineNum != 0 && checkCharIsSymbol(currentCharNum - lineWidth)); // above
                    symbolAdjacent |= (lineNum != lineCount - 1 && checkCharIsSymbol(currentCharNum + lineWidth)); // below
                    symbolAdjacent |= (currentLineCharIdx != 0 && checkCharIsSymbol(currentCharNum - 1)); // left
                    symbolAdjacent |=  (currentLineCharIdx != lineWidth - 1 && checkCharIsSymbol(currentCharNum + 1)); // right

                    symbolAdjacent |= (lineNum != 0 && currentLineCharIdx != 0 && checkCharIsSymbol(currentCharNum - lineWidth - 1)); // above left
                    symbolAdjacent |= (lineNum != lineCount - 1 && currentLineCharIdx != 0 && checkCharIsSymbol(currentCharNum + lineWidth - 1)); // below left
                    symbolAdjacent |= (lineNum != 0 && currentLineCharIdx != lineWidth && checkCharIsSymbol(currentCharNum - lineWidth + 1)); // above right
                    symbolAdjacent |= (lineNum != lineCount - 1 && currentLineCharIdx != lineWidth && checkCharIsSymbol(currentCharNum + lineWidth + 1)); // below right


                }
                number += line[currentCharNum];
                currentCharNum++;
                currentLineCharIdx++;
            }

            charNum = currentCharNum-1;
            if (symbolAdjacent) enginePartsSum += std::stoi(number);
        }
    }

    std::cout << enginePartsSum << std::endl;

}

// Part 2 function
void part2(const std::string& input) {

    int gearRatioSum = 0;
    int lineWidth = 140;
    int lineCount = 140;

    // Given an index to a digit, expands it and returns the whole number. e.g. given . . 3 4 5 . 2 3 ., and idx 2,3 or 4, returns 345, idx 6 or 7 returns 23
    // ALso returns every index checked so we can avoid rechecking them. Useful to maintain a list of checked indexs to avoid expanding the same number multiple times
    const auto expandNumber = [&](const int& numIdx, const int& lineCharIdx) -> std::pair<int, std::vector<int>>
    {
        std::string number{ input[numIdx] };
        std::vector<int> idxs{ numIdx };

        if (lineCharIdx - 1 >= 0 && std::isdigit(input[numIdx - 1])) {
            number.insert(number.begin(), input[numIdx - 1]);
            idxs.emplace_back(numIdx - 1);
            if (lineCharIdx - 2 >= 0 && std::isdigit(input[numIdx - 2])) {
                number.insert(number.begin(), input[numIdx - 2]);
                idxs.emplace_back(numIdx - 2);
            }
        }

        if (lineCharIdx + 1 < lineWidth && std::isdigit(input[numIdx + 1])) {
            number.insert(number.end(), input[numIdx + 1]);
            idxs.emplace_back(numIdx + 1);

            if (lineCharIdx + 2 < lineWidth && std::isdigit(input[numIdx + 2])) {
                number.insert(number.end(), input[numIdx + 2]);
                idxs.emplace_back(numIdx + 2);

            }
        }
        return { std::stoi(number), idxs };
    };



    for (int charNum = 0; charNum < input.size(); charNum++)
    {
        const char character = input[charNum];
        int lineNum = charNum / lineWidth;
        int lineCharIdx = charNum % lineWidth;

        if (character == '*')
        {
            std::vector<int> idxsToCheck;

            // Find which of the surrounding 8 chars exist (should really just append a border of * but cba now ive done this)
            const bool notAtTop = lineNum > 0;
            const bool notAtBottom= lineNum < lineCount - 1;
            const bool notAtLeft= lineCharIdx > 0;
            const bool notAtRight= lineCharIdx < lineWidth - 1;

            if (notAtTop)
            {
                idxsToCheck.emplace_back(charNum - lineWidth); // up
                if (notAtLeft) idxsToCheck.emplace_back(charNum - lineWidth - 1); // up left
                if (notAtRight) idxsToCheck.emplace_back(charNum - lineWidth + 1); // up right
            }

            if (notAtBottom)
            {
                idxsToCheck.emplace_back(charNum + lineWidth); // down
                if (notAtLeft) idxsToCheck.emplace_back(charNum + lineWidth - 1); // down left
                if (notAtRight) idxsToCheck.emplace_back(charNum + lineWidth + 1); // down right
            }

            if (notAtLeft) //left
            {
                idxsToCheck.emplace_back(charNum - 1);
            }

            if (notAtRight) //right
            {
                idxsToCheck.emplace_back(charNum + 1);
            }
            
            std::vector<int> gearRatios;
            std::vector<int> checkedIdxs;

            // For every index to check, if its not been checked before expand the number there if one exists
            for (auto idx : idxsToCheck)
            {
                if (std::find(checkedIdxs.begin(), checkedIdxs.end(), idx) != checkedIdxs.end()) 
                {
                    continue;
                }


                if (std::isdigit(input[idx])) 
                {
                    auto [num, itterationCheckedIdxs] = expandNumber(idx, idx % lineWidth);
                    gearRatios.push_back(num);
                    checkedIdxs.insert(checkedIdxs.end(), itterationCheckedIdxs.begin(), itterationCheckedIdxs.end());
                } 
                
            }

            if (gearRatios.size() == 2)
            {
                gearRatioSum += (gearRatios[0] * gearRatios[1]);
            }
            
            
        }
    }

    std::cout << gearRatioSum << std::endl;

}

int main() {
    std::string line = aoc_util::readFileToSingleLine("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day3\\input.txt");
    part1(line);
    part2(line);
    return 0;
}
