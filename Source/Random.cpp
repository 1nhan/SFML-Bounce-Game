#include"Random.h"

Random::Random()                                        
    :generator_{device_()}
{

}
auto Random::GetInt     (int min,int max)       ->int   
{
    return std::uniform_int_distribution(min,max)(generator_);
}
auto Random::GetFloat   (float min, float max)  ->float 
{
    return std::uniform_real_distribution(min,max)(generator_);
}

