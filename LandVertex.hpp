// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <utility>
#include <vector>
using std::vector;
using std::pair;

class Player;
class LandEdge;

namespace catan
{

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
            ~LandVertex() {};

            LandVertex(int id);

            void addNeighbors(LandVertex* vertex0, LandVertex* vertex1, LandVertex* vertex2);
            void addIncidentEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2);
            void setOwner(Player* owner);
            void setSettlement(bool isSettlement);
            bool getSettlement() { return this->isSettlement; };
            Player* getOwner() { return this->owner; };

    };
}