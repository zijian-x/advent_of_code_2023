#include "part1.h"

#include <cctype>
#include <fmt/core.h>
#include <memory>
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

static int get_cnt(const std::string& dir, const graph& gph)
{
    auto start = *std::find_if(begin(gph), end(gph), [](const std::shared_ptr<vertex>& v) {
            return v->name == "AAA";
            });
    auto cnt = 0;
    for (auto i = 0uz; i < dir.size(); i = ++i % dir.size()) {
        if (start->name == "ZZZ")
            return cnt;

        start = (dir[i] == 'L') ? start->left.lock() : start->right.lock();
        ++cnt;
    }

    return -1;
}

void solve_part1(std::ifstream& input)
{
    auto dir = [&]() {
        auto line = std::string();
        std::getline(input, line);
        return line;
    }();

    auto gph = parse_gph(input);
    fmt::println("{}", get_cnt(dir, gph));
}
