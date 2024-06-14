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

void catan::Player::placeSettlement(bool isCity, size_t vertexId)
{
    if(isCity)
    {
        // this->constructions[1]--;
        this->victoryPoints += 2;
    }
    else
    {
        // this->constructions[0]--;
        this->victoryPoints++;
    }
}
