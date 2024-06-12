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

class Card;

namespace catan
{
    enum PLAYERCOLOR{
        RED,
        BLUE,
        GREEN
    };

    class Player
    {
        private:
            string name;            
            int color;
            int victoryPoints;
            int resources[5]; // 0 = brick, 1 = wood, 2 = wheat, 3 = sheep, 4 = iron
            // int constructions[3] = {0}; // 0 = road, 1 = settlement, 2 = city
            // vector<Card*> devCards;

        public:
            Player() {};
            Player(std::string name, int color) : name(name), color(color), 
            victoryPoints(0), resources{0}
            {};
            // Player(std::string name, int color)
            // {
            //     this->name = name;
            //     this->color = color;
            //     this->victoryPoints = 0;
            //     for (int i = 0; i < 5; i++)
            //         this->resources[i] = 0;
            // }
            
            ~Player() {};
            


            /**
             *@brief overloaded assignment operator 
            **/
            Player& operator=(const Player& other);

            void addResource(int resourceType, int amount);
            void removeResource(int resourceType, int amount);
            /**
             * @brief Get the amount of a resource a player holds. 
            **/
            int getResource(int resourceType);
            void addDevCard(Card* card);
            void removeDevCard(Card* card);

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
                return this->name;}



            bool operator==(const Player& other) const;
            bool operator!=(const Player& other) const;
    };
}