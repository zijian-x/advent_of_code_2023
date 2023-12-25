#include "utils.h"

std::vector<std::string> getlines(std::ifstream& input)
{
    auto lines = std::vector<std::string>();
    for (std::string line; std::getline(input, line);)
        lines.emplace_back(std::move(line));
    return lines;
}
