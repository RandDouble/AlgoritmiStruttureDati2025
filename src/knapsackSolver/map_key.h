#pragma once 

struct MapKey
{
    const int considered{0}, target{0};

    MapKey(const int c, const int t) : considered(c), target(t) {}

    constexpr bool operator==(const MapKey &other) const noexcept
    {
        return considered == other.considered && target == other.target;
    }
};

template <>
struct std::hash<MapKey>
{
    std::size_t operator()(const MapKey &k) const noexcept
    {
        std::size_t seed = 1;
        seed = hash_combine(seed, k.considered);
        seed = hash_combine(seed, k.target);
        return seed;
    }

    constexpr std::size_t hash_combine(const std::size_t seed, const std::size_t hash) const noexcept
    {
        return mix(seed + 0x9e3779b9 + hash);
    }

    /* Taken from Boost::hash_combine implementation*/
    constexpr std::size_t mix(std::size_t x) const noexcept
    {
        x ^= x >> 32;
        x *= 0xe9846af9b1a615d;
        x ^= x >> 32;
        x *= 0xe9846af9b1a615d;
        x ^= x >> 28;
        return x;
    }
};