// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "Card.hpp"

namespace catan
{
    class KnightCard : public catan::Card
    {
        public:
            KnightCard();
            ~KnightCard();

            CARDTYPE getType();
            std::string getDescription();
    };
}