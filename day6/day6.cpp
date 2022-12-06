#include <fstream>
#include <iostream>
#include <string>

#define MARKER_LEN 4U

template<unsigned L>
bool is_a_marker(const char *current) {
    unsigned char_counts['z' - 'a' + 1] = { 0 };
    for (unsigned i = 0; i < L; i++) {
        char_counts[*(current - i) - 'a']++;
    }
    for (unsigned i = 0; i < 'z' - 'a' + 1; i++) {
        if (char_counts[i] > 1) return false;
    }
    return true;
}


int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    std::getline(input, line);

    for (unsigned i = MARKER_LEN - 1; i < line.length(); i++) {
        if (is_a_marker<MARKER_LEN>(line.c_str() + i)) {
            std::cout << i + 1 << std::endl;
            break;
        }        
    }


    input.close();
    
    return 0;
}