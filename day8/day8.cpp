#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline bool is_visible(unsigned tx, unsigned ty, const std::vector<std::string> &map)
{
    char height = map[ty][tx];
    // The tree is visible when it is visible from any of the four sides
    // From left
    bool visible = true;
    for (unsigned x = 0; x < tx && visible; x++) {
        if (map[ty][x] >= height) visible = false;
    }
    if (visible) return true;

    // From right
    visible = true;
    for (unsigned x = tx + 1; x < map[0].size() && visible; x++) {
        if (map[ty][x] >= height) visible = false;
    }
    if (visible) return true;
    
    // From above
    visible = true;
    for (unsigned y = 0; y < ty && visible; y++) {
        if (map[y][tx] >= height) visible = false;
    }
    if (visible) return true;

    // From below
    visible = true;
    for (unsigned y = ty + 1; y < map.size() && visible; y++) {
        if (map[y][tx] >= height) visible = false;
    }
    if (visible) return true;
    
    return false;
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
    unsigned long long num_visible = 2 * (map.size() + map[0].size()) - 4;

    for (unsigned y = 1; y < map.size() - 1; y++) {
        for (unsigned x = 1; x < map[0].size() - 1; x++) {
            num_visible += is_visible(x, y, map) ? 1 : 0;
        }
    }

    std::cout << num_visible << std::endl;

    input.close();
    
    return 0;
}