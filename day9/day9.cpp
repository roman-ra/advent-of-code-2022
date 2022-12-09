#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

#define MAP_SIZE 1024U

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

inline void step(int step_x, int step_y, 
                 int &head_x, int &head_y,
                 int &tail_x, int &tail_y)
{
    head_x += step_x;
    head_y += step_y;
    int diff_x{head_x - tail_x}, diff_y{head_y - tail_y};
    if (diff_x * diff_x + diff_y * diff_y > 2) {
        tail_x += sgn(diff_x);
        tail_y += sgn(diff_y);
    }
}

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;

    std::bitset<MAP_SIZE> map[MAP_SIZE]; 
    
    int head_x{MAP_SIZE / 2}, head_y{MAP_SIZE / 2};
    int tail_x{MAP_SIZE / 2}, tail_y{MAP_SIZE / 2};

    map[MAP_SIZE / 2].set(MAP_SIZE / 2, true);

    while (std::getline(input, line)) {
        std::stringstream ss{line};

        char direction;
        int steps;

        ss >> direction >> steps;

        while (steps > 0) {
            int step_x = 0;
            int step_y = 0;

            switch(direction) { 
            case 'L': step_x = -1; break;
            case 'R': step_x = 1; break;
            case 'D': step_y = -1; break;
            case 'U': step_y = 1; break;
            default: break;
            }

            step(step_x, step_y, head_x, head_y, tail_x, tail_y);

            map[tail_y].set(tail_x, true);

            steps--;
        }
    }

    unsigned long long total_visited{0};
    for (unsigned i = 0; i < MAP_SIZE; i++) {
        total_visited += map[i].count();
    }

    std::cout << total_visited << std::endl;

    input.close();
    
    return 0;
}