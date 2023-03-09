#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class Random
{
public:
    static unsigned randomNumber() {
        std::random_device rd{};
        std::mt19937 engine{ rd() };
        std::uniform_int_distribution<int> dist{ 0, 1000000 };
        return dist(engine);
    }
};

#endif
