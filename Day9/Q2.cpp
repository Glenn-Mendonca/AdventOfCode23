#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <stack>

int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    if (!file || !file.is_open()) return -1;
    long long res = 0, num;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<long long> nums;
        std::stack<std::vector<long long>> stk;
        while (ss >> num) nums.push_back(num);
        stk.push(nums);
        while (std::set<long long>(stk.top().begin(), stk.top().end()).size() != 1) {
            std::vector<long long> tmp;
            for (int i = 1; i < stk.top().size(); i++)
                tmp.push_back(stk.top()[i] - stk.top()[i - 1]);
            stk.push(tmp);
        }
        num = 0;
        while (!stk.empty()) {
            num = (stk.top()[0] - num);
            stk.pop();
        }
        res += num;
    }
    std::cout << res << std::endl;
    return 0;
}