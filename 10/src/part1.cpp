#include "part1.h"

#include <algorithm>
#include <cmath>
#include <fmt/core.h>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <boost/functional/hash.hpp>

#include "utils.h"

using pair_unordered_set = std::unordered_set<std::pair<size_t, size_t>,
      boost::hash<std::pair<size_t, size_t>>>;

enum class direction : int
{
    to_top, to_bottom, to_left, to_right
};

const static std::unordered_map<char, std::unordered_set<direction>> pipe_dirs{
    {'S', {direction::to_top, direction::to_bottom,
              direction::to_left, direction::to_right}},
        {'|', {direction::to_top, direction::to_bottom}},
        {'-', {direction::to_left, direction::to_right}},
        {'L', {direction::to_top, direction::to_right}},
        {'J', {direction::to_top, direction::to_left}},
        {'7', {direction::to_bottom, direction::to_left}},
        {'F', {direction::to_bottom, direction::to_right}},
};

const static std::unordered_map<direction, std::unordered_set<char>> next_pipes{
    {direction::to_top, {'|', '7', 'F'}},
    {direction::to_bottom, {'|', 'J', 'L'}},
    {direction::to_left, {'-', 'F', 'L'}},
    {direction::to_right, {'-', '7', 'J'}},
};

static void measure(const std::vector<std::string>& lines)
{
    auto pos = [&]() {
        for (auto i = 0uz; i < lines.size(); ++i) {
            for (auto j = 0uz; j < lines[i].size(); ++j) {
                if (lines[i][j] == 'S')
                    return std::make_pair(i, j);
            }
        }
        return std::make_pair(-1uz, -1uz);
    }();
    auto matrix = [&]() {
        auto matrix = std::vector<std::vector<size_t>>(lines.size());
        for(auto& dist : matrix)
            dist = std::vector<size_t>(lines.front().size());
        return matrix;
    }();

    auto visited = pair_unordered_set();
    auto bfs_que = std::queue<std::pair<size_t, size_t>>();
    bfs_que.push(pos);
    visited.insert(pos);
    while (!bfs_que.empty()) {
        auto [cur_x, cur_y] = bfs_que.front();
        bfs_que.pop();
        auto cur_pipe = lines[cur_x][cur_y];
        const auto& valid_to = pipe_dirs.at(cur_pipe);
        //              (x - 1, y)
        //  (x, y - 1)              (x, y + 1)
        //              (x + 1, y)
        for (auto i = -1; i < 2; ++i) {
            for (auto j = -1; j < 2; ++j) {
                // get only top -> left -> right -> bottom neighbors in this order
                if (i == j || std::abs(i - j) > 1)
                    continue;

                auto next_pos = std::make_pair(cur_x + i, cur_y + j);
                auto [next_x, next_y] = next_pos;
                if (next_x >= lines.size() || next_y >= lines[next_x].size()
                        || lines[next_x][next_y] == '.')
                    continue;

                auto to_dir = [i, j]() {
                    if (!i)
                        return (j == -1) ? direction::to_left : direction::to_right;
                    if (!j)
                        return (i == -1) ? direction::to_top : direction::to_bottom;
                    throw std::invalid_argument("invalid delta values.");
                }();

                if (!valid_to.count(to_dir)
                        || !next_pipes.at(to_dir).count(lines[next_x][next_y])
                        || !visited.insert(next_pos).second)
                    continue;

                matrix[next_x][next_y] = matrix[cur_x][cur_y] + 1;
                bfs_que.push(next_pos);
            }
        }
    }

    auto max = [&matrix]() {
        auto max = 0uz;
        for(const auto& row : matrix) {
            for(auto n : row) {
                max = std::max(max, n);
            }
        }
        return max;
    }();

    fmt::println("max: {}", max);
}

void solve_part1(std::ifstream& input)
{
    auto lines = getlines(input);
    measure(lines);
}
