#ifndef UTILS_H
#define UTILS_H
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>
#include <iostream>
#include <math.h>
#include <assert.h>

class Utils
{
    public:
        static std::mt19937 mt;
        static int seed;

        static int integer_random_generator(const int &a , const int &b );
        static double real_random_generator(const double& a, const double& b);
        static void shuffle(std::vector<int> &vec);

    private:

};

#endif // UTILS_H
