#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>

#define MAX_NUM_STACKS 9

// Width of a column, including a whitespace after it
#define COLUMN_WIDTH 4

// Checks if a line represents crates in stacks by looking for the symbol '['
inline bool is_line_for_crates(const std::string &line) {
    return line.find('[') != std::string::npos;
}

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    
    // Up to MAX_STACKS stacks are supported
    std::deque<char> stacks[MAX_NUM_STACKS];
    std::deque<char> crane;

    unsigned num_stacks = 0;

    bool stacks_are_parsed = false;

    while (std::getline(input, line)) {
        
        if (!stacks_are_parsed) {
            if (line.length() == 0) {
                // Encountered an empty line that separates initial stack states from actions
                stacks_are_parsed = true;
                continue;
            }

            if (is_line_for_crates(line)) {
                // If the line represents crates, then populate corresponding stacks with these crates
                // Column width is hardcoded
                for (unsigned i = 1; i < line.length(); i += COLUMN_WIDTH) {
                    if (line[i] != ' '){
                        stacks[i / COLUMN_WIDTH].push_back(line[i]);
                    }
                }
            } else {
                // If line lists stack numbers, count them and initialize num_stacks
                for (char c: line) {
                    if (c != ' ') num_stacks++;
                }
            }
        } else {
            // Parse and apply actions
            std::stringstream ss(line);

            unsigned num_moved = 0;
            unsigned stack_num = 0;

            char dummy[5];
            // read "move "
            ss.read(dummy, 5);
            ss >> num_moved;
            // read "from "
            ss.read(dummy, 5);
            ss >> stack_num; stack_num -= 1;
            // Remove num_moved crates from the stack stack_num
            for (unsigned i = 0; i < num_moved; i++) {
                crane.push_back(stacks[stack_num].front());
                stacks[stack_num].pop_front();
            }
            // read "to "
            ss.read(dummy, 3);
            ss >> stack_num; stack_num -= 1;
            // Add removed crates to the target stack
            while(!crane.empty()) {
                stacks[stack_num].push_front(crane.front());
                crane.pop_front();
            }
        }
    }

    for (unsigned i = 0; i < num_stacks; i++) {
        std::cout << stacks[i].front();
    }
    std::cout << std::endl;

    input.close();
    
    return 0;
}