#include "part2.h"
#include <array>
#include <cctype>

static const std::unordered_map<std::string, int> map{
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

static const std::array<std::string, 10> numbers{
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
};

void part2_list(std::istream& input)
{
    auto sum = 0;
    auto line = std::string();
    while (std::getline(input, line)) {
        auto nums = std::vector<int>();

        for (size_t i = 0; i < line.size(); ++i) {
            auto c = line[i];
            if (std::isdigit(c)) {
                nums.push_back(c - '0');
            } else {
                for (const auto& num : numbers) {
                    if (line.find(num, i) == i) {
                        nums.push_back(map.at(num));
                        break;
                    }
                }
            }
        }

        auto num = nums.front() * 10 + nums.back();
        sum += num;
    }

    fmt::println("{}", sum);
}
