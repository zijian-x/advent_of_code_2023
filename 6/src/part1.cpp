#include "part1.h"

#include <array>
#include <iterator>
#include <sstream>
#include <vector>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include "race.h"

static auto get_races(std::ifstream& input) -> std::array<race, 4>
{
    auto times = std::array<size_t, 4>();
    auto distances = std::array<size_t, 4>();
    for (auto i = 0; i < 2; ++i) {
        auto line = std::string(), tmp = std::string();
        std::getline(input, line);
        auto iss = std::istringstream(line);
        iss >> tmp;
        for (size_t j = 0; j < 4; ++j)
            iss >> ((!i) ? times[j] : distances[j]);
    }

    auto races = std::array<race, 4>();
    for (size_t i = 0; i < races.size(); ++i)
        races[i] = {times[i], distances[i]};
    return races;
}

auto win_rate(const race& race) -> size_t
{
    size_t rate = 0;
    for (size_t speed = 1; speed < race.time; ++speed) {
        auto speed_time = race.time - speed;
        if (speed_time * speed > race.distance)
            ++rate;
    }

    return rate;
}

auto solve_part1(std::ifstream& file) -> void
{
    auto races = get_races(file);

    auto sum = 1;
    for (const auto& race : races)
        sum *= win_rate(race);

    fmt::println("{}", sum);
}
