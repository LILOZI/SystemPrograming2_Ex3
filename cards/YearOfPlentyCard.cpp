// @author: oz.atar@msmail.ariel.ac.il

#include "YearOfPlentyCard.hpp"

void catan::YearOfPlentyCard::useCard(Catan *game, Player *player)
{
    cout << "You have just used a Year of Plenty card!" << endl;
    cout << "Please select two resources you wish to take from the bank:" << endl;
    cout << "1. Brick" << endl;
    cout << "2. Wood" << endl;
    cout << "3. Wheat" << endl;
    cout << "4. Wool" << endl;
    cout << "5. Iron" << endl;
    cout << "6. Display your resources" << endl;    
    int res;
    while(true)
    {
        cin >> res;
        if (res == 6)
        {
            player->displayResources();
            continue;
        }
        if (res < 1 || res > 5)
        {
            cout << "Invalid choice" << endl;
            continue;
        }
        break;
    }
    cout << "You have selected " << game->intToResource(res-1) << endl;
    player->addResource(res-1, 1);
    cout << "Please select another resource you wish to take from the bank:" << endl;
    while(true)
    {
        cin >> res;
        if (res == 6)
        {
            player->displayResources();
            continue;
        }
        if (res < 1 || res > 5)
        {
            cout << "Invalid choice" << endl;
            continue;
        }
        break;
    }
    cout << "You have selected " << game->intToResource(res-1) << endl;
    player->addResource(res-1, 1);
    cout << "Resources status after using Year of Plenty Card" << endl;
    player->displayResources();
}

std::string catan::YearOfPlentyCard::getDescription() const
{
    return "Take any two resources from the bank.";
}

catan::Card *catan::YearOfPlentyCard::clone()
{
    return new YearOfPlentyCard(*this);
}

catan::CARDTYPE catan::YearOfPlentyCard::getType() const
{
    return YEAR_OF_PLENTY;
}