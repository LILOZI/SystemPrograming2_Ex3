// @author: oz.atar@msmail.ariel.ac.il

#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <ios>
#include <set>
#include <utility>
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::set;
using std::pair;
using std::cin;
using std::make_pair;

#include <algorithm>

#include <ctime>

#include "Player.hpp"
#include "Land.hpp"
#include "cards/Card.hpp"
#include "LandVertex.hpp"
#include "LandEdge.hpp"

namespace catan
{

    #define POINTS_TO_WIN 10
    #define MAX_PLAYERS 3

    enum 
    {
        BRICK,
        WOOD,
        WHEAT,
        WOOL,
        IRON,
        DESERT
    };
    
    class Catan
    {

        private:
            int curPlayer;
            vector<Player*> players;
            vector<Land*> board;
            vector<pair<Card*, int>> devCardsDeck; // how many of each card are left in the deck -1 is unlimited, 0 is none
            // 0 = MONOPOLY, 1 = ROAD_BUILDING, 2 = YEAR_OF_PLENTY 3 = KNIGHT, 4 = VICTORY_POINT
            map<int, vector<Land*>> landNum; // "equivalence classes" of lands with the same number

        /**
         * @brief Initialize board and cards. 
        **/
        void init();

        /**
         * @brief Generate cards for the game.
        **/
        void initDevCards();

        /**
         * @brief Create the board.
        **/
        void initBoard();

        /** 
         * @brief Initialize random resources and numbers for lands..
        **/
        void initBoardResources();
        
        /** 
         * @brief Create the vertices of the board and save them in the Land objects.
        **/
        void createBoardVertices();

        /** 
         * @brief Create the edges of the board and save them in the Land objects.
        **/
        void createBoardEdges();

        /** 
         * @brief For each vertex and edge, set the adjacent vertices and edges. 
        **/
        void setVxsAndEdges();

        /**
         * @brief Get the number of the land.
        **/
        int getLandIndex(Land* land);

        public:
            Catan(Player &player1, Player &player2, Player &player3);
            
            // constructor for testing and demo, seed is constant
            Catan(Player &player1, Player &player2, Player &player3, uint seed);
            ~Catan();

            /** 
             * @brief Start the game.
             * @return The player that won the game. 
            **/
            Player* start();

            /** 
             * @brief Roll 2 fair dices, return the sum.
            **/
            int rollDice();

            /** 
             * @brief Distribute resources to players according to the dice sum.
            **/
            void distributeResources(int diceSum);

            /**
             * @brief Play the "0 - round".
            **/
            void playRound0();

            /**
             * @brief Let the current player play. 
            **/
            void playTurn();
            
            /** 
             * @brief Checks if a player has won. 
            **/
            Player* isGameOver();

            /** 
            * @brief Only for testing purposes.
            **/
            vector<Land*> getBoard() { return this->board; }

            /** 
            * @brief Only for testing purposes.
            **/
            vector<pair<Card*, int>> getDevCardsDeck() { return this->devCardsDeck; }   

            /** 
            * @brief et players vector.
            **/
            vector<Player*> getPlayers() {return this->players;};

            /**
             * @brief Manage trade offer that was sent from sender to receiver.
            **/
            int trade(Player* sender, Player *receiver, vector<int> giveResources, vector<int> recvResources, vector<int> giveCard, vector<int> recvCard);

            /** 
            * @brief Only for testing purposes.
            **/
            int placeSettlement(Player *player, size_t landNum,size_t vertexIndex, bool round0);
            
            /** 
            * @brief Only for testing purposes.
            **/
            int placeCity(Player *player, size_t landNum, size_t vertexIndex);

            /** 
            * @brief Checks if the player can place the road.
            * @return 0 if the player can place the road, -1 if there is a road there already, 
            **/
            int placeRoad(Player *player, size_t landNum, size_t edgeIndex);

            /** 
            * @brief Print the board.
            **/
            void displayBoard();

            /**
             * @brief Draw a random carf drom deck, update restrictions.
            **/
            Card* drawDevCard(Player* player);

            /**
             * @brief Take all resources of a certain type and give to player.
            **/
            void takeOthersResources(Player* player, int resourceType);

            /**
             * @brief Return the resource type as a string. 
            **/
            string intToResource(int resourceType);

            /**
             * @brief Print all players resources.
            **/
            void displayPlayersResources();

            /**
             * @brief 
            **/
            int buyDevCard(Player *player);

    };
}