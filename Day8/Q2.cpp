#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>


bool  didAllReach(std::vector<int64_t> src) {
    uint64_t reached = 0;
    for (auto x : src) reached += (x != -1) ? 1 : 0;
    return src.size() == reached;
}

int64_t lcm(int64_t a, int64_t b)
{
    return (a / std::__gcd(a, b)) * b;
}

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::string dirs; char src[4], left[4], right[4];
    std::unordered_map<std::string, std::pair<std::string, std::string>> tree;
    std::vector<std::string> start;
    std::getline(file, dirs);
    std::getline(file, line);
    while (std::getline(file, line)) {
        sscanf(line.c_str(), "%3s = (%3s, %3s)", src, left, right);
        tree[std::string(src)] = std::make_pair(std::string(left), std::string(right));
    }
    for (auto x : tree) if (x.first[2] == 'A') start.push_back(x.first);
    std::vector<int64_t> steps(start.size(), -1);
    int64_t step = 0;
    while (!didAllReach(steps)) {
        for (int i = 0; i < dirs.size(); i++) {
            if (didAllReach(steps)) break;
            for (int j = 0; j < start.size(); j++) {
                if (steps[j] != -1) continue;
                if (start[j][2] == 'Z') {
                    steps[j] = step;
                    continue;
                }
                if (dirs[i] == 'L') start[j] = tree[start[j]].first;
                else start[j] = tree[start[j]].second;
            }
            step++;
        }
    }
    step--;
    for (auto x : steps) {
        step = lcm(x, step);
    }
    std::cout << std::endl;
    std::cout << step << std::endl;
    return 0;
}