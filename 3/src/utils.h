#pragma once

#include <utility>
#include <unordered_set>
#include <vector>

#include <boost/functional/hash.hpp>

namespace std
{
    template<>
    struct hash<std::pair<size_t, size_t>>
    {
        std::size_t operator()(const std::pair<size_t, size_t>& p) const
        { return boost::hash<std::pair<size_t, size_t>>{}(p); }
    };
};

int get_num(const std::vector<std::string>&, size_t, size_t,
        std::unordered_set<std::pair<size_t, size_t>>&);
