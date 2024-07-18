// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"

#include <sstream>

void demo();
void real();

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        real();
        return 0;
    }
    demo();
    return 0;
    
}

void demo()
{
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3, 6);
    std::streambuf* orig = cin.rdbuf();
    string placements1 = "5\n0\n5\n0\n12\n1\n12\n1\n0\n0\n0\n5\n";
    string placements2 = "2\n5\n2\n4\n7\n0\n7\n0\n18\n0\n18\n0\n";
    string rolls = "1\nE\n1\nE\n1\nE\n";
    
    game.start(placements1 + placements2 + rolls);

}

void real()
{   
    catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    game.start();
}