#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>

// Структура Results
struct Results 
{
    std::map<double, std::vector<double>> RlC_map;
    std::vector<double> time_simulation_vector;

    void PrintUsersTroughput();
};
// Объявление функции RlC_counting
Results* RlC_counting(const std::string &RlC_namefile);

#endif // RESULTS_HPP