// #include "config.h"
#include "instance_vrp.h"
#include "solver_vrp.h"
using namespace std;

int main() {
    try {
        // Config config(argc, argv);
        Instance_vrp instance("../X/X-n101-k25.vrp");
        Solver_VRP solver(&instance);
        solver.solve();

    } catch (const string& e) {
        std::cerr << "EXCEPTION | " << e << "\n";
    }

    return 0;
}
