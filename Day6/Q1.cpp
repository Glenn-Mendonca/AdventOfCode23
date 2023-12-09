#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    std::vector<long long> times, distances;
    long long temp, res = 1;
    std::getline(file, line);
    std::stringstream ss(line);
    ss.ignore(line.size(), ':');
    while (ss >> temp) times.push_back(temp);
    std::getline(file, line);
    std::stringstream ss1(line);
    ss1.ignore(line.size(), ':');
    while (ss1 >> temp) distances.push_back(temp);
    for (long long i = 0; i < times.size(); i++) {
        long long count = 0;
        for (; count <= times[i]; count++) {
            if (count * (times[i] - count) > distances[i]) break;
        }
        res *= (1 + times[i] - 2 * count);
    }
    std::cout << res << std::endl;
    return 0;
}