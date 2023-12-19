#include "part2.h"

#include <fmt/core.h>
#include <fstream>

int main()
{
    auto input = std::ifstream("./data/input");
    if (!input.is_open()) {
        fmt::println("input not found.");
        std::exit(1);
    }

    solve_part2(input);
}
