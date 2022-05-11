#include "utils.h"
#include <cmath>
#include <string>

int Utils::seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 Utils::mt = std::mt19937(Utils::seed);


int Utils::integer_random_generator(const int &a, const int &b){
    if (b<=a)
        throw std::string("ERROR | int random problem");
    return std::uniform_int_distribution<int>{a, b-1}(Utils::mt);
}

double Utils::real_random_generator(const double &a, const double &b){
    if (b<=a)
        throw std::string("ERROR | double random problem");
    return std::uniform_real_distribution<double>{a, b}(Utils::mt);
}

void Utils::shuffle(std::vector<int> &vec){
    std::shuffle(vec.begin(), vec.end(), Utils::mt);
}
