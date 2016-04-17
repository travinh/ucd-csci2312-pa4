//
// Created by Vinh Van Tran on 4/17/16.
//

/*
 //
// Created by Ivo Georgiev on 12/8/15.
//

#ifndef PA5GAME_DEFAULTAGENTSTRATEGY_H
#define PA5GAME_DEFAULTAGENTSTRATEGY_H

#include "Strategy.h"

namespace Gaming {

    class DefaultAgentStrategy : public Strategy {
    public:

        DefaultAgentStrategy();
        ~DefaultAgentStrategy();
        ActionType operator()(const Surroundings &s) const override;
    };

}

#endif //PA5GAME_DEFAULTAGENTSTRATEGY_H

 */
#include<vector>
#include"Game.h"
#include"DefaultAgentStrategy.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() { }

    DefaultAgentStrategy::~DefaultAgentStrategy() { }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
//        std::vector<int> simp, strat, adv, food, empt;
//        Position pos(1,1);
//        for(unsigned i = 0; i < 9; ++i)
//            switch(s.array[i])
//            {
//                case SIMPLE: simp.push_back(i); break;
//                case STRATEGIC: strat.push_back(i); break;
//                case ADVANTAGE: adv.push_back(i); break;
//                case FOOD: food.push_back(i); break;
//                case EMPTY: empt.push_back(i); break;
//            }

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
        if(A.size())
            return Game::reachSurroundings(pos, Game::randomPosition(A));
        if(F.size())
            return Game::reachSurroundings(pos, Game::randomPosition(F));
        if(E.size())
            return Game::reachSurroundings(pos, Game::randomPosition(E));
        if(S.size())
            return Game::reachSurroundings(pos, Game::randomPosition(S));
        return STAY;


    }
}