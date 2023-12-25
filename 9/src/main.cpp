#include <fstream>
#include <fmt/core.h>

#include "part1.h"
#include "part2.h"

int main()
{
    auto input = std::ifstream("./data/input");
    if (!input.is_open()) {
        fmt::println(stderr, "input file not found.");
        std::exit(1);
    }

    solve_part2(input);
}
