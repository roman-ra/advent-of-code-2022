#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    
    unsigned long long num_overlapping = 0;

    while (std::getline(input, line)) {
        std::stringstream ss(line);

        char dummy;
        unsigned start1, end1, start2, end2;
        
        ss >> start1 >> dummy >> end1 >> dummy >> start2 >> dummy >> end2;

        if (start1 <= end2 && start2 <= end1) {
            num_overlapping++;
        }
    }

    std::cout << num_overlapping << std::endl;

    input.close();
    
    return 0;
}