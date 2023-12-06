#include "part2.h"

#include <array>
#include <fmt/core.h>
#include <unordered_set>
#include <vector>

#include "utils.h"

void solve_part2(std::ifstream& input)
{
    auto scheme = std::vector<std::string>();

    for (auto line = std::string(); std::getline(input, line);)
        scheme.emplace_back(std::move(line));

    // using int_pair = std::pair<int, int>;
    // auto visited = std::unordered_set<int_pair, boost::hash<int_pair>>();
    auto visited = std::unordered_set<std::pair<size_t, size_t>>();

    long long sum = 0;
    for (size_t i = 0; i < scheme.size(); ++i) {
        for (size_t j = 0; j < scheme[i].size(); ++j) {
            if (scheme[i][j] != '*')
                continue;

            auto nums = std::array<int, 2>();
            auto cnt = 0;
            for (int k = -1; k < 2; ++k) {
                auto cur_i = i + k;
                for (int l = -1; l < 2; ++l) {
                    auto cur_j = j + l;
                    if (cur_i < scheme.size() && cur_j < scheme[cur_i].size() &&
                            std::isdigit(scheme[cur_i][cur_j]) && !visited.count(std::make_pair(cur_i, cur_j))) {
                        auto num = get_num(scheme, cur_i, cur_j, visited);
                        nums[cnt++] = num;
                    }
                }
            }

            if (nums.size() == 2)
                sum += nums.front() * nums.back();
        }
    }

    fmt::println("{}", sum);
}
