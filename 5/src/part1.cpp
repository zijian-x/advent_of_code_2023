#include "part1.h"

#include <fmt/core.h>
#include <regex>
#include <vector>
#include <unordered_map>

static auto get_values(const std::string& line) -> std::vector<size_t>
{
    auto iss = std::istringstream(line);
    auto seeds = std::vector<size_t>();

    size_t i;
    while (!iss.eof()) {
        iss >> i;
        if (iss.fail()) {
            iss.clear();
            iss.ignore();
        } else {
            seeds.push_back(i);
        }
    }

    return seeds;
}

static auto test_values(const std::vector<size_t>& values) -> void
{
    fmt::print("seeds: ");
    for (auto val : values)
        fmt::print("{} ", val);
    fmt::println("");
}

static auto fill_map(const std::string& line,
        std::unordered_map<size_t, std::pair<size_t, size_t>>& map) -> void
{
    auto iss = std::istringstream(line);
    auto vals = std::vector<size_t>(
            std::istream_iterator<size_t>{iss},
            std::istream_iterator<size_t>{});

    auto dest = vals.front();
    auto src  = vals[1];
    auto len = vals.back();
    map[dest] = std::make_pair(src, len);
}

static auto map_values(std::vector<size_t>& values,
        const std::unordered_map<size_t, std::pair<size_t, size_t>>& map) -> void
{
    for (auto& val : values) {
        for (const auto& [dest, pair] : map) {
            auto [src, len] = pair;

            if (val >= src && val < src + len) {
                val = dest + (val - src);
                break;
            }
        }
    }
}

static auto test_map(const std::unordered_map<size_t, std::pair<size_t, size_t>>& map) -> void
{
    for (const auto& [key, val] : map)
        fmt::println("{} {} {}", key, val.first, val.second);
}

void solve_part1(std::ifstream& input)
{
    auto line = std::string();
    auto values = std::vector<size_t>();
    auto map = std::unordered_map<size_t, std::pair<size_t, size_t>>();
    auto map_match = std::regex("[0-9]+ [0-9]+ [0-9]+");

    std::getline(input, line);
    values = get_values(line);

    while (std::getline(input, line)) {
        if (std::regex_match(line, map_match)) {
            fill_map(line, map);
        } else if (!map.empty()) {
            map_values(values, map);
            map.clear();
        }
    }
    map_values(values, map);
    map.clear();

    std::sort(begin(values), end(values));
    fmt::println("{}", values.front());
}
