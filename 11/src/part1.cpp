#include "part1.h"

#include <algorithm>
#include <cstddef>
#include <fmt/core.h>
#include <numeric>
#include <unordered_set>
#include <queue>
#include <utility>
#include <boost/functional/hash.hpp>

#include "utils.h"

static std::vector<std::vector<size_t>> convert_to_map(const std::vector<std::string>& lines)
{
    auto map = std::vector<std::vector<size_t>>(lines.size(),
            std::vector<size_t>(lines.front().size()));

    for (size_t i = 0; i < lines.size(); ++i) 
        for (size_t j = 0; j < lines[i].size(); ++j)
            map[i][j] = (lines[i][j] == '.') ? 1 : 0;

    /*
    for (size_t i = 0; i < map.size(); ++i) {
        auto row_cnt = 0uz;
        for (size_t j = 0; j < map[i].size(); ++j)
            row_cnt += map[i][j];
        if (row_cnt == map[i].size())
            map.insert(begin(map) + static_cast<ptrdiff_t>(++i),
                    std::vector<size_t>(map.front().size(), 1));
    }
    for (size_t i = 0; i < map.front().size(); ++i) {
        auto col_cnt = 0uz;
        for (size_t j = 0; j < map.size(); ++j)
            col_cnt += map[j][i];
        if (col_cnt == map.size()) {
            for (size_t j = 0; j < map.size(); ++j)
                map[j].insert(begin(map[j]) + static_cast<ptrdiff_t>(i + 1), 1);
            ++i;
        }
    }
    */

    for (size_t i = 0; i < map.size(); ++i) {
        auto row_cnt = 0uz;
        for (size_t j = 0; j < map[i].size(); ++j) {
            if (map[i][j])
                ++row_cnt;
            if (i + 1 == map.size()) {
                auto col_cnt = 0uz;
                for (size_t k = 0; k < map.size(); ++k) {
                    if (map[k][j])
                        ++col_cnt;
                }
                if (col_cnt == map.size()) {
                    for (size_t k = 0; k < map.size(); ++k)
                        map[k][j] *= 1000000;
                }
            }
        }

        if (row_cnt == map[i].size())
            for (size_t j = 0; j < map[i].size(); ++j)
                map[i][j] *= 1000000;
    }

    return map;
}

static void visualize(const std::vector<std::vector<size_t>>& distances,
        size_t nx, size_t ny)
{
    fmt::println("====================================================");
    for (size_t i = 0; i < distances.size(); ++i) {
        iterate_container(distances[i]);
    }
}

static std::vector<std::vector<size_t>> get_distance_map(
        const std::vector<std::vector<size_t>>& map,
        const std::pair<size_t, size_t>& galaxy)
{
    auto visited = std::unordered_set<std::pair<size_t, size_t>,
         boost::hash<std::pair<size_t, size_t>>>();
    auto bfs_que = std::queue<std::pair<size_t, size_t>>();
    bfs_que.push(galaxy);
    visited.insert(galaxy);
    auto distances = std::vector<std::vector<size_t>>(map.size(),
            std::vector<size_t>(map.front().size()));

    while (!bfs_que.empty()) {
        auto [x, y] = bfs_que.front();
        bfs_que.pop();

        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                auto neighbor = std::make_pair(x + i, y + j);
                auto [nx, ny] = neighbor;

                if (std::abs(i - j) != 1 ||
                        nx >= map.size() || ny >= map[nx].size())
                    continue;

                if (visited.insert(neighbor).second) {
                    distances[nx][ny] = distances[x][y] + map[nx][ny];
                    bfs_que.push(neighbor);
                }
            }
        }
    }

    return distances;
}

void solve_part1(std::ifstream& input)
{
    const auto lines = getlines(input);
    auto map = convert_to_map(lines);
    const auto galaxies = [&map]() {
        auto galaxies = std::vector<std::pair<size_t, size_t>>();
        for (size_t i = 0; i < map.size(); ++i) {
            for (size_t j = 0; j < map[i].size(); ++j) {
                if (map[i][j] == 0) {
                    map[i][j] = 1;
                    galaxies.push_back(std::make_pair(i, j));
                }
            }
        }

        return galaxies;
    }();

    fmt::println("lines:");
    for (size_t i = 0; i < lines.size(); ++i)
        iterate_container(lines[i]);
    fmt::println("map");
    for (size_t i = 0; i < map.size(); ++i)
        iterate_container(map[i]);
    fmt::println("galaxy locations:");
    iterate_container(galaxies);

    auto sum = 0uz;
    for (size_t i = 0; i < galaxies.size(); ++i) {
        auto dist_map = get_distance_map(map, galaxies[i]);
        for (size_t j = i + 1; j < galaxies.size(); ++j) {
            auto [x, y] = galaxies[j];
            auto dist = dist_map[x][y];
            sum += dist;
        }
    }
    fmt::println("sum of distances: {}", sum);
}
