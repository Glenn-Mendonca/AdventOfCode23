#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>


int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line, winstr, cardstr;
    std::ifstream file(filename);
    long long res = 0, temp, matches = 0, id;
    std::map<int, long long> mp;
    if (!file || !file.is_open()) return -1;
    while (std::getline(file, line)) {
        matches = 0;
        std::set<long long> winNos;
        sscanf(line.c_str(), "Card %ld:", &id);
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
        mp[id] = (mp[id] == 0) ? 1 : mp[id];
        for (long long i = id + 1; i <= id + matches; i++) mp[i] = (mp[i] == 0) ? 1 + mp[id] : mp[i] + mp[id];
        res += mp[id];
    }
    std::cout << res << std::endl;
    file.close();
    return 0;
}