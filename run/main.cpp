#include "config.h"
#include "instance_vrp.h"
#include "solver_vrp.h"
using namespace std;

int main(int argc, char* argv[]) {
    try {
        Config config(argc, argv);
        Instance_vrp instance(config.input, config.time_limit);
        Solver_VRP solver(&instance);
        solver.solve();

    } catch (const string& e) {
        std::cerr << "EXCEPTION | " << e << "\n";
    }

    return 0;
}
