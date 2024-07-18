// @author: oz.atar@msmail.ariel.ac.il

#include "Catan.hpp"
#include "cards/MonopolyCard.hpp"
#include "cards/RoadBuildingCard.hpp"
#include "cards/YearOfPlentyCard.hpp"
#include "cards/KnightCard.hpp"
#include "cards/VictoryPointCard.hpp"

catan::Catan::Catan(Player &player1, Player &player2, Player &player3) 
: curPlayer(0), players{&player1, &player2, &player3}, board(19), devCardsDeck((5), std::make_pair(nullptr, 0)), landNum()
{   
    srand(time(nullptr));
    init();
}

catan::Catan::Catan(Player &player1, Player &player2, Player &player3, uint seed) 
: curPlayer(0), players{&player1, &player2, &player3}, board(19), devCardsDeck((5), std::make_pair(nullptr, 0)), landNum()
{   
    srand(seed);
    init();
}

catan::Catan::~Catan()
{
    set<LandVertex*> vertices;
    set<LandEdge*> edges;
    for(size_t i = 0; i < 19; i++)
    {
        for(size_t j = 0; j < 6; j++)
        {
            auto insertAns = vertices.insert(this->board[i]->getVertex(j));
            if(!insertAns.second)
            {
                this->board[i]->setVertex(j, nullptr); 
            }
        }
        for(size_t j = 0; j < 6; j++)
        {
            auto insertAns = edges.insert(board[i]->getEdge(j));
            if(!insertAns.second)
            {
                this->board[i]->setEdge(j, nullptr);
            }
        }
    }
    for(size_t i = 0; i < 19; i++)
    {
        delete board[i];
    }
    for(size_t i = 0; i < 5; i++)
    {
        delete devCardsDeck[i].first;
    }
}


void catan::Catan::init()
{
    initBoard();
    initDevCards();
}

void catan::Catan::initDevCards()
{
    devCardsDeck[0] = make_pair(new MonopolyCard(), -1);
    devCardsDeck[1] = make_pair(new RoadBuildingCard(), -1);
    devCardsDeck[2] = make_pair(new YearOfPlentyCard(), -1);
    devCardsDeck[3] = make_pair(new KnightCard(), 3);
    devCardsDeck[4] = make_pair(new VictoryPointCard(), 4);
}

void catan::Catan::initBoard()
{   
    for(size_t i = 0; i < 19; i++)
    {
        board[i] = new Land(i);   
    }
    createBoardVertices();
    createBoardEdges();
    setVxsAndEdges();
    initBoardResources();
}

void catan::Catan::initBoardResources()
{
    int resource = BRICK;
    int num;
    // set at least one land of each resource at a random place and give it a random number
    for(size_t i = 0; i < 6; i++)
    {
        size_t index = (size_t)rand() % 19;
        while(!board[index]->getResource().empty())
        {
            index = (size_t)rand() % 19;
        }
        board[index]->setResource(resource);
        num = rand() % 11 + 2;
        landNum[num].push_back(board[index]);
        resource++;
    }
    resource = 0;
    // set random resources and numbers for the rest of the lands
    for(size_t i = 0; i < 19; i++)
    {
        if(board[i]->getResource().empty())
        {
            resource = (size_t)rand() % 6;
            board[i]->setResource(resource);
            num = rand() % 11 + 2;
            landNum[num].push_back(board[i]);
        }
    }
}

int catan::Catan::rollDice()
{
    size_t d1 = (size_t)rand() % 6 + 1;
    size_t d2 = (size_t)rand() % 6 + 1;
    size_t sum = d1 + d2;
    cout << "Dice 1: " << d1 << " Dice 2: " << d2 << " Sum: " << sum << endl;
    if(sum == 7)
    {
        this->distributeResources(sum);
        cout << "Dices result is 7, all players with more than 7 resources must discard half of their resources" << endl;
        for(size_t i = 0; i < MAX_PLAYERS; i++)
        {
            int resourceTotal = players[i]->getTotalResources();
            if(resourceTotal > 7)
            {
                players[i]->discardResources(resourceTotal);
            }
        }
    }
    else
    {
        // give resources to players
        this->distributeResources(sum);
    }
    return sum;
}

void catan::Catan::distributeResources(int sum)
{
    for(auto& land : landNum[sum])
        {
            if(land->getResourceNum() == DESERT)
            {
                continue;
            }
            for(size_t i = 0; i < 6; i++)
            {
                if(land->getVertex(i)->getOwner() != nullptr)
                {   
                    if(land->getVertex(i)->isSettlementf())
                    {
                        land->getVertex(i)->getOwner()->addResource(land->getResourceNum(), 1);
                    }
                    else 
                    {
                        land->getVertex(i)->getOwner()->addResource(land->getResourceNum(), 2);
                    }
                }
            }
        }
}

void catan::Catan::playRound0()
{
    for(size_t i = 0; i < MAX_PLAYERS; i++)
    {
        this->displayBoard();
        cout << this->players[i]->getName() << " turn to place a settlement and a road" << endl;
        this->players[i]->placeSettlement(this, true);
        this->players[i]->placeRoad(this, true);
    }
    cout << "Now place the second settlement and road" << endl;
    for(size_t i = 0; i < MAX_PLAYERS; i++)
    {
        this->displayBoard();
        cout << this->players[i]->getName() << " turn to place a settlement and a road" << endl;
        this->players[i]->placeSettlement(this, true);
        this->players[i]->placeRoad(this, true);
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
    this->board[0]->getVertex(2)->addIncidentEdges(this->board[0]->getEdge(1), this->board[3]->getEdge(0), this->board[0]->getEdge(2));
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
    this->board[0]->getEdge(0)->addAdjEdges(this->board[0]->getEdge(1), this->board[0]->getEdge(5), nullptr, nullptr);
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
    this->board[1]->getEdge(0)->addAdjEdges(this->board[0]->getEdge(5), this->board[0]->getEdge(4), this->board[1]->getEdge(5), nullptr);
    this->board[1]->getEdge(2)->addAdjEdges(this->board[0]->getEdge(4), this->board[0]->getEdge(3), this->board[4]->getEdge(4), this->board[1]->getEdge(3));
    this->board[1]->getEdge(3)->addAdjEdges(this->board[1]->getEdge(2), this->board[4]->getEdge(4), this->board[5]->getEdge(5), this->board[1]->getEdge(4));
    this->board[1]->getEdge(4)->addAdjEdges(this->board[1]->getEdge(5), this->board[1]->getEdge(3), this->board[5]->getEdge(5), this->board[2]->getEdge(0));
    this->board[1]->getEdge(5)->addAdjEdges(this->board[1]->getEdge(0), this->board[1]->getEdge(4), this->board[2]->getEdge(0), nullptr);

    // Land 2
        // LandVertices
            // vertices
    this->board[2]->getVertex(0)->addNeighbors(this->board[1]->getVertex(5), this->board[2]->getVertex(5), nullptr);
    this->board[2]->getVertex(3)->addNeighbors(this->board[1]->getVertex(4), this->board[5]->getVertex(4), this->board[2]->getVertex(4));
    this->board[2]->getVertex(4)->addNeighbors(this->board[2]->getVertex(5), this->board[2]->getVertex(3), this->board[6]->getVertex(5));
    this->board[2]->getVertex(5)->addNeighbors(this->board[2]->getVertex(0), this->board[2]->getVertex(4), nullptr);
            // edges
    this->board[2]->getVertex(0)->addIncidentEdges(this->board[2]->getEdge(0), this->board[2]->getEdge(5), nullptr);
    this->board[2]->getVertex(3)->addIncidentEdges(this->board[2]->getEdge(2), this->board[5]->getEdge(4), this->board[2]->getEdge(3));
    this->board[2]->getVertex(4)->addIncidentEdges(this->board[2]->getEdge(4), this->board[2]->getEdge(3), this->board[6]->getEdge(5));
    this->board[2]->getVertex(5)->addIncidentEdges(this->board[2]->getEdge(5), this->board[2]->getEdge(4), nullptr);
        // LandEdges
            // vertices
    this->board[2]->getEdge(0)->setVertices(this->board[2]->getVertex(0), this->board[1]->getVertex(5));
    this->board[2]->getEdge(2)->setVertices(this->board[1]->getVertex(4), this->board[2]->getVertex(3));
    this->board[2]->getEdge(3)->setVertices(this->board[2]->getVertex(3), this->board[2]->getVertex(4));
    this->board[2]->getEdge(4)->setVertices(this->board[2]->getVertex(4), this->board[2]->getVertex(5));
    this->board[2]->getEdge(5)->setVertices(this->board[2]->getVertex(5), this->board[2]->getVertex(0));
            // edges
    this->board[2]->getEdge(0)->addAdjEdges(this->board[1]->getEdge(5), this->board[1]->getEdge(4), this->board[2]->getEdge(5), nullptr);
    this->board[2]->getEdge(2)->addAdjEdges(this->board[1]->getEdge(4), this->board[1]->getEdge(3), this->board[5]->getEdge(4), this->board[2]->getEdge(3));
    this->board[2]->getEdge(3)->addAdjEdges(this->board[2]->getEdge(2), this->board[5]->getEdge(4), this->board[6]->getEdge(5), this->board[2]->getEdge(4));
    this->board[2]->getEdge(4)->addAdjEdges(this->board[2]->getEdge(5), this->board[2]->getEdge(3), this->board[6]->getEdge(5), nullptr);
    this->board[2]->getEdge(5)->addAdjEdges(this->board[2]->getEdge(0), this->board[2]->getEdge(4), nullptr, nullptr);

    // Land 3
        // LandVertices
            // vertices
    this->board[3]->getVertex(1)->addNeighbors(this->board[3]->getVertex(2), this->board[0]->getVertex(2), nullptr);
    this->board[3]->getVertex(2)->addNeighbors(this->board[3]->getVertex(1), this->board[7]->getVertex(1), this->board[3]->getVertex(3));
    this->board[3]->getVertex(3)->addNeighbors(this->board[3]->getVertex(2), this->board[7]->getVertex(4), this->board[3]->getVertex(4));
    this->board[3]->getVertex(4)->addNeighbors(this->board[0]->getVertex(3), this->board[3]->getVertex(3), this->board[4]->getVertex(3));
            // edges
    this->board[3]->getVertex(1)->addIncidentEdges(this->board[3]->getEdge(1), this->board[3]->getEdge(0), nullptr);   
    this->board[3]->getVertex(2)->addIncidentEdges(this->board[3]->getEdge(1), this->board[7]->getEdge(0), this->board[3]->getEdge(2)); 
    this->board[3]->getVertex(3)->addIncidentEdges(this->board[3]->getEdge(2), this->board[7]->getEdge(4), this->board[3]->getEdge(3));
    this->board[3]->getVertex(4)->addIncidentEdges(this->board[3]->getEdge(4), this->board[3]->getEdge(3), this->board[4]->getEdge(2));
        // LandEdges
            // vertices    
    this->board[3]->getEdge(0)->setVertices(this->board[0]->getVertex(2), this->board[3]->getVertex(1));
    this->board[3]->getEdge(1)->setVertices(this->board[3]->getVertex(1), this->board[3]->getVertex(2));
    this->board[3]->getEdge(2)->setVertices(this->board[3]->getVertex(2), this->board[3]->getVertex(3));
    this->board[3]->getEdge(3)->setVertices(this->board[3]->getVertex(3), this->board[3]->getVertex(4));
    this->board[3]->getEdge(4)->setVertices(this->board[3]->getVertex(4), this->board[0]->getVertex(3));
            // edges
    this->board[3]->getEdge(0)->addAdjEdges(this->board[0]->getEdge(1), this->board[3]->getEdge(1), this->board[0]->getEdge(2), nullptr);
    this->board[3]->getEdge(1)->addAdjEdges(this->board[7]->getEdge(0), this->board[3]->getEdge(2), this->board[3]->getEdge(0), nullptr);
    this->board[3]->getEdge(2)->addAdjEdges(this->board[3]->getEdge(1), this->board[7]->getEdge(0), this->board[7]->getEdge(4), this->board[3]->getEdge(3));
    this->board[3]->getEdge(3)->addAdjEdges(this->board[3]->getEdge(2), this->board[7]->getEdge(4), this->board[4]->getEdge(2), this->board[3]->getEdge(4));
    this->board[3]->getEdge(4)->addAdjEdges(this->board[0]->getEdge(2), this->board[3]->getEdge(3), this->board[4]->getEdge(2), this->board[0]->getEdge(3));

    // Land 4
        // LandVertices
            // vertices
    this->board[4]->getVertex(3)->addNeighbors(this->board[3]->getVertex(4), this->board[8]->getVertex(4), this->board[4]->getVertex(4));
    this->board[4]->getVertex(4)->addNeighbors(this->board[1]->getVertex(3), this->board[4]->getVertex(3), this->board[5]->getVertex(3));
            // edges
    this->board[4]->getVertex(3)->addIncidentEdges(this->board[4]->getEdge(2), this->board[8]->getEdge(4), this->board[4]->getEdge(3));
    this->board[4]->getVertex(4)->addIncidentEdges(this->board[4]->getEdge(4), this->board[4]->getEdge(3), this->board[5]->getEdge(2));
        
        // LandEdges
            // vertices
    this->board[4]->getEdge(2)->setVertices(this->board[3]->getVertex(4), this->board[4]->getVertex(3));
    this->board[4]->getEdge(3)->setVertices(this->board[4]->getVertex(3), this->board[4]->getVertex(4));
    this->board[4]->getEdge(4)->setVertices(this->board[4]->getVertex(4), this->board[4]->getVertex(5));
            // edges
    this->board[4]->getEdge(2)->addAdjEdges(this->board[3]->getEdge(4), this->board[3]->getEdge(3), this->board[8]->getEdge(4), this->board[4]->getEdge(3));
    this->board[4]->getEdge(3)->addAdjEdges(this->board[4]->getEdge(2), this->board[8]->getEdge(4), this->board[5]->getEdge(2), this->board[4]->getEdge(4));
    this->board[4]->getEdge(4)->addAdjEdges(this->board[1]->getEdge(2), this->board[4]->getEdge(3), this->board[5]->getEdge(2), this->board[1]->getEdge(3));

    // Land 5
        // LandVertices
            // vertices
    this->board[5]->getVertex(3)->addNeighbors(this->board[4]->getVertex(4), this->board[9]->getVertex(4), this->board[5]->getVertex(4));
    this->board[5]->getVertex(4)->addNeighbors(this->board[2]->getVertex(3), this->board[5]->getVertex(3), this->board[6]->getVertex(3));
            // edges
    this->board[5]->getVertex(3)->addIncidentEdges(this->board[5]->getEdge(2), this->board[9]->getEdge(4), this->board[5]->getEdge(3));
    this->board[5]->getVertex(4)->addIncidentEdges(this->board[5]->getEdge(4), this->board[5]->getEdge(3), this->board[6]->getEdge(2));

        // LandEdges
            // vertices
    this->board[5]->getEdge(2)->setVertices(this->board[5]->getVertex(2), this->board[5]->getVertex(3));
    this->board[5]->getEdge(3)->setVertices(this->board[5]->getVertex(3), this->board[5]->getVertex(4));
    this->board[5]->getEdge(4)->setVertices(this->board[5]->getVertex(4), this->board[5]->getVertex(5));
            // edges
    this->board[5]->getEdge(2)->addAdjEdges(this->board[4]->getEdge(4), this->board[4]->getEdge(3), this->board[9]->getEdge(4), this->board[5]->getEdge(3));
    this->board[5]->getEdge(3)->addAdjEdges(this->board[5]->getEdge(2), this->board[9]->getEdge(4), this->board[6]->getEdge(2), this->board[5]->getEdge(4));
    this->board[5]->getEdge(4)->addAdjEdges(this->board[2]->getEdge(2), this->board[5]->getEdge(3), this->board[6]->getEdge(2), this->board[2]->getEdge(3));
    
    // Land 6
        // LandVertices
            // vertices
    this->board[6]->getVertex(3)->addNeighbors(this->board[5]->getVertex(4), this->board[10]->getVertex(4), this->board[6]->getVertex(4));
    this->board[6]->getVertex(4)->addNeighbors(this->board[6]->getVertex(5), this->board[6]->getVertex(3), this->board[11]->getVertex(5));
    this->board[6]->getVertex(5)->addNeighbors(this->board[2]->getVertex(4), this->board[6]->getVertex(4), nullptr);
            // edges
    this->board[6]->getVertex(3)->addIncidentEdges(this->board[6]->getEdge(2), this->board[10]->getEdge(4), this->board[6]->getEdge(3));
    this->board[6]->getVertex(4)->addIncidentEdges(this->board[6]->getEdge(4), this->board[6]->getEdge(3), this->board[11]->getEdge(5));
    this->board[6]->getVertex(5)->addIncidentEdges(this->board[6]->getEdge(5), this->board[6]->getEdge(4), nullptr);
        
        // LandEdges
            // vertices
    this->board[6]->getEdge(2)->setVertices(this->board[6]->getVertex(2), this->board[6]->getVertex(3));
    this->board[6]->getEdge(3)->setVertices(this->board[6]->getVertex(3), this->board[6]->getVertex(4));
    this->board[6]->getEdge(4)->setVertices(this->board[6]->getVertex(4), this->board[6]->getVertex(5));
    this->board[6]->getEdge(5)->setVertices(this->board[6]->getVertex(5), this->board[6]->getVertex(0));
            // edges
    this->board[6]->getEdge(2)->addAdjEdges(this->board[5]->getEdge(4), this->board[5]->getEdge(3), this->board[10]->getEdge(4), this->board[6]->getEdge(3));
    this->board[6]->getEdge(3)->addAdjEdges(this->board[6]->getEdge(2), this->board[10]->getEdge(4), this->board[11]->getEdge(5), this->board[6]->getEdge(4));
    this->board[6]->getEdge(4)->addAdjEdges(this->board[6]->getEdge(5), this->board[6]->getEdge(3), this->board[11]->getEdge(5), nullptr);
    this->board[6]->getEdge(5)->addAdjEdges(this->board[2]->getEdge(4), this->board[2]->getEdge(3), this->board[6]->getEdge(4), nullptr);

    // Land 7
        // LandVertices
            // vertices
    this->board[7]->getVertex(1)->addNeighbors(this->board[7]->getVertex(2), this->board[3]->getVertex(2), nullptr);
    this->board[7]->getVertex(2)->addNeighbors(this->board[7]->getVertex(1), this->board[12]->getVertex(1), nullptr);
    this->board[7]->getVertex(3)->addNeighbors(this->board[7]->getVertex(2), this->board[12]->getVertex(2), this->board[7]->getVertex(4));
    this->board[7]->getVertex(4)->addNeighbors(this->board[3]->getVertex(3), this->board[7]->getVertex(3), this->board[8]->getVertex(3));
            // edges
    this->board[7]->getVertex(1)->addIncidentEdges(this->board[7]->getEdge(1), this->board[7]->getEdge(0), nullptr);
    this->board[7]->getVertex(2)->addIncidentEdges(this->board[7]->getEdge(1), this->board[7]->getEdge(2), nullptr);
    this->board[7]->getVertex(3)->addIncidentEdges(this->board[7]->getEdge(2), this->board[12]->getEdge(1), this->board[7]->getEdge(3));
    this->board[7]->getVertex(4)->addIncidentEdges(this->board[7]->getEdge(4), this->board[7]->getEdge(3), this->board[8]->getEdge(2));
        
        // LandEdges
            // vertices
    this->board[7]->getEdge(0)->setVertices(this->board[7]->getVertex(0), this->board[7]->getVertex(1));
    this->board[7]->getEdge(1)->setVertices(this->board[7]->getVertex(1), this->board[7]->getVertex(2));
    this->board[7]->getEdge(2)->setVertices(this->board[7]->getVertex(2), this->board[7]->getVertex(3));
    this->board[7]->getEdge(3)->setVertices(this->board[7]->getVertex(3), this->board[7]->getVertex(4));
    this->board[7]->getEdge(4)->setVertices(this->board[7]->getVertex(4), this->board[7]->getVertex(5));
            // edges
    this->board[7]->getEdge(0)->addAdjEdges(this->board[3]->getEdge(1), this->board[7]->getEdge(1), this->board[3]->getEdge(2), nullptr);
    this->board[7]->getEdge(1)->addAdjEdges(this->board[7]->getEdge(2), this->board[7]->getEdge(0), nullptr, nullptr);
    this->board[7]->getEdge(2)->addAdjEdges(this->board[7]->getEdge(1), this->board[12]->getEdge(1), this->board[7]->getEdge(3), nullptr);
    this->board[7]->getEdge(3)->addAdjEdges(this->board[7]->getEdge(2), this->board[12]->getEdge(1), this->board[8]->getEdge(2), this->board[7]->getEdge(4));
    this->board[7]->getEdge(4)->addAdjEdges(this->board[3]->getEdge(2), this->board[7]->getEdge(3), this->board[8]->getEdge(2), this->board[3]->getEdge(3));

    // Land 8
        // LandVertices
            // vertices
    this->board[8]->getVertex(3)->addNeighbors(this->board[7]->getVertex(4), this->board[12]->getVertex(4), this->board[8]->getVertex(4));
    this->board[8]->getVertex(4)->addNeighbors(this->board[4]->getVertex(3), this->board[8]->getVertex(3), this->board[9]->getVertex(3));
            // edges
    this->board[8]->getVertex(3)->addIncidentEdges(this->board[8]->getEdge(2), this->board[12]->getEdge(4), this->board[8]->getEdge(3));
    this->board[8]->getVertex(4)->addIncidentEdges(this->board[8]->getEdge(4), this->board[8]->getEdge(3), this->board[9]->getEdge(2));

        // LandEdges
            // vertices
    this->board[8]->getEdge(2)->setVertices(this->board[8]->getVertex(2), this->board[8]->getVertex(3));
    this->board[8]->getEdge(3)->setVertices(this->board[8]->getVertex(3), this->board[8]->getVertex(4));
    this->board[8]->getEdge(4)->setVertices(this->board[8]->getVertex(4), this->board[8]->getVertex(5));
            // edges
    this->board[8]->getEdge(2)->addAdjEdges(this->board[7]->getEdge(4), this->board[7]->getEdge(3), this->board[12]->getEdge(4), this->board[8]->getEdge(3));
    this->board[8]->getEdge(3)->addAdjEdges(this->board[8]->getEdge(2), this->board[12]->getEdge(4), this->board[9]->getEdge(2), this->board[8]->getEdge(4));
    this->board[8]->getEdge(4)->addAdjEdges(this->board[4]->getEdge(2), this->board[8]->getEdge(3), this->board[9]->getEdge(2), this->board[4]->getEdge(3));

    // Land 9
        // LandVertices
            // vertices
    this->board[9]->getVertex(3)->addNeighbors(this->board[8]->getVertex(4), this->board[13]->getVertex(4), this->board[9]->getVertex(4));
    this->board[9]->getVertex(4)->addNeighbors(this->board[5]->getVertex(3), this->board[9]->getVertex(3), this->board[10]->getVertex(3));
            // edges
    this->board[9]->getVertex(3)->addIncidentEdges(this->board[9]->getEdge(2), this->board[13]->getEdge(4), this->board[9]->getEdge(3));
    this->board[9]->getVertex(4)->addIncidentEdges(this->board[9]->getEdge(4), this->board[9]->getEdge(3), this->board[10]->getEdge(2));

        // LandEdges
            // vertices
    this->board[9]->getEdge(2)->setVertices(this->board[9]->getVertex(2), this->board[9]->getVertex(3));
    this->board[9]->getEdge(3)->setVertices(this->board[9]->getVertex(3), this->board[9]->getVertex(4));
    this->board[9]->getEdge(4)->setVertices(this->board[9]->getVertex(4), this->board[9]->getVertex(5));
            // edges
    this->board[9]->getEdge(2)->addAdjEdges(this->board[8]->getEdge(4), this->board[8]->getEdge(3), this->board[13]->getEdge(4), this->board[9]->getEdge(3));
    this->board[9]->getEdge(3)->addAdjEdges(this->board[9]->getEdge(2), this->board[13]->getEdge(4), this->board[10]->getEdge(2), this->board[9]->getEdge(4));
    this->board[9]->getEdge(4)->addAdjEdges(this->board[5]->getEdge(2), this->board[9]->getEdge(3), this->board[10]->getEdge(2), this->board[5]->getEdge(3));
    
    // Land 10
        // LandVertices
            // vertices
    this->board[10]->getVertex(3)->addNeighbors(this->board[9]->getVertex(4), this->board[14]->getVertex(4), this->board[10]->getVertex(4));
    this->board[10]->getVertex(4)->addNeighbors(this->board[6]->getVertex(3), this->board[10]->getVertex(3), this->board[11]->getVertex(3));
            // edges
    this->board[10]->getVertex(3)->addIncidentEdges(this->board[10]->getEdge(2), this->board[14]->getEdge(4), this->board[10]->getEdge(3));
    this->board[10]->getVertex(4)->addIncidentEdges(this->board[10]->getEdge(4), this->board[10]->getEdge(3), this->board[11]->getEdge(2));    

        // LandEdges
            // vertices
    this->board[10]->getEdge(2)->setVertices(this->board[10]->getVertex(2), this->board[10]->getVertex(3));
    this->board[10]->getEdge(3)->setVertices(this->board[10]->getVertex(3), this->board[10]->getVertex(4));
    this->board[10]->getEdge(4)->setVertices(this->board[10]->getVertex(4), this->board[10]->getVertex(5));
            // edges
    this->board[10]->getEdge(2)->addAdjEdges(this->board[9]->getEdge(4), this->board[9]->getEdge(3), this->board[14]->getEdge(4), this->board[10]->getEdge(3));
    this->board[10]->getEdge(3)->addAdjEdges(this->board[10]->getEdge(2), this->board[14]->getEdge(4),this->board[11]->getEdge(2), this->board[10]->getEdge(4));
    this->board[10]->getEdge(4)->addAdjEdges(this->board[6]->getEdge(2), this->board[10]->getEdge(3), this->board[11]->getEdge(2), this->board[6]->getEdge(3));
    
    // Land 11
        // LandVertices
            // vertices
    this->board[11]->getVertex(3)->addNeighbors(this->board[10]->getVertex(4), this->board[15]->getVertex(4), this->board[11]->getVertex(4));
    this->board[11]->getVertex(4)->addNeighbors(this->board[11]->getVertex(5), this->board[11]->getVertex(3), nullptr);
    this->board[11]->getVertex(5)->addNeighbors(this->board[11]->getVertex(0), this->board[11]->getVertex(4), nullptr);
            // edges
    this->board[11]->getVertex(3)->addIncidentEdges(this->board[11]->getEdge(2), this->board[15]->getEdge(4), this->board[11]->getEdge(3));
    this->board[11]->getVertex(4)->addIncidentEdges(this->board[11]->getEdge(4), this->board[11]->getEdge(3), nullptr);
    this->board[11]->getVertex(5)->addIncidentEdges(this->board[11]->getEdge(5), this->board[11]->getEdge(4), nullptr);
        
        // LandEdges
            // vertices
    this->board[11]->getEdge(2)->setVertices(this->board[11]->getVertex(2), this->board[11]->getVertex(3));
    this->board[11]->getEdge(3)->setVertices(this->board[11]->getVertex(3), this->board[11]->getVertex(4));
    this->board[11]->getEdge(4)->setVertices(this->board[11]->getVertex(4), this->board[11]->getVertex(5));
    this->board[11]->getEdge(5)->setVertices(this->board[11]->getVertex(5), this->board[11]->getVertex(0));
            // edges
    this->board[11]->getEdge(2)->addAdjEdges(this->board[10]->getEdge(4), this->board[10]->getEdge(3), this->board[15]->getEdge(4),this->board[11]->getEdge(3));
    this->board[11]->getEdge(3)->addAdjEdges(this->board[11]->getEdge(2), this->board[15]->getEdge(4), this->board[11]->getEdge(4), nullptr);
    this->board[11]->getEdge(4)->addAdjEdges(this->board[11]->getEdge(5), this->board[11]->getEdge(3), nullptr, nullptr);
    this->board[11]->getEdge(5)->addAdjEdges(this->board[6]->getEdge(4), this->board[6]->getEdge(3), this->board[11]->getEdge(4), nullptr);
    
    // Land 12
        // LandVertices
            // vertices
    this->board[12]->getVertex(2)->addNeighbors(this->board[12]->getVertex(1), this->board[12]->getVertex(3), nullptr);
    this->board[12]->getVertex(3)->addNeighbors(this->board[12]->getVertex(2), this->board[16]->getVertex(2), this->board[12]->getVertex(4));
    this->board[12]->getVertex(4)->addNeighbors(this->board[8]->getVertex(3), this->board[12]->getVertex(3), this->board[13]->getVertex(3));
            // edges
    this->board[12]->getVertex(2)->addIncidentEdges(this->board[12]->getEdge(1), this->board[12]->getEdge(2), nullptr);
    this->board[12]->getVertex(3)->addIncidentEdges(this->board[12]->getEdge(2), this->board[16]->getEdge(1), this->board[12]->getEdge(3));
    this->board[12]->getVertex(4)->addIncidentEdges(this->board[12]->getEdge(4), this->board[12]->getEdge(3), this->board[13]->getEdge(2));

        // LandEdges
            // vertices
    this->board[12]->getEdge(1)->setVertices(this->board[12]->getVertex(1), this->board[12]->getVertex(2));
    this->board[12]->getEdge(2)->setVertices(this->board[12]->getVertex(2), this->board[12]->getVertex(3));
    this->board[12]->getEdge(3)->setVertices(this->board[12]->getVertex(3), this->board[12]->getVertex(4));
    this->board[12]->getEdge(4)->setVertices(this->board[12]->getVertex(4), this->board[12]->getVertex(5));
            // edges
    this->board[12]->getEdge(1)->addAdjEdges(this->board[7]->getEdge(2), this->board[12]->getEdge(2), this->board[7]->getEdge(3), nullptr);
    this->board[12]->getEdge(2)->addAdjEdges(this->board[12]->getEdge(1), this->board[16]->getEdge(1), this->board[16]->getEdge(0), nullptr);
    this->board[12]->getEdge(3)->addAdjEdges(this->board[12]->getEdge(2), this->board[16]->getEdge(1), this->board[13]->getEdge(2), this->board[12]->getEdge(4));
    this->board[12]->getEdge(4)->addAdjEdges(this->board[8]->getEdge(2), this->board[12]->getEdge(3), this->board[13]->getEdge(2), this->board[8]->getEdge(3));

    // Land 13
        // LandVertices
            // vertices
    this->board[13]->getVertex(3)->addNeighbors(this->board[12]->getVertex(4), this->board[16]->getVertex(4),this->board[13]->getVertex(4));
    this->board[13]->getVertex(4)->addNeighbors(this->board[9]->getVertex(3), this->board[13]->getVertex(3), this->board[14]->getVertex(3));
            // edges
    this->board[13]->getVertex(3)->addIncidentEdges(this->board[13]->getEdge(2), this->board[16]->getEdge(4), this->board[13]->getEdge(3));
    this->board[13]->getVertex(4)->addIncidentEdges(this->board[13]->getEdge(4), this->board[13]->getEdge(3), this->board[14]->getEdge(2));

        // LandEdges
            // vertices
    this->board[13]->getEdge(2)->setVertices(this->board[13]->getVertex(2), this->board[13]->getVertex(3));
    this->board[13]->getEdge(3)->setVertices(this->board[13]->getVertex(3), this->board[13]->getVertex(4));
    this->board[13]->getEdge(4)->setVertices(this->board[13]->getVertex(4), this->board[13]->getVertex(5));
            // edges
    this->board[13]->getEdge(2)->addAdjEdges(this->board[13]->getEdge(1), this->board[12]->getEdge(3), this->board[16]->getEdge(4), this->board[13]->getEdge(3));
    this->board[13]->getEdge(3)->addAdjEdges(this->board[13]->getEdge(2), this->board[16]->getEdge(4), this->board[14]->getEdge(2), this->board[13]->getEdge(4));
    this->board[13]->getEdge(4)->addAdjEdges(this->board[9]->getEdge(2), this->board[13]->getEdge(3), this->board[14]->getEdge(2), this->board[9]->getEdge(3));
    
    // Land 14
        // LandVertices
            // vertices
    this->board[14]->getVertex(3)->addNeighbors(this->board[13]->getVertex(4), this->board[17]->getVertex(4), this->board[14]->getVertex(4));
    this->board[14]->getVertex(4)->addNeighbors(this->board[10]->getVertex(3), this->board[14]->getVertex(3), this->board[15]->getVertex(3));
            // edges
    this->board[14]->getVertex(3)->addIncidentEdges(this->board[14]->getEdge(2), this->board[17]->getEdge(4), this->board[14]->getEdge(3));
    this->board[14]->getVertex(4)->addIncidentEdges(this->board[14]->getEdge(4), this->board[14]->getEdge(3), this->board[15]->getEdge(2));
        
        // LandEdges
            // vertices
    this->board[14]->getEdge(2)->setVertices(this->board[14]->getVertex(2), this->board[14]->getVertex(3));
    this->board[14]->getEdge(3)->setVertices(this->board[14]->getVertex(3), this->board[14]->getVertex(4));
    this->board[14]->getEdge(4)->setVertices(this->board[14]->getVertex(4), this->board[14]->getVertex(5));       
            // edges
    this->board[14]->getEdge(2)->addAdjEdges(this->board[13]->getEdge(4), this->board[13]->getEdge(3), this->board[17]->getEdge(4), this->board[14]->getEdge(3));
    this->board[14]->getEdge(3)->addAdjEdges(this->board[14]->getEdge(2), this->board[17]->getEdge(4), this->board[15]->getEdge(2), this->board[14]->getEdge(4));
    this->board[14]->getEdge(4)->addAdjEdges(this->board[10]->getEdge(2), this->board[14]->getEdge(3), this->board[15]->getEdge(2), this->board[10]->getEdge(3));
    
    // Land 15
        // LandVertices
            // vertices
    this->board[15]->getVertex(3)->addNeighbors(this->board[14]->getVertex(4), this->board[18]->getVertex(4), this->board[15]->getVertex(4));
    this->board[15]->getVertex(4)->addNeighbors(this->board[11]->getVertex(3), this->board[15]->getVertex(3), nullptr);
            // edges
    this->board[15]->getVertex(3)->addIncidentEdges(this->board[15]->getEdge(2), this->board[18]->getEdge(4), this->board[15]->getEdge(3));
    this->board[15]->getVertex(4)->addIncidentEdges(this->board[15]->getEdge(4), this->board[15]->getEdge(3), nullptr);
        
        // LandEdges
            // vertices
    this->board[15]->getEdge(2)->setVertices(this->board[15]->getVertex(2), this->board[15]->getVertex(3));
    this->board[15]->getEdge(3)->setVertices(this->board[15]->getVertex(3), this->board[15]->getVertex(4));
    this->board[15]->getEdge(4)->setVertices(this->board[15]->getVertex(4), this->board[15]->getVertex(5));
            // edges
    this->board[15]->getEdge(2)->addAdjEdges(this->board[14]->getEdge(4), this->board[14]->getEdge(3), this->board[18]->getEdge(4), this->board[15]->getEdge(3));
    this->board[15]->getEdge(3)->addAdjEdges(this->board[15]->getEdge(2), this->board[18]->getEdge(4), this->board[15]->getEdge(4), nullptr);
    this->board[15]->getEdge(4)->addAdjEdges(this->board[15]->getEdge(5), this->board[15]->getEdge(3), this->board[11]->getEdge(3), nullptr);
    
    // Land 16
        // LandVertices
            // vertices
    this->board[16]->getVertex(2)->addNeighbors(this->board[16]->getVertex(1), this->board[16]->getVertex(3), nullptr);
    this->board[16]->getVertex(3)->addNeighbors(this->board[16]->getVertex(2), this->board[16]->getVertex(4), nullptr);
    this->board[16]->getVertex(4)->addNeighbors(this->board[13]->getVertex(3), this->board[16]->getVertex(3), this->board[17]->getVertex(3));
            // edges
    this->board[16]->getVertex(2)->addIncidentEdges(this->board[16]->getEdge(1), this->board[16]->getEdge(2), nullptr);
    this->board[16]->getVertex(3)->addIncidentEdges(this->board[16]->getEdge(2), this->board[16]->getEdge(3), nullptr);
    this->board[16]->getVertex(4)->addIncidentEdges(this->board[16]->getEdge(4), this->board[16]->getEdge(3), this->board[17]->getEdge(2));
        
        // LandEdges
            // vertices
    this->board[16]->getEdge(1)->setVertices(this->board[16]->getVertex(1), this->board[16]->getVertex(2));
    this->board[16]->getEdge(2)->setVertices(this->board[16]->getVertex(2), this->board[16]->getVertex(3));
    this->board[16]->getEdge(3)->setVertices(this->board[16]->getVertex(3), this->board[16]->getVertex(4));
    this->board[16]->getEdge(4)->setVertices(this->board[16]->getVertex(4), this->board[16]->getVertex(5));
            // edges
    this->board[16]->getEdge(1)->addAdjEdges(this->board[12]->getEdge(2), this->board[16]->getEdge(2), this->board[12]->getEdge(3), nullptr);
    this->board[16]->getEdge(2)->addAdjEdges(this->board[16]->getEdge(1), this->board[16]->getEdge(3), nullptr, nullptr);
    this->board[16]->getEdge(3)->addAdjEdges(this->board[16]->getEdge(2), this->board[17]->getEdge(2), this->board[16]->getEdge(4), nullptr);
    this->board[16]->getEdge(4)->addAdjEdges(this->board[13]->getEdge(2), this->board[16]->getEdge(3), this->board[17]->getEdge(2), this->board[13]->getEdge(3));
    
    // Land 17
        // LandVertices
            // vertices
    this->board[17]->getVertex(3)->addNeighbors(this->board[17]->getVertex(2), this->board[17]->getVertex(4), nullptr);
    this->board[17]->getVertex(4)->addNeighbors(this->board[14]->getVertex(3), this->board[17]->getVertex(3), this->board[18]->getVertex(3));
            // edges
    this->board[17]->getVertex(3)->addIncidentEdges(this->board[17]->getEdge(2), this->board[17]->getEdge(3), nullptr);
    this->board[17]->getVertex(4)->addIncidentEdges(this->board[17]->getEdge(4), this->board[17]->getEdge(3), this->board[18]->getEdge(2));
        
        // LandEdges
            // vertices
    this->board[17]->getEdge(2)->setVertices(this->board[17]->getVertex(2), this->board[17]->getVertex(3));
    this->board[17]->getEdge(3)->setVertices(this->board[17]->getVertex(3), this->board[17]->getVertex(4));
    this->board[17]->getEdge(4)->setVertices(this->board[17]->getVertex(4), this->board[17]->getVertex(5));
            // edges
    this->board[17]->getEdge(2)->addAdjEdges(this->board[16]->getEdge(4), this->board[16]->getEdge(3), this->board[17]->getEdge(3), nullptr);
    this->board[17]->getEdge(3)->addAdjEdges(this->board[17]->getEdge(2), this->board[18]->getEdge(2), this->board[17]->getEdge(4), nullptr);
    this->board[17]->getEdge(4)->addAdjEdges(this->board[14]->getEdge(2), this->board[17]->getEdge(3), this->board[18]->getEdge(2), this->board[14]->getEdge(3));
    
    // Land 18
        // LandVertices
            // vertices
    this->board[18]->getVertex(3)->addNeighbors(this->board[18]->getVertex(2), this->board[18]->getVertex(4), nullptr);
    this->board[18]->getVertex(4)->addNeighbors(this->board[15]->getVertex(3), this->board[18]->getVertex(3), nullptr);
            // edges
    this->board[18]->getVertex(3)->addIncidentEdges(this->board[18]->getEdge(2), this->board[18]->getEdge(3), nullptr);
    this->board[18]->getVertex(4)->addIncidentEdges(this->board[18]->getEdge(4), this->board[18]->getEdge(3), nullptr);
        
        // LandEdges
            // vertices
    this->board[18]->getEdge(2)->setVertices(this->board[18]->getVertex(2), this->board[18]->getVertex(3));
    this->board[18]->getEdge(3)->setVertices(this->board[18]->getVertex(3), this->board[18]->getVertex(4));
    this->board[18]->getEdge(4)->setVertices(this->board[18]->getVertex(4), this->board[18]->getVertex(5));
            // edges
    this->board[18]->getEdge(2)->addAdjEdges(this->board[17]->getEdge(4), this->board[17]->getEdge(3), this->board[18]->getEdge(3), nullptr);
    this->board[18]->getEdge(3)->addAdjEdges(this->board[18]->getEdge(2), this->board[18]->getEdge(4), nullptr, nullptr);
    this->board[18]->getEdge(4)->addAdjEdges(this->board[15]->getEdge(2), this->board[18]->getEdge(3), this->board[15]->getEdge(3), nullptr);

}

catan::Player* catan::Catan::start()
{
    this->playRound0();
    Player* winner = nullptr;
    while((winner = isGameOver()) == nullptr)
    {
        playTurn();
    }
    cout << winner->getName() << " has won the game!" << endl;
    return winner;
}

catan::Player* catan::Catan::start(string inp)
{
    std::streambuf* orig = cin.rdbuf();
    std::istringstream input(inp);
    cin.rdbuf(input.rdbuf());
    
    this->playRound0();
    Player* winner = nullptr;
    playTurn();
    playTurn();
    playTurn();
    cin.rdbuf(orig);  
    while((winner = isGameOver()) == nullptr)
    {
        playTurn();
    }
    cout << winner->getName() << " has won the game!" << endl;
    return winner;
}

int catan::Catan::trade(Player* sender, Player *receiver, vector<int> giveResources, vector<int> recvResources, vector<int> giveCard, vector<int> recvCard)
{
    cout << sender->getName() << " wants to trade " << endl;
    for(size_t i = 0; i < giveResources.size(); i++)
    {
        cout << giveResources[i] << " of resource type" << i << endl;
    }
    cout << " and " << endl;
    for(size_t i = 0; i < giveCard.size(); i++)
    {
        cout << giveCard[i] << " of card type" << i << endl;
    }
    cout << "for" << endl;
    for(size_t i = 0; i < recvResources.size(); i++)
    {
        cout << recvResources[i] << " of resource type" << i << endl;
    }
    cout << " and " << endl;
    for(size_t i = 0; i < recvCard.size(); i++)
    {
        cout << recvCard[i] << " of card type" << i << endl;
    }
    cout << receiver->getName() << " do you accept? (y/n)" << endl;
    char response;
    cin >> response;
    if(response == 'y')
    {
        for(size_t i = 0; i < giveResources.size(); i++)
        {
            if(sender->getResource(i) < giveResources[i])
            {
                return -1;
            }
        }
        for(size_t i = 0; i < giveCard.size(); i++)
        {
            if(sender->getDevCards()[i].second < giveCard[i])
            {
                return -1;
            }
        }
        for(size_t i = 0; i < recvResources.size(); i++)
        {
            if(receiver->getResource(i) < recvResources[i])
            {
                return -1;
            }
        }
        for(size_t i = 0; i < recvCard.size(); i++)
        {
            if(receiver->getDevCards()[i].second < recvCard[i])
            {
                return -1;
            }
        }
        for(size_t i = 0; i < giveResources.size(); i++)
        {
            sender->removeResource(i, giveResources[i]);
            receiver->addResource(i, giveResources[i]);
        }
        for(size_t i = 0; i < giveCard.size(); i++)
        {
            for(size_t j = 0; j < giveCard[i]; j++)
            {
                Card* card = sender->getDevCards()[i].first->clone();
                receiver->addDevCard(card);
                sender->removeDevCard(card);
                if(sender->getDevCards()[i].second > 1)
                {
                    delete card;
                }
            }
        }
        for(size_t i = 0; i < recvResources.size(); i++)
        {
            receiver->removeResource(i, recvResources[i]);
            sender->addResource(i, recvResources[i]);
        }
        for(size_t i = 0; i < recvCard.size(); i++)
        {
            for(size_t j = 0; j < recvCard[i]; j++)
            {
                Card* card = receiver->getDevCards()[i].first->clone();
                sender->addDevCard(card);
                receiver->removeDevCard(card);
                if(sender->getDevCards()[i].second > 1)
                {
                    delete card;
                }
            }
        }
        return 0;
    }
    else
    {
        cout << "Trade declined" << endl;
        return -2;
    }
    return -1;
}

void catan::Catan::playTurn()
{
    this->displayBoard();
    Player* currentPlayer = players[(size_t)this->curPlayer]; 
    cout << currentPlayer->getName() << " turn" << endl;
    currentPlayer->playTurn(this);
    this->curPlayer = (this->curPlayer + 1) % 3;
}   

catan::Player* catan::Catan::isGameOver()
{
    for(size_t i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i]->getVictoryPoints() >= 10)
        {
            return players[i];
        }
    }
    return nullptr;
}

int catan::Catan::getLandIndex(Land* land)
{
    for(const auto& pair : this->landNum)
    {
        const int key = pair.first;
        const vector<Land*> value = pair.second;
        for(const auto& item : value)
        {
            if(item == land)
            {
                return key;
            }
        }
    }
    return -1;
}

int catan::Catan::placeSettlement(Player* player, size_t landNum, size_t vertexIndex, bool round0)
{
    if(this->board[landNum]->getVertex(vertexIndex)->getOwner() != nullptr)
    {
        // vertex is already occupied
        return -1;
    }
    if(!this->board[landNum]->getVertex(vertexIndex)->settRadValid())
    {
        // vertex is too close to another settlement
        return -2;
    }
    if(!round0)
    {
        if(!this->board[landNum]->getVertex(vertexIndex)->settRoadValid(player))
        {
            // vertex is not connected to a road owned by the player
            return -3;
        }
    }
    if(round0)
    {
        vector<int> res = this->board[landNum]->getVertex(vertexIndex)->getResources();
        for(size_t i = 0; i < res.size(); i++)
        {
            if(res[i] != DESERT)
            {
                if(player->getResource(res[i]) < 1)
                {
                    player->addResource(res[i], 1);
                }
            }
        }
    }
    this->board[landNum]->getVertex(vertexIndex)->placeSettlement(player);

    return 0;
}

int catan::Catan::placeCity(Player* player, size_t landNum, size_t vertexIndex)
{
    if(this->board[landNum]->getVertex(vertexIndex)->getOwner() == nullptr)
    {
        // need a settlement first
        return -1;
    }
    if(this->board[landNum]->getVertex(vertexIndex)->getOwner() != player)
    {
        // vertex is not owned by the player
        return -2;
    }
    if(!this->board[landNum]->getVertex(vertexIndex)->isSettlementf())
    {
        // vertex is already a city
        return -3;
    }
    this->board[landNum]->getVertex(vertexIndex)->placeCity();
    return 0;
}

int catan::Catan::placeRoad(Player* player, size_t landNum, size_t edgeIndex)
{
    if(this->board[landNum]->getEdge(edgeIndex)->getOwner() != nullptr)
    {
        // edge is already occupied
        return -1;
    }
    if(!this->board[landNum]->getEdge(edgeIndex)->roadValid(player))
    {
        // edge is not connected to a settlement or another road owned by the player
        return -2;
    }
    this->board[landNum]->getEdge(edgeIndex)->placeRoad(player);
    return 0;
}

int catan::Catan::buyDevCard(Player *player)
{
    if(player->getResource(WHEAT) < 1 || player->getResource(WOOL) < 1 || player->getResource(IRON) < 1)
    {
        // not enough resources
        return -1;
    }
    player->removeResource(WHEAT, 1);
    player->removeResource(WOOL, 1);
    player->removeResource(IRON, 1);
    return 0;
}

catan::Card* catan::Catan::drawDevCard(Player* player)
{
    size_t index = (size_t)rand() % 5;
    while(this->devCardsDeck[index].second == 0)
    {
        index = (size_t)rand() % 5;
    }
    if(this->devCardsDeck[index].second > 0)
    {
        this->devCardsDeck[index].second--;
        if(this->devCardsDeck[index].second == 0)
        {
            Card* card = this->devCardsDeck[index].first->clone();
            delete this->devCardsDeck[index].first;
            this->devCardsDeck[index].first = nullptr;
            return card;
        }
    }
    return this->devCardsDeck[index].first->clone();
}

void catan::Catan::takeOthersResources(Player* player, int resource)
{
    for(size_t i = 0; i < MAX_PLAYERS; i++)
    {
        int amount = 0;
        if(this->players[i] != player)
        {
            amount = this->players[i]->getResource(resource);
            player->addResource(resource, amount);
            this->players[i]->removeResource(resource, amount);  
            cout << player->getName() << " has taken " << amount << " " << this->intToResource(resource) << " from " << this->players[i]->getName() << "" << endl;
        }
    }
}

void catan::Catan::displayPlayersResources()
{
    for(size_t i = 0; i < MAX_PLAYERS; i++)
    {
        this->players[i]->displayResources();
    }
}

string catan::Catan::intToResource(int resource)
{
    switch(resource)
    {
        case BRICK:
            return "brick";
        case WOOD:
            return "wood";
        case WOOL:
            return "wool";
        case WHEAT:
            return "wheat";
        case IRON:
            return "iron";
        default:
            return "invalid resource";
    }
}

void catan::Catan::displayBoard()
{
    cout << "            " << this->board[0]->getVertex(0)->getConstructionSymbol() << "      " << this->board[1]->getVertex(0)->getConstructionSymbol() << "       " << this->board[2]->getVertex(0)->getConstructionSymbol() << "\n"
         << "          " << this->board[0]->getEdge(0)->getColor() << "/   " << this->board[0]->getEdge(5)->getColor() << "\\  " << this->board[1]->getEdge(0)->getColor() << "/   " << this->board[1]->getEdge(5)->getColor() << "\\   " << this->board[2]->getEdge(0)->getColor() << "/   " << this->board[2]->getEdge(5)->getColor() << "\\\033[0m\n"
         << "         " << this->board[0]->getVertex(1)->getConstructionSymbol() << "     " << this->board[0]->getVertex(5)->getConstructionSymbol() << "       " << this->board[1]->getVertex(5)->getConstructionSymbol() << "      " << this->board[2]->getVertex(5)->getConstructionSymbol() << "\n"
         << "         " << this->board[0]->getEdge(1)->getColor() << "| " << this->board[0]->getLandSymbol() << this->board[0]->getEdge(4)->getColor() << "  |" << "  " << this->board[1]->getLandSymbol() << this->board[1]->getEdge(4)->getColor() << "   |  " << this->board[2]->getLandSymbol() << "  " << this->board[2]->getEdge(4)->getColor() << "|\033[0m\n"
         << "         " << this->board[0]->getVertex(2)->getConstructionSymbol() << " " << this->getLandIndex(this->board[0]) << "  " << this->board[0]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[1]) << "   " << this->board[1]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[2]) << "  " << this->board[2]->getVertex(4)->getConstructionSymbol() << "\n"
         << "       " << this->board[3]->getEdge(0)->getColor() << "/   " << this->board[3]->getEdge(5)->getColor() << "\\ " << this->board[4]->getEdge(0)->getColor() << "/   " << this->board[4]->getEdge(5)->getColor() << "\\   " << this->board[5]->getEdge(0)->getColor() << "/   " << this->board[5]->getEdge(5)->getColor() << "\\  " << this->board[6]->getEdge(0)->getColor() << "/   " << this->board[6]->getEdge(5)->getColor() << "\\\033[0m\n"
         << "      " << this->board[3]->getVertex(1)->getConstructionSymbol() << "     " << this->board[3]->getVertex(5)->getConstructionSymbol() << "      " << this->board[4]->getVertex(5)->getConstructionSymbol() << "      " << this->board[5]->getVertex(5)->getConstructionSymbol() << "      " << this->board[6]->getVertex(5)->getConstructionSymbol() << "\n"
         << "      " << this->board[3]->getEdge(1)->getColor() << "| " << this->board[3]->getLandSymbol() << this->board[3]->getEdge(4)->getColor() << "  |  " << this->board[4]->getLandSymbol() << this->board[4]->getEdge(4)->getColor() << "  |  " << this->board[5]->getLandSymbol() << this->board[5]->getEdge(4)->getColor() << "  |  " << this->board[6]->getLandSymbol() << "  " << this->board[6]->getEdge(4)->getColor() << "|\033[0m\n"
         << "      " << this->board[3]->getVertex(2)->getConstructionSymbol() << " " << this->getLandIndex(this->board[3]) << "  " << this->board[3]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[4]) << "   " << this->board[4]->getVertex(4)->getConstructionSymbol() << "  " << this->getLandIndex(this->board[5]) << "  " << this->board[5]->getVertex(4)->getConstructionSymbol() << "  " << this->getLandIndex(this->board[6]) << "  " << this->board[6]->getVertex(4)->getConstructionSymbol() << "\n"
         << "    " << this->board[7]->getEdge(0)->getColor() << "/   " << this->board[7]->getEdge(5)->getColor() << "\\ " << this->board[8]->getEdge(0)->getColor() << "/   " << this->board[8]->getEdge(5)->getColor() << "\\   " << this->board[9]->getEdge(0)->getColor() << "/   " << this->board[9]->getEdge(5)->getColor() << "\\ " << this->board[10]->getEdge(0)->getColor() << "/   " << this->board[10]->getEdge(5)->getColor() << "\\  " << this->board[11]->getEdge(0)->getColor() << "/   " << this->board[11]->getEdge(5)->getColor() << "\\\033[0m\n"
         << "   " << this->board[7]->getVertex(1)->getConstructionSymbol() << "     " << this->board[7]->getVertex(5)->getConstructionSymbol() << "      " << this->board[8]->getVertex(5)->getConstructionSymbol() << "      " << this->board[9]->getVertex(5)->getConstructionSymbol() << "     " << this->board[10]->getVertex(5)->getConstructionSymbol() << "      " << this->board[11]->getVertex(5)->getConstructionSymbol() << "\n"
         << "   " << this->board[7]->getEdge(1)->getColor() << "| " << this->board[7]->getLandSymbol() << this->board[7]->getEdge(4)->getColor() << "  |  " << this->board[8]->getLandSymbol() << this->board[8]->getEdge(4)->getColor() << "  |  " << this->board[9]->getLandSymbol() << this->board[9]->getEdge(4)->getColor() << "   | " << this->board[10]->getLandSymbol() << this->board[10]->getEdge(4)->getColor() << "  |  " << this->board[11]->getLandSymbol() << "  " << this->board[11]->getEdge(4)->getColor() << "|\033[0m\n"
         << "   " << this->board[7]->getVertex(2)->getConstructionSymbol() << "  " << this->getLandIndex(this->board[7]) << "  " << this->board[7]->getVertex(4)->getConstructionSymbol() << "  " << this->getLandIndex(this->board[8]) << "  " << this->board[8]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[9]) << "  " << this->board[9]->getVertex(4)->getConstructionSymbol() << "  " << this->getLandIndex(this->board[10]) << "  " << this->board[10]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[11]) << "  " << this->board[11]->getVertex(4)->getConstructionSymbol() << "\n"
         << "    " << this->board[7]->getEdge(2)->getColor() << "\\   " << this->board[7]->getEdge(3)->getColor() << "/ " << this->board[8]->getEdge(2)->getColor() << "\\    " << this->board[8]->getEdge(3)->getColor() << "/   " << this->board[9]->getEdge(2)->getColor() << "\\ " << this->board[9]->getEdge(3)->getColor() << "/   " << this->board[10]->getEdge(2)->getColor() << "\\ " << this->board[10]->getEdge(3)->getColor() << "/   " << this->board[11]->getEdge(2)->getColor() << "\\   " << this->board[11]->getEdge(3)->getColor() << "/\033[0m\n"
         << "      " << this->board[12]->getVertex(1)->getConstructionSymbol() << "     " << this->board[12]->getVertex(5)->getConstructionSymbol() << "      " << this->board[13]->getVertex(5)->getConstructionSymbol() << "      " << this->board[14]->getVertex(5)->getConstructionSymbol() << "      " << this->board[15]->getVertex(5)->getConstructionSymbol() << "\n"
         << "      " << this->board[12]->getEdge(1)->getColor() << "| " << this->board[12]->getLandSymbol() << this->board[12]->getEdge(4)->getColor() << "  |  " << this->board[13]->getLandSymbol() << this->board[13]->getEdge(4)->getColor() << "  |  " << this->board[14]->getLandSymbol() << this->board[14]->getEdge(4)->getColor() << "  |  " << this->board[15]->getLandSymbol() << this->board[15]->getEdge(4)->getColor() << "  |\033[0m\n"
         << "      " << this->board[12]->getVertex(2)->getConstructionSymbol() << "  " << this->getLandIndex(this->board[12]) << "  " << this->board[12]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[13]) << "  " << this->board[13]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[14]) << "  " << this->board[14]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[15]) << "  " << this->board[15]->getVertex(4)->getConstructionSymbol() << "\n"
         << "       " << this->board[12]->getEdge(2)->getColor() << "\\   " << this->board[12]->getEdge(3)->getColor() << "/  " << this->board[13]->getEdge(2)->getColor() << "\\   " << this->board[13]->getEdge(3)->getColor() << "/  " << this->board[14]->getEdge(2)->getColor() << "\\   " << this->board[14]->getEdge(3)->getColor() << "/  " << this->board[15]->getEdge(2)->getColor() << "\\   " << this->board[15]->getEdge(3)->getColor() << "/\033[0m\n"
         << "         " << this->board[16]->getVertex(1)->getConstructionSymbol() << "      " << this->board[16]->getVertex(5)->getConstructionSymbol() << "      " << this->board[17]->getVertex(5)->getConstructionSymbol() << "      " << this->board[18]->getVertex(5)->getConstructionSymbol() << "\n"
         << "         " << this->board[16]->getEdge(1)->getColor() << "|  " << this->board[16]->getLandSymbol() << this->board[16]->getEdge(4)->getColor() << "  |  " << this->board[17]->getLandSymbol() << this->board[17]->getEdge(4)->getColor() << "  |  " << this->board[18]->getLandSymbol() << this->board[18]->getEdge(4)->getColor() << "  |\033[0m\n"
         << "         " << this->board[16]->getVertex(2)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[16]) << "  " << this->board[16]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[17]) << "  " <<this->board[17]->getVertex(4)->getConstructionSymbol() << "   " << this->getLandIndex(this->board[18]) << " " << this->board[18]->getVertex(4)->getConstructionSymbol() << "\n"
         << "           " << this->board[16]->getEdge(2)->getColor() << "\\   " << this->board[16]->getEdge(3)->getColor() << "/  " << this->board[17]->getEdge(2)->getColor() << "\\   " << this->board[17]->getEdge(3)->getColor() << "/  " << this->board[18]->getEdge(2)->getColor() << "\\   " << this->board[18]->getEdge(3)->getColor() << "/\033[0m\n"
         << "             " << this->board[16]->getVertex(3)->getConstructionSymbol() << "      " << this->board[17]->getVertex(3)->getConstructionSymbol() << "      " << this->board[18]->getVertex(3)->getConstructionSymbol() << "\n";
}
