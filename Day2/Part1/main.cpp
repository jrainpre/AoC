#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>


// Game 1: 1 green, 4 blue; 1 blue, 2 green, 1 red; 1 red, 1 green, 2 blue; 1 green, 1 red; 1 green; 1 green, 1 blue, 1 red

#define RED 12
#define BLUE 14
#define GREEN 13


struct grab{
    std::string raw;
    std::map <std::string, int> cubes;
};


struct game{
    std::string raw;
    std::vector<grab> grabs;
};

std::string trimWhitespace(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

void seperateGrabs(game &game)
{
  size_t pos = game.raw.find(":");
  if (pos != std::string::npos)
    game.raw = game.raw.substr(pos + 1);
    std::string line = game.raw;
    while(pos != std::string::npos)
    {
        grab act;
        
        pos = line.find(";");
        if (pos != std::string::npos)
        {
            act.raw = trimWhitespace(line.substr(0, pos));
            game.grabs.push_back(act);
            line = line.substr(pos + 1);
        } else {
            act.raw = line;
            game.grabs.push_back(act);
            break;
        }
    }

}

void assignGrabs(game &game)
{
    for (auto& grab : game.grabs)
    {
        grab.cubes["green"] = 0;
        grab.cubes["red"] = 0;
        grab.cubes["blue"] = 0;

    std::string line = grab.raw;
    size_t pos = 1;
    while(pos != std::string::npos)
    {
        std::string cube_str;
        pos = line.find(",");
        if (pos != std::string::npos)
          cube_str = line.substr(0, pos);
        else
            cube_str = line;

    
            for (auto &cube : grab.cubes)
            {
                size_t pos1 = cube_str.find(cube.first);
                if (pos1 != std::string::npos)
                {
                    cube_str = cube_str.erase(pos1, cube.first.length());
                    cube.second += std::stoi(cube_str);
                    line = line.substr(pos + 1);
                    break;
                }
            }
            if (pos == std::string::npos)
                break;
      
        }
    }

}


bool checkGame(game game)
{
    for (auto grab : game.grabs)
    {
        if(grab.cubes["red"] > RED)
            return 0;
        if (grab.cubes["green"] > GREEN)
            return 0;
        if (grab.cubes["BLUE"] > BLUE)
            return 0;
    }
    return 1;
}

size_t countGrabs(std::vector<game> games)
{
    size_t count = 0;
    for (auto game : games)
    {
        for (auto grab : game.grabs)
            count++;
    }
    return count;
}

int main(int argc, char **argv)
{


    std::ifstream file("input.txt");
    if (!file.is_open())
        {   
        std::cerr << "Problem with open input file" << std::endl;
        exit(1);
        }

    std::vector<game> games;
    std::string line;
    int count = 0;
    while (getline(file, line))
    {
        game act_game;
        act_game.raw = line;

        seperateGrabs(act_game);
        assignGrabs(act_game);
        if (checkGame(act_game))
            games.push_back(act_game);
        continue;

    





    }
    count = countGrabs(games);
    std::cout << count << std::endl;




}


