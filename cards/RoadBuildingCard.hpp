// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "PromotionCard.hpp"

namespace catan
{
    class RoadBuildingCard : public catan::PromotionCard
    {
        public:
            RoadBuildingCard(){};
            ~RoadBuildingCard(){};
            RoadBuildingCard(const RoadBuildingCard &other) = default;

            CARDTYPE getType() const override;
            string getDescription() const override;
            void useCard(Catan *game, Player *player) override;
            Card* clone() override;
    };
}