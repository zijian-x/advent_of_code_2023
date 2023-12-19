#include "part2.h"

#include <cstdio>
#include <fmt/core.h>
#include <iterator>
#include <queue>
#include <regex>
#include <sstream>
#include <vector>
#include <unordered_map>

struct range
{
    size_t head;
    size_t tail;
};

auto get_ranges(const std::string& line)
{
    auto iss = std::istringstream(line);
    auto tmp = std::string();
    iss >> tmp;

    auto vals = std::vector<size_t>(
            std::istream_iterator<size_t>(iss),
            std::istream_iterator<size_t>());
    auto ranges = std::vector<range>();
    for (size_t i = 0; i < vals.size() - 1; i += 2) {
        auto begin = vals[i];
        auto end = begin + vals[i + 1];
        ranges.push_back({begin, end - 1});
    }

    if (ranges.empty()) {
        fmt::println(stderr, "values empty");
        std::exit(1);
    }

    return ranges;
}

static auto test_ranges(const std::vector<range>& ranges) -> void
{
    for (const auto& range : ranges) {
        fmt::println("begin: {}, end: {}", range.head, range.tail);
    }
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

static auto test_map(const std::unordered_map<size_t, std::pair<size_t, size_t>>& map) -> void
{
    for (const auto& [key, val] : map)
        fmt::println("{} {} {}", key, val.first, val.second);
}

auto map_values(const std::vector<range>& ranges,
        const std::unordered_map<size_t, std::pair<size_t, size_t>>& map)
    -> std::vector<range>
{
    auto que = std::queue<range>();
    for (const auto& range : ranges)
        que.push(range);

    auto new_range = std::vector<range>();
    while (!que.empty()) {
        auto [begin, end] = que.front();
        que.pop();
        auto process = false;

        for (const auto& [dest, pair] : map) {
            auto [src, len] = pair;
            if (begin >= src + len || end < src) {
                continue;
            } else if (begin < src) {
                que.push({begin, src - 1});
                if (end < src + len) {
                    new_range.push_back({dest, dest + end - src});
                } else  {
                    new_range.push_back({dest, dest + len - 1});
                    que.push({src + len, end});
                }
                process = true;
                break;
            } else if (begin == src) {
                if (end < src + len) {
                    new_range.push_back({dest, dest + end - src});
                } else {
                    new_range.push_back({dest, dest + len - 1});
                    que.push({src + len, end});
                }
                process = true;
                break;
            } else {
                if (end < src + len) {
                    new_range.push_back({dest + begin - src, dest + end - src});
                } else {
                    new_range.push_back({dest + begin - src, dest + len - 1});
                    que.push({src + len, end});
                }
                process = true;
                break;
            }
        }
        if (!process)
            new_range.push_back({begin, end});
    }

    return new_range;
}

auto solve_part2(std::ifstream& input) -> void
{
    auto line = std::string();
    auto ranges = std::vector<range>();
    auto map = std::unordered_map<size_t, std::pair<size_t, size_t>>();
    auto map_match = std::regex("[0-9]+ [0-9]+ [0-9]+");

    std::getline(input, line);
    ranges = get_ranges(line);

    while (std::getline(input, line)) {
        if (std::regex_match(line, map_match)) {
            fill_map(line, map);
        } else if (!map.empty()) {
            ranges = map_values(ranges, map);
            map.clear();
        }
    }
    ranges = map_values(ranges, map);
    map.clear();

    std::sort(begin(ranges), end(ranges), [](const range& r1, const range& r2) {
            return r1.head < r2.head;
            });
    test_ranges(ranges);
}
