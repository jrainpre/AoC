#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>


std::vector<int> parseNums(std::string &input, char start, char end)
{
    int number;
    std::vector<int> nums;
    size_t startpos = input.find_first_of(start) + 1;
    size_t endpos = input. find_first_of(end) - 1;
    std::string numstr = input.substr(startpos, endpos - startpos);
    std::istringstream numstokens(numstr);
    while (numstokens >> number)
        nums.push_back(number);
    return nums;
}

int getCardScore(std::vector<int> &win, std::vector<int> &player)
{
    int count = 0;
    for (auto num : win)
    {
        if (std::find(player.begin(), player.end(), num) != player.end())
        {
            if (count == 0)
                count = 1;
            else
                count *= 2;
        }
    }
    return count;
}




int main(int argc, char **argv)
{
    std::vector<int> winning_nums;
    std::vector<int> player_nums;

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
        winning_nums = parseNums(line, ':', '|');
        player_nums = parseNums(line, '|', '\n');
        count += getCardScore(winning_nums, player_nums);
    }
    

    std::cout << count << std::endl;



}


