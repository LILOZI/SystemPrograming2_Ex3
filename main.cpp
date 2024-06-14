// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"

int main()
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    // vector<int> ans = {17, 30, 19};
    // game.start();
    game.displayBoard();
    // for(size_t i = 0; i < 3; i++)
    // {
    // game.displayBoard();
    // cout << game.getBoard()[4]->getVertex(3)->getNeighbors()[1]->getId() << endl;
        
    // }
    return 0;
}