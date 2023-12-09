#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("./input.txt");
    std::string line;
    long long sum = 0;
    if (!file || !file.is_open()) return -1;
    while (std::getline(file, line)) {
        int low = 0, high = line.length();
        while (!isdigit(line[low])) low++;
        while (!isdigit(line[high])) high--;
        sum += ((line[low] - '0') * 10 + (line[high] - '0'));
    }
    std::cout << sum << "\n";
    return 0;
}