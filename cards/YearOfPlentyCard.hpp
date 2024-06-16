// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "PromotionCard.hpp"

namespace catan
{
    class YearOfPlentyCard : public catan::PromotionCard
    {
        public:
            YearOfPlentyCard(){};
            ~YearOfPlentyCard(){};
            YearOfPlentyCard(const YearOfPlentyCard &other) = default;
            
            void useCard(Catan *game, Player *player) override;
            CARDTYPE getType() const override;
            string getDescription() const override;
            Card* clone() override;
    };
}