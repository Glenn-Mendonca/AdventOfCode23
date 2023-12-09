#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int > words = {
    {"one", 1 },
    {"two",  2},
    {"three", 3 },
    {"four",  4},
    {"five",  5},
    {"six",  6},
    {"seven", 7 },
    {"eight",  8},
    {"nine", 9}
};

int main() {
    std::ifstream file("./input.txt");
    std::string line, word;
    long long sum = 0;
    if (!file || !file.is_open()) return -1;
    while (std::getline(file, line)) {
        int low = 0, high = line.length(), temp, lowVal, highVal, num;
        while (!isdigit(line[low])) low++;
        lowVal = line[low] - '0';
        while (!isdigit(line[high])) high--;
        highVal = line[high] - '0';
        for (std::pair<std::string, int> x : words) {
            word = x.first;
            num = x.second;
            temp = line.find(word);
            if (temp != std::string::npos && temp < low) {
                low = temp;
                lowVal = num;
            }
        }
        for (std::pair<std::string, int> x : words) {
            word = x.first;
            num = x.second;
            temp = line.rfind(word);
            if (temp != std::string::npos && temp > high) {
                high = temp;
                highVal = num;
            }
        }
        temp = (lowVal * 10 + highVal);
        sum += temp;
    }
    std::cout << sum << "\n";
    return 0;
}