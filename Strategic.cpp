//
// Created by Vinh Van Tran on 4/17/16.
//

 /*
#ifndef PA5GAME_STRATEGIC_H
#define PA5GAME_STRATEGIC_H

#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"

namespace Gaming {

    class Strategic : public Agent {
    private:
        static const char STRATEGIC_ID;

        Strategy *__strategy;

    public:
        Strategic(const Game &g, const Position &p, double energy, Strategy *s = new DefaultAgentStrategy());
        ~Strategic();

        PieceType getType() const override { return PieceType::STRATEGIC; }

        void print(std::ostream &os) const override;

        ActionType takeTurn(const Surroundings &s) const override;

    };

}


#endif //PA5GAME_STRATEGIC_H
  */

#include <iomanip>
#include "Strategic.h"

namespace Gaming
{
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s): Agent(g,p,energy), __strategy(s) {
    }

    Strategic::~Strategic()
    {
        delete __strategy;
    }

    void Strategic::print(std::ostream &os) const
    {
        os << STRATEGIC_ID << std::left << std::setw(4) << __id << std::setw(0);
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }

}