#include <string>
#include <fstream>
#include <iostream>
#include <sstream>




int main(int argc, char **argv)
{

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
        std::string first;
        std::string second;
        int indexfirst = 0;
        int indexlast = 0;
        indexfirst = line.find_first_of("1234567890");
        indexlast = line.find_last_of("1234567890");
        std::string result = "";
        result += line[indexfirst];
        result += line[indexlast];
        count += std::stoi(result);


    }

    std::cout << count << std::endl;




}


