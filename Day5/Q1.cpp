#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Step {
    std::string name, nextStep;
public:
    std::map<uint64_t, std::pair<uint64_t, uint64_t>> mp;
    Step(std::string name, std::string nextStep) : name(name), nextStep(nextStep) {}
    std::string getName() { return name; }
    std::string getNext() { return nextStep; }
    void addMapping(uint64_t dest, uint64_t src, uint64_t range) {
        mp[src] = std::make_pair(dest, range);
    }
    uint64_t getDestVal(uint64_t src) {
        auto x = mp.lower_bound(src);
        if (x == mp.begin()) return src;
        if (x->first != src)x--;
        if (x->first + x->second.second - 1 < src) return src;
        return x->second.first + src - x->first;
    }
};

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::unordered_map<std::string, Step*> stepMp;
    std::vector<uint64_t > seeds;
    uint64_t  temp, res = 1e9, src, dest, range;
    std::string name, nextStep;
    std::getline(file, line);
    line = line.substr(line.find(":") + 1, line.size() - line.find(":"));
    std::stringstream ss(line);
    while (ss >> temp) seeds.push_back(temp);
    getline(file, line);
    while (!file.eof()) {
        std::getline(file, line);
        temp = line.find("-");
        name = line.substr(0, temp);
        nextStep = line.substr(temp + 4, line.find(" ") - temp - 4);
        Step* step = new Step(name, nextStep);
        while (std::getline(file, line) && line != "") {
            sscanf(line.c_str(), "%lld %lld %lld", &dest, &src, &range);
            step->addMapping(dest, src, range);
        }
        stepMp[name] = step;
    }
    file.close();
    for (uint64_t& seed : seeds) {
        src = seed;
        Step* step = stepMp["seed"];
        while (step->getNext() != "location") {
            src = step->getDestVal(src);
            step = stepMp[step->getNext()];
        }
        src = step->getDestVal(src);
        res = std::min(res, src);
    }
    std::cout << res << std::endl;
    return 0;
}