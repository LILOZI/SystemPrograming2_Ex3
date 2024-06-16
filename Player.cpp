// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"

string catan::Player::getColor() const
{
    switch(this->color)
    {
        case RED:
            return "\033[1;31m";
        case BLUE:
            return "\033[1;34m";
        case GREEN:
            return "\033[1;32m";
        default:
            return "\033[1;37m";
    }
}

catan::Player::~Player()
{
}

int catan::Player::placeSettlement(Catan* game, bool round0)
{
    if(this->resources[0] < 1 && this->resources[1] < 1 && this->resources[2] < 1 && this->resources[3] < 1 && !round0)
    {
        // not enough resources to buy a settlement
        return -1;
    }

    while(true)
    {
        cout << "Enter 102 at any stage to leave this process." << endl;
        cout << "Enter the number of the land you want to place your settlement on: ";
        size_t landNum;
        cin >> landNum;
        if(landNum < 0 || landNum > 18)
        {
            if(landNum == 102)
            {
                if(round0)
                {
                    cout << "You must place a settlement on the first round." << endl;
                    continue;
                }
                cout << "Leaving settelment placement process." << endl;
                return -1;
            }
            cout << "Land number must be between 0 - 18, please try again." << endl;
            continue;
        }
        cout << "Enter the vertex index you want to place your settlement on: ";
        size_t vertexIndex;
        cin >> vertexIndex;
        if(vertexIndex < 0 || vertexIndex > 5)
        {
            if(vertexIndex == 102)
            {
                if(round0)
                {
                    cout << "You must place a settlement on the first round." << endl;
                    continue;
                }
                cout << "Leaving settelment placement process." << endl;
                return -1;
            }
            cout << "Vertex index must be between 0 - 5, please try again." << endl;
            continue;
        }
        cout << "can not change your mind anymore." << endl;
        int ans = game->placeSettlement(this, landNum, vertexIndex, round0);
        switch(ans)
        {
            case -1:
                cout << "Vertex already has a settlement, please try again." << endl;
                break;
            case -2:
                cout << "Vertex has a neighbor with a settlement, please try again." << endl;
                break;
            case -3:
                cout << "No road owned by you connects to this vertex, please try again." << endl;
                break;
            case 0:
                cout << "Settlement placed successfully." << endl;
                this->buySettlement(round0);
                return 0;
        }  
    }
    return -1;
}

int catan::Player::placeRoad(Catan* game, bool round0)
{
    if(this->resources[0] < 1 && this->resources[1] < 1 && !round0)
    {
        // not enough resources to buy a road
        return -1;
    }

    while(true)
    {
        cout << "Enter 102 at any stage to leave this process." << endl;
        cout << "Enter the number of the land you want to place your road on: ";
        size_t landNum;
        cin >> landNum;
        if(landNum < 0 || landNum > 71)
        {
            if(landNum == 102)
            {
                if(round0)
                {
                    cout << "You must place a road on the first round." << endl;
                    continue;
                }
                cout << "Leaving road placement process." << endl;
                return -1;
            }
            cout << "Land number must be between 0 -18, please try again." << endl;
            continue;
        }
        cout << "Enter the edge index you want to place your road on: ";
        size_t edgeIndex;
        cin >> edgeIndex;
        if(edgeIndex < 0 || edgeIndex > 5)
        {
            if(edgeIndex == 102)
            {
                if(round0)
                {
                    cout << "You must place a road on the first round." << endl;
                    continue;
                }
                cout << "Leaving road placement process." << endl;
                return -1;
            }
            cout << "Edge index must be between 0 - 5, please try again." << endl;
            continue;
        }
        cout << "can not change your mind anymore." << endl;
        int ans = game->placeRoad(this, landNum, edgeIndex);
        switch(ans)
        {
            case -1:
                cout << "Edge already has a road, please try again." << endl;
                break;
            case -2:
                cout << "Road must be connected to a settlement or a road owned by you, please try again." << endl;
                break;
            case 0:
                cout << "Road placed successfully." << endl;
                this->buyRoad(round0);
                return 0;
        }  
    }
    return -1;
}

int catan::Player::placeCity(Catan *game)
{
    if(this->resources[2] < 3 && this->resources[4] < 2)
    {
        // not enough resources to buy a city
        return -1;
    }

    while(true)
    {
        cout << "Enter 102 at any stage to leave this process." << endl;
        cout << "Enter the number of the land you want to place your city on: ";
        size_t landNum;
        cin >> landNum;
        if(landNum < 0 || landNum > 18)
        {
            if(landNum == 102)
            {
                cout << "Leaving city placement process." << endl;
                return -1;
            }
            cout << "Land number must be between 0 - 18, please try again." << endl;
            continue;
        }
        cout << "Enter the vertex index you want to place your city on: ";
        size_t vertexIndex;
        cin >> vertexIndex;
        if(vertexIndex < 0 || vertexIndex > 5)
        {
            if(vertexIndex == 102)
            {
                cout << "Leaving city placement process." << endl;
                return -1;
            }
            cout << "Vertex index must be between 0 - 5, please try again." << endl;
            continue;
        }
        cout << "can not change your mind anymore." << endl;
        int ans = game->placeCity(this, landNum, vertexIndex);
        switch(ans)
        {
            case -1:
                cout << "Vertex does not have a settlement, please try again." << endl;
                break;
            case -2:
                cout << "Vertex is owned by another player, please try again." << endl;
                break;
            case -3:
                cout << "Vertex already has a city, please try again." << endl;
                break;
            case 0:
                cout << "City placed successfully." << endl;
                this->buyCity();
                return 0;
        }  
    }
    return -1;

}

int catan::Player::getTotalResources() const
{
    int total = 0;
    for(size_t i = 0; i < 5; i++)
    {
        total += this->resources[i];
    }
    return total;
}

void catan::Player::displayResources() const
{
    cout << this->getName() << " Resources:" << endl;
    cout << "BRICK: " << this->resources[0] << endl;
    cout << "WOOD: " << this->resources[1] << endl;
    cout << "WHEAT: " << this->resources[2] << endl;
    cout << "WOOL: " << this->resources[3] << endl;
    cout << "IRON: " << this->resources[4] << endl;
}

string catan::Player::getName() const
{
    return this->getColor() + this->name + "\033[0m";
}

void catan::Player::discardResources(int resourceTotal)
{
    int toDiscard = resourceTotal / 2;
    while(toDiscard > 0)
    {
        cout << "You must discard " << toDiscard << " resources." << endl;
        cout << "0 = BRICK, 1 = WOOD, 2 = WHEAT, 3 = WOOL, 4 = IRON" << endl;
        cout << "Enter the number of the resource you want to discard: ";
        int resourceType;
        cin >> resourceType;
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Resource number must be between 0 - 4, please try again." << endl;
            continue;
        }
        cout << "Enter the amount of the resource you want to discard: ";
        int amount;
        cin >> amount;
        if(amount < 0 || amount > this->resources[resourceType])
        {
            cout << "Amount must be between 0 - " << this->resources[resourceType] << ", please try again." << endl;
            continue;
        }
        this->removeResource(resourceType, amount);
        toDiscard -= amount;
    }
}

void catan::Player::buySettlement(bool round0)
{
    this->addVictoryPoints(1);
    this->constructions[1]++;
    if(!round0)
    {
        this->removeResource(0, 1);
        this->removeResource(1, 1);
        this->removeResource(2, 1);
        this->removeResource(3, 1);
    
    }
}

void catan::Player::buyCity()
{
    this->addVictoryPoints(1);
    this->constructions[1]--;
    this->constructions[2]++;
    this->removeResource(2, 3);
    this->removeResource(4, 2);
}

void catan::Player::buyRoad(bool round0)
{
    this->constructions[0]++;
    if(!round0)
    {
        this->removeResource(0, 1);
        this->removeResource(1, 1);
    }
}

void catan::Player::playTurn(Catan *game)
{
    char op = 0;
    bool rolled = false;
    while(true)
    {
        cout << "Enter your move:"<< endl;
        cout << "   Press 1 to rool the dice." << endl;
        cout << "   Press 2 to use a development card." << endl;
        cout << "   Press C to display development cards." << endl;
        cout << "   Press R to display resources." << endl;
        cout << "   Press K to display knight cards." << endl;
        cout << "   Press V to display victory points." << endl;
        cin >> op;
        switch(op)
        {
            case '1':
                game->rollDice();
                rolled = true;
                break;
            case '2':
                // this->playDevCard();
               return;
            case 'C':
                // this->displayDevCards();
                break;
            case 'R':
                this->displayResources();
                break;
            case 'K':
                // this->displayKnightCards();
                break;
            case 'V':
                cout << "Victory Points: " << this->getVictoryPoints() << endl;
                break;
            default:
                cout << "You must first rool the dice or use a development card!" << endl;
        }
        if(rolled) {break;}
    }
    while(true)
    {
        cout << "Enter your move:"<< endl;
        cout << "   Press 1 to place a settlement." << endl;
        cout << "   Press 2 to place a city." << endl;
        cout << "   Press 3 to place a road." << endl;
        cout << "   Press 4 to buy a development card." << endl;
        cout << "   Press 5 to use a development card." << endl;
        cout << "   Press 6 to trade." << endl;
        cout << "   Press B to display board." << endl;
        cout << "   Press R to display resources." << endl;
        cout << "   Press V to display victory points." << endl;
        cin >> op;
        switch(op)
        {
            case '1':
                if(this->placeSettlement(game, false) == 0)
                {return;}
                break;
            case '2':
                if(this->placeCity(game) == 0)
                {return;}
                break;
            case '3':
                if(this->placeRoad(game, false) == 0)
                {return;}
                break;
            case '4':
                // this->buyDevCard();
                break;
            case '5':
                // this->playDevCard();
                break;
            case '6':
                // this->trade();
                break;
            case 'B':
                game->displayBoard();
                break;
            case 'R':
                this->displayResources();
                break;
            case 'V':
                cout << "Victory Points: " << this->getVictoryPoints() << endl;
                break;
            default:
                cout << "Invalid move, please try again." << endl;
        }
    }
}