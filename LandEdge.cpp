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
}

void catan::LandEdge::placeRoad(Player* player)
{
    this->setOwner(player);
}

bool catan::LandEdge::roadValid(Player* player) const
{
    for(size_t i = 0; i < this->adjEdges.size(); i++)
    {
        if(this->adjEdges[i] != nullptr)
        {
            if(this->adjEdges[i]->getOwner() == player)
            {
                return true;
            }
        }
    }
    if(this->vertices.first->getOwner() == player || this->vertices.second->getOwner() == player)
    {
        return true;
    }
    return false;
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

