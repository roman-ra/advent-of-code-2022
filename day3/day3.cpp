#include <fstream>
#include <iostream>
#include <string>
#include <bitset>

inline unsigned get_item_index(char item)
{
    if (item >= 'a') {
        return item - 'a';
    }
    return 26 + item - 'A';
}

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    
    unsigned long long total_priority = 0;

    std::bitset<52> is_in_compartment[2];

    while (std::getline(input, line)) {
        is_in_compartment[0].reset();
        is_in_compartment[1].reset();
        for (unsigned i = 0; i < line.length(); i++) {
            is_in_compartment[i < line.length() / 2 ? 0 : 1].set(get_item_index(line[i]), true);
        }
        // Find items of the same type that are in both compartments
        std::bitset<52> are_in_both = is_in_compartment[0] & is_in_compartment[1];
        for (unsigned i = 0; i < 52; i++) {
            if (are_in_both[i]) total_priority += (i + 1);
        }
    }

    std::cout << total_priority << std::endl;

    input.close();
    
    return 0;
}