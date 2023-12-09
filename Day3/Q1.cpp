#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> dirx = { -1, -1, -1, 0, 0, 1, 1, 1 };
std::vector<int> diry = { -1, 0, 1, -1, 1, -1, 0, 1 };

int getDig(std::vector<std::string>& lines, int x, int y) {
    std::string num = "";
    int ycpy = y;
    while (ycpy < lines[x].length() && isdigit(lines[x][ycpy])) {
        num += lines[x][ycpy];
        lines[x][ycpy++] = '.';
    }
    ycpy = y - 1;
    while (ycpy >= 0 && isdigit(lines[x][ycpy])) {
        num = lines[x][ycpy] + num;
        lines[x][ycpy--] = '.';
    }
    return std::stoi(num);
}


int main(int argc, char** argv) {
    if (argc < 2) return -2;
    std::string filename = argv[1], line;
    std::ifstream file(filename);
    std::vector<std::string> lines;
    long long res = 0;
    if (!file || !file.is_open()) {
        std::cout << "Unable to open file " << filename << "\n";
        return 0;
    }
    while (std::getline(file, line)) lines.push_back(line);
    file.close();
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '.' || isdigit(lines[i][j])) continue;
            for (int k = 0; k < 8; k++) {
                int x = i + dirx[k], y = j + diry[k];
                if (x < 0 || x >= lines.size() || y < 0 || y >= lines[i].size()) continue;
                if (isdigit(lines[x][y])) res += getDig(lines, x, y);
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}