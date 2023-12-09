#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line, time, distance;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    long long _time, _distance, res = 0;
    std::getline(file, line);
    std::stringstream ss(line);
    ss.ignore(line.size(), ':');
    while (ss >> _time) time += std::to_string(_time);
    std::getline(file, line);
    std::stringstream ss1(line);
    ss1.ignore(line.size(), ':');
    while (ss1 >> _distance) distance += std::to_string(_distance);
    _time = atoll(time.c_str());
    _distance = atoll(distance.c_str());
    for (; res <= _time; res++) {
        if (res * (_time - res) > _distance) break;
    }
    std::cout << (1 + _time - 2 * res) << std::endl;
    return 0;
}