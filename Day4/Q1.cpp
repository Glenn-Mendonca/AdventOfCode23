#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>


int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line, winstr, cardstr;
    std::ifstream file(filename);
    long long res = 0, temp, matches;
    if (!file || !file.is_open()) return -1;
    while (std::getline(file, line)) {
        matches = 0;
        std::set<long long> winNos;
        temp = line.find(":");
        line = line.substr(temp + 1, line.size() - temp);
        temp = line.find("|");
        winstr = line.substr(0, temp);
        cardstr = line.substr(temp + 1, line.size() - temp);
        std::stringstream winss(winstr.c_str()), iss(cardstr.c_str());
        while (winss >> temp) winNos.insert(temp);
        while (iss >> temp) {
            if (winNos.find(temp) != winNos.end()) matches++;
        }
        if (matches > 0)
            res += (1 << (matches - 1));
    }
    std::cout << res << std::endl;
    return 0;
}