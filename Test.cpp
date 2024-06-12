// @author oz.atar@msmail.ariel.ac.il

#include "doctest.h"
#include "Catan.hpp"

TEST_CASE("Test right id")
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    vector<int> ans = {17, 30, 19};
    for(size_t i = 0; i < 3; i++)
    {
        // CHECK(game.getBoard()[4]->getVertex(3)->getNeighbors(i)->getId(),ans[i]);
    }
    
}