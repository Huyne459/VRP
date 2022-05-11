#include "solution.h"
// #include "gnuplot-iostream.h"
#include "instance.h"
#include <iostream>
#include <thread>
// #include <instance.h>

Solution::Solution()
{
    distance = 0;
    tour.reserve(200);
    tour = {0, 0};
}

Solution::Solution(const Solution &s)
{
    distance = s.distance;
    tour = s.tour;
}

Solution &Solution::operator =(const Solution &s)
{
    tour.clear();
    distance = s.distance;
    tour = s.tour;
    return *this;
}

double Solution::getDistance()
{
    return distance;
}

// void Solution::display(Instance *instance){
//     vector<double> x = instance->x;
//     vector<double> y = instance->y;
//     double result = distance;

//     gp << "set key outside\n"; // turn off legend altogether
//     gp << "set key box lt -1 lw 1\n";
//     gp << "set title 'Total cost = " << to_string(result) << "'\n";

//     // Scatter locations
//     vector<pair<double, double>> coor;
//     for (int i=1; i<x.size(); ++i){
//         coor.push_back(make_pair(x[i] , y[i] ));
//         gp << "set label '" << to_string(i) << "' at " << x[i] << "," << y[i] << " font 'arial,8'\n";
//     }
//     // Text
//     vector<int> label;
//     for (int i=0; i< instance->num_nodes; ++i){
//         label.push_back(i);
//     }
//     // route
//     vector<double> startx;
//     vector<double> starty;
//     vector<double> deltax;
//     vector<double> deltay;

//     for (int i = 0; i < tour.size() - 1; ++i){
//         startx.push_back(x[ tour[i] ]);
//         starty.push_back(y[ tour[i] ]);
//         deltax.push_back(x[ tour[i+1] ] - x[ tour[i] ]);
//         deltay.push_back(y[tour[i+1]] - y[tour[i]]);
//     }

//     gp << "plot '-' with points pointtype 7 lc 'brown' ps 0.4 title 'customer',"
// //       << "'-' with vector title 'drone' nohead lc 'gray',"
//        << "'-' with vector title 'truck' nohead lc 'blue'"
//        << std::endl;

//     gp.send1d(coor);
//     gp.send1d(boost::make_tuple(startx, starty, deltax, deltay));
//     gp.flush();
// //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// }

void Solution::print()
{
    for (int i : tour)
        cout << i << " ";
    cout << endl;
}
