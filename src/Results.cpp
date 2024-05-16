#include "Results.hpp"
#include <fstream>
#include <numeric>
#include <cmath>
#include <sstream>
const double num = 1024;

Results* RlC_counting(const std::string &RlC_namefile)
{
    Results* ptr = new Results;  // Инициализация указателя на Results
    std::fstream RlC;
    std::string line;

    RlC.open(RlC_namefile, std::fstream::in);

    if (!RlC.is_open())
    {
        std::cerr << "Can't open RlC file: " << RlC_namefile << std::endl;
        return nullptr;
    }

    std::getline(RlC, line);

    while (std::getline(RlC, line))
    {
        std::istringstream iss(line);
        double current_key;
        std::string value;
        int columnIndex = 0;

        while (iss >> value)
        {
            if (columnIndex == 1)
            { 
                ptr->time_simulation_vector.push_back(std::stod(value));
            }
            else if (columnIndex == 3)
            {
                current_key = std::stod(value);
                if (ptr->RlC_map.find(current_key) == ptr->RlC_map.end())
                {
                    ptr->RlC_map[current_key] = std::vector<double>();
                }
            }
            else if (columnIndex == 9)
            {
                    double val = std::stod(value);
                    ptr->RlC_map[current_key].push_back(val);
            }

            columnIndex++;
        }
    }

    RlC.close();

    return ptr;
}

void Results::PrintUsersTroughput()
{
    double each_sum;
    double throughput;
    double SimulationTime = time_simulation_vector.back();

    for (const auto& iter : RlC_map)
    {
        const double& key = iter.first;
        const std::vector<double>& values = iter.second;

        // Вычисление суммы элементов vector<double> для текущего ключа
        each_sum = std::accumulate(values.begin(), values.end(), 0.0);
        throughput = SimulationTime == 0 ? 0 : each_sum / (SimulationTime * num);
        // Вывод ключа и суммы элементов
        std::cout << "USER ID: " << key << "\t" << "Throughput: " << throughput << " Kb/s" << std::endl;
    }
}