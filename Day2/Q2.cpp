#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <tuple>
#include <algorithm>

std::tuple<long long, long long, long long> processMove(std::string move) {
    std::unordered_map<std::string, long long> cubeCnt;
    std::string color, temp;
    long long comma = move.find(","), cubes;
    while (comma != std::string::npos) {
        temp = move.substr(0, comma);
        move = move.substr(comma + 2, move.length() - comma - 2);
        comma = move.find(",");
        std::istringstream iss(temp);
        iss >> cubes >> color;
        cubeCnt[color] += cubes;
    }
    temp = move.substr(0, comma);
    std::istringstream iss(temp);
    iss >> cubes >> color;
    cubeCnt[color] += cubes;
    return std::make_tuple(cubeCnt["red"], cubeCnt["green"], cubeCnt["blue"]);
}

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file || !file.is_open()) {
        std::cout << "Unable to open file " << filename << "\n";
        return 0;
    }
    std::string line, set;
    long long r = 0, g = 0, b = 0;
    long long red, green, blue;
    long long res = 0, temp;
    while (std::getline(file, line)) {
        r = 0; g = 0; b = 0;
        temp = line.find(":");
        line = line.substr(temp + 2, line.length() - temp - 2);
        temp = line.find(";");
        while (temp != std::string::npos) {
            set = line.substr(0, temp);
            std::tie(red, green, blue) = processMove(set);
            r = std::max(r, red);
            g = std::max(g, green);
            b = std::max(b, blue);
            line = line.substr(temp + 2, line.length() - temp - 2);
            temp = line.find(";");
        }
        set = line.substr(0, temp);
        std::tie(red, green, blue) = processMove(line);
        r = std::max(r, red);
        g = std::max(g, green);
        b = std::max(b, blue);
        res += (r * g * b);
    }
    std::cout << res << "\n";
    return 0;
}