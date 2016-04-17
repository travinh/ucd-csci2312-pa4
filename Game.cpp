//
// Created by Vinh Van Tran on 4/17/16.
//

#include<iomanip>

#include"Exceptions.h"
#include"Game.h"
#include"Simple.h"
#include"Strategic.h"
#include"Food.h"
#include"Advantage.h"


namespace Gaming
{
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

     const unsigned Game::MIN_WIDTH =3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;


    void Game::populate()
    {
        int __numInitAgents = (__width * __height )/NUM_INIT_AGENT_FACTOR;
        int __numInitResources = (__width * __height)/NUM_INIT_RESOURCE_FACTOR;
        unsigned numStrategic = __numInitAgents/2;
        unsigned numSimple = __numInitAgents - numStrategic;
        unsigned numAdvantages = __numInitResources/4;
        unsigned numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height -1);


        while(numFoods > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL and i!= (__width * __height))
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                 numFoods--;
            }
        }


        while(numStrategic > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL and i!= (__width * __height))
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                 numStrategic--;
            }
        }


        while(numSimple > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL and i!= (__width * __height))
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                 numSimple--;
            }
        }


        while(numAdvantages > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL and i!= (__width * __height))
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                 numAdvantages--;
            }
        }


    }

    //PublicPublic

    //Constructor

    Game::Game():
        __width(Game::MIN_WIDTH),
        __height(Game::MIN_HEIGHT)

    {
        for(unsigned int i = 0; i < __width*__height; i++)
            __grid.push_back(NULL);

         __status= NOT_STARTED;
        __verbose= false;
        __round = 0;
    }

    Game::Game(unsigned int width, unsigned int height, bool manual):
        __width(width),
        __height(height)
    {
         if(height < Game::MIN_HEIGHT || width < Game::MIN_WIDTH)
             throw InsufficientDimensionsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, width, height);

        __status= NOT_STARTED;
        __verbose=false;
        __round=0;

         for(unsigned int i = 0; i < width*height; i++)
             __grid.push_back(NULL);

         if(!manual)
             populate();
    }

    //Destrct
    Game::~Game()
    {
        for(auto i = __grid.begin(); i != __grid.end(); ++i)
            if(*i != NULL)
                delete *i;
    }


    unsigned int Game::getNumPieces() const
    {
        unsigned int num = 0;
        for(auto i = __grid.begin(); i != __grid.end(); i++)
            if(*i != NULL)
                num++;
        return num;
    }

    unsigned int Game::getNumAgents() const
    {
         unsigned int num = 0;
         for(auto i = __grid.begin(); i != __grid.end(); i++)
         {
             Agent* test = dynamic_cast<Agent*>(*i);
             if(test)
                 num++;
         }
         return num;
    }

    unsigned int Game::getNumSimple() const
    {
         unsigned int num = 0;
         for(auto i = __grid.begin(); i != __grid.end(); i++)
         {
             Simple* test = dynamic_cast<Simple*>(*i);
             if(test)
                 num++;
         }
         return num;
    }

    unsigned int Game::getNumStrategic() const
    {
         unsigned int num = 0;
         for(auto i = __grid.begin(); i != __grid.end(); ++i)
         {
             Strategic* test = dynamic_cast<Strategic*>(*i);
             if(test)
                 num++;
         }
         return num;
    }

    unsigned int Game::getNumResources() const
    {
         unsigned int num = 0;
         for(auto i = __grid.begin(); i != __grid.end(); ++i)
         {
             Resource* test = dynamic_cast<Resource*>(*i);
             if(test)
                 num++;
         }
         return num;
    }

    const Piece* Game::getPiece(unsigned int x, unsigned int y) const
    {
         if(y >= __width ||  x >=__height)
             throw OutOfBoundsEx(__height, __width, x, y);


        if (__grid[y + (x * __width)] == nullptr) throw PositionEmptyEx(x, y);
        return __grid[y + (x * __width)];
    }

    void Game::addSimple(const Position &position)
    {
         int i = position.x * __width + position.y;

         if( position.y >= __width|| position.x >= __height)
             throw OutOfBoundsEx(__height, __width, position.x, position.y);



         if(__grid[i])
             throw PositionNonemptyEx(position.x, position.y);

         __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
    }


    void Game::addSimple(const Position &position, double energy)
    {
        int i = position.x * __width + position.y;

         if(position.y >=__width || position.x >= __height)
             throw OutOfBoundsEx(__height, __width, position.x, position.y);


         if(__grid[i])
             throw PositionNonemptyEx(position.x, position.y);

         __grid[i] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned int x, unsigned int y)
    {    int i = x * __width + y;

         if( y >= __width ||  x >= __height)
             throw OutOfBoundsEx(__height, __width, x, y);

         if(__grid[i])
             throw PositionNonemptyEx(x, y);

         __grid[i] = new Simple(*this, Position(x,y), Game::STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned int x, unsigned int y, double energy)
    {
         int i = x * __width + y;

         if(y >= __width || x >=__height)
             throw OutOfBoundsEx(__height, __width, x, y);

         if(__grid[i])
             throw PositionNonemptyEx(x, y);


         __grid[i] = new Simple(*this, Position(x,y), energy);

    }

    void Game::addStrategic(const Position &p, Strategy *s)
    {
         int i = p.x * __width + p.y;

         if(p.y >__width || p.x >= __height)
             throw OutOfBoundsEx(__height, __width, p.x, p.y);

         if(__grid[i])
             throw PositionNonemptyEx(p.x, p.y);

         __grid[i] = new Strategic(*this, p, Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned int x, unsigned int y, Strategy *s)
    {
         int i = x * __width + y;

         if(y >= __width || x>=__height)
             throw OutOfBoundsEx(__height, __width, x, y);

         if(__grid[i])
             throw PositionNonemptyEx(x, y);

         __grid[i] = new Strategic(*this, Position(x,y), Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &p)
    {
        int i = p.x * __width + p.y;

        if(p.y >__width || p.x >= __height)
             throw OutOfBoundsEx(__height, __width, p.x, p.y);

         if(__grid[i])
             throw PositionNonemptyEx(p.x, p.y);

         __grid[i] = new Food(*this, p, Game::STARTING_RESOURCE_CAPACITY);
    }


    void Game::addFood(unsigned int x, unsigned int y)
    {
        int i = x * __width + y;

        if(y >= __width || x>=__height)
             throw OutOfBoundsEx(__height, __width, x, y);

         if(__grid[i])
             throw PositionNonemptyEx(x, y);

         __grid[i] = new Food(*this, Position(x,y), Game::STARTING_RESOURCE_CAPACITY);
    }


    void Game::addAdvantage(const Position &p)
    {
        int i = p.x * __width + p.y;

        if(p.y >__width || p.x >= __height)
             throw OutOfBoundsEx(__height, __width, p.x, p.y);

         if(__grid[i])
             throw PositionNonemptyEx(p.x, p.y);

         __grid[i] = new Advantage(*this, p, Game::STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned int x, unsigned int y)
    {
        int i = x * __width + y;
        if(y >= __width || x>=__height)
             throw OutOfBoundsEx(__height, __width, x, y);

         if(__grid[i])
             throw PositionNonemptyEx(x, y);

         __grid[i] = new Advantage(*this, Position(x,y), Game::STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings surround;

        //initial
        for(int i = 0; i < 9; ++i)
            surround.array[i] = EMPTY;

        for(int row = -1; row < 2; row++)
        {
            for (int col = -1; col < 2; col++)
            {
                if (pos.x + row < 0 || pos.x + row >= __height || pos.y + col < 0 || pos.y + col >= __width)
                    surround.array[col + 3 * row + 4] = INACCESSIBLE;
                else if (__grid[pos.y + col + __width * (pos.x + row)])
                    surround.array[col + 3 * row + 4] = __grid[pos.y + col + __width * (pos.x + row)]->getType();
            }
        }
        surround.array[4] = SELF;
        return surround;
    }

    //static stuff
    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        int x = to.x - from.x, y = to.y - from.y;

        if(x == -1 && y == 0)  //Go up one
            return N;
        if(x == -1 && y == -1) //Go up one and go left one
            return NW;
        if(x == 0 && y == -1)  //Go left one
            return W;
        if(x == -1 && y == 1)  //Go up one and go right one
            return NE;

        if(x == 1 && y == 0)   //Go down one
            return S;
        if(x == 1 && y == -1)  //Go down one and go left one
            return SW;
        if(x == 0 && y == 1)   //Go right one
            return E;
        if(x == 1 && y == 1)   //Go down one and go right one
            return SE;
        return STAY;
    }

 bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x = pos.x;
        int y = pos.y;

        switch(ac)
        {
            case N: x--; break;
            case NW: x--; y--; break;
            case W: y--; break;
            case NE: x--; y++; break;
            case S: x++; break;
            case SW: x++; y--; break;
            case E: y++; break;
            case SE: x++; y++; break;
            case STAY: break;
        }
        //check if still inside
        if (x >=0 && x < __height && y >= 0 && y < __width  )
            return true;
        return false;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const
    {
        if(!isLegal(ac, pos))
            return pos;
        int x = pos.x, y = pos.y;
        switch(ac)
        {
            case N: x--; break;
            case NW: x--; y--; break;
            case W: y--; break;
            case NE: x--; y++; break;
            case S: x++; break;
            case SW: x++; y--; break;
            case E: y++; break;
            case SE: x++; y++; break;
            case STAY: break;
        }
        return Position(x,y);
    }

    void Game::round()
    {
         __status = PLAYING;
         for(int i = 0; i < __grid.size(); ++i)
             if(__grid[i] != NULL && !(__grid[i]->getTurned()))
             {
                 __grid[i]->setTurned(true);
                 ActionType ac = __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()));

                 if(ac == STAY)
                     continue;

                 Position moved = move(__grid[i]->getPosition(), ac);
                 int j = moved.x * __width + moved.y;
                 if(__grid[j] != NULL)
                 {
                     __grid[i]->operator*(*__grid[j]);
                     if(__grid[i]->isViable())
                     {
                          delete __grid[j];
                          __grid[j] = __grid[i];
                          __grid[i]->setPosition(moved);
                          __grid[i] = NULL;
                     }
                     else if(__grid[j]->isViable())
                     {
                         delete __grid[i];
                         __grid[i] = NULL;
                     }
                     else
                     {
                          delete __grid[i];
                          delete __grid[j];
                          __grid[i] = NULL;
                          __grid[j] = NULL;
                     }
                 }
                 else
                 {
                      __grid[i]->setPosition(moved);
                      __grid[j] = __grid[i];
                      __grid[i] = NULL;
                 }
             }

         for(int i = 0; i < __grid.size(); ++i)
            if(__grid[i] != NULL)
            {
                __grid[i]->setTurned(false);
                __grid[i]->age();
                if(!__grid[i]->isViable())
                {
                    delete __grid[i];
                    __grid[i] = NULL;
                }
            }
         __round++;
    }


    void Game::play(bool verbose)
    {
        __status = PLAYING;
        if(verbose)
        {
             __verbose = verbose;
             while(getNumResources())
             {
                 std::cout << *this << std::endl;
                 round();
             }
            __status = OVER;
            std::cout << *this << std::endl;
        }
        else
        {
            while(getNumResources())
                round();
            __status = OVER;
        }

    }

    std::ostream& operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round <<std::endl;
        int index = 0;
        for(auto i = game.__grid.begin(); i != game.__grid.end(); ++i)
        {
            if(index % game.__width == 0)
                os << std::endl;
            os << '[';
            if(!*i)
                os << "     ";
            else
                os << **i;
            os << ']';
            index++;
        }
         os << std::endl << "Status: ";

         switch(game.__status)
         {
             case(Game::Status::NOT_STARTED): os << "Not Started!"; break;
             case(Game::Status::PLAYING): os << "Playing..."; break;
             case(Game::Status::OVER): os << "Over!"; break;
         }
         os << std::endl << std::endl;
         return os;

    }

}