#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>




std::string getNumber(int pos, std::string line, std::map<std::string, std::string> numbers)
{


    std::string result = "";
    for (const auto& number : numbers) 
    {
        int match = line.compare(pos, number.first.length(), number.first);
        if (match == 0)
        {
            result = number.second;
            break;
        }
    }
    if (result.empty())
        result = line[pos];
    return result;
}

int main(int argc, char **argv)
{

    std::map<std::string, std::string> numbers;
    numbers["zero"] = "0";
    numbers["one"] = "1";
    numbers["two"] = "2";
    numbers["three"] = "3";
    numbers["four"] = "4";
    numbers["five"] = "5";
    numbers["six"] = "6";
    numbers["seven"] = "7";
    numbers["eight"] = "8";
    numbers["nine"] = "9";

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

        for (const auto& number : numbers)
        {
            if (indexfirst == -1)
                indexfirst = 0;
            int pos = line.find(number.first);
            if (pos <= indexfirst && pos != -1)
                indexfirst = pos;
        }
        std::string resultfirst = getNumber(indexfirst, line, numbers);

         for (const auto& number : numbers)
        {
            if (indexlast == -1)
                indexlast = 0;
            int pos = line.rfind(number.first);
            if (pos >= indexlast && pos != -1)
                indexlast = pos;
        }
        std::string resultlast = getNumber(indexlast, line, numbers);

        std::string result;
        result += resultfirst;
        result += resultlast;


        count += std::stoi(result);


    }

    std::cout << count << std::endl;




}


