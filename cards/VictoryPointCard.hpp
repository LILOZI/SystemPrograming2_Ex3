// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "Card.hpp"

namespace catan
{
    class VictoryPointCard : public catan::Card
    {
        public:
            VictoryPointCard() {};
            ~VictoryPointCard() {};
            VictoryPointCard(const VictoryPointCard &other) = default;

            CARDTYPE getType() const override;
            string getDescription() const override;
            Card* clone() override;
    };
}