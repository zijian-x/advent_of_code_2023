#include "part2.h"

#include <fmt/core.h>
#include <limits>

#include "utils.h"

// what if there is no color x in all sets of a game?
int get_min_cnt(const std::string& color, const std::string& line)
{
    auto max = 0;
    auto idx = line.find(color, 0);
    while (idx != std::string::npos) {
        auto num = get_num(line, idx - 2);
        max = std::max(max, num);

        idx = line.find(color, idx + 1);
    }

    return max;
}

void solve_part2(std::ifstream& input)
{
    auto sum = 0;
    auto line = std::string();
    while (std::getline(input, line)) {
        auto min_red = get_min_cnt("red", line);
        auto min_green = get_min_cnt("green", line);
        auto min_blue = get_min_cnt("blue", line);

        sum += min_red * min_green * min_blue;
    }

    fmt::println("{}", sum);
}
