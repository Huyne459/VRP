#ifndef SOLUTION_H
#define SOLUTION_H
#include <vector>
#include "utils.h"
// #include "gnuplot-iostream.h"

using namespace std;

class Instance;
class Solution
{

public:
    // Gnuplot gp;
    Solution();
    Solution(const Solution& s);
    Solution& operator =(const Solution& s);
    vector<int> tour;
    double distance;
    double getDistance();
    // void display(Instance *instance);
    void print();
};

#endif // SOLUTION_H
