#include "../util/util.h"

#include <unordered_map>
#include <set>
#include <array>

enum HandType {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
    InvalidHandType
};

std::unordered_map<HandType, std::unordered_map<int, HandType>> bestReachableHand =
{
    {
        HandType::HighCard, {{1,HandType::OnePair}}

    },
    {
        HandType::OnePair, {{1,HandType::ThreeOfAKind}, {2, HandType::ThreeOfAKind}}

    },
    {
        HandType::TwoPair, {{1,HandType::FullHouse},  {2,HandType::FourOfAKind}}

    },
    {
        HandType::ThreeOfAKind, {{1,HandType::FourOfAKind}, {3, HandType::FourOfAKind}}

    },
    {
        HandType::FullHouse, {{2,HandType::FiveOfAKind}, {3,HandType::FiveOfAKind}}

    },
    {
        HandType::FourOfAKind, {{1,HandType::FiveOfAKind}, {4,HandType::FiveOfAKind}}

    },
    {
        HandType::FiveOfAKind, {{5,HandType::FiveOfAKind}}

    }
};

int cardToInt(const char& card, const int& jValue)
{
    switch (card)
    {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return jValue;
        case 'T':
            return 10;
        default:
            return card - '0';
    }
}

int compareHandRanks(const std::string& hand1, const std::string& hand2, const int& jValue) {
    for (int i = 0; i < 5; i++) {
        int rank1 = cardToInt(hand1[i], jValue);
        int rank2 = cardToInt(hand2[i], jValue);
        if (rank1 != rank2) {
            return rank1 - rank2;
        }
    }
    return 0;
}

std::pair<int, int> calcGroupings(const std::string& cards, const int& jValue)
{
    char groupings[15] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };

    for (char card : cards) {
        groupings[cardToInt(card, jValue)]++;
    }

    std::string nonZeroCounts;
    for (char count : groupings) {
        if (count != '0') {
            nonZeroCounts += count;
        }
    }

    return { std::stoi(nonZeroCounts), groupings[jValue]- '0'};
}

const HandType groupingsToHandType(const int& groupings)
{
    switch (groupings) {
    case 11111: return HandType::HighCard;
    case 1112: 
    case 1121: 
    case 1211: 
    case 2111: return HandType::OnePair;
    case 221: 
    case 212:
    case 122: return HandType::TwoPair;
    case 311:
    case 131:
    case 113: return HandType::ThreeOfAKind;
    case 41:
    case 14: return HandType::FourOfAKind;
    case 23:
    case 32: return HandType::FullHouse;
    case 5: return HandType::FiveOfAKind;
    default: return HandType::InvalidHandType;
    }

}


// Part 1 function
void part1(std::vector<std::string>& lines) {
    constexpr int jValue = 11;

    std::unordered_map <HandType, std::vector<int>> sortedHandsMap = { {HandType::FiveOfAKind, { }}, {HandType::FourOfAKind, { }}, {HandType::FullHouse, { }}, {HandType::ThreeOfAKind, { }}, {HandType::TwoPair, { }}, {HandType::OnePair, { }}, {HandType::HighCard, { }} };


    std::sort(lines.begin(), lines.end(),
        [](const std::string& a, const std::string& b) {
            return compareHandRanks(a,b,jValue) < 0;  // Sort based on length
        });


    for (int i = 0; i < lines.size(); i++)
    {
        const std::vector<std::string> cardsAndBid = aoc_util::string::splitString<std::string>(lines[i], "\\s");

        const int handGroupingSizes = calcGroupings(cardsAndBid[0], jValue).first;
    
        HandType handType = groupingsToHandType(handGroupingSizes);

        std::vector<int>* handTypeVector = &sortedHandsMap[handType];

        handTypeVector->emplace_back(std::stoi(cardsAndBid[1]));

    }

    int64_t sum = 0;
    int rank = 1;

    for (int i = HighCard; i <= FiveOfAKind; ++i) {
        HandType handType = static_cast<HandType>(i);
        for (const auto& bid : sortedHandsMap[handType])
        {
            sum += bid * rank;
            rank += 1;
        }
    }
    std::cout << sum << std::endl;

}

// Part 2 function
void part2(std::vector<std::string>& lines) {

    std::unordered_map <HandType, std::vector<int>> sortedHandsMap = { {HandType::FiveOfAKind, { }}, {HandType::FourOfAKind, { }}, {HandType::FullHouse, { }}, {HandType::ThreeOfAKind, { }}, {HandType::TwoPair, { }}, {HandType::OnePair, { }}, {HandType::HighCard, { }} };

    constexpr int jValue = 0;
    std::sort(lines.begin(), lines.end(),
        [](const std::string& a, const std::string& b) {
            return compareHandRanks(a, b, jValue) < 0;  // Sort based on length
        });

    for (int i = 0; i < lines.size(); i++)
    {
        const std::vector<std::string> cardsAndBid = aoc_util::string::splitString<std::string>(lines[i], "\\s");

        auto [handGroupings, jokerCount] = calcGroupings(cardsAndBid[0], jValue);
        HandType handType = groupingsToHandType(handGroupings);
        if (jokerCount > 0) handType = bestReachableHand[handType][jokerCount];

        std::vector<int>* handTypeVector = &sortedHandsMap[handType];

        handTypeVector->emplace_back(std::stoi(cardsAndBid[1]));


    }

    int64_t sum = 0;
    int rank = 1;

    for (int i = HighCard; i <= FiveOfAKind; ++i) {
        HandType handType = static_cast<HandType>(i);
        for (const auto& bid : sortedHandsMap[handType])
        {
            sum += bid * rank;
            rank += 1;
        }
    }
    std::cout << sum << std::endl;

}


int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day7\\input.txt");

    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines); //255048101
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines); //253718286

    return 0;

}
