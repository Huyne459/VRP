#ifndef SOLVER_H
#define SOLVER_H
#include <unordered_set>

#include "instance.h"
#include "solution.h"

class Solver {
   public:
    double threshold;
    double cooling_rate;
    Instance *instance;
    Solution *bestSol;
    Solution *currentSol;
    Solver(Instance *instance);
    void solution_construction();
    void solve();
    void mutate(Solution *s);
    double getMinDistanceTour();

    void insertNode(Solution *s, int node, int position);
    void nearestHeuristic(Solution *s);
    void cheapestHeuristic(Solution *s);
    void cheapestHeuristic_random(Solution *s);
    int find_nearest(unordered_set<int> &danhsach, int i);

    double getDistance(int i, int j);
    void local_search(Solution *s);
    void LS_swap(Solution *s, bool &improved);
    void LS_relocate(Solution *s, bool &improved);
    void LS_two_opt(Solution *s, bool &improved);

    void swap_two_nodes(Solution *s, int pi, int pj, double delta);
    void reverse(Solution *s, int pi, int pj);
    void two_opt_nodes(Solution *s, int pi, int pj, double delta);

    void do_relocate(Solution *s, int nodePos, int newPos, double delta);
    void check(Solution *s);
};

#endif  // SOLVER_H
