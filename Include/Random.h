#pragma once
#include <random>

class Random
{
public:
    Random()                                        ;
    auto GetInt     (int min,int max)       ->int   ;
    auto GetFloat   (float min, float max)  ->float ;
private:
    std::random_device  device_;
    std::mt19937        generator_;
};

inline Random gRandom;