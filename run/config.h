#ifndef CONFIG_H
#define CONFIG_H
#include <bits/stdc++.h>
using namespace std;

class Config {
   public:
    string input;
    bool found_input = false;

    double time_limit = 30.0;
    bool found_time_limit = false;

    int max_iter = 50000;
    bool found_max_iter = false;

    Config(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            string key = argv[i];

            if (key == "-i") {
                string value = argv[++i];
                input = value;
                found_input = true;
            }

            else if (key == "-t") {
                string value = argv[++i];
                time_limit = stof(value);
                found_time_limit = true;
            } else if (key == "-it") {
                string value = argv[++i];
                max_iter = stoi(value);
                found_max_iter = true;
            } else {
                cerr << "Invalid argument !!!\n";
                exit(0);
            }
        }

        if (!found_input) {
            cerr << "ERROR: Input is required !!!\n";
            exit(0);
        }

        if (!found_time_limit) {
            //	    cout << "Warning: time_limit default = 30.0s\n";
        }
        if (!found_max_iter) {
            cout << "Warning: max_iter default = 50,000 iterations\n";
        }
        cout << flush;
    }
};

#endif  // CONFIG_H
