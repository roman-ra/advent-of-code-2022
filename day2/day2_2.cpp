#include <fstream>
#include <iostream>
#include <string>

const unsigned score_lut[3][3] = {{0 + 3, 3 + 1, 6 + 2},
                                  {0 + 1, 3 + 2, 6 + 3},
                                  {0 + 2, 3 + 3, 6 + 1}};

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