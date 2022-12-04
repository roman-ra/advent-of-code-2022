#include <fstream>
#include <iostream>
#include <string>
#include <queue>

#define MAX_N 3

int main(int argc, char *argv[])
{
    std::ifstream input("input_2.txt");
    std::string line;
    
    std::priority_queue<unsigned long long, 
                        std::vector<unsigned long long>,
                        std::greater<unsigned long long>> max_calories;
    unsigned long long current_calories = 0;

    while (std::getline(input, line)) {
        if (line.length() == 0) {
            max_calories.push(current_calories);
            if (max_calories.size() == MAX_N + 1) max_calories.pop();
            current_calories = 0;
        } else {
            current_calories += std::stoull(line);
        }
    }

    max_calories.push(current_calories);
    if (max_calories.size() == MAX_N + 1) max_calories.pop();

    unsigned long long total_calories = 0;
    while(!max_calories.empty()) {
        total_calories += max_calories.top();
        max_calories.pop();
    }

    std::cout << total_calories << std::endl;

    input.close();
    
    return 0;
}