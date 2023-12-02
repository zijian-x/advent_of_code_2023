#include "part1.h"

void part1_list(std::ifstream& input)
{
    auto sum = 0;
    auto line = std::string();
    auto out = std::ofstream("./data/list");
    while (std::getline(input, line)) {
        auto nums = std::vector<int>();
        std::for_each(begin(line), end(line), [&nums](char c) {
                if (std::isdigit(c)) {
                    nums.push_back(c - '0');
                }});

        auto num = nums.front() * 10 + nums.back();
        out << num << '\n';
        sum += num;
    }

    fmt::println("{}", sum);
}

void part1_two_ptr(std::ifstream& input)
{
    auto sum = 0;
    auto line = std::string();
    auto out = std::ofstream("./data/two_ptr");
    while (std::getline(input, line)) {
        auto num1 = std::optional<int>();
        auto num2 = std::optional<int>();
        for (size_t i = 0, j = 0; j < line.size(); ++j) {
            if (std::isdigit(line[i])) {
                if (!num1.has_value())
                    num1 = line[i] - '0';
            } else {
                ++i;
            }

            if (std::isdigit(line[j])) {
                num2 = line[j] - '0';
            }
        }

        sum += num1.value() * 10 + num2.value();
    }

    fmt::println("{}", sum);
}
