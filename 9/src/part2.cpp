#include "part2.h"

#include <algorithm>
#include <fmt/core.h>
#include <iterator>
#include <sstream>
#include <unistd.h>

#include "utils.h"

static size_t predict(const std::vector<size_t>& nums)
{
    if (std::all_of(begin(nums), end(nums), [](size_t i) { return !i; }))
        return 0;

    auto diffs = std::vector<size_t>(nums.size() - 1);
    for (size_t i = 1; i < nums.size(); ++i)
        diffs[i - 1] = nums[i] - nums[i - 1];
    auto last = predict(diffs);

    return nums.front() - last;
}

void solve_part2(std::ifstream& input)
{
    auto lines = getlines(input);
    auto sum = 0z;

    for(const auto& line : lines) {
        auto iss = std::istringstream(line);
        auto nums = std::vector<size_t>(std::istream_iterator<size_t>(iss),
                std::istream_iterator<size_t>());
        auto p =  predict(nums);
        sum += p;
    }

    fmt::println("{}", sum);
}
