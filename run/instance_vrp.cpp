#include "instance_vrp.h"

#include <bits/stdc++.h>

using namespace std;

Instance_vrp::Instance_vrp(std::string linkFileInstance_vrp, double time) {
    read_input(linkFileInstance_vrp);
    initialize();
    time_limit = time;
    cout << "Done loading !" << endl;
}

void Instance_vrp::read_input(const string &linkFileInstance_vrp) {
    ifstream myFile(linkFileInstance_vrp);
    if (!myFile.is_open()) {
        cout << "Unable to open file \n";
        exit(0);
    }
    string line;

    for (int i = 0; i < 4; i++) {
        getline(myFile, line);
    }

    stringstream s(line);
    string token;
    // getline(s, token, ':');
    // getline(s ,token, ':');
    // num_nodes = stoi(token);
    s >> token >> token;
    s >> demension;
    cout << "demension: " << demension << endl;

    getline(myFile, line);
    getline(myFile, line);

    stringstream s1(line);
    string token1;
    s1 >> token >> token;
    s1 >> capacity;
    std::cout << "capacity: " << capacity << endl;

    getline(myFile, line);

    for (int i = 0; i < demension; ++i) {
        int j;
        getline(myFile, line);
        stringstream ss(line);
        int id;
        double xx, yy;
        ss >> j >> xx >> yy;

        x.push_back(xx);
        y.push_back(yy);
    }
    getline(myFile, line);
    double summ = 0;
    for (int i = 0; i < demension; ++i) {
        int j;
        getline(myFile, line);
        stringstream s(line);
        double demandd;
        s >> j >> demandd;
        summ += demandd;
        demand.push_back(demandd);
    }

    // number_truck = ceil(summ / capacity);
    cout << "number_truck: ";
    cin >> number_truck;
    // so khach hang phuc vu max = sokhach/soxe + 2
    number_client = ceil((demension - 1) / number_truck) + 2;

    cout << "number_truck " << number_truck << endl;
    cout << "number_client " << number_client << endl;

    myFile.close();
}

void Instance_vrp::initialize() {
    dist_matrix.resize(demension, {});
    // Compute distance matrix
    for (int i = 0; i < demension; ++i) {
        for (int j = 0; j < demension; ++j) {
            double d = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            dist_matrix[i].push_back(d);
        }
    }
}

double Instance_vrp::getDistance(int i, int j) {
    return dist_matrix[i][j];
}
double Instance_vrp::getTimelimit() {
    return time_limit;
}

void Instance_vrp::show_position_custom() {
    std::cout << "Position:\nid: x - y - demand\n";
    for (int i = 0; i < x.size(); ++i) {
        std::cout << i << ": " << x[i] << " - " << y[i] << " - " << demand[i] << "\n";
    }
    std::cout << "================================\n";
}

// int main(int argc, char const *argv[]) {
//     Instance_vrp d = Instance_vrp("./X/X-n101-k25.vrp");
//     d.show_position_custom();
//     // cout << d.getDistance(0, 1) << "\n";
//     return 0;
// }
