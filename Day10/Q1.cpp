#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

typedef long long ll;
std::map<char, std::map<std::pair<ll, ll>, std::vector<char>>> dirs = {
    {'S', {{{0, 1}, {'7', 'J', '-'}},{{0, -1}, {'F', 'L', '-'}},{{1, 0}, {'J', 'L', '|'}},{{-1, 0}, {'F', '7', '|'}}}},
    {'F', {{{0, 1}, {'J', '7', '-'}},{{1, 0}, {'L', 'J', '|'}}}},
    {'L', {{{0, 1}, {'-', '7', 'J'}},{{-1, 0}, {'F', '7', '|'}}}},
    {'J', {{{0, -1}, {'-', 'L', 'F'}},{{-1, 0}, {'F', '|','7'}}}},
    {'7', {{{0, -1}, {'-', 'F', 'L'}},{{1, 0}, {'L', '|', 'J'}}}},
    {'|', {{{1, 0}, {'|','L', 'J'}},{{-1, 0}, {'F', '|','7'}}}},
    {'-', {{{0, 1}, {'-', 'J', '7'}},{{0, -1}, {'F', 'L', '-'}}}}
};

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    ll res = 0, x, y, xprev, yprev, distance;
    std::vector<std::vector<char>> map;
    std::vector<std::vector<ll>> visited;
    std::tuple<ll, ll, ll, ll> src;
    while (std::getline(file, line)) {
        std::vector<char> row;
        for (char c : line) {
            if (c == '\n' || c == ' ') continue;
            row.push_back(c);
            if (c == 'S')
                src = { map.size(),row.size() - 1, -1 , -1 };
        }
        map.push_back(row);
    }
    visited.resize(map.size(), std::vector<ll>(map[0].size(), 0));
    while (!visited[std::get<0>(src)][std::get<1>(src)]) {
        std::tie(x, y, xprev, yprev) = src;
        visited[x][y] = 1;
        res++;
        for (auto innermp : dirs[map[x][y]]) {
            auto dir = innermp.first;
            auto next = innermp.second;
            ll xnew = x + dir.first, ynew = y + dir.second;
            if (xnew < 0 || xnew >= map.size() || ynew < 0 || ynew >= map[0].size()) continue;
            if (xnew == xprev && ynew == yprev) continue;
            if (find(next.begin(), next.end(), map[xnew][ynew]) == next.end()) continue;
            src = { xnew, ynew, x, y };
        }
    }
    for (auto row : visited) {
        for (auto cell : row)
            std::cout << cell;
        std::cout << std::endl;
    }
    std::cout << res / 2 << std::endl;
    return 0;
}