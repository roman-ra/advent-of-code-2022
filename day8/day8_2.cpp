#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline unsigned long long 
get_scenic_score(unsigned tx, unsigned ty, const std::vector<std::string> &map)
{
    char height = map[ty][tx];

    if (tx == 0 || ty == 0 || tx == map[0].size() - 1 || ty == map.size() - 1) return 0;

    // From left
    unsigned long long left = 0;
    for (int x = tx - 1; x >= 0; x--) {
        left++;
        if (map[ty][x] >= height) break;
    }

    // From right
    unsigned long long right = 0;
    for (int x = tx + 1; x < (int)map[0].size(); x++) {
        right++;
        if (map[ty][x] >= height) break;
    }

    // From above
    unsigned long long above = 0;
    for (int y = ty - 1; y >= 0; y--) {
        above++;
        if (map[y][tx] >= height) break;
    }

    // From below
    unsigned long long below = 0;
    for (int y = ty + 1; y < (int)map.size(); y++) {
        below++;
        if (map[y][tx] >= height) break;
    }

    return left * right * above * below;
}

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;

    std::vector<std::string> map;
   
    while (std::getline(input, line)) {
        map.push_back(line);
    }

    // Edge trees are always visible
    unsigned long long max_score = 0;

    for (unsigned y = 0; y < map.size(); y++) {
        for (unsigned x = 0; x < map[0].size(); x++) {
            unsigned long long score = get_scenic_score(x, y, map);
            if (score > max_score) {
                max_score = score;
            }
        }
    }

    std::cout << max_score << std::endl;

    input.close();
    
    return 0;
}