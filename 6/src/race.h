#pragma once

#include <cstddef>
#include <fmt/core.h>

struct race
{
    size_t time;
    size_t distance;
};

template <>
struct fmt::formatter<race>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FmtContext>
    constexpr auto format(const race& r, FmtContext& ctx)
    {
        return format_to(ctx.out(), "time: {}, distance: {}", r.time, r.distance);
    }
};
