#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    
    unsigned long long max_calories = 0;
    unsigned long long current_calories = 0;

    while (std::getline(input, line)) {
        if (line.length() == 0) {
            if (current_calories > max_calories) {
                max_calories = current_calories;
            }
            current_calories = 0;
        } else {
            current_calories += std::stoull(line);
        }
    }
    if (current_calories > max_calories) {
        max_calories = current_calories;
    }

    std::cout<<max_calories<<std::endl;

    input.close();
    
    return 0;
}