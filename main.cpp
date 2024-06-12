// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"

int main()
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    // game.start();
    return 0;
}