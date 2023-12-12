#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

typedef long long ll;

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::vector<std::vector<char>> map;
    std::vector<ll> spacex, spacey;
    std::vector<std::pair<ll, ll>> galaxies;
    ll res = 0;
    while (std::getline(file, line)) {
        std::vector<char> row;
        for (char c : line) {
            if (c == '\n' || c == ' ') continue;
            row.push_back(c);
        }
        map.push_back(row);
    }
    spacex = std::vector<ll>(map.size(), 0);
    spacey = std::vector<ll>(map[0].size(), 0);
    for (ll i = 0; i < map.size(); i++) {
        std::set<char> row(map[i].begin(), map[i].end());
        if (row.size() == 1 && *row.begin() == '.') spacex[i] += (i > 0) ? spacex[i - 1] + 1 : 1;
        else spacex[i] += (i > 0) ? spacex[i - 1] : 0;
    }
    for (ll j = 0; j < map[0].size(); j++) {
        std::set<char> col;
        for (ll i = 0; i < map.size(); i++)
            col.insert(map[i][j]);
        if (col.size() == 1 && *col.begin() == '.') spacey[j] += (j > 0) ? spacey[j - 1] + 1 : 1;
        else spacey[j] += (j > 0) ? spacey[j - 1] : 0;
    }
    for (ll i = 0; i < spacex.size(); i++) {
        for (ll j = 0; j < spacey.size(); j++) {
            if (map[i][j] == '#')
                galaxies.push_back({ spacex[i] + i, spacey[j] + j });
        }
    }
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            if (!(galaxies[i].first == galaxies[j].first && galaxies[i].second == galaxies[j].second))
                res += (abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second));
        }
    }
    std::cout << res << std::endl;
    return 0;
}