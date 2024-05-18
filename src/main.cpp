
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

    //checking address of pointer

    if (UL != nullptr) 
    {
        std::cout << "UL stats:" << std::endl;
        UL->PrintUsersThroughput();
        delete UL;  // delete pointer to free space
    }

    if (DL != nullptr) 
    {
        std::cout << "DL stats:" << std::endl;
        DL->PrintUsersThroughput();
        delete DL;  // delete pointer to free space
    }
    return 0;
}
