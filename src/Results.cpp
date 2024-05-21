#include "Results.hpp"
#include <fstream>
#include <numeric>
#include <cmath>
#include <sstream>

const double NUM = 1024;

Results* RlC_counting(const std::string &RlC_namefile) {

    //initializing

    Results* ptr = new Results;  
    std::fstream RlC;
    std::string line;

    //checking for file availability

    RlC.open(RlC_namefile, std::fstream::in);

    if (!RlC.is_open()) {
        std::cerr << "Can't open RlC file: " << RlC_namefile << std::endl;
        return nullptr;
    }

    //skiping first row of file

    std::getline(RlC, line); 

    //going in columns

    while (std::getline(RlC, line)) {
        std::istringstream iss(line);

        double temp_time_first;
        double temp_time_second;
        double val;
        double current_key;
        int columnIndex = 0;
        std::string value;

        while (iss >> value) {

            //cheking columns for writing data in file

            if (columnIndex == 1) 
            {
                temp_time_second = std::stod(value);
            } 
            else if (columnIndex == 3) 
            {
                current_key = std::stod(value);
                if (ptr->RlC_map.find(current_key) == ptr->RlC_map.end()) {
                    ptr->RlC_map[current_key] = Data();
                }
            } 
            else if (columnIndex == 9) 
            {
                val = std::stod(value);
            }
            columnIndex++;
        }

        // push to hash-map our data from files

        ptr->RlC_map[current_key].time.push_back(temp_time_second);
        ptr->RlC_map[current_key].vec.push_back(val);

    }

    RlC.close();

    return ptr;
}

//outputing data

void Results::PrintUsersThroughput() {
    for (const auto& iter : RlC_map) {
        const double& key = iter.first;
        const Data& data = iter.second;
        double temp_sum_user = 0;
        double throughput_user;
        for(int i = 0; i < iter.second.time.size(); i++)
        {
            temp_sum_user+=iter.second.vec[i];
            throughput_user = temp_sum_user / (iter.second.time.back() * NUM);
        }

        std::cout << "USER ID: " << key << "\t" << "Throughput: " << throughput_user << " Kb/s" << std::endl;
    }
}
