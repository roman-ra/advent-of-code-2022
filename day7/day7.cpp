#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAX_DIR_SIZE 100000ULL

enum line_type { LINE_CMD_CD_ROOT, LINE_CMD_CD_PARENT, LINE_CMD_CD_DIR, LINE_CMD_LS, LINE_DIR, LINE_FILE };

inline line_type get_line_type(const std::string &line) {
    if (line[0] == '$') {
        if (line[2] == 'l') return LINE_CMD_LS;
        switch (line[5]) {
        case '/': return LINE_CMD_CD_ROOT; 
        case '.': return LINE_CMD_CD_PARENT;
        default: return LINE_CMD_CD_DIR;
        }
    } else if (line[0] == 'd') {
        return LINE_DIR;
    } else {
        return LINE_FILE;
    }
}

struct dir {
    dir(dir *parent): own_files_size(0), parent(parent) {}
    ~dir() {
        for (auto subdir: subdirs) {
            delete subdir;
        }
    }

    unsigned long long size() const {
        unsigned long long total = own_files_size;
        for (auto subdir: subdirs) {
            total += subdir->size();
        }
        return total;
    }

    void count_total_smaller_than(unsigned long long &sum,
                                  unsigned long long threshold) {
        unsigned long long own_size = size();
        if (own_size <= threshold) {
            sum += own_size;
        }
        for (auto subdir: subdirs) {
            subdir->count_total_smaller_than(sum, threshold);
        }
    }

    unsigned long long own_files_size;
    dir *parent;
    std::vector<dir*> subdirs;
};

int main(int argc, char *argv[])
{
    std::ifstream input("input.txt");
    std::string line;

    dir rootdir(nullptr);
    dir *current_dir = &rootdir;
   
    while (std::getline(input, line)) {
        std::stringstream ss{line};
        dir *new_subdir{nullptr};
        unsigned long long file_size{0};

        switch (get_line_type(line)) {
        case LINE_CMD_CD_ROOT:
            current_dir = &rootdir; break;
        case LINE_CMD_CD_PARENT:
            current_dir = current_dir->parent; break;
        case LINE_CMD_CD_DIR:
            new_subdir = new dir(current_dir);
            current_dir->subdirs.push_back(new_subdir);
            current_dir = new_subdir;
            break;
        case LINE_FILE:
            ss >> file_size;
            current_dir->own_files_size += file_size;
            break;
        default: break;
        }
    }

    unsigned long long sum{0};
    rootdir.count_total_smaller_than(sum, MAX_DIR_SIZE);
    std::cout << sum << std::endl;
   
    input.close();
    
    return 0;
}