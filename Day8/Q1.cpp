#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::string dirs; char src[4], left[4], right[4];
    std::unordered_map<std::string, std::pair<std::string, std::string>> tree;
    std::unordered_map<std::string, short> visited;
    std::getline(file, dirs);
    std::getline(file, line);
    while (std::getline(file, line)) {
        sscanf(line.c_str(), "%3s = (%3s, %3s)", src, left, right);
        tree[std::string(src)] = std::make_pair(std::string(left), std::string(right));
    }
    std::string start = "AAA";
    uint64_t steps = 0;
    while (start != "ZZZ") {
        for (int i = 0; i < dirs.size(); i++) {
            if (start == "ZZZ") break;
            if (dirs[i] == 'L') start = tree[start].first;
            else if (dirs[i] == 'R') start = tree[start].second;
            steps++;
        }
    }
    std::cout << steps << std::endl;
    return 0;
}