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

    std::bitset<52> is_in_rucksack[3];

    while (std::getline(input, line)) {
        for (unsigned elf = 0; elf < 3; elf++) {
            if (elf) { 
                std::getline(input, line);
            }
            is_in_rucksack[elf].reset();
            for (unsigned i = 0; i < line.length(); i++) {
                is_in_rucksack[elf].set(get_item_index(line[i]), true);
            }
        }
        // Find the item that is present in all 3
        std::bitset<52> in_all_3 = is_in_rucksack[0] & is_in_rucksack[1] & is_in_rucksack[2];
        for (unsigned i = 0; i < 52; i++) {
            if (in_all_3[i]) total_priority += (i + 1);
        }
    }

    std::cout << total_priority << std::endl;

    input.close();
    
    return 0;
}