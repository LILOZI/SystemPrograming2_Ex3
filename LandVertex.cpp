// @author oz.atar@msmail.ariel.ac.il

#include "LandVertex.hpp"

catan::LandVertex::LandVertex(int id) : id(id), owner(nullptr), isSettlement(false), neighbors(3), incidentEdges(3)
{
}

void catan::LandVertex::addNeighbors(LandVertex* vertex0, LandVertex* vertex1, LandVertex* vertex2)
{
    this->neighbors[0] = vertex0;
    this->neighbors[1] = vertex1;
    this->neighbors[2] = vertex2;
}

void catan::LandVertex::addIncidentEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2)
{
    this->incidentEdges[0] = edge0;
    this->incidentEdges[1] = edge1;
    this->incidentEdges[2] = edge2;
}