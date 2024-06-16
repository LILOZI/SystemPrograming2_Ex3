// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "PromotionCard.hpp"

namespace catan
{
    class Catan;
    class MonopolyCard : public catan::PromotionCard
    {
        public:
            MonopolyCard() {};
            ~MonopolyCard() {};
            MonopolyCard(const MonopolyCard &other) = default;

            void useCard(Catan *game, Player *player) override;
            CARDTYPE getType() const override;
            string getDescription() const override;
            // virtual std::string icon() = 0;
            Card* clone() override;
    };
}