// @author: oz.atar@msmail.ariel.ac.il

#include "MonopolyCard.hpp"

void catan::MonopolyCard::useCard(Catan *game, Player *player)
{
    cout << "You have just used a Monopoly Card" << endl;
    cout << "Choose what resource type you wish to take from all other players" << endl;
    cout << "1. Brick" << endl;
    cout << "2. Wood" << endl;
    cout << "3. Wheat" << endl;
    cout << "4. Wool" << endl;
    cout << "5. Iron" << endl;
    cout << "6. Display players resources" << endl;
    int res;
    while(true)
    {
        cin >> res;
        if (res == 6)
        {
            game->displayPlayersResources();
            continue;
        }
        if (res < 1 || res > 5)
        {
            cout << "Invalid choice" << endl;
            continue;
        }
        break;
    }
    game->takeOthersResources(player, res-1);
    cout << "Resources status after using Monopoly Card" << endl;
    game->displayPlayersResources();
}

catan::CARDTYPE catan::MonopolyCard::getType() const
{
    return MONOPOLY;
}

string catan::MonopolyCard::getDescription() const
{
    return "Monopoly Card, lets you take all the resources of a specific type from all other players.";
}

catan::Card* catan::MonopolyCard::clone()
{
    return new MonopolyCard(*this);
}