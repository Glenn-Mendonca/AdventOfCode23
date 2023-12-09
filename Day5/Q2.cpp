#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>

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
    uint64_t getDestVal(std::vector<std::pair<uint64_t, uint64_t>>& ranges, std::vector<std::pair<uint64_t, uint64_t>>& resRanges) {
        for (auto& x : ranges) {
            bool flag = false;
            for (auto y : mp) {
                if (x.second < y.first) {
                    resRanges.push_back({ x.first, x.second });
                    flag = true;
                    break;
                }
                if (x.first < y.first) {
                    resRanges.push_back({ x.first, y.first - 1 });
                    x.first = y.first;
                }
                if (x.second <= y.first + y.second.second - 1) {
                    resRanges.push_back({ y.second.first + x.first - y.first, y.second.first + x.second - y.first });
                    flag = true;
                    break;
                }
                if (x.second > y.first + y.second.second - 1 && x.first <= y.first + y.second.second - 1) {
                    resRanges.push_back({ y.second.first + x.first - y.first, y.second.first + y.second.second - 1 });
                    x.first = y.first + y.second.second;
                }
            }
            if (!flag) resRanges.push_back({ x.first, x.second });
        }
    }
};

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::unordered_map<std::string, Step*> stepMp;
    std::vector<uint64_t > seeds;
    uint64_t  temp, res = LLONG_MAX, src, dest, range;
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
    for (int indx = 0; indx < seeds.size(); indx += 2) {
        std::pair<uint64_t, uint64_t> range = { seeds[indx], seeds[indx] + seeds[indx + 1] - 1 };
        std::vector<std::pair<uint64_t, uint64_t>> ranges = { range }, resRanges;
        Step* step = stepMp["seed"];
        while (step->getNext() != "location") {
            step->getDestVal(ranges, resRanges);
            step = stepMp[step->getNext()];
            ranges = resRanges;
            resRanges.clear();
        }
        src = step->getDestVal(ranges, resRanges);
        for (auto x : resRanges) res = std::min(res, std::min(x.first, x.second));
    }
    std::cout << res << std::endl;
    return 0;
}