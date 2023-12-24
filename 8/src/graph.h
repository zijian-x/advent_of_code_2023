#pragma once

#include <boost/container_hash/hash_fwd.hpp>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <boost/functional/hash.hpp>

class vertex
{
public:
    std::string name{};
    std::weak_ptr<vertex> left{};
    std::weak_ptr<vertex> right{};

    vertex() = default;

    vertex(std::string name)
        : name{std::move(name)}
    {}

    vertex(std::string name,
            std::weak_ptr<vertex> left,
            std::weak_ptr<vertex> right)
        : name{std::move(name)}
        , left{left}
        , right{right}
    {}

};

using graph = std::vector<std::shared_ptr<vertex>>;

namespace std
{
    template<>
    struct hash<vertex>
    {
        std::size_t operator()(const vertex& node) const
        {
            auto seed = std::hash<std::string>{}(node.name);
            boost::hash_combine(seed, node.left.lock());
            boost::hash_combine(seed, node.right.lock());

            return seed;
        }
    };
};
