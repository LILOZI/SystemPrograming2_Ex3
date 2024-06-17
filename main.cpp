// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"

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
    
}

void real()
{catan::Player player1("Player1", 0);
    catan::Player player2("Player2", 1);
    catan::Player player3("Player3", 2);
    catan::Catan game(player1, player2, player3);
    game.start();
}