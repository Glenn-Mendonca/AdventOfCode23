#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::unordered_map<char, int> charPriority = {
    {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 1}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}
};



class Compare {
public:
    bool operator()(std::pair<std::string, int> a, std::pair<std::string, int> b) {
        std::unordered_map<char, int> mp1, mp2;
        std::string a1, a2;
        for (int i = 0; i < 5; i++) {
            mp1[a.first[i]]++;
            mp2[b.first[i]]++;
        }
        for (auto x : mp1) {
            if (x.first == 'J') continue;
            a1.push_back(x.second + '0');
        }
        for (auto x : mp2) {
            if (x.first == 'J') continue;
            a2.push_back(x.second + '0');
        }
        a1.resize(5, '0'); a2.resize(5, '0');
        std::sort(a1.begin(), a1.end(), std::greater<int>());
        std::sort(a2.begin(), a2.end(), std::greater<int>());
        if (mp1['J']) a1[0] += mp1['J'];
        if (mp2['J']) a2[0] += mp2['J'];
        if (a1 != a2) return stoi(a1) > stoi(a2);
        for (int i = 0; i < 5; i++) {
            if (a.first[i] != b.first[i]) return charPriority[a.first[i]] > charPriority[b.first[i]];
        }
        return false;
    }
};

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line, cards;
    int bid, res = 0, cnt = 1;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, Compare> pq;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> cards >> bid;
        pq.push(std::make_pair(cards, bid));
    }
    while (!pq.empty()) {
        bid = pq.top().second;
        res += (bid * cnt++);
        pq.pop();
    }
    std::cout << res << "\n";
    return 0;
}