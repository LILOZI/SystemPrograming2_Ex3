// @author oz.atar@msmail.ariel.ac.il

#include "LandVertex.hpp"


catan::LandVertex::LandVertex(int id) : id(id), owner(nullptr), isSettlement(false), neighbors(3), incidentEdges(3)
{
    // cout << id << endl;
}

catan::LandVertex::~LandVertex()
{   
}

catan::LandVertex::LandVertex(const LandVertex& other)
{
    this->id = other.id;
    this->owner = other.owner;
    this->isSettlement = other.isSettlement;
    for(size_t i = 0; i < other.neighbors.size(); i++)
    {
        this->neighbors.push_back(other.neighbors[i]);
    }
    for(size_t i = 0; i < other.incidentEdges.size(); i++)
    {
        this->incidentEdges.push_back(other.incidentEdges[i]);
    }
}

catan::LandVertex& catan::LandVertex::operator=(const LandVertex& other)
{
    if(this == &other)
    {
        return *this;
    }
    this->id = other.id;
    this->owner = other.owner;
    this->isSettlement = other.isSettlement;
    // for(size_t i = 0; i < this->neighbors.size(); i++)
    // {
        // if(this->neighbors[i] != nullptr){delete this->neighbors[i];}
    // }
    // for(size_t i = 0; i < this->incidentEdges.size(); i++)
    // {
        // if(this->incidentEdges[i] != nullptr){delete this->incidentEdges[i];}
    // }
    this->neighbors.clear();
    this->incidentEdges.clear();
    for(size_t i = 0; i < other.neighbors.size(); i++)
    {
        this->neighbors.push_back(other.neighbors[i]);
    }
    for(size_t i = 0; i < other.incidentEdges.size(); i++)
    {
        this->incidentEdges.push_back(other.incidentEdges[i]);
    }
    return *this;
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

string catan::LandVertex::getConstructionSymbol() const
{

    if (this->owner == nullptr) {
        // empty vertex emoji
        return "E";
    }
    string col = this->owner->getColor();
    string rstCol = "\033[0m";
    string res = col;

    if (this->isSettlement) {
        res += "🏙" + rstCol;
    } else {
        res += "🏘" + rstCol;
    }

    return res;
}
