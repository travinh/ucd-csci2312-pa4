//
// Created by Vinh Van Tran on 4/17/16.
//

/*
 //
// Created by Ivo Georgiev on 12/4/15.
//

#ifndef PA5GAME_EXCEPTIONS_H
#define PA5GAME_EXCEPTIONS_H

#include <iostream>

namespace Gaming {

    class GamingException {
    protected:
        std::string __name;
        virtual void __print_args(std::ostream &os) const = 0;
        void setName(std::string name);
    public:
        std::string getName() const { return __name; };
        friend std::ostream &operator<<(std::ostream &os, const GamingException &ex);
    };

    class DimensionEx : public GamingException {
    protected:
        unsigned __exp_width, __exp_height, __width, __height;
    public:
        DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height);
        unsigned getExpWidth() const;
        unsigned getExpHeight() const;
        unsigned getWidth() const;
        unsigned getHeight() const;
    };

    class InsufficientDimensionsEx : public DimensionEx {
        void __print_args(std::ostream &os) const override;

    public:
        InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height);
    };

    class OutOfBoundsEx : public DimensionEx {
        void __print_args(std::ostream &os) const override;

    public:
        OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height);
    };

    class PositionEx : public GamingException {
    private:
        unsigned int __x, __y;

    protected:
        void __print_args(std::ostream &os) const override;

    public:
        PositionEx(unsigned x, unsigned y);
    };

    // to use in population methods
    class PositionNonemptyEx : public PositionEx {
    public:
        PositionNonemptyEx(unsigned x, unsigned y);
    };

    // to use in Game Piece getter
    class PositionEmptyEx : public PositionEx {
    public:
        PositionEmptyEx(unsigned x, unsigned y);
    };

    // to use with position randomizer
    class PosVectorEmptyEx : public GamingException {
    protected:
        void __print_args(std::ostream &os) const override;

    public:
        PosVectorEmptyEx();
    };

}



#endif //PA5GAME_EXCEPTIONS_H

 */
#include"Exceptions.h"

namespace Gaming
{
    //GamingException stuff
    void GamingException::setName(std::string name)
    {
        __name = name;
    }

    std::ostream& operator<<(std::ostream &os, const GamingException &ex)
    {
        os << ex.getName() << std::endl;
        ex.__print_args(os);
        return os;
    }

    //DimensionEx stuff
    DimensionEx::DimensionEx(unsigned int expWidth, unsigned int expHeight, unsigned int width, unsigned int height):
        __exp_width(expWidth),
        __exp_height(expHeight),
        __width(width),
        __height(height)
    { setName("DimensionEx"); }

    unsigned int DimensionEx::getExpWidth() const
    { return __exp_width; }

    unsigned int DimensionEx::getExpHeight() const
    { return __exp_height; }

    unsigned int DimensionEx::getWidth() const
    { return __width; }

    unsigned int DimensionEx::getHeight() const
    { return __height; }

    //InsufficientDimensionsEx stuff
    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        os << "minWidth: " << getExpWidth() << ", minHeight: " << getExpHeight() <<
            std::endl << "Width: " << getWidth() << ", Height: " << getHeight() << std::endl;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned int minWidth, unsigned int minHeight, unsigned int width, unsigned int height):
        DimensionEx(minWidth, minHeight, width, height)
    { setName("InsufficientDimensionsEx"); }

    //OutOfBoundsEx stuff
    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {
         os << "maxWidth: " << getExpWidth() << ", maxHeight: " << getExpHeight() <<
             std::endl << "Width: " << getWidth() << ", Height: " << getHeight() << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height):
        DimensionEx(maxWidth, maxHeight, width, height)
    { setName("OutOfBoundsEx"); }

    //PositionEx stuff
    void PositionEx::__print_args(std::ostream &os) const
    { os << "x: " << __x << ", y: " << __y << std::endl; }

    PositionEx::PositionEx(unsigned x, unsigned y):
        __x(x),
        __y(y)
    { setName("PositionEx"); }

    //PositionNonemptyEx stuff
    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y):
        PositionEx(x,y)
    { setName("PositionNonemptyEx"); }

    //PositionEmptyEx stuff
    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y):
        PositionEx(x,y)
    { setName("PositionEmptyEx"); }

    //PosVectorEmptyEx stuff
    void PosVectorEmptyEx::__print_args(std::ostream &os) const
    {}

    PosVectorEmptyEx::PosVectorEmptyEx()
    { setName("PosVectorEmptyEx"); }


}