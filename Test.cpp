// @author oz.atar@msmail.ariel.ac.il

#include "doctest.h"
#include "Catan.hpp"

TEST_CASE("Test right for Lands vertices")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {10, 9, 8, 11, 12, 13};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[2]->getVertex(i)->getId(), ans[i]);
    }
    ans = {4, 3, 17, 18, 19, 7};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[4]->getVertex(i)->getId(), ans[i]);
    }
    ans = {19, 18, 30, 31, 32, 20};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[9]->getVertex(i)->getId(), ans[i]);
    }
    ans = {28, 27, 38, 39, 40, 29};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[12]->getVertex(i)->getId(), ans[i]);
    }
    ans = {44, 43, 51, 52, 53, 45};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[18]->getVertex(i)->getId(), ans[i]);
    }
}

TEST_CASE("Test right for Lands edges")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {6, 4, 7, 8, 9, 10};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[1]->getEdge(i)->getId(), ans[i]);
    }
    ans = {13, 26, 27, 28, 29, 30};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[6]->getEdge(i)->getId(), ans[i]);
    }
    ans = {31, 32, 33, 34, 35, 18};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[7]->getEdge(i)->getId(), ans[i]);
    }
    ans = {40, 55, 56, 57, 58, 42};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[14]->getEdge(i)->getId(), ans[i]);
    }
    ans = {54, 65, 66, 67, 68, 56};
    for(size_t i = 0; i < 6; i++)
    {
        CHECK_EQ(game.getBoard()[17]->getEdge(i)->getId(), ans[i]);
    }
}

TEST_CASE("Test right id for vertetex neighbors")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {17, 30, 19};
    for(size_t i = 0; i < 3; i++)
    {
        CHECK_EQ(game.getBoard()[4]->getVertex(3)->getNeighbors()[i]->getId(), ans[i]);
    }
    ans = {29, 39, 41};
    for(size_t i = 0; i < 3; i++)
    {
        CHECK_EQ(game.getBoard()[12]->getVertex(4)->getNeighbors()[i]->getId(), ans[i]);
    }
    ans = {40, 49, 42};
    for(size_t i = 0; i < 3; i++)
    {
        CHECK_EQ(game.getBoard()[13]->getVertex(3)->getNeighbors()[i]->getId(), ans[i]);
        CHECK_EQ(game.getBoard()[17]->getVertex(1)->getNeighbors()[i]->getId(), ans[i]);
    }
    ans = {15, 2};
    CHECK_EQ(game.getBoard()[3]->getVertex(1)->getNeighbors()[0]->getId(), ans[0]);
    CHECK_EQ(game.getBoard()[3]->getVertex(1)->getNeighbors()[1]->getId(), ans[1]);
    CHECK_EQ(game.getBoard()[3]->getVertex(1)->getNeighbors()[2], nullptr);
}

TEST_CASE("Test right id for vertex incident edges")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {1, 16, 2};
    for(size_t i = 0; i < 3; i++)
    {
        CHECK_EQ(game.getBoard()[0]->getVertex(2)->getIncidentEdges()[i]->getId(), ans[i]);
    }
    ans = {39, 55, 40};
    for(size_t i = 0; i < 3; i++)
    {
        CHECK_EQ(game.getBoard()[9]->getVertex(3)->getIncidentEdges()[i]->getId(), ans[i]);
    }
    ans = {45, 61, 46};
    for(size_t i = 0; i < 3; i++)
    {
        CHECK_EQ(game.getBoard()[15]->getVertex(5)->getIncidentEdges()[i]->getId(), ans[i]);
    }
}

TEST_CASE("Test right id for edge's vertices")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {28, 16};
    CHECK_EQ(game.getBoard()[7]->getEdge(4)->getVertices().first->getId(), ans[0]);
    CHECK_EQ(game.getBoard()[7]->getEdge(4)->getVertices().second->getId(), ans[1]);
    ans = {32, 33};
    CHECK_EQ(game.getBoard()[10]->getEdge(2)->getVertices().first->getId(), ans[0]);
    CHECK_EQ(game.getBoard()[10]->getEdge(2)->getVertices().second->getId(), ans[1]);

}

TEST_CASE("Test right id for edge's adjacent edges")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {44, 43, 61, 46};
    for(size_t i = 0; i < 4; i++)
    {
        CHECK_EQ(game.getBoard()[11]->getEdge(2)->getAdjEdges()[i]->getId(), ans[i]);
    }
    ans = {17, 31, 35, 19};
    for(size_t i = 0; i < 4; i++)
    {
        CHECK_EQ(game.getBoard()[3]->getEdge(2)->getAdjEdges()[i]->getId(), ans[i]);
    }
    ans = {18, 35, 21, 20};
    for(size_t i = 0; i < 4; i++)
    {
        CHECK_EQ(game.getBoard()[3]->getEdge(3)->getAdjEdges()[i]->getId(), ans[i]);
    }
    ans = {12, 25, 27, 13};
    for(size_t i = 0; i < 4; i++)
    {
        CHECK_EQ(game.getBoard()[5]->getEdge(4)->getAdjEdges()[i]->getId(), ans[i]);
    }
    ans = {33, 31};
    for(size_t i = 0; i < 2; i++)
    {
        CHECK_EQ(game.getBoard()[7]->getEdge(1)->getAdjEdges()[i]->getId(), ans[i]);
    }
    CHECK_EQ(game.getBoard()[7]->getEdge(1)->getAdjEdges()[2], nullptr);
    CHECK_EQ(game.getBoard()[7]->getEdge(1)->getAdjEdges()[3], nullptr);
}

TEST_CASE("Receive resource after dice rolled")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3, 6);
    game.placeSettlement(&player1, 5, 0, true);
    game.placeRoad(&player1, 5, 0);
    game.placeSettlement(&player2, 8, 0, true);
    game.placeRoad(&player2, 8, 0);
    game.placeSettlement(&player3, 12, 0, true);
    game.placeRoad(&player3, 12, 0);
    
    
}

TEST_CASE("Settlement placement")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    game.placeSettlement(&player1, 0, 0, true);
    CHECK_EQ(game.getBoard()[0]->getVertex(0)->getOwner(), &player1);
    int ans = game.placeRoad(&player1, 7, 0);
    CHECK_EQ(ans, -2);
    game.placeRoad(&player1, 0, 0);
    ans = game.placeSettlement(&player2, 0, 1, true);
    CHECK_EQ(ans, -2);
    game.placeSettlement(&player2, 5, 2, true);
    ans = game.placeRoad(&player2, 0, 5);
    CHECK_EQ(ans, -2);
    game.placeRoad(&player2, 5, 1);
    CHECK_EQ(game.getBoard()[5]->getVertex(2)->getOwner(), &player2);
    CHECK_EQ(game.getBoard()[5]->getEdge(1)->getOwner(), &player2);
    CHECK_EQ(game.getBoard()[0]->getEdge(0)->getOwner(), &player1);
    CHECK(game.getBoard()[0]->getVertex(0)->isSettlementf());
    CHECK(game.getBoard()[5]->getVertex(2)->isSettlementf());
}