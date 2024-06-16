// @author: oz.atar@msmail.ariel.ac.il

#include "VictoryPointCard.hpp"

catan::CARDTYPE catan::VictoryPointCard::getType() const
{
    return VICTORY_POINT;
}

string catan::VictoryPointCard::getDescription() const
{
    return "Victory Point Card - gives you 1 victory point.";
}

catan::Card *catan::VictoryPointCard::clone()
{
    return new VictoryPointCard(*this);
}