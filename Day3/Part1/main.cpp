#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

bool charInSet(char ch) {
    std::vector<char> setOfChars = {'#', '/', '@', '$', '*', '+', '-', '=', '&', '%'};
    return std::find(setOfChars.begin(), setOfChars.end(), ch) != setOfChars.end();
}


std::pair<std::pair<int, int>, std::pair<int, int>> findNumber(const std::vector<char>& grid, std::pair<int, int> start, int grid_x, int grid_y) {
    std::pair<int, int> start_pos(-1, -1);
    std::pair<int, int> end_pos(-1, -1);
    bool has_started = false;


    for (int y = start.second; y < grid_y; ++y) {
        for (int x = start.first; x < grid_x; ++x) {
            char c = grid[y * grid_x + x];
            if (std::isdigit(c)) {
                if (!has_started) {
                    has_started = true;
                    start_pos = {x, y};
                }
                end_pos = {x, y};
            }
            else if(has_started){
                return {start_pos, end_pos};
            }
        }
        start.first = 0;
    }
    return {start_pos, end_pos};
}


bool check_neighbours(std::vector<char>& grid,  std::pair<std::pair<int, int>, std::pair<int, int>>& pos, int grid_x, int grid_y)
{
    std::vector<std::pair<int, int>> dir {{1,0}, {-1,0}, {0,1}, {0, -1}, {1,1}, {1, -1}, {-1, 1}, {-1, -1}};
    int y = pos.first.second;
    for (int x = pos.first.first; x <= pos.second.first; x++)
    {
        for (auto act_dir : dir)
        {
            int check_x = x + act_dir.first;
            int check_y = y + act_dir.second;

            if (check_x < 0 || check_y < 0 || check_x > grid_x || check_y > grid_y)
                continue;
            char to_check = grid[check_y * grid_x + check_x];
            if (charInSet(to_check))
                return true;
        }
    }
    return false;
}

int getNumber(std::vector<char>& grid,  std::pair<std::pair<int, int>, std::pair<int, int>>& pos, int grid_x)
{
    std::string num;
    for (int x = pos.first.first; x <= pos.second.first; x++){
        char to_add = grid[pos.first.second * grid_x + x];
        num.push_back(to_add);
    }
    return(std::stoi(num));
}

int main(int argc, char **argv)
{
    std::vector<char> grid;
    int grid_x = 0;
    int grid_y = 0;

    std::ifstream file("input.txt");
    if (!file.is_open())
        {   
        std::cerr << "Problem with open input file" << std::endl;
        exit(1);
        }
    std::string line;
    int count = 0;
    while (getline(file, line))
    {
        for (char c : line)
            grid.push_back(c);
        grid_x = line.length();
        grid_y++;
    }
    std::pair<int, int> start {0,0};
    while (start.first <= grid_x && start.second <= grid_y)
    {
        std::pair<std::pair<int, int>, std::pair<int, int>>  pos = findNumber(grid, start, grid_x, grid_y);
        if (pos.second.first == -1)
            break;

        if (check_neighbours(grid, pos, grid_x, grid_y))
        count += getNumber(grid, pos, grid_x);
        if (pos.second.first == grid_x)
            start = {0, pos.second.second +1};
        else
            start = {pos.second.first + 1, pos.second.second};

    }
    std::cout << count << std::endl;



}


