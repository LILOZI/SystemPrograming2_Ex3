// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "Player.hpp"
// #include "LandEdge.hpp"

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


            void setOwner(Player* owner) { this->owner = owner; };
            void setSettlement(bool isSettlement) { this->isSettlement = isSettlement; };
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
    
            bool isSettlementf() { return this->isSettlement; };
            Player* getOwner() { return this->owner; };

            string getConstructionSymbol() const;

            void placeSettlement(Player* player);

            void placeCity();

            /**
             * @brief Check if this vertex has no neighbors with settlements.
            **/
            bool settRadValid() const;

            bool settRoadValid(Player *player) const; 

            /** 
             * @brief For testing purposes
            **/
            vector<LandVertex*> getNeighbors() { return this->neighbors; };
            /** 
             * @brief For testing purposes
            **/
            vector<LandEdge*> getIncidentEdges() { return this->incidentEdges; };

            int getId() { return this->id; };

            

    };
}