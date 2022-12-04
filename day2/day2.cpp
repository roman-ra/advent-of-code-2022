#include <fstream>
#include <iostream>
#include <string>

const unsigned score_lut[3][3] = {{4,8,3}, {1,5,9}, {7,2,6}};

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    
    unsigned long long score = 0;

    while (std::getline(input, line)) {
        score += score_lut[line[0] - 'A'][line[2] - 'X'];
    }

    std::cout << score << std::endl;

    input.close();
    
    return 0;
}