#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <cstdint>
#include <cmath>

#define ROUNDS 20
#define TOP_N  2

class monkey
{
public:
    struct monkey_operation
    {
        enum monkey_operation_type { MULTIPLY, ADD, SQUARE } type;
        int64_t parameter;

        int64_t operator()(int64_t value) const
        {
            switch(type) {
            case MULTIPLY:  return value * parameter;
            case ADD:       return value + parameter;
            case SQUARE:    return value * value;
            default:        return value;
            }
        }
    };

    monkey(monkey_operation operation, uint64_t test, 
           uint64_t pass_to_if_true, uint64_t pass_to_if_false,
           std::vector<int64_t> &starting_items): 
        operation(operation), test(test),
        pass_to_if_true(pass_to_if_true), pass_to_if_false(pass_to_if_false),
        num_inspected(0)
    {
        for (auto item: starting_items) {
            items.push(item);
        }
    }

    void add_item(uint64_t worry_level)
    { 
        items.push(worry_level);
    }

    void inspect_items(std::vector<monkey> &monkey_group)
    {
        if (items.size() == 0) return;

        while (!items.empty()) {
            int64_t worry_level = items.front();
            items.pop();
            num_inspected++;

            worry_level = operation(worry_level);

            worry_level = (int64_t) ((double)worry_level / 3.0);

            if (worry_level % test == 0) {
                monkey_group[pass_to_if_true].add_item(worry_level);
            } else {
                monkey_group[pass_to_if_false].add_item(worry_level);
            }
        }
    }

    uint64_t get_num_inspected() const { return num_inspected; }

private:
    monkey_operation     operation;
    uint64_t             test;
    uint64_t             pass_to_if_true;
    uint64_t             pass_to_if_false;

    uint64_t             num_inspected;
    std::queue<int64_t>  items;
};

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;
    char dummy[100];

    std::vector<monkey> monkey_group;

    // Parse first
    while (std::getline(input, line)) {
        std::vector<int64_t> items;
        monkey::monkey_operation operation;
        uint64_t test;
        uint64_t pass_to_if_true;
        uint64_t pass_to_if_false;

        // Starting items
        std::getline(input, line);
        std::stringstream ss(line); 
        ss.read(dummy, 18);
        while (ss.good()) {
            std::string item;
            std::getline(ss, item, ',');
            items.push_back(stoll(item));
        }
    
        // Operation
        std::getline(input, line);
        char op = line[23];
        if (line[25] == 'o') {
            operation.type = monkey::monkey_operation::SQUARE;
        } else {
            operation.parameter = stoll(line.substr(25));
            if (op == '+') {
                operation.type = monkey::monkey_operation::ADD;
            } else {
                operation.type = monkey::monkey_operation::MULTIPLY;
            }
        }

        // Test
        std::getline(input, line);
        test = stoull(line.substr(21));
        
        // If true
        std::getline(input, line);
        pass_to_if_true = stoull(line.substr(29));

        // If false
        std::getline(input, line);
        pass_to_if_false = stoull(line.substr(30));

        // Empty line
        std::getline(input, line);

        monkey_group.emplace_back(operation, test, 
                                  pass_to_if_true, pass_to_if_false, items);
    }

    // Simulate 20 rounds
    for (uint64_t i = 0; i < ROUNDS; i++) {
        for (auto &monkey: monkey_group) {
            monkey.inspect_items(monkey_group);
        }
    }

    // Find TOP_N highest numbers and calculate the monkey business
    std::priority_queue<uint64_t> nums_inspected;
    for (const auto &monkey: monkey_group) {
            nums_inspected.push(monkey.get_num_inspected());
    }
    uint64_t monkey_business = nums_inspected.top();
    nums_inspected.pop();
    for (uint64_t i = 1; i < TOP_N; i++) {
        monkey_business *= nums_inspected.top();
        nums_inspected.pop();
    }

    std::cout<<monkey_business<<std::endl;

    input.close();
    
    return 0;
}