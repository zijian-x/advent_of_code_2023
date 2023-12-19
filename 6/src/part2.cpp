#include "part2.h"

#include <array>
#include <limits>
#include <sstream>

#include "race.h"

race get_race(std::ifstream& input)
{
    size_t time;
    size_t distance;
    for (size_t i = 0; i < 2; ++i) {
        auto line = std::string();
        std::getline(input, line);
        auto iss = std::istringstream(line);
        iss >> line;
        line.clear();
        for (size_t j = 0; j < 4; ++j) {
            auto buf = std::string();
            iss >> buf;
            line.append(std::move(buf));
        }

        if (!i)
            time = std::stoull(line);
        else
            distance = std::stoull(line);
    }

    return race{time, distance};
}

void solve_part2(std::ifstream& input)
{
    auto race = get_race(input);
    fmt::println("{}", race);

    auto rate = 0;
    for (size_t speed = 1; speed < race.time; ++speed) {
        if (speed * (race.time - speed) > race.distance)
            ++rate;
    }

    fmt::println("rate: {}", rate);
}
