// @author oz.atar@msmail.ariel.ac.il

#pragma once

#include "Player.hpp"
#include "LandVertex.hpp"

#include <utility>
#include <vector>
#include <string>
using std::vector;
using std::pair;
using std::string;

namespace catan
{
    // class Player;
    class LandEdge
    {
        private:
            int id;
            pair<LandVertex*, LandVertex*> vertices;
            vector<LandEdge*> adjEdges;
            Player* owner;

            void setOwner(Player* owner) { this->owner = owner; };
        public:
            LandEdge();
            ~LandEdge();
            
            LandEdge(int id);

            /**
             * @brief Call these before destructor so it will not try to delete "dangling pointers".
            **/
            void clearAdjEdges() { this->adjEdges = vector<LandEdge*>(4);};
            /**
             * @brief Call these before destructor so it will not try to delete "dangling pointers".
            **/
            void clearVertices() { this->vertices = std::make_pair(nullptr, nullptr);};

            LandEdge(const LandEdge& other);
            LandEdge& operator=(const LandEdge& other);

            void setVertices(LandVertex* vertex0, LandVertex* vertex1);
            void addAdjEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3);
            
            Player* getOwner() { return this->owner; };

            void placeRoad(Player* player);

            int getId() { return this->id; };   

            bool roadValid(Player* player) const;

            /**
             * @brief Get color of player owning the edge / white if nobody owns it. 
            **/
            string getColor() const;

            /** 
             * @brief For testing purposes
            **/
            pair<LandVertex*, LandVertex*> getVertices() { return this->vertices; };
            /** 
             * @brief For testing purposes
            **/
           vector<LandEdge*> getAdjEdges() { return this->adjEdges; };

    };

}