//
// Created by Vinh Van Tran on 4/17/16.
//

/*
 //
// Created by Ivo Georgiev on 12/9/15.
//

#ifndef PA5GAME_AGGRESSIVEAGENTSTRATEGY_H
#define PA5GAME_AGGRESSIVEAGENTSTRATEGY_H

#include "Strategy.h"

namespace Gaming {

    class AggressiveAgentStrategy : public Strategy {
        double __agentEnergy;

    public:
        static const double DEFAULT_AGGRESSION_THRESHOLD;

        AggressiveAgentStrategy(double agentEnergy);
        ~AggressiveAgentStrategy();
        ActionType operator()(const Surroundings &s) const override;

    };

}


#endif //PA5GAME_AGGRESSIVEAGENTSTRATEGY_H

 */


#include"Game.h"
#include"AggressiveAgentStrategy.h"

namespace Gaming
{
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {
        __agentEnergy=agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {
    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
    {
        std::vector<int> S, T, A, F, E;  //s= simple, t= strategic, a = advantage, f= food, e = empty
        Position pos(1,1);
        for(unsigned i = 0; i < 9; ++i)
            switch(s.array[i])
            {
                case SIMPLE: S.push_back(i); break;
                case STRATEGIC: T.push_back(i); break;
                case ADVANTAGE: A.push_back(i); break;
                case FOOD: F.push_back(i); break;
                case EMPTY: E.push_back(i); break;
            }
        if(S.size() && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
            return Game::reachSurroundings(pos, Game::randomPosition(S));
        if(A.size())
            return Game::reachSurroundings(pos, Game::randomPosition(A));
        if(F.size())
            return Game::reachSurroundings(pos, Game::randomPosition(F));
        return STAY;
    }

}
