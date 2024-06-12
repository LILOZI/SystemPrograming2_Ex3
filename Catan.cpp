// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"

catan::Catan::Catan(Player &player1, Player &player2, Player &player3) 
: players{&player1, &player2, &player3}, board(19), landNum()
{   
    srand(time(nullptr));
    current_player = 0;

    for(size_t i = 0; i < 19; i++)
    {
        board[i] = new Land(i);
        int num = rand() % 11 + 2;
        landNum[num].push_back(board[i]);   
    }
    

    init();
}

catan::Catan::~Catan()
{
    for(size_t i = 0; i < 19; i++)
    {
        delete board[i];
    }
}

void catan::Catan::init()
{
    initBoard();
    // initDevCards();
}

void catan::Catan::initBoard()
{   
    initBoardResources();
    createBoardVertices();
    createBoardEdges();
}

void catan::Catan::initBoardResources()
{
    int resource = BRICK;
    // set at least one land of each resource at a random place
    for(size_t i = 0; i < 5; i++)
    {
        size_t index = (size_t)rand() % 19;
        while(!board[index]->getResource().empty())
        {
            index = (size_t)rand() % 19;
        }
        board[index]->setResource(resource);
        resource++;
    }
    resource = 0;
    // set random resources for the rest of the lands
    for(size_t i = 0; i < 19; i++)
    {
        if(board[i]->getResource().empty())
        {
            resource = (size_t)rand() % 6;
            board[i]->setResource(resource);
        }
    }
}

void catan::Catan::createBoardVertices()
{
    // set vertices for each land
    // first row
    this->board[0]->setVertices(new LandVertex(0), new LandVertex(1), new LandVertex(2), new LandVertex(3), new LandVertex(4), new LandVertex(5));
    this->board[1]->setVertices(new LandVertex(6), this->board[0]->getVertex(5), this->board[0]->getVertex(4), new LandVertex(7), new LandVertex(8), new LandVertex(9));
    this->board[2]->setVertices(new LandVertex(10), this->board[1]->getVertex(5), this->board[1]->getVertex(4),new LandVertex(11), new LandVertex(12), new LandVertex(13));

    // second row
    this->board[3]->setVertices(this->board[0]->getVertex(2), new LandVertex(14), new LandVertex(15), new LandVertex(16), new LandVertex(17), this->board[0]->getVertex(3));
    this->board[4]->setVertices(this->board[1]->getVertex(2), this->board[3]->getVertex(5), this->board[3]->getVertex(4), new LandVertex(18), new LandVertex(19), this->board[1]->getVertex(3));
    this->board[5]->setVertices(this->board[2]->getVertex(2), this->board[4]->getVertex(5), this->board[4]->getVertex(4), new LandVertex(20), new LandVertex(21), this->board[2]->getVertex(3));
    this->board[6]->setVertices(this->board[2]->getVertex(4), this->board[5]->getVertex(5), this->board[5]->getVertex(4), new LandVertex(22), new LandVertex(23), new LandVertex(24));

    // third row
    this->board[7]->setVertices(this->board[3]->getVertex(2), new LandVertex(25), new LandVertex(26), new LandVertex(27), new LandVertex(28), this->board[3]->getVertex(3));
    this->board[8]->setVertices(this->board[4]->getVertex(2), this->board[7]->getVertex(5), this->board[7]->getVertex(4), new LandVertex(29), new LandVertex(30), this->board[4]->getVertex(3));
    this->board[9]->setVertices(this->board[5]->getVertex(2), this->board[8]->getVertex(5), this->board[8]->getVertex(4), new LandVertex(31), new LandVertex(32), this->board[5]->getVertex(3));
    this->board[10]->setVertices(this->board[6]->getVertex(2), this->board[9]->getVertex(5), this->board[9]->getVertex(4), new LandVertex(33), new LandVertex(34), this->board[6]->getVertex(3));
    this->board[11]->setVertices(this->board[6]->getVertex(4), this->board[10]->getVertex(5), this->board[10]->getVertex(4), new LandVertex(35), new LandVertex(36), new LandVertex(37));

    // fourth row
    this->board[12]->setVertices(this->board[7]->getVertex(4), this->board[7]->getVertex(3), new LandVertex(38), new LandVertex(39), new LandVertex(40), this->board[8]->getVertex(3));
    this->board[13]->setVertices(this->board[8]->getVertex(4), this->board[12]->getVertex(5), this->board[12]->getVertex(4), new LandVertex(41), new LandVertex(42), this->board[9]->getVertex(3));
    this->board[14]->setVertices(this->board[9]->getVertex(4), this->board[13]->getVertex(5), this->board[13]->getVertex(4), new LandVertex(43), new LandVertex(44), this->board[10]->getVertex(3));
    this->board[15]->setVertices(this->board[10]->getVertex(4), this->board[14]->getVertex(5), this->board[14]->getVertex(4), new LandVertex(45), new LandVertex(46), this->board[11]->getVertex(3));

    // fifth row
    this->board[16]->setVertices(this->board[12]->getVertex(4), this->board[12]->getVertex(3), new LandVertex(47), new LandVertex(48), new LandVertex(49), this->board[13]->getVertex(3));
    this->board[17]->setVertices(this->board[13]->getVertex(4), this->board[16]->getVertex(5), this->board[16]->getVertex(4), new LandVertex(50), new LandVertex(51), this->board[14]->getVertex(3));
    this->board[18]->setVertices(this->board[14]->getVertex(4), this->board[17]->getVertex(5), this->board[17]->getVertex(4), new LandVertex(52), new LandVertex(53), this->board[15]->getVertex(3));
}

void catan::Catan::createBoardEdges()
{
    // set edges for each land
    // first row
    this->board[0]->setEdges(new LandEdge(0), new LandEdge(1), new LandEdge(2), new LandEdge(3), new LandEdge(4), new LandEdge(5));
    this->board[1]->setEdges(new LandEdge(6), this->board[0]->getEdge(4), new LandEdge(7), new LandEdge(8), new LandEdge(9), new LandEdge(10));
    this->board[2]->setEdges(new LandEdge(11), this->board[1]->getEdge(4), new LandEdge(12), new LandEdge(13), new LandEdge(14), new LandEdge(15));

    // second row
    this->board[3]->setEdges(new LandEdge(16), new LandEdge(17), new LandEdge(18), new LandEdge(19), new LandEdge(20), this->board[0]->getEdge(2));
    this->board[4]->setEdges(this->board[0]->getEdge(3), this->board[3]->getEdge(4), new LandEdge(21), new LandEdge(22), new LandEdge(23), this->board[1]->getEdge(2));
    this->board[5]->setEdges(this->board[1]->getEdge(3), this->board[4]->getEdge(4), new LandEdge(24), new LandEdge(25), new LandEdge(26), this->board[2]->getEdge(2));
    this->board[6]->setEdges(this->board[2]->getEdge(3), this->board[5]->getEdge(4), new LandEdge(27), new LandEdge(28), new LandEdge(29), new LandEdge(30));

    // third row
    this->board[7]->setEdges(new LandEdge(31), new LandEdge(32), new LandEdge(33), new LandEdge(34), new LandEdge(35), this->board[3]->getEdge(2));
    this->board[8]->setEdges(this->board[3]->getEdge(3), this->board[7]->getEdge(4), new LandEdge(36), new LandEdge(37), new LandEdge(38), this->board[4]->getEdge(2));
    this->board[9]->setEdges(this->board[4]->getEdge(3), this->board[8]->getEdge(4), new LandEdge(39), new LandEdge(40), new LandEdge(41), this->board[5]->getEdge(2));
    this->board[10]->setEdges(this->board[5]->getEdge(3), this->board[9]->getEdge(4), new LandEdge(42), new LandEdge(43), new LandEdge(44), this->board[6]->getEdge(2));
    this->board[11]->setEdges(this->board[6]->getEdge(3), this->board[10]->getEdge(4), new LandEdge(45), new LandEdge(46), new LandEdge(47), new LandEdge(48));

    // fourth row
    this->board[12]->setEdges(this->board[7]->getEdge(3), new LandEdge(49), new LandEdge(50), new LandEdge(51), new LandEdge(52), this->board[8]->getEdge(2));
    this->board[13]->setEdges(this->board[8]->getEdge(3), this->board[12]->getEdge(4), new LandEdge(53), new LandEdge(54), new LandEdge(55), this->board[9]->getEdge(2));
    this->board[14]->setEdges(this->board[9]->getEdge(3), this->board[13]->getEdge(4), new LandEdge(56), new LandEdge(57), new LandEdge(58), this->board[10]->getEdge(2));
    this->board[15]->setEdges(this->board[10]->getEdge(3), this->board[14]->getEdge(4), new LandEdge(59), new LandEdge(60), new LandEdge(61), this->board[11]->getEdge(2));

    // fifth row
    this->board[16]->setEdges(this->board[12]->getEdge(3), new LandEdge(62), new LandEdge(63), new LandEdge(64), new LandEdge(65), this->board[13]->getEdge(2));
    this->board[17]->setEdges(this->board[13]->getEdge(3), this->board[16]->getEdge(4), new LandEdge(66), new LandEdge(67), new LandEdge(68), this->board[14]->getEdge(2));
    this->board[18]->setEdges(this->board[14]->getEdge(3), this->board[17]->getEdge(4), new LandEdge(69), new LandEdge(70), new LandEdge(71), this->board[15]->getEdge(2));

}

void catan::Catan::setVxsAndEdges()
{   
    // Land 0
        // LandVertices
            // vertices
    this->board[0]->getVertex(0)->addNeighbors(this->board[0]->getVertex(1), this->board[0]->getVertex(5), nullptr);
    this->board[0]->getVertex(1)->addNeighbors(this->board[0]->getVertex(2), this->board[0]->getVertex(0), nullptr);
    this->board[0]->getVertex(2)->addNeighbors(this->board[0]->getVertex(1),  this->board[3]->getVertex(1), this->board[0]->getVertex(3));
    this->board[0]->getVertex(3)->addNeighbors(this->board[0]->getVertex(2),  this->board[3]->getVertex(4), this->board[0]->getVertex(4));
    this->board[0]->getVertex(4)->addNeighbors(this->board[0]->getVertex(5), this->board[0]->getVertex(3), this->board[4]->getVertex(5));
    this->board[0]->getVertex(5)->addNeighbors(this->board[0]->getVertex(0), this->board[0]->getVertex(4), this->board[1]->getVertex(0));
            // edges
    this->board[0]->getVertex(0)->addIncidentEdges(this->board[0]->getEdge(0), this->board[0]->getEdge(5), nullptr);
    this->board[0]->getVertex(1)->addIncidentEdges(this->board[0]->getEdge(1), this->board[0]->getEdge(0), nullptr);
    this->board[0]->getVertex(2)->addIncidentEdges(this->board[0]->getEdge(1), this->board[3]->getEdge(0), this->board[0]->getEdge(1));
    this->board[0]->getVertex(3)->addIncidentEdges(this->board[0]->getEdge(2), this->board[3]->getEdge(4), this->board[0]->getEdge(3));
    this->board[0]->getVertex(4)->addIncidentEdges(this->board[0]->getEdge(4), this->board[0]->getEdge(3), this->board[4]->getEdge(5));
    this->board[0]->getVertex(5)->addIncidentEdges(this->board[0]->getEdge(5), this->board[0]->getEdge(4), this->board[1]->getEdge(0));
        // LandEdges
            // vertices
    this->board[0]->getEdge(0)->setVertices(this->board[0]->getVertex(0), this->board[0]->getVertex(1));
    this->board[0]->getEdge(1)->setVertices(this->board[0]->getVertex(1), this->board[0]->getVertex(2));
    this->board[0]->getEdge(2)->setVertices(this->board[0]->getVertex(2), this->board[0]->getVertex(3));
    this->board[0]->getEdge(3)->setVertices(this->board[0]->getVertex(3), this->board[0]->getVertex(4));
    this->board[0]->getEdge(4)->setVertices(this->board[0]->getVertex(4), this->board[0]->getVertex(5));
    this->board[0]->getEdge(5)->setVertices(this->board[0]->getVertex(5), this->board[0]->getVertex(0));
            // edges
    this->board[0]->getEdge(0)->addAdjEdges(this->board[0]->getEdge(0), this->board[0]->getEdge(5), nullptr, nullptr);
    this->board[0]->getEdge(1)->addAdjEdges(this->board[3]->getEdge(0), this->board[0]->getEdge(2), this->board[0]->getEdge(0), nullptr);
    this->board[0]->getEdge(2)->addAdjEdges(this->board[0]->getEdge(1), this->board[3]->getEdge(0), this->board[3]->getEdge(4), this->board[0]->getEdge(3));
    this->board[0]->getEdge(3)->addAdjEdges(this->board[0]->getEdge(2), this->board[3]->getEdge(4), this->board[4]->getEdge(5), this->board[0]->getEdge(4));
    this->board[0]->getEdge(4)->addAdjEdges(this->board[0]->getEdge(5), this->board[0]->getEdge(3), this->board[1]->getEdge(2), this->board[1]->getEdge(0));
    this->board[0]->getEdge(5)->addAdjEdges(this->board[0]->getEdge(0), this->board[0]->getEdge(4), this->board[1]->getEdge(0), nullptr);

    // vertices and edges that have been set in previous lands will be ignored.

    // Land 1
        // LandVertices
            // vertices
    this->board[1]->getVertex(0)->addNeighbors(this->board[0]->getVertex(5), this->board[1]->getVertex(5), nullptr);
    this->board[1]->getVertex(3)->addNeighbors(this->board[0]->getVertex(4), this->board[4]->getVertex(4), this->board[1]->getVertex(4));
    this->board[1]->getVertex(4)->addNeighbors(this->board[1]->getVertex(5), this->board[1]->getVertex(3), this->board[5]->getVertex(5));
    this->board[1]->getVertex(5)->addNeighbors(this->board[1]->getVertex(0), this->board[1]->getVertex(4), this->board[2]->getVertex(0));
            // edges
    this->board[1]->getVertex(0)->addIncidentEdges(this->board[1]->getEdge(0), this->board[1]->getEdge(5), nullptr);
    this->board[1]->getVertex(3)->addIncidentEdges(this->board[1]->getEdge(2), this->board[4]->getEdge(4), this->board[1]->getEdge(3));
    this->board[1]->getVertex(4)->addIncidentEdges(this->board[1]->getEdge(4), this->board[1]->getEdge(3), this->board[5]->getEdge(5));
    this->board[1]->getVertex(5)->addIncidentEdges(this->board[1]->getEdge(5), this->board[1]->getEdge(4), this->board[2]->getEdge(0));
        // LandEdges
            // vertices
    this->board[1]->getEdge(0)->setVertices(this->board[1]->getVertex(0), this->board[0]->getVertex(5));
    this->board[1]->getEdge(2)->setVertices(this->board[0]->getVertex(4), this->board[1]->getVertex(3));
    this->board[1]->getEdge(3)->setVertices(this->board[1]->getVertex(3), this->board[1]->getVertex(4));
    this->board[1]->getEdge(4)->setVertices(this->board[1]->getVertex(4), this->board[1]->getVertex(5));
    this->board[1]->getEdge(5)->setVertices(this->board[1]->getVertex(5), this->board[1]->getVertex(0));
            // edges
        

}

catan::Player* catan::Catan::start()
{
    // playRound0();
    Player* winner = nullptr;
    while((winner = isGameOver()) == nullptr)
    {
        // playTurn();
    }
    return winner;
}


catan::Player* catan::Catan::isGameOver()
{
    for(size_t i = 0; i < 3; i++)
    {
        if(players[i]->getVictoryPoints() >= 10)
        {
            return players[i];
        }
    }
    return nullptr;
}
