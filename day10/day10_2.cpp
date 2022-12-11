#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>

struct cpu
{
    uint64_t num_cycles{1};

    struct instruction
    { 
        enum opcode { NOOP, ADDX } opcode{NOOP};
        int64_t remaining_cycles{0};
        int64_t immediate{0};
    } instruction;

    char line[41]{'\0'};

    struct registers
    {
        int64_t X{1};
    } registers;

    bool is_instruction_finished() const {
        return instruction.remaining_cycles == 0;
    }

    void run_cycle() {
        // Update the line
        int64_t pos = (num_cycles - 1) % 40;
        if (std::abs(pos - registers.X) <= 1) {
            line[pos] = '#';
        } else {
            line[pos] = '.';
        }

        if (!is_instruction_finished()) {
            instruction.remaining_cycles--;
        }
        if (instruction.opcode == instruction.ADDX && is_instruction_finished()) {
            registers.X += instruction.immediate;
        }
        num_cycles++;
    }

    int64_t get_signal_strength() const 
    {
        return registers.X * num_cycles;
    }

    bool is_interesting_cycle() const
    {
        return num_cycles >= 20 && num_cycles <= 220 && ((num_cycles - 20) % 40 == 0);
    }
} cpu;

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;

    while (std::getline(input, line)) {
        std::stringstream ss{line};
        char dummy[5];
        int64_t immediate;

        // Fetch and decode
        if (line[0] == 'n') {
            cpu.instruction.opcode           = cpu.instruction.NOOP;
            cpu.instruction.remaining_cycles = 1;
        } else if (line[0] == 'a') {
            ss.read(dummy, 5);
            ss >> immediate;
            cpu.instruction.opcode           = cpu.instruction.ADDX;
            cpu.instruction.immediate        = immediate;
            cpu.instruction.remaining_cycles = 2;
        }
        
        // Execute
        while (!cpu.is_instruction_finished()) {
            cpu.run_cycle();
            if (cpu.num_cycles > 1 && (cpu.num_cycles - 1) % 40 == 0) {
                std::cout << cpu.line << std::endl;
            }
        }
    }

    input.close();
    
    return 0;
}