#include "part1.h"

#include <cctype>
#include <unordered_set>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/functional/hash.hpp>

#include "utils.h"

void solve_part1(std::ifstream& input)
{
    auto scheme = std::vector<std::string>();

    for (auto line = std::string(); std::getline(input, line);)
        scheme.emplace_back(std::move(line));

    auto is_symbol = [](char c) {
        return c != '.' && !std::isdigit(c);
    };

    // using int_pair = std::pair<int, int>;
    // auto visited = std::unordered_set<int_pair, boost::hash<int_pair>>();
    auto visited = std::unordered_set<std::pair<size_t, size_t>>();

    auto sum = 0;
    for (size_t i = 0; i < scheme.size(); ++i) {
        for (size_t j = 0; j < scheme[i].size(); ++j) {
            if (!is_symbol(scheme[i][j]))
                continue;

            for (int k = -1; k < 2; ++k) {
                auto cur_i = i + k;
                for (int l = -1; l < 2; ++l) {
                    auto cur_j = j + l;
                    if (cur_i < scheme.size() && cur_j < scheme[cur_i].size() &&
                            std::isdigit(scheme[cur_i][cur_j]) && !visited.count(std::make_pair(cur_i, cur_j))) {
                        auto num = get_num(scheme, cur_i, cur_j, visited);
                        // fmt::print("{}, ", num);
                        sum += num;
                    }
                }
            }
        }
    }

    fmt::println("{}", sum);
}
