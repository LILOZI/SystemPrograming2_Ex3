// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "Player.hpp"


#include <utility>
#include <vector>
#include <string>
using std::vector;
using std::pair;
using std::string;

#include <iostream>
using std::cout;
using std::endl;

namespace catan
{
    class LandEdge;
    class LandVertex
    {
        private:
            int id;
            vector<LandVertex*> neighbors;
            vector<LandEdge*> incidentEdges;
            Player* owner;
            bool isSettlement;

        public:
            LandVertex() {};
            ~LandVertex();

            LandVertex(const LandVertex& other);
            LandVertex(int id);

            LandVertex& operator=(const LandVertex& other);
            
            void clearNeighbors() { this->neighbors.clear();}; 
            void clearIncidentEdges() { this->incidentEdges.clear();};

            void addNeighbors(LandVertex* vertex0, LandVertex* vertex1, LandVertex* vertex2);
            void addIncidentEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2);
            void setOwner(Player* owner) { this->owner = owner; };
            void setSettlement(bool isSettlement) { this->isSettlement = isSettlement; };
            bool isSettlementf() { return this->isSettlement; };
            Player* getOwner() { return this->owner; };

            string getConstructionSymbol() const;

            /** 
             * @brief For testing purposes
            **/
            vector<LandVertex*> getNeighbors() { return this->neighbors; };

            int getId() { return this->id; };

            

    };
}