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

catan::LandEdge::~LandEdge()
{
    // this->adjEdges.clear();
    if(this->vertices.first != nullptr){delete this->vertices.first;}
    if(this->vertices.second != nullptr){delete this->vertices.second;}
    for(size_t i = 0; i < this->adjEdges.size(); i++)
    {
        if(this->adjEdges[i] != nullptr){delete this->adjEdges[i];}
    }
}

catan::LandEdge::LandEdge(const LandEdge& other)
{
    this->id = other.id;
    this->owner = other.owner;
    this->vertices.first = other.vertices.first;
    this->vertices.second = other.vertices.second;
    for(size_t i = 0; i < other.adjEdges.size(); i++)
    {
        this->adjEdges.push_back(other.adjEdges[i]);
    }
}

catan::LandEdge& catan::LandEdge::operator=(const LandEdge& other)
{
    if(this == &other)
    {
        return *this;
    }
    this->id = other.id;
    this->owner = other.owner;
    this->vertices.first = other.vertices.first;
    this->vertices.second = other.vertices.second;
    for(size_t i = 0; i < this->adjEdges.size(); i++)
    {
        if(this->adjEdges[i] != nullptr){delete this->adjEdges[i];}
    }
    for(size_t i = 0; i < other.adjEdges.size(); i++)
    {
        this->adjEdges.push_back(other.adjEdges[i]);
    }
    return *this;
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

string catan::LandEdge::getColor() const
{
    if(this->owner == nullptr)
    {
        return "\033[1;37m";
    }
    else
    {
        return this->owner->getColor();
    }
}

