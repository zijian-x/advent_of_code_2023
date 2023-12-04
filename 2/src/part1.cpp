#include "part1.h"

#include <cctype>
#include <fmt/core.h>
#include <string>

#include "utils.h"

int get_max_cube_cnt(const std::string& color, const std::string& line)
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

void solve_part1(std::ifstream& input)
{
    auto line = std::string();

    auto red_cnt = 12;
    auto green_cnt = 13;
    auto blue_cnt = 14;

    auto sum = 0;
    while (std::getline(input, line)) {
        auto max_red = get_max_cube_cnt("red", line);
        auto max_green = get_max_cube_cnt("green", line);
        auto max_blue = get_max_cube_cnt("blue", line);

        if (max_red <= red_cnt && max_green <= green_cnt && max_blue <= blue_cnt)
            sum += get_num(line, line.find(":") - 1);
    }

    fmt::print("{}", sum);
}
