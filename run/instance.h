#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>
#include <iostream>
#define MY_EPSILON 0.0001 // Precision parameter, used to avoid numerical instabilities

using namespace std;

class Instance
{




public:
    int num_nodes;
    std::vector <double> x;
    std::vector <double> y;
    vector<vector<double>> dist_matrix;
    Instance(std::string instanceName);
    Instance(vector<vector<double>> dist_matrix, vector<double> x = vector<double>(), vector<double> y = vector<double>());
    void read_input(const std::string &inputFile);
    void initialize();
    double getDistance(int i, int j);
};

#endif // INSTANCE_H
