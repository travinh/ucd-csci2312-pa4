//
// Created by Vinh Van Tran on 4/17/16.
//
 /*
  //
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_RESOURCE_H
#define PA5GAME_RESOURCE_H

#include "Game.h"
#include "Piece.h"

namespace Gaming {

    class Resource : public Piece {

    protected:
        double __capacity;

    public:
        static const double RESOURCE_SPOIL_FACTOR;

        Resource(const Game &g, const Position &p, double capacity);
        ~Resource();

        virtual double getCapacity() const { return __capacity; }
        virtual double consume();

        void age() override final;

        bool isViable() const override final { return !isFinished() && __capacity > 0.0; }

        ActionType takeTurn(const Surroundings &s) const override;

        // note: these won't be called while resources don't move
        Piece &operator*(Piece &other) override final;
        Piece &interact(Agent *) override final;
        Piece &interact(Resource *) override final; // note: no interaction between resources
    };

}


#endif //PA5GAME_RESOURCE_H

  */
#include"Resource.h"

namespace Gaming
{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity): Piece(g,p), __capacity(capacity) {
    }

    Resource::~Resource() {
    }

    double Resource::consume()
    {
        double cap = getCapacity();
        __capacity = -1;
        finish();
        return cap;
    }

    void Resource::age()
    {
        __capacity -= RESOURCE_SPOIL_FACTOR;
        if (__capacity <= 0)
            finish();
    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
    }

    Piece& Resource::operator*(Piece &other)
    {
        return other;
    }

    Piece& Resource::interact(Agent *)
    {
        return *this;
    }

    Piece& Resource::interact(Resource *)
    { return *this; }

}