#pragma once
#include <bits/stdc++.h>

#define MY_EPSILON 0.0001  // Precision parameter, used to avoid numerical instabilities

using namespace std;

class Instance_vrp {
   private:
    int demension;
    double capacity;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> demand;
    int number_truck;
    vector<vector<double>> dist_matrix;
    double time_limit;

   public:
    int number_client;
    Instance_vrp();
    Instance_vrp(std::string linkFileInstance_vrp, double time);
    double getDistance(int i, int j);
    void show_position_custom();
    double getTimelimit();

   protected:
    void initialize();
    void read_input(const std::string &inputFile);
    friend class Solution_vrp;
};