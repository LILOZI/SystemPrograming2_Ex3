// @author: oz.atar@msmail.ariel.ac.il

#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <utility>
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::set;
using std::pair;

#include <algorithm>

#include <ctime>

#include "Player.hpp"
#include "Land.hpp"
#include "Card.hpp"
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
        SHEEP,
        IRON,
        DESERT
    };
    
    class Catan
    {

        private:
            int current_player;
            vector<Player*> players;
            vector<Land*> board;
            // vector<Card*> devCardsDeck;
            map<int, vector<Land*>> landNum; // "equivalence classes" of lands with the same number

        /**
         * @brief Initialize board and cards. 
        **/
        void init();

        void initDevCards();

        void initBoard();

        /** 
         * @brief Initialize random resources on the board.
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
         * @brief Roll 2 fair dices, return the sum.
        **/
        int rollDice();

        int getLandIndex(Land* land);

        public:
            Catan(Player &player1, Player &player2, Player &player3);
            // Catan();
            
            // copy constructor, assignment operator, destructor - rule of three
            // Catan(const Catan &other);
            ~Catan();
            // Catan& operator=(const Catan &other);

            /** 
             * @brief Start the game.
             * @return The player that won the game. 
            **/
            Player* start();

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

            bool placeSettlement(Player &player, size_t vertexNumber);
            bool placeCity(Player &player, size_t vertexNumber);
            bool placeRoad(Player &player, size_t edgeNumber);

            void displayBoard();

    };
}