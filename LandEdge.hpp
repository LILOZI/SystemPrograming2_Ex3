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
            

        public:
            LandEdge();
            ~LandEdge();
            Player* owner;
            LandEdge(int id);

            void clearAdjEdges() { this->adjEdges = vector<LandEdge*>(4);};
            void clearVertices() { this->vertices = std::make_pair(nullptr, nullptr);};

            LandEdge(const LandEdge& other);
            LandEdge& operator=(const LandEdge& other);

            void setVertices(LandVertex* vertex0, LandVertex* vertex1);
            void addAdjEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3);
            void setOwner(Player* owner) { this->owner = owner; };
            Player* getOwner() { return this->owner; };

            string getColor() const;
    };

}