// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include<utility>
#include <string>
#include <stdexcept>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Card;

namespace catan
{
    enum PLAYERCOLOR{
        RED,
        BLUE,
        GREEN
    };
    class Catan;

    class Player
    {
        private:
            string name;            
            int color;
            int victoryPoints;
            int resources[5]; // 0 = brick, 1 = wood, 2 = wheat, 3 = sheep, 4 = iron
            int constructions[3] = {0}; // 0 = road, 1 = settlement, 2 = city
            // vector<Card*> devCards;

        public:
            Player() {};
            Player(std::string name, int color) : name(name), color(color), 
            victoryPoints(0), resources{0}
            {};        
            ~Player();
            
            /**
             *@brief overloaded assignment operator 
            **/
            Player& operator=(const Player& other);

            void addVictoryPoints(int points) { this->victoryPoints += points; };

            int placeSettlement(Catan* gane, bool round0);

            int placeCity(Catan* game);

            void addResource(int resourceType, int amount) { this->resources[resourceType] += amount; };
            void removeResource(int resourceType, int amount) { this->resources[resourceType] -= amount;}
            /**
             * @brief Get the amount of a resource a player holds. 
            **/
            int getResource(int resourceType) { return this->resources[resourceType]; };
            void addDevCard(Card* card);
            void removeDevCard(Card* card);

            void buySettlement(bool round0);
            void buyCity();
            void buyRoad(bool round0);
            int placeRoad(Catan* game, bool round0);

            int getTotalResources() const;

            void playTurn(Catan *game);

            void discardResources(int resourceTotal);

            void displayResources() const;

            /**
             * @brief Get the amount of victory points a player holds.
             * @return the amount of victory points a player holds.
            **/
            int getVictoryPoints() 
            {
                if (this->name.empty()){ throw std::invalid_argument("Player not initialized");}
                return this->victoryPoints;
            }
            
            /** 
             * @brief Get the name of the player
            **/
            string getName() {
                if (this->name.empty()){throw std::invalid_argument("Player not initialized");}
                return this->name + this->getColor();}

            string getColor() const;

            bool operator==(const Player& other) const;
            bool operator!=(const Player& other) const;
    };
}