// @author: oz.atar@msmail.ariel.ac.il

#include "RoadBuildingCard.hpp"

std::string catan::RoadBuildingCard::getDescription() const
{
    return "Road Building Card: Build 2 roads for free";
}

catan::CARDTYPE catan::RoadBuildingCard::getType() const
{
    return ROAD_BUILDING;
}

void catan::RoadBuildingCard::useCard(Catan *game, Player *player)
{
    // it is like round0 because the roads are free for the player
    cout << "You have just used a Road Building Card" << endl;
    player->placeRoad(game, true);
    player->placeRoad(game, true);
}

catan::Card* catan::RoadBuildingCard::clone()
{
    return new RoadBuildingCard(*this);
}