#ifndef Solver_VRP_H
#define Solver_VRP_H
#include <unordered_set>

#include "instance_vrp.h"
#include "solution_vrp.h"

class Solver_VRP {
   public:
    double threshold;
    double cooling_rate;
    Instance_vrp *instance;
    Solution_vrp *bestSol;
    Solution_vrp *currentSol;
    Solver_VRP(Instance_vrp *instance);
    void solution_construction();
    void solve();
    void mutate(Solution_vrp *s);
    double getMaxDistanceTour();

    void local_search(Solution_vrp *s);
    void LS_swap(Solution_vrp *s, bool &improved);
    void LS_relocate(Solution_vrp *s, bool &improved);

    void check(Solution_vrp *s);

    // void nearestHeuristic(Solution *s);
};

#endif  // Solver_VRP_H
