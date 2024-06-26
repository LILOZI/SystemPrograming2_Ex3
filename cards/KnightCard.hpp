// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "Card.hpp"


namespace catan
{
    class KnightCard : public catan::Card
    {
        public:
            KnightCard() {};
            ~KnightCard() {};
            KnightCard(const KnightCard &other) = default;

            CARDTYPE getType() const override;
            string getDescription() const override;
            Card* clone() override;
    };
}