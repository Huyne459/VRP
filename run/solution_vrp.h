#pragma once
#include <bits/stdc++.h>

#include "instance_vrp.h"

using namespace std;

class Solution_vrp {
   private:
    Instance_vrp* instance;
    vector<vector<int>> tours;
    double maxDistance;
    // double minDistance;
    vector<double> totalDistance;
    double capacity;
    vector<double> demain_tour;
    int number_tour;
    vector<bool> flag_point;

   public:
    Solution_vrp();
    Solution_vrp(Instance_vrp& instance);
    Solution_vrp(const Solution_vrp& s);
    Solution_vrp& operator=(const Solution_vrp& s);

    vector<double> getTotalDistance();
    void Solution_vrpH();
    void print();
    int Point_near(int id_point);
    int Point_far();
    vector<vector<int>> getTours();
    double getMaxDistance();
    vector<vector<double>> dist_subTour(vector<int> id_node_subTour);
    void setAt(int index_tour, vector<int> id_nodes);
    void setDistanceSubTour(int index_tour, double distance_);
    void setMaxDistance();
    int getIndexMaxdistance();

    // void insertNode(vector<int> s, int node, int position);
};
