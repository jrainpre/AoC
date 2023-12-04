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
        bool executed = 0;
        int freq;
        int score;
        std::vector<int> win;
        std::vector<int> play;
        std::vector<int> parseNums(std::string &input, char start, char end);
        void getCardScore();
        
};

std::vector<Card> unfoldCards(std::vector<Card>& allCards)
{
    std::vector<Card> addCards;
    for (auto& card : allCards)
    {
        if (card.score > 0 && !card.executed)
        {
            int i = card.id + 1;
            while(i <= card.id + card.score)
            {
                for (auto& check_card : allCards)
                {
                    if (check_card.id == i)
                    {
                        Card newCard = check_card;
                        newCard.executed = false;
                        addCards.push_back(newCard);
                        break;
                    }
                }
                i++;
            }
        }
        card.executed = true;
    }
    return addCards;
}

bool checkCardsUnfolded(std::vector<Card>& allCard)
{
    for (auto& card : allCard)
    {
        if (!card.executed)
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
   std::vector<Card> cards;

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
        cards.push_back(card);
    }

    while(!checkCardsUnfolded(cards))
    {
        std::vector<Card> newCards = unfoldCards(cards);
        for (auto card: newCards)
            cards.push_back(card);
    }
    count = cards.size();

    

    std::cout << count << std::endl;



}


