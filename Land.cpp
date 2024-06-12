// @author oz.atar@msmail.ariel.ac.il

#include "Land.hpp"

catan::Land::Land()
{
    this->id = 0;
    this->resource = "";
}   

catan::Land::Land(int id) : id(id), resource(""), vertices(6), edges(5)
{
}



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
            this->resource = "SHEEP";
            break;
        case 4:
            this->resource = "IRON";
            break;
        case 5:
            this->resource = "DESERT";
            break;
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

string catan::Land::getLandSynbol() const {
    if (this->resource == "WOOD") {
        return "🌲";
    } else if (this->resource == "BRICK") {
        return "🧱";
    } else if (this->resource == "SHEEP") {
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
