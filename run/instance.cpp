#include "instance.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

Instance::Instance(string instanceFile)
{
    read_input(instanceFile);
    initialize();
    cout << "Done loading !" << endl;
}

Instance::Instance(vector<vector<double>> dist_matrix,vector<double> x, vector<double> y ){
    num_nodes = dist_matrix.size();
    this->dist_matrix = dist_matrix;
}

void Instance::read_input(const string &inputFile)
{
    ifstream myFile(inputFile);
    if (!myFile.is_open())
    {
        cout << "Unable to open file \n";
        exit(0);
    }
    string line;
    num_nodes = 0;
    while (getline(myFile, line)){
        stringstream ss(line);
        int id;
        double xx, yy;
        ss >> id >> xx >> yy;
        x.push_back(xx);
        y.push_back(yy);
        num_nodes++;
    }
    myFile.close();
}

void Instance::initialize()
{
    dist_matrix.resize(num_nodes, {});
    // Compute distance matrix
    for (int i = 0; i < num_nodes; ++i){
        for (int j = 0 ; j < num_nodes; ++j){
            double d = sqrt( (x[i] - x[j])*(x[i] - x[j])  + (y[i] - y[j])*(y[i] - y[j]) );
            dist_matrix[i].push_back(d);
        }
    }
}

double Instance::getDistance(int i, int j)
{
    return dist_matrix[i][j];
}
