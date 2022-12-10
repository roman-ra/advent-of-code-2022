#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

#define MAP_SIZE 1024U
#define NUM_KNOTS 10U

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

inline void step(int step_x, int step_y, 
                 int *knots_x, int *knots_y)
{
    // Move the head
    knots_x[0] += step_x;
    knots_y[0] += step_y;
    // Iteratively move the rest
    for (unsigned i = 1; i < NUM_KNOTS; i++) {
        int diff_x{knots_x[i - 1] - knots_x[i]}, diff_y{knots_y[i - 1] - knots_y[i]};
        if (diff_x * diff_x + diff_y * diff_y > 2) {
            knots_x[i] += sgn(diff_x);
            knots_y[i] += sgn(diff_y);
        }
    }
}

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;

    std::bitset<MAP_SIZE> map[MAP_SIZE]; 
    
    int knots_x[NUM_KNOTS], knots_y[NUM_KNOTS];
    for (unsigned i = 0; i < NUM_KNOTS; i++) {
        knots_x[i] = MAP_SIZE / 2;
        knots_y[i] = MAP_SIZE / 2;
    }

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

            step(step_x, step_y, knots_x, knots_y);

            map[knots_y[NUM_KNOTS - 1]].set(knots_x[NUM_KNOTS - 1], true);

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