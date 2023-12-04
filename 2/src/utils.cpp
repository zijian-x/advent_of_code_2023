#include "utils.h"

int get_num(const std::string& line, size_t i)
{
    auto num = 0;
    auto base = 1;
    while (std::isdigit(line[i])) {
        num += (line[i] - '0') * base;
        base *= 10;
        --i;
    }

    return num;
}
