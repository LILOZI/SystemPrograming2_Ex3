// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <vector>
#include <string>
using std::string;
using std::vector;

class LandVertex;
class LandEdge;


namespace catan
{
    class Land
    {
        private:
            int id;
            string resource;
            vector<LandVertex*> vertices;
            vector<LandEdge*> edges;
        
        public:
            Land();
            ~Land() {};

            Land(int id);

            void setResource(int resourceType);
            string getResource() const { return this->resource;};
            string getLandSynbol() const;
            LandVertex* getVertex(int index) const { return this->vertices[index]; };
            LandEdge* getEdge(int index) const { return this->edges[index]; };
            void setVertices(LandVertex* vertex0, LandVertex* vertex1, LandVertex* vertex2, LandVertex* vertex3, LandVertex* vertex4, LandVertex* vertex5);
            void setEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3, LandEdge* edge4, LandEdge* edge5);
    };
}