#include "solver_vrp.h"

#include "instance.h"
#include "solution_vrp.h"
#include "solver.h"
#define esp 0.00001

Solver_VRP::Solver_VRP(Instance_vrp *instance) : instance(instance) {
    cooling_rate = 0.996;
    threshold = 0.2;  //
}

void Solver_VRP::solution_construction() {
    bestSol = new Solution_vrp(*instance);
    currentSol = new Solution_vrp(*instance);
    // nearestHeuristic(bestSol);
    //    cheapestHeuristic(bestSol);
    // cout << instance->getDistance(3, 6) << " - distance 3-6 \n";
    bestSol->Solution_vrpV();
    // bestSol->getTotalDistance();

    *currentSol = *bestSol;
}
// void Solver_VRP::nearestHeuristic(Solution *s) {
//     bestSol->Solution_vrpV();
//     cout << instance->getDistance(3, 4);
//     // nearest neighbor
//     // unordered_set<int> danhsachNode;
//     // for (int i = 1; i < instance->num_nodes; ++i)
//     //     danhsachNode.insert(i);

//     // int last = 0;
//     // while (!danhsachNode.empty()) {
//     //     // tim diem gan nhat nearest voi diem cuoi cung cua tour
//     //     int nearest = find_nearest(danhsachNode, last);
//     //     // insert vao cuoi tour
//     //     insertNode(s, nearest, s->tour.size() - 1);
//     //     // xoa nearest khoi danh sach
//     //     danhsachNode.erase(nearest);
//     //     //        s->display(instance);
//     //     s->print();
//     //     // cap nhat last
//     //     last = nearest;
//     // }
// }

void Solver_VRP::solve() {
    solution_construction();

    for (int iter = 0; iter < 1; ++iter) {
        Solution_vrp *s = new Solution_vrp(*instance);
        *s = *currentSol;
        // Mutate
        // mutate(&s);
        // local search
        local_search(s);

        // check and save
        // if ((s->getMaxDistance() - currentSol->getMaxDistance()) / currentSol->getMaxDistance() < threshold) {
        //     *currentSol = *s;
        //     if (currentSol->getMaxDistance() - bestSol->getMaxDistance() < -0.0001) {
        //         *bestSol = *currentSol;
        //         cout << iter << " - Found improvement " << bestSol->getMaxDistance() << endl;
        //     }
        // }
        // threshold = threshold * cooling_rate;
        //        cout << iter << " " << threshold << endl;
    }
    // bestSol->display(instance);
}

double Solver_VRP::getMaxDistanceTour() {
    return bestSol->getMaxDistance();
}

void Solver_VRP::local_search(Solution_vrp *s) {
    bool improved = true;
    while (improved) {
        improved = false;
        LS_relocate(s, improved);
        LS_swap(s, improved);

        cout << "\n";
        s->print();
    }
}

void Solver_VRP::LS_swap(Solution_vrp *s, bool &improved) {
here:

    int i = s->getIndexMaxdistance();
    for (int j = 0; j < s->getTours().size(); ++j) {
        if (i == j) continue;
        vector<int> tour_i = s->getTours()[i];
        vector<int> tour_j = s->getTours()[j];
        for (int &node_i : tour_i) {
            if (node_i == 0) continue;
            for (int &node_j : tour_j) {
                if (node_j == 0) continue;
                swap(node_i, node_j);
                vector<vector<double>> matrix_dist_i = s->dist_subTour(tour_i);
                vector<vector<double>> matrix_dist_j = s->dist_subTour(tour_j);
                Instance instance_i = Instance(matrix_dist_i);
                Instance instance_j = Instance(matrix_dist_j);

                Solver s_i = Solver(&instance_i);

                // cout <<
                // double distance_i_ = s_i.getMinDistanceTour();
                s_i.solve();

                Solver s_j = Solver(&instance_j);

                // double distance_j_ = s_j.getMinDistanceTour();
                s_j.solve();

                double distance_i = s_i.getMinDistanceTour();
                double distance_j = s_j.getMinDistanceTour();
                if (s->getMaxDistance() > distance_i + esp && s->getMaxDistance() > distance_j + esp) {
                    cout << "========================\n";
                    cout << "Swap: i- " << i << "\n";
                    cout << "Swap: j- " << j << "\n";
                    s->setAt(i, tour_i);
                    s->setAt(j, tour_j);
                    s->setDistanceSubTour(i, distance_i);
                    s->setDistanceSubTour(j, distance_j);
                    s->setMaxDistance();
                    improved = true;
                    cout << "Max Dis: " << s->getMaxDistance() << "\n";
                    goto here;
                }
                swap(node_j, node_i);
            }
        }
    }
}

void Solver_VRP::LS_relocate(Solution_vrp *s, bool &improved) {
here:
    int i = s->getIndexMaxdistance();
    for (int j = 0; j < s->getTours().size(); ++j) {
        if (i == j) continue;
        vector<int> tour_i_ = s->getTours()[i];
        vector<int> tour_j_ = s->getTours()[j];
        vector<int> tour_i = tour_i_;
        vector<int> tour_j = tour_j_;

        for (int index_node_i = 1; index_node_i < tour_i.size() - 1; index_node_i++) {
            if (tour_j.size() - 1 >= instance->number_client) {
                break;
            }

            tour_j.push_back(0);
            tour_j[tour_j.size() - 2] = tour_i[index_node_i];
            tour_i.erase(tour_i.begin() + index_node_i);

            vector<vector<double>> matrix_dist_i = s->dist_subTour(tour_i);
            vector<vector<double>> matrix_dist_j = s->dist_subTour(tour_j);
            // cout << s->dist_subTour(tour_i)[1][2];
            Instance instance_i = Instance(matrix_dist_i);
            Instance instance_j = Instance(matrix_dist_j);

            Solver s_i = Solver(&instance_i);
            // cout << "tour i: " << i << "\n";
            s_i.solve();
            Solver s_j = Solver(&instance_j);
            // cout << "tour j: " << j << "\n";
            s_j.solve();
            double distance_i = s_i.getMinDistanceTour();
            double distance_j = s_j.getMinDistanceTour();
            if (s->getMaxDistance() > distance_i + esp && s->getMaxDistance() > distance_j + esp) {
                cout << "========================\n";
                cout << "Relocate: i- " << i << "\n";
                cout << "Relocate: j- " << j << "\n";
                s->setAt(i, tour_i);
                s->setAt(j, tour_j);
                s->setDistanceSubTour(i, distance_i);
                s->setDistanceSubTour(j, distance_j);
                s->setMaxDistance();
                improved = true;
                cout << "Max Dis: " << s->getMaxDistance() << "\n";
                goto here;
            }

            tour_i = tour_i_;
            tour_j = tour_j_;
        }
    }
}

// void Solver_VRP::do_relocate(Solution_vrp *s, int nodePos, int newPos, double delta) {
//     int node = s->tour[nodePos];
//     if (newPos > nodePos) {
//         s->tour.insert(s->tour.begin() + newPos, node);
//         s->tour.erase(s->tour.begin() + nodePos);
//     } else {
//         s->tour.erase(s->tour.begin() + nodePos);
//         s->tour.insert(s->tour.begin() + newPos, node);
//     }
//     s->distance += delta;
// }

void Solver_VRP::check(Solution_vrp *s) {
    // double d = 0;
    // for (int i = 0; i < s->tour.size() - 1; ++i) {
    //     d += getDistance(s->tour[i], s->tour[i + 1]);
    // }
    // assert(abs(d - s->distance) < 0.00001);
}

void Solver_VRP::mutate(Solution_vrp *s) {
    // int numSwap = Utils::integer_random_generator(1, 4);
    // for (int i = 0; i < numSwap; ++i) {
    //     int p1, p2;
    //     do {
    //         p1 = Utils::integer_random_generator(1, s->tour.size() - 1);
    //         p2 = Utils::integer_random_generator(1, s->tour.size() - 1);
    //     } while (p1 == p2);

    //     swap_two_nodes(s, p1, p2);
    //     check(s);
    // }
}