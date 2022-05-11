#include "solution_vrp.h"
//#include "gnuplot-iostream.h"
#include <bits/stdc++.h>

#include "instance_vrp.h"

Solution_vrp::Solution_vrp() {
    tours = {{0, 0}};
    flag_point = vector<bool>();
}
Solution_vrp::Solution_vrp(Instance_vrp &instance) {
    number_tour = instance.number_truck;
    this->instance = &instance;
    flag_point = vector<bool>(instance.demension, false);
    tours.resize(number_tour, {0});
    demain_tour.resize(number_tour, 0);
    totalDistance.resize(number_tour, 0);
    capacity = instance.capacity;
}

Solution_vrp::Solution_vrp(const Solution_vrp &s) {
    totalDistance = s.totalDistance;
    tours = s.tours;
}

int Solution_vrp::getIndexMaxdistance() {
    int index = 0;
    for (int i = 1; i < tours.size(); i++) {
        if (totalDistance[index] < totalDistance[i]) {
            index = i;
        }
    }
    return index;
}

Solution_vrp &Solution_vrp::operator=(const Solution_vrp &s) {
    number_tour = s.number_tour;
    *instance = *(s.instance);
    totalDistance = s.totalDistance;
    tours = s.tours;
    maxDistance = s.maxDistance;
    number_tour = s.number_tour;
    capacity = s.capacity;
    demain_tour = s.demain_tour;
    flag_point = s.flag_point;

    return *this;
}

vector<double> Solution_vrp::getTotalDistance() {
    return totalDistance;
}

void Solution_vrp::print() {
    int id = 0;
    for (auto subTour : tours) {
        cout << id++ << "\t=>>\t" << totalDistance[id - 1] << " | ";
        for (auto i : subTour) {
            cout << " -> " << i;
        }
        cout << "\n";
    }
    cout << "\n";
    // cout << instance->dist_matrix[1][2];
}

int Solution_vrp::Point_near(int id_point) {
    double d_min = 10e9;
    int index = 0;

    for (int i = 1; i < instance->demension; i++) {
        if (flag_point[i] == false) {
            if (instance->dist_matrix[id_point][i] < d_min) {
                // if (instance->dist_matrix[id_point][i] < d_min) {
                d_min = instance->dist_matrix[id_point][i];
                index = i;
            }
        }
    }
    return index;
}

int Solution_vrp::Point_far() {
    int id_point = 0;
    double d_max = 0;
    int index = 0;

    for (int i = 1; i < instance->demension; i++) {
        if (flag_point[i] == false) {
            if (instance->dist_matrix[id_point][i] > d_max) {
                // if (instance->dist_matrix[id_point][i] < d_min) {
                d_max = instance->dist_matrix[id_point][i];
                index = i;
            }
        }
    }
    return index;
}

int Solution_vrp::Point_random() {
    int index = 0;
    while (index == 0 || flag_point[index]) {
        index = rand() % instance->demension;
    }
    return index;
}

void Solution_vrp::Solution_vrpV() {
    int count_cust = instance->demension;
    // int id_begin = 0;

    for (int i = 0; i < number_tour; i++) {
        int id_far = Point_far();
        flag_point[id_far] = true;
        tours[i].push_back(id_far);
        demain_tour[i] += instance->demand[id_far];
        totalDistance[i] += instance->dist_matrix[0][id_far];
        count_cust--;
    }

    while (count_cust > 1) {
        for (int i = 0; i < number_tour && count_cust > 1; i++) {
            int id_point_last = tours[i].back();
            // cout << id_point_last << "\t";
            int id_point_next = Point_near(id_point_last);
            // int id_point_next = Point_random();
            flag_point[id_point_next] = true;
            tours[i].push_back(id_point_next);
            demain_tour[i] += instance->demand[id_point_next];
            totalDistance[i] += instance->dist_matrix[id_point_last][id_point_next];
            // if (demain_tour[i]>capacity) {
            //     flag_point[id_point_next] = false;
            //     tours[i].pop_back();
            //     demain_tour[i] -= instance->demand[id_point_next];
            // }
            count_cust--;
        }
    }
    for (int i = 0; i < number_tour; i++) {
        tours[i].push_back(0);
        demain_tour[i] += instance->demand[0];
        totalDistance[i] += instance->dist_matrix[tours[i].size() - 2][0];
        // cout << tours[i].size() << "\n";
    }
    maxDistance = getMaxDistance();
    print();
}

double Solution_vrp::getMaxDistance() {
    maxDistance = totalDistance[0];
    for (auto i : totalDistance) {
        if (maxDistance < i) {
            maxDistance = i;
        }
    }
    return maxDistance;
}

vector<vector<double>> Solution_vrp::dist_subTour(vector<int> id_node_subTour) {
    vector<vector<double>> dist_;
    for (int i = 0; i < id_node_subTour.size() - 1; ++i) {
        dist_.push_back({});
    }
    int index = 0;

    // for (auto i : id_node_subTour) {
    //     // cout << id_node_subTour[2];
    //     for (auto j : id_node_subTour) {
    //         // cout << instance->dist_matrix[1][2] << "khoong casu bnafy k chayj";
    //         dist_[index].push_back(instance->dist_matrix[i][j]);
    //     }
    //     index++;
    // }
    // cout << instance->getDistance(0, 0) << "\n";
    // cout << instance->dist_matrix[2][3] << "--------\n";

    for (int i = 0; i < id_node_subTour.size() - 1; i++) {
        for (int j = 0; j < id_node_subTour.size() - 1; j++) {
            // cout << "1233546\n";
            // cout << id_node_subTour[i + 2] << " - " << id_node_subTour[j + 3] << "\n";
            dist_[index].push_back(instance->dist_matrix[id_node_subTour[i]][id_node_subTour[j]]);
        }
        index++;
    }

    return dist_;
}

vector<vector<int>> Solution_vrp::getTours() {
    return tours;
}

void Solution_vrp::setAt(int index_tour, vector<int> id_nodes) {
    tours[index_tour] = id_nodes;
}

void Solution_vrp::setDistanceSubTour(int index_tour, double distance_) {
    totalDistance[index_tour] = distance_;
}

void Solution_vrp::setMaxDistance() {
    maxDistance = getMaxDistance();
}

// int main(int argc, char const *argv[]) {
//     Instance_vrp instance = Instance_vrp("../X/X-n101-k25.vrp");
//     Solution_vrp s(instance);
//     s.Solution_vrpV();
//     // s.Point_random();
//     s.print();

//     vector<vector<int>> tours = s.getTours();

//     for (auto subTour : tours) {
//         //tsp
//         for (auto i : subTour) {

//         }
//     }

//     return 0;
// }
