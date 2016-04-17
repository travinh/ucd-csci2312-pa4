//
// Created by Vinh Van Tran on 4/17/16.
//

  /*

// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_WEAPON_H
#define PA5GAME_WEAPON_H

#include "Game.h"
#include "Resource.h"

namespace Gaming {
    class Advantage : public Resource {
    private:
        static const char ADVANTAGE_ID;

    public:
        static const double ADVANTAGE_MULT_FACTOR;

        Advantage(const Game &g, const Position &p, double capacity);
        ~Advantage();

        PieceType getType() const override { return PieceType::ADVANTAGE; }

        void print(std::ostream &os) const override;

        double getCapacity() const override;
        double consume() override;
    };
}


#endif //PA5GAME_WEAPON_H
    */
#include <iomanip>
#include "Advantage.h"
#include <sstream>

namespace Gaming
{
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity): Resource(g,p,capacity) {
    }

    Advantage::~Advantage() {
    }

    void Advantage::print(std::ostream &os) const
    {

        std::string str;

        str = std::to_string(__id);


        std::stringstream ss;
        ss << Advantage::ADVANTAGE_ID;
        ss << str;

        std::getline(ss, str);
        for (int i = 0; i < str.length(); ++i) {
            os << str[i];
        }
    }

    double Advantage::getCapacity() const
    {
        return __capacity * ADVANTAGE_MULT_FACTOR;
    }

    double Advantage::consume()
    {
        double cap = getCapacity();
        __capacity = -1;
        finish();
        return cap ;
    }

}