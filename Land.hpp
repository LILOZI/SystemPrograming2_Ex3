// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include "LandVertex.hpp"
#include "LandEdge.hpp"

#include <vector>
#include <string>
using std::string;
using std::vector;



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
            ~Land();

            Land(const Land& other);
            Land(int id);

            Land& operator=(const Land& other);
            void setResource(int resourceType);
            string getResource() const { return this->resource;};
            string getLandSymbol() const;
            LandVertex* getVertex(size_t index) const { return this->vertices[index]; };
            LandEdge* getEdge(size_t index) const { return this->edges[index]; };
            void setVertices(LandVertex* vertex0, LandVertex* vertex1, LandVertex* vertex2, LandVertex* vertex3, LandVertex* vertex4, LandVertex* vertex5);
            void setEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3, LandEdge* edge4, LandEdge* edge5);
            size_t getResourceNum() const;
    };
}