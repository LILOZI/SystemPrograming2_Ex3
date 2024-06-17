// @author oz.atar@msmail.ariel.ac.il

#include "doctest.h"
#include "Catan.hpp"
#include "cards/MonopolyCard.hpp"
#include "cards/RoadBuildingCard.hpp"
#include "cards/YearOfPlentyCard.hpp"
#include "cards/KnightCard.hpp"
#include "cards/VictoryPointCard.hpp"

#include <sstream>

std::streambuf* orig = std::cout.rdbuf(); 

void suppressOutput()
{
    std::cout.rdbuf(NULL);
}

void restoreOutput()
{
    std::cout.rdbuf(orig);
}

TEST_CASE("Test right id for Lands vertices")
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
    suppressOutput();
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3, 6);
    game.placeSettlement(&player1, 5, 0, true);
    game.placeRoad(&player1, 5, 0);
    game.placeSettlement(&player1, 16, 0, true);
    game.placeRoad(&player1, 16, 0);
    game.placeSettlement(&player2, 8, 0, true);
    game.placeRoad(&player2, 8, 0);
    game.placeSettlement(&player2, 7, 3, true);
    game.placeRoad(&player2, 7, 2);
    game.placeSettlement(&player3, 6, 3, true);
    game.placeRoad(&player3, 6, 4);
    game.placeSettlement(&player3, 5, 3, true);
    game.placeRoad(&player3, 5, 2);
    vector<int> v1  = {1, 0, 1 , 1, 1};
    vector<int> v2  = {1, 1, 0 , 1, 1};
    vector<int> v3  = {1, 0, 0 , 1, 1};
    restoreOutput();
    for(size_t i = 0; i < 5; i++)
    {
        CHECK_EQ(player1.getResource(i), v1[i]);
        CHECK_EQ(player2.getResource(i), v2[i]);
        CHECK_EQ(player3.getResource(i), v3[i]);
    }
    suppressOutput();
    for(size_t i = 0; i < 10; i++)
    {
       game.rollDice();
    }
    restoreOutput();
    v1  = {2, 0, 2 , 1, 2};
    v2 = {2, 1, 0 , 3, 2};
    v3 = {1, 0, 0 , 1, 1};
    for(size_t i = 0; i < 5; i++)
    {
        CHECK_EQ(player1.getResource(i), v1[i]);
        CHECK_EQ(player2.getResource(i), v2[i]);
        CHECK_EQ(player3.getResource(i), v3[i]);
    }

}

TEST_CASE("Dice roll equal 7")
{
    suppressOutput();
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3, 6);
    game.placeSettlement(&player1, 5, 0, true);
    game.placeRoad(&player1, 5, 0);
    game.placeSettlement(&player1, 16, 0, true);
    game.placeRoad(&player1, 16, 0);
    game.placeSettlement(&player2, 8, 0, true);
    game.placeRoad(&player2, 8, 0);
    game.placeSettlement(&player2, 7, 3, true);
    game.placeRoad(&player2, 7, 2);
    game.placeSettlement(&player3, 6, 3, true);
    game.placeRoad(&player3, 6, 4);
    game.placeSettlement(&player3, 5, 3, true);
    game.placeRoad(&player3, 5, 2);
    vector<int> v1  = {4, 0, 4, 2, 2};
    vector<int> v2  = {5, 1, 0 , 5, 2};
    vector<int> v3  = {2, 0, 0 , 3, 1};
    for(size_t i = 0; i < 18; i++)
    {
        game.rollDice();
    }
    restoreOutput();
    for(size_t i = 0; i < 5; i++)
    {
        CHECK_EQ(player1.getResource(i), v1[i]);
        CHECK_EQ(player2.getResource(i), v2[i]);
        CHECK_EQ(player3.getResource(i), v3[i]);
    }
    std::streambuf* orig = cin.rdbuf();
    // 7 is to much so it will ask again , 5 again will be to much so it will ask again
    std::istringstream input("0\n7\n0\n4\n4\n2\n0\n5\n3\n5\n1\n1");
    cin.rdbuf(input.rdbuf());
    suppressOutput();
    game.rollDice();
    restoreOutput();
    cin.rdbuf(orig);
    v1 = {0, 0, 4, 2, 0};
    v2  = {0, 0, 0 , 5, 2};
    v3  = {2, 0, 0 , 3, 1};
    for(size_t i = 0; i < 5; i++)
    {
        CHECK_EQ(player1.getResource(i), v1[i]);
        CHECK_EQ(player2.getResource(i), v2[i]);
        CHECK_EQ(player3.getResource(i), v3[i]);
    }
    
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
    SUBCASE("Bring resources in first round")
    {   
        int resourceType = game.getBoard()[0]->getResourceNum();
        if(resourceType != catan::DESERT)
        {CHECK_EQ(player1.getResource(resourceType), 1);}
        else{CHECK_EQ(player1.getResource(catan::DESERT), 0);}
        resourceType = game.getBoard()[5]->getResourceNum();
        if(resourceType != catan::DESERT)
        {CHECK_EQ(player2.getResource(resourceType), 1);} 
        else{CHECK_EQ(player2.getResource(catan::DESERT), 0);}
        resourceType = game.getBoard()[4]->getResourceNum();
        if(resourceType != catan::DESERT)
        {CHECK_EQ(player2.getResource(resourceType), 1);} 
        else{CHECK_EQ(player2.getResource(catan::DESERT), 0);}
        resourceType = game.getBoard()[9]->getResourceNum();
        if(resourceType != catan::DESERT)
        {CHECK_EQ(player2.getResource(resourceType), 1);} 
        else{CHECK_EQ(player2.getResource(catan::DESERT), 0);}
    }
}

TEST_CASE("Road placement")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    game.placeSettlement(&player1, 9, 1, true);
    game.placeRoad(&player1, 9, 0);
    game.placeSettlement(&player2, 9, 3, true);
    game.placeRoad(&player2, 9, 2);
    CHECK_EQ(game.getBoard()[9]->getEdge(2)->getOwner(), &player2);
    game.placeRoad(&player2, 9, 1);
    CHECK_EQ(game.getBoard()[9]->getEdge(1)->getOwner(), &player2);

}

TEST_CASE("City placement")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    game.placeSettlement(&player1, 9, 1, true);
    game.placeSettlement(&player2, 9, 3, true);
    SUBCASE("City placement on a settlement that is not owned by the player")
    {   
        game.placeCity(&player1, 9, 1);
        CHECK_EQ(game.getBoard()[9]->getVertex(1)->getOwner(), &player1);
        CHECK_FALSE(game.getBoard()[9]->getVertex(1)->isSettlementf());
    } 
    int ans = 0;
    SUBCASE("City placement on a settlement that is not owned by the player")
    {
        ans = game.placeCity(&player2, 9, 1);
        CHECK_EQ(ans, -2);
    }
    SUBCASE("City placement on a vertex that is already a city owned by the player")
    {   
        //place the city for the first time, legitimate placement
        game.placeCity(&player1, 9, 1);
        // try to place it again
        ans = game.placeCity(&player1, 9, 1);
        CHECK_EQ(ans, -3);
    }
    
    // again a legitimate city placement
    game.placeCity(&player2, 9, 3);
    CHECK_EQ(game.getBoard()[9]->getVertex(3)->getOwner(), &player2);
    CHECK_FALSE(game.getBoard()[9]->getVertex(3)->isSettlementf());
    SUBCASE("Player has not enough resources to buy a city")
    {
        ans = player1.placeCity(&game);
        CHECK_EQ(ans, -1);
    }
}

TEST_CASE("Cards initialization")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<pair<catan::Card*, int>> deck = game.getDevCardsDeck();
    SUBCASE("Test right amount in deck and order")
    {
        CHECK_EQ(deck[0].first->getType(), catan::MONOPOLY);
        CHECK_EQ(deck[0].second, -1);
        CHECK_EQ(deck[1].first->getType(), catan::ROAD_BUILDING);
        CHECK_EQ(deck[1].second, -1);
        CHECK_EQ(deck[2].first->getType(), catan::YEAR_OF_PLENTY);
        CHECK_EQ(deck[2].second, -1);
        CHECK_EQ(deck[3].first->getType(), catan::KNIGHT);
        CHECK_EQ(deck[3].second, 3);
        CHECK_EQ(deck[4].first->getType(), catan::VICTORY_POINT);
        CHECK_EQ(deck[4].second, 4);
    }
}

TEST_CASE("Buy a development card")
{
    suppressOutput();
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<pair<catan::Card*, int>> deck = game.getDevCardsDeck();
    SUBCASE("Player does not have enough resources to buy a card")
    {
        int ans = player1.buyDevCard(&game);
        restoreOutput();
        CHECK_EQ(ans, -1);
    }
    SUBCASE("Player buys a card")
    {
        player1.addResource(catan::IRON, 1);
        player1.addResource(catan::WOOL, 1);
        player1.addResource(catan::WHEAT, 1);
        int cardType = player1.buyDevCard(&game);
        restoreOutput();
        CHECK_NE(player1.getDevCards()[(size_t)cardType].first, nullptr);
        // check thatthe player actually points to a new instance of the card
        CHECK_NE(player1.getDevCards()[(size_t)cardType].first, deck[(size_t)cardType].first);
        CHECK_EQ(player1.getDevCards()[(size_t)cardType].second, 1);
        
        while(cardType < 3)
        {
            suppressOutput();
            player1.addResource(catan::IRON, 1);
            player1.addResource(catan::WOOL, 1);
            player1.addResource(catan::WHEAT, 1);
            cardType = player1.buyDevCard(&game);
        }
        vector<pair<catan::Card*, int>> newDeck = game.getDevCardsDeck();
        restoreOutput();
        CHECK_EQ(newDeck[(size_t)cardType].second, deck[(size_t)cardType].second - 1);
    }
}

TEST_CASE("Use \"pure\" development cards")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    suppressOutput();
    SUBCASE("Big army card - 3 Knight cards")
    {   
        while(game.getDevCardsDeck()[(size_t)catan::KNIGHT].second > 0)
        {
            player1.addResource(catan::IRON, 1);
            player1.addResource(catan::WOOL, 1);
            player1.addResource(catan::WHEAT, 1);
            player1.buyDevCard(&game);
        }
        int victoryPointsCard = 4 - game.getDevCardsDeck()[(size_t)catan::VICTORY_POINT].second;
        restoreOutput();
        CHECK_EQ(player1.getVictoryPoints(), 2 + victoryPointsCard);
        SUBCASE("Lost a knight card")
        {
            player1.removeDevCard(player1.getDevCards()[(size_t)catan::KNIGHT].first);
            // CHECK_EQ(player1.getVictoryPoints(), victoryPointsCard);
        }
    }
    SUBCASE("Victory point card")
    {
        suppressOutput();
        while(game.getDevCardsDeck()[(size_t)catan::VICTORY_POINT].second > 0)
        {
            player1.addResource(catan::IRON, 1);
            player1.addResource(catan::WOOL, 1);
            player1.addResource(catan::WHEAT, 1);
            player1.buyDevCard(&game);
        }
        int bigArmy = (game.getDevCardsDeck()[(size_t)catan::KNIGHT].second == 0) ? 2 : 0;
        restoreOutput();
        CHECK_EQ(player1.getVictoryPoints(), 4 + bigArmy);
    }
}

TEST_CASE("Use a promotion card")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    suppressOutput();
    SUBCASE("No cards to play")
    {   
        int ans = player1.playDevCard(&game);
        restoreOutput();
        CHECK_EQ(ans, -1);
        SUBCASE("Only non promotion cards")
        {   
            suppressOutput();
            player1.addDevCard(game.getDevCardsDeck()[(size_t)catan::KNIGHT].first->clone());
            player1.addDevCard(game.getDevCardsDeck()[(size_t)catan::VICTORY_POINT].first->clone());
            ans = player1.playDevCard(&game);
            restoreOutput();
            CHECK_EQ(ans, -1);
        }
    }
    SUBCASE("Monopoly card")
    {
        player1.addDevCard(game.getDevCardsDeck()[(size_t)catan::MONOPOLY].first->clone());
        player1.addResource(catan::IRON, 1);
        player2.addResource(catan::IRON, 3);
        player2.addResource(catan::WOOL, 3);
        player3.addResource(catan::IRON, 5);
        player3.addResource(catan::WHEAT, 5);
        std::streambuf* orig = cin.rdbuf();
        std::istringstream input("0\n5\n");
        cin.rdbuf(input.rdbuf());
        player1.playDevCard(&game);
        cin.rdbuf(orig);
        restoreOutput();
        CHECK_EQ(player1.getResource(catan::IRON), 9);
        CHECK_EQ(player2.getResource(catan::IRON), 0);
        CHECK_EQ(player3.getResource(catan::IRON), 0);
        CHECK_EQ(player1.getResource(catan::WOOL), 0);
        CHECK_EQ(player2.getResource(catan::WOOL), 3);
        CHECK_EQ(player1.getResource(catan::WHEAT), 0);
        CHECK_EQ(player3.getResource(catan::WHEAT), 5);
        CHECK_EQ(player1.getDevCards()[(size_t)catan::MONOPOLY].first, nullptr);
        CHECK_EQ(player1.getDevCards()[(size_t)catan::MONOPOLY].second, 0);
    }
    SUBCASE("Road building caard")
    {
        player1.addDevCard(game.getDevCardsDeck()[(size_t)catan::ROAD_BUILDING].first->clone());
        game.placeSettlement(&player1, 0, 0, true);
        SUBCASE("Legitimate road placement")
        {
            std::streambuf* orig = cin.rdbuf();
            std::istringstream input("1\n0\n0\n0\n5\n");
            cin.rdbuf(input.rdbuf());
            player1.playDevCard(&game);
            cin.rdbuf(orig);
            restoreOutput();
            CHECK_EQ(game.getBoard()[0]->getEdge(0)->getOwner(), &player1);
            CHECK_EQ(game.getBoard()[0]->getEdge(5)->getOwner(), &player1);
        
        }
        SUBCASE("Bad placement")
        {
            std::streambuf* orig = cin.rdbuf();
            std::istringstream input("1\n7\n3\n0\n0\n0\n5\n");
            cin.rdbuf(input.rdbuf());
            player1.playDevCard(&game);
            cin.rdbuf(orig);
            restoreOutput();
            CHECK_EQ(game.getBoard()[0]->getEdge(0)->getOwner(), &player1);
            CHECK_EQ(game.getBoard()[0]->getEdge(5)->getOwner(), &player1);
        }
    }
    SUBCASE("Year of plenty card")
    {
        player1.addDevCard(game.getDevCardsDeck()[(size_t)catan::YEAR_OF_PLENTY].first->clone());
        std::streambuf* orig = cin.rdbuf();
        std::istringstream input("2\n1\n3\n");
        cin.rdbuf(input.rdbuf());
        player1.playDevCard(&game);
        cin.rdbuf(orig);
        restoreOutput();
        CHECK_EQ(player1.getResource(catan::BRICK), 1);
        CHECK_EQ(player1.getResource(catan::WHEAT), 1);
        CHECK_EQ(player1.getDevCards()[(size_t)catan::YEAR_OF_PLENTY].first, nullptr);
        CHECK_EQ(player1.getDevCards()[(size_t)catan::YEAR_OF_PLENTY].second, 0);
    }
}

TEST_CASE("Winner determination")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    suppressOutput();
    player1.addVictoryPoints(10);
    catan::Player* winner = game.isGameOver();
    restoreOutput();
    CHECK_EQ(winner, &player1);
    CHECK_NE(winner, &player2);
}