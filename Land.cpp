// @author oz.atar@msmail.ariel.ac.il

#include "Land.hpp"
#include <iostream>
catan::Land::Land()
{
    this->id = 0;
    this->resource = "";
}   

catan::Land::Land(int id) : id(id), resource(""), vertices(6), edges(6)
{
}

catan::Land::~Land()
{
    for(size_t i = 0; i < this->vertices.size(); i++)
    {
        if(this->vertices[i] != nullptr)
        {
            this->vertices[i]->clearIncidentEdges();
            this->vertices[i]->clearNeighbors();
            delete this->vertices[i];
        }
    }
    for(size_t i = 0; i < this->edges.size(); i++)
    {
        if(this->edges[i] != nullptr)
        {   
            
            this->edges[i]->clearVertices();
            this->edges[i]->clearAdjEdges();
            delete this->edges[i];
        }
    }
};

void catan::Land::setResource(int resourceType)
{
    switch(resourceType)
    {
        case 0:
            this->resource = "BRICK";
            break;
        case 1:
            this->resource = "WOOD";
            break;
        case 2:
            this->resource = "WHEAT";
            break;
        case 3:
            this->resource = "WOOL";
            break;
        case 4:
            this->resource = "IRON";
            break;
        case 5:
            this->resource = "DESERT";
            break;
    }
    this->setVerticesResource(resourceType);
}

void catan::Land::setVerticesResource(int resourceType)
{
    for(size_t i = 0; i < this->vertices.size(); i++)
    {
        this->vertices[i]->setREsource(resourceType);
    }
}

void catan::Land::setVertices(LandVertex* vertex0, LandVertex* vertex1, LandVertex* vertex2, LandVertex* vertex3, LandVertex* vertex4, LandVertex* vertex5)
{
    this->vertices[0] = vertex0;
    this->vertices[1] = vertex1;
    this->vertices[2] = vertex2;
    this->vertices[3] = vertex3;
    this->vertices[4] = vertex4;
    this->vertices[5] = vertex5;
}

void catan::Land::setEdges(LandEdge* edge0, LandEdge* edge1, LandEdge* edge2, LandEdge* edge3, LandEdge* edge4, LandEdge* edge5)
{
    this->edges[0] = edge0;
    this->edges[1] = edge1;
    this->edges[2] = edge2;
    this->edges[3] = edge3;
    this->edges[4] = edge4;
    this->edges[5] = edge5;
}

string catan::Land::getLandSymbol() const {
    if (this->resource == "WOOD") {
        return "🌲";
    } else if (this->resource == "BRICK") {
        return "🧱";
    } else if (this->resource == "WOOL") {
        return "🐑";
    } else if (this->resource == "WHEAT") {
        return "🌾";
    } else if (this->resource == "IRON") {
        return "⛰️ ";
    } else if (this->resource == "DESERT") {
        return "🏜️";
    } else {
        return " ";
    }
}

size_t catan::Land::getResourceNum() const
{
    if(this->resource == "BRICK")
    {
        return 0;
    }
    else if(this->resource == "WOOD")
    {
        return 1;
    }
    else if(this->resource == "WHEAT")
    {
        return 2;
    }
    else if(this->resource == "WOOL")
    {
        return 3;
    }
    else if(this->resource == "IRON")
    {
        return 4;
    }
    else if(this->resource == "DESERT")
    {
        return 5;
    }
    return 6;
}