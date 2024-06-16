// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "Card.hpp"
#include "../Player.hpp"
#include "../Catan.hpp"

namespace catan
{
    class PromotionCard : public catan::Card
    {
        public:
            virtual void useCard(Catan *game, Player *player) = 0;
    };
}