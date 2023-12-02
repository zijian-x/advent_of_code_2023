#include "part1.h"
#include "part2.h"

void solve_part1(std::ifstream& input)
{
    // part1_list(input);
    // input.clear();
    // input.seekg(0);
    part1_two_ptr(input);
    input.clear();
    input.seekg(0);
}

void solve_part2(std::ifstream& input)
{
    part2_list(input);
}

int main()
{
    auto input = std::ifstream("./data/input");
    if (!input.is_open()) {
        fmt::println(stderr, "input not found.");
        std::exit(1);
    }

    solve_part1(input);
    solve_part2(input);
}
