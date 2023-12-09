#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <tuple>

int MAX_RED = 12, MAX_GREEN = 13, MAX_BLUE = 14;

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
    long long red, green, blue;
    long long idSum = 0, idx, temp;
    bool flag = false;
    while (std::getline(file, line)) {
        bool flag = false;
        sscanf(line.c_str(), "Game %lld: ", &idx);
        temp = line.find(":");
        line = line.substr(temp + 2, line.length() - temp - 2);
        temp = line.find(";");
        while (temp != std::string::npos) {
            set = line.substr(0, temp);
            std::tie(red, green, blue) = processMove(set);
            if (red > MAX_RED || green > MAX_GREEN || blue > MAX_BLUE) {
                flag = true;
                break;
            }
            line = line.substr(temp + 2, line.length() - temp - 2);
            temp = line.find(";");
        }
        if (flag) continue;
        set = line.substr(0, temp);
        std::tie(red, green, blue) = processMove(line);
        if (red > MAX_RED || green > MAX_GREEN || blue > MAX_BLUE)continue;
        else idSum += idx;
    }
    std::cout << idSum << "\n";
    return 0;
}