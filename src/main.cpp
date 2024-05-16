
#include "Results.hpp"
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Incorrect CLI arguments, please write ULRlC.txt and DLRlC.txt" << std::endl;
        return 1;
    }

    std::string ULRlC_namefile = argv[1];
    std::string DLRlC_namefile = argv[2];

    Results* UL =  RlC_counting(ULRlC_namefile);
    Results* DL = RlC_counting(DLRlC_namefile);

    if (UL != nullptr) {
        std::cout << "UL stats:" << std::endl;
        UL->PrintUsersTroughput();
        delete UL;  // Освобождение памяти
    }

    if (DL != nullptr) {
        std::cout << "DL stats:" << std::endl;
        DL->PrintUsersTroughput();
        delete DL;  // Освобождение памяти
    }
    return 0;
}
