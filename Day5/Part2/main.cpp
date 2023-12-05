#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

class Card{
    public:
        int id;
        int to_execute = 0;
        int score;
        std::vector<int> win;
        std::vector<int> play;
        std::vector<int> parseNums(std::string &input, char start, char end);
        void getCardScore();
        
};

void unfoldCards(std::map<int, Card>& allCards, int& count, int max)
{
    for (auto& card : allCards)
    {
        if (card.second.score > 0 && card.second.to_execute > 0)
        {
            int i = card.second.id + 1;
            while(i <= card.second.id + card.second.score)
            {
                if (i <= max)
                {
                    if (allCards[i].score > 0)
                        allCards[i].to_execute++;
                    count++;
                }
                i++;
            }
            card.second.to_execute--;
        }
    }
}

bool checkCardsUnfolded(std::map<int, Card>& allCard)
{
    for (auto& card : allCard)
    {
        if (card.second.to_execute > 0)
            return false;
    }
    return true;
}

void Card::getCardScore()
{
    int count = 0;
    for (auto num : this->win)
    {
        if (std::find(this->play.begin(), this->play.end(), num) != this->play.end())
        {
            count++;
        }
    }
    this->score = count;
}

std::vector<int> Card::parseNums(std::string &input, char start, char end)
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




int main(int argc, char **argv)
{
   std::map<int, Card> cards;

    std::ifstream file("input.txt");
    if (!file.is_open())
        {   
        std::cerr << "Problem with open input file" << std::endl;
        exit(1);
        }
    std::string line;
    int count = 0;
    int id = 1;
    while (getline(file, line))
    {
        Card card;
        card.win = card.parseNums(line, ':', '|');
        card.play = card.parseNums(line, '|', '\n');
        card.getCardScore();
        card.id = id++;
        if (card.score > 0)
            card.to_execute = 1;
        cards[card.id] = card;
        count++;
    }
    int maxCards = count;

    while(!checkCardsUnfolded(cards))
    {
        unfoldCards(cards, count, maxCards);
    }

    

    std::cout << count << std::endl;



}


