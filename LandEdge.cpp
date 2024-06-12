// @author oz.atar@msmail.ariel.ac.il

#include "LandEdge.hpp"


catan::LandEdge::LandEdge()
{
    this->id = 0;
    this->owner = nullptr;
}

catan::LandEdge::LandEdge(int id) : id(id), owner(nullptr), adjEdges(4), vertices()
{
}

void catan::LandEdge::setVertices(LandVertex* vertex0, LandVertex* vertex1)
{
    this->vertices.first = vertex0;
    this->vertices.second = vertex1;
}


void catan::LandEdge::addAdjEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3)
{
    this->adjEdges[0] = edge0;
    this->adjEdges[1] = edge1;
    this->adjEdges[2] = edge2;
    this->adjEdges[3] = edge3;
}