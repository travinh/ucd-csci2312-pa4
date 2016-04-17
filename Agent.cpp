//
// Created by Vinh Van Tran on 4/17/16.
//
  /*
   //
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_AGENT_H
#define PA5GAME_AGENT_H

#include "Game.h"
#include "Piece.h"

namespace Gaming {

    class Agent : public Piece {

    protected:
        double __energy;

    public:
        static const double AGENT_FATIGUE_RATE;

        Agent(const Game &g, const Position &p, double energy);
        ~Agent();

        double getEnergy() const { return __energy; }
        void addEnergy(double e) { __energy += e; }

        void age() override final;

        bool isViable() const override final { return !isFinished() && __energy > 0.0; }

        Piece &operator*(Piece &other) override final;
        Piece &interact(Agent *) override final;
        Piece &interact(Resource *) override final;

    };

}


#endif //PA5GAME_AGENT_H

   */
#include"Food.h"
#include"Advantage.h"
#include"Agent.h"

namespace Gaming
{
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g,p), __energy(energy) {
    }

    Agent::~Agent() {
    }

    void Agent::age()
    {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece& Agent::operator*(Piece &other)
    {
        if(dynamic_cast<Resource*>(&other))
            interact(dynamic_cast<Resource*>(&other));
        else
            interact(dynamic_cast<Agent*>(&other));

        if(!isFinished())
        {
            Position pNew;
            pNew = other.getPosition();
            Position pOld;
            pOld = getPosition();
            setPosition(pNew);
            other.setPosition(pOld);
        }


        return *this;

    }

    Piece& Agent::interact(Agent *other)
    {
        if(__energy >= other->__energy)
            other->finish();
        if (__energy < other->__energy)
            finish();
        return *this;
    }

    Piece& Agent::interact(Resource *res)
    {
        __energy += res->consume();
        return *this;
    }

}
