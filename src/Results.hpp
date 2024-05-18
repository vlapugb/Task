#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>

struct Data {
    std::vector<double> time;
    std::vector<double> vec;
};

struct Results {
    std::map<double, Data> RlC_map;
    void PrintUsersThroughput();
};

Results* RlC_counting(const std::string &RlC_namefile);

#endif // RESULTS_HPP