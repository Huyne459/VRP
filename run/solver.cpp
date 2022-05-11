#include "solver.h"

Solver::Solver(Instance *instance) : instance(instance) {
    cooling_rate = 0.996;
    threshold = 0.2;  //
}

void Solver::solution_construction() {
    bestSol = new Solution();
    currentSol = new Solution();
    //    nearestHeuristic(bestSol);
    //    cheapestHeuristic(bestSol);
    cheapestHeuristic_random(bestSol);

    *currentSol = *bestSol;
}

void Solver::solve() {
    solution_construction();
    for (int iter = 0; iter < 1000; ++iter) {
        Solution s = *currentSol;
        // Mutate
        mutate(&s);
        // local search
        local_search(&s);
        // check and save
        if ((s.distance - currentSol->distance) / currentSol->distance < threshold) {
            *currentSol = s;
            if (currentSol->distance - bestSol->distance < -0.0001) {
                *bestSol = *currentSol;
                // cout << iter << " - Found improvement TSP " << bestSol->distance << endl;
            }
        }
        threshold = threshold * cooling_rate;
        //        cout << iter << " " << threshold << endl;
    }
    // bestSol->display(instance);
}

double Solver::getMinDistanceTour() {
    return bestSol->getDistance();
}

void Solver::local_search(Solution *s) {
    bool improved = true;
    while (improved) {
        improved = false;
        LS_relocate(s, improved);
        LS_swap(s, improved);
        LS_two_opt(s, improved);
    }
}

void Solver::LS_swap(Solution *s, bool &improved) {
here:
    vector<int> &tour = s->tour;
    for (int i = 1; i < tour.size() - 2; ++i) {
        for (int j = i + 1; j < tour.size() - 1; ++j) {
            double delta;
            int pi = i;
            int pj = j;
            if (j - i > 1) {
                delta = -getDistance(tour[pi - 1], tour[pi]) - getDistance(tour[pi], tour[pi + 1]) - getDistance(tour[pj - 1], tour[pj]) - getDistance(tour[pj], tour[pj + 1])

                        + getDistance(tour[pi - 1], tour[pj]) + getDistance(tour[pj], tour[pi + 1]) + getDistance(tour[pj - 1], tour[pi]) + getDistance(tour[pi], tour[pj + 1]);

            } else {
                delta = -getDistance(tour[pi - 1], tour[pi]) - getDistance(tour[pj], tour[pj + 1]) + getDistance(tour[pi - 1], tour[pj]) + getDistance(tour[pi], tour[pj + 1]);
            }
            if (delta < -0.0001) {  // improved
                swap_two_nodes(s, i, j, delta);
                check(s);
                improved = true;
                goto here;
            }
        }
    }
}

void Solver::LS_two_opt(Solution *s, bool &improved) {
here:
    vector<int> &tour = s->tour;
    for (int i = 1; i < tour.size() - 2; ++i) {
        for (int j = i + 1; j < tour.size() - 1; ++j) {
            double delta;
            int pi = i;
            int pj = j;
            delta = -getDistance(tour[pi - 1], tour[pi]) - getDistance(tour[pj], tour[pj + 1]) + getDistance(tour[pi - 1], tour[pj]) + getDistance(tour[pi], tour[pj + 1]);

            if (delta < -0.0001) {  // improved
                two_opt_nodes(s, i, j, delta);
                check(s);
                improved = true;
                goto here;
            }
        }
    }
}

void Solver::LS_relocate(Solution *s, bool &improved) {
here:
    vector<int> &tour = s->tour;
    for (int i = 1; i < tour.size() - 1; ++i) {
        int node = tour[i];

        for (int p = 1; p < tour.size(); ++p) {
            if (p == i || p == i + 1) continue;
            double delta = getDistance(s->tour[p - 1], node) + getDistance(node, s->tour[p]) - getDistance(s->tour[p - 1], s->tour[p]) + getDistance(s->tour[i - 1], s->tour[i + 1]) - getDistance(s->tour[i], s->tour[i - 1]) - getDistance(s->tour[i], s->tour[i + 1]);
            if (delta < -0.0001) {  // improved
                do_relocate(s, i, p, delta);
                check(s);
                improved = true;
                goto here;
            }
        }
    }
}

void Solver::swap_two_nodes(Solution *s, int pi, int pj, double delta = 0) {
    vector<int> &tour = s->tour;

    if (pi > pj) {
        int tmp = pi;
        pi = pj;
        pj = tmp;
    }

    // cap nhat distance
    if (delta == 0) {
        if (pj - pi > 1) {
            delta = -getDistance(tour[pi - 1], tour[pi]) - getDistance(tour[pi], tour[pi + 1]) - getDistance(tour[pj - 1], tour[pj]) - getDistance(tour[pj], tour[pj + 1])

                    + getDistance(tour[pi - 1], tour[pj]) + getDistance(tour[pj], tour[pi + 1]) + getDistance(tour[pj - 1], tour[pi]) + getDistance(tour[pi], tour[pj + 1]);

        } else {
            delta = -getDistance(tour[pi - 1], tour[pi]) - getDistance(tour[pj], tour[pj + 1]) + getDistance(tour[pi - 1], tour[pj]) + getDistance(tour[pi], tour[pj + 1]);
        }
    }

    s->distance += delta;
    int temp = tour[pi];
    tour[pi] = tour[pj];
    tour[pj] = temp;
}

void Solver::two_opt_nodes(Solution *s, int pi, int pj, double delta) {
    vector<int> &tour = s->tour;

    if (pi > pj) {
        int tmp = pi;
        pi = pj;
        pj = tmp;
    }
    bool flag = true;
    if (delta == 0) flag = false;

    if (!flag) {
        delta = -(getDistance(tour[pi - 1], tour[pi]) + getDistance(tour[pj], tour[pj + 1]));
    }

    reverse(s, pi, pj);

    if (!flag) {
        delta += (getDistance(tour[pi - 1], tour[pi]) + getDistance(tour[pj], tour[pj + 1]));
    }

    s->distance += delta;
}

void Solver::reverse(Solution *s, int pi, int pj) {
    vector<int> &tour = s->tour;

    if (pi > pj) {
        int tmp = pi;
        pi = pj;
        pj = tmp;
    }

    for (int k = 0; k <= (pj - pi) / 2; ++k) {
        int temp = tour[pi + k];
        tour[pi + k] = tour[pj - k];
        tour[pj - k] = temp;
    }
}

void Solver::do_relocate(Solution *s, int nodePos, int newPos, double delta) {
    int node = s->tour[nodePos];
    if (newPos > nodePos) {
        s->tour.insert(s->tour.begin() + newPos, node);
        s->tour.erase(s->tour.begin() + nodePos);
    } else {
        s->tour.erase(s->tour.begin() + nodePos);
        s->tour.insert(s->tour.begin() + newPos, node);
    }
    s->distance += delta;
}

void Solver::check(Solution *s) {
    double d = 0;
    for (int i = 0; i < s->tour.size() - 1; ++i) {
        d += getDistance(s->tour[i], s->tour[i + 1]);
    }
    assert(abs(d - s->distance) < 0.00001);
}

void Solver::mutate(Solution *s) {
    int numSwap = Utils::integer_random_generator(1, 4);
    for (int i = 0; i < numSwap; ++i) {
        int p1, p2;
        do {
            p1 = Utils::integer_random_generator(1, s->tour.size() - 1);
            p2 = Utils::integer_random_generator(1, s->tour.size() - 1);
        } while (p1 == p2);

        swap_two_nodes(s, p1, p2);
        check(s);
    }
}

void Solver::nearestHeuristic(Solution *s) {
    // nearest neighbor
    unordered_set<int> danhsachNode;
    for (int i = 1; i < instance->num_nodes; ++i)
        danhsachNode.insert(i);

    int last = 0;
    while (!danhsachNode.empty()) {
        // tim diem gan nhat nearest voi diem cuoi cung cua tour
        int nearest = find_nearest(danhsachNode, last);
        // insert vao cuoi tour
        insertNode(s, nearest, s->tour.size() - 1);
        // xoa nearest khoi danh sach
        danhsachNode.erase(nearest);
        //        s->display(instance);
        s->print();
        // cap nhat last
        last = nearest;
    }
}

void Solver::cheapestHeuristic(Solution *s) {
    unordered_set<int> danhsachNode;
    for (int i = 1; i < instance->num_nodes; ++i)
        danhsachNode.insert(i);

    while (!danhsachNode.empty()) {
        int bestNode = -1;
        int bestPosition = -1;
        double bestCost = 1e5;

        for (int node : danhsachNode) {
            for (int position = 1; position < s->tour.size(); ++position) {
                double cost_gain = getDistance(s->tour[position - 1], node) + getDistance(node, s->tour[position]) - getDistance(s->tour[position - 1], s->tour[position]);
                if (cost_gain < bestCost) {
                    bestNode = node;
                    bestPosition = position;
                    bestCost = cost_gain;
                }
            }
        }
        insertNode(s, bestNode, bestPosition);
        danhsachNode.erase(bestNode);
    }
}

void Solver::cheapestHeuristic_random(Solution *s) {
    vector<int> danhsachNode;
    for (int i = 1; i < instance->num_nodes; ++i)
        danhsachNode.push_back(i);
    Utils::shuffle(danhsachNode);

    for (int node : danhsachNode) {
        int bestPosition = -1;
        double bestCost = 1e5;
        for (int position = 1; position < s->tour.size(); ++position) {
            double cost_gain = getDistance(s->tour[position - 1], node) + getDistance(node, s->tour[position]) - getDistance(s->tour[position - 1], s->tour[position]);
            if (cost_gain < bestCost) {
                bestPosition = position;
                bestCost = cost_gain;
            }
        }
        insertNode(s, node, bestPosition);
    }
}

double Solver::getDistance(int i, int j) {
    return instance->getDistance(i, j);
}

int Solver::find_nearest(unordered_set<int> &danhsach, int i) {
    double bestDis = 999999;
    int nearest = -1;
    for (int node : danhsach) {
        double d = instance->getDistance(i, node);
        if (d < bestDis) {
            bestDis = d;
            nearest = node;
        }
    }
    return nearest;
}

void Solver::insertNode(Solution *s, int node, int position) {
    s->distance += instance->getDistance(s->tour[position - 1], node) + instance->getDistance(s->tour[position], node) - instance->getDistance(s->tour[position - 1], s->tour[position]);
    s->tour.insert(s->tour.begin() + position, node);
}
