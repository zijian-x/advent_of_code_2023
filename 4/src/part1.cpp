#include "part1.h"

#include <algorithm>
#include <fmt/core.h>
#include <iterator>
#include <sstream>
#include <unordered_set>
#include <vector>

void solve_part1(std::ifstream& input)
{
    auto line = std::string();

    auto sum = 0;
    while (std::getline(input, line)) {
        auto iss = std::istringstream(line);
        auto words = std::vector<std::string>(std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{});
        auto lucky_nums = std::unordered_set<int>();
        auto score = 0;

        auto check_num = false;
        for (size_t i = 2; i < words.size(); ++i) {
            if (words[i] == "|") {
                check_num = true;
                continue;
            }

            auto num = std::stoi(words[i]);
            if (!check_num)
                lucky_nums.insert(num);
            else if (lucky_nums.count(num))
                score = (!score) ? 1 : score << 1;
        }

        sum += score;
    }
    fmt::println("{}", sum);
}
