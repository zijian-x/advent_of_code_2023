#include "utils.h"

#include <cctype>
#include <fmt/core.h>
#include <fstream>

#include <boost/functional/hash.hpp>

int get_num(const std::vector<std::string>& vec, size_t i, size_t j,
        std::unordered_set<std::pair<size_t, size_t>>& visited)
{
    while (j - 1 < vec[i].size() && std::isdigit(vec[i][j - 1]))
        --j;

    int num = 0;
    while (j < vec[i].size() && std::isdigit(vec[i][j])) {
        num = num * 10 + (vec[i][j] - '0');
        visited.insert(std::make_pair(i, j));
        ++j;
    }
    return num;
}

void test(std::ifstream& input)
{
    auto line = std::string();
    auto vec = std::vector<std::string>();
    while (std::getline(input, line))
        vec.push_back(std::move(line));

    auto visited = std::unordered_set<std::pair<size_t, size_t>>();
    auto num_rows = std::vector<std::vector<int>>();
    for (size_t i = 0; i < vec.size(); ++i) {
        auto nums = std::vector<int>();
        for (size_t j = 0; j < vec[i].size(); ++j) {
            if (std::isdigit(vec[i][j]) && !visited.count(std::make_pair(i, j)))
                nums.push_back(get_num(vec, i, j, visited));
        }
        if (!nums.empty())
            num_rows.push_back(std::move(nums));
    }

    for (const auto& row : num_rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            fmt::print("{}{}", row[i], (i + 1 == row.size() ? "" : ", "));
        }
        fmt::print("\n");
    }
}

