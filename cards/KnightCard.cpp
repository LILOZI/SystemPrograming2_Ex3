// @author: oz.atar@msmail.ariel.ac.il

#include "KnightCard.hpp"

string catan::KnightCard::getDescription() const
{
    return "Knight Card - if you have 3 knights, you get 2 victory points.";
}

catan::CARDTYPE catan::KnightCard::getType() const
{
    return KNIGHT;
}

catan::Card *catan::KnightCard::clone()
{
    return new KnightCard(*this);
}

