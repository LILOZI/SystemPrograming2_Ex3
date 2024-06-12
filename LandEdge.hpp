// @author oz.atar@msmail.ariel.ac.il

#pragma once

#include <utility>
#include <vector>
using std::vector;
using std::pair;

class LandVertex;
class Player;

namespace catan
{
    class LandEdge
    {
        private:
            int id;
            pair<LandVertex*, LandVertex*> vertices;
            vector<LandEdge*> adjEdges;
            Player* owner;

        public:
            LandEdge();
            ~LandEdge() {};

            LandEdge(int id);

            void setVertices(LandVertex* vertex0, LandVertex* vertex1);
            void addAdjEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3);
            void setOwner(Player* owner);
            Player* getOwner() { return this->owner; };
    };

}