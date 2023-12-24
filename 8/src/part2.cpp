#include "part2.h"

#include <cctype>
#include <fmt/core.h>
#include <iterator>
#include <memory>
#include <numeric>
#include <queue>
#include <sstream>
#include <unordered_set>

#include "graph.h"

static void print_gph(const graph& gph)
{
    auto que = std::queue<std::weak_ptr<vertex>>();
    auto visited = std::unordered_set<std::shared_ptr<vertex>>();
    for (const auto& v  : gph) que.push(v); 

    while (!que.empty()) {
        auto node = que.front().lock();
        que.pop();
        if (visited.count(node))
            continue;
        visited.insert(node);
        fmt::print("{}: ", node->name);

        auto left = node->left.lock();
        auto right = node->right.lock();
        if (left) {
            que.push(left);
            fmt::print("{} ", left->name);
        }
        if (right) {
            que.push(right);
            fmt::print("{}", right->name);
        }
        fmt::println("");
    }
}

static graph parse_gph(std::ifstream& input)
{
    auto gph = graph{};
    auto index_map = std::unordered_map<std::string, std::shared_ptr<vertex>>();

    auto add_or_get_node = [&](const std::string& name) {
        if (index_map.count(name))
            return index_map[name];

        auto node = std::make_shared<vertex>(name);
        index_map[name] = node;
        gph.push_back(node);
        return node;
    };
    auto clean_word = [](std::string& word) {
        word.erase(std::remove_if(begin(word), end(word),
                    [](char c) { return !std::isalpha(c); }),
                std::end(word));
    };

    for (auto line = std::string(); std::getline(input, line);) {
        if (line.empty())
            continue;
        auto iss = std::istringstream(line);
        auto word = std::string();
        iss >> word;
        auto parent = add_or_get_node(word);

        while (iss >> word) {
            clean_word(word);
            if (word.empty())
                continue;
            auto child = add_or_get_node(word);
            if (!parent->left.lock())
                parent->left = child;
            else if (!parent->right.lock())
                parent->right = child;
        }
    }

    return gph;
}

static size_t get_lcm(const std::string& dir, const graph& gph)
{
    auto cnts = std::vector<size_t>();
    auto vertices = std::vector<std::shared_ptr<vertex>>();
    std::copy_if(begin(gph), end(gph), std::back_inserter(vertices),
            [](const std::shared_ptr<vertex>& v) {
                return v->name.back() == 'A';
            });

    for (auto v : vertices) {
        auto cnt = 0uz;
        for (auto i = 0uz; i < dir.size(); i = ++i % dir.size()) {
            if (v->name.back() == 'Z')
                break;

            v = (dir[i] == 'L') ? v->left.lock() : v->right.lock();
            ++cnt;
        }
        cnts.push_back(cnt);
    }

    auto lcm = cnts.front();
    for (auto i = 1uz; i < cnts.size(); ++i)
        lcm = std::lcm(lcm, cnts[i]);

    return lcm;
}

void solve_part2(std::ifstream& input)
{
    auto dir = [&]() {
        auto line = std::string();
        std::getline(input, line);
        return line;
    }();

    auto gph = parse_gph(input);
    fmt::println("{}", get_lcm(dir, gph));
}
