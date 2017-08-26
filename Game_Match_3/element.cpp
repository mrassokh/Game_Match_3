#include "element.h"

Element::Element()
{
    this->setType(0);
}

Element::Element(int type, int x, int y, int width, int height)
{
    this->setType(type);
    this->setPositionX(x, width);
    this->setPositionY(y, height);
    this->setVisability(1);
}

Element::Element(const Element & rhs)
{
    this->setType(rhs.getType());
    this->setPositionX(rhs.getPositionX(), 100000);
    this->setPositionY(rhs.getPositionY(), 100000);
    this->setVisability(rhs.getVisability());
}

Element &Element::operator=(const Element & rhs)
{
    if (this == &rhs)
        return *this;

    this->setType(rhs.getType());
    this->setPositionX(rhs.getPositionX(), 100000);
    this->setPositionY(rhs.getPositionY(), 100000);
    this->setVisability(rhs.getVisability());

    return *this;
}

Element:: ~Element()
{

}


int         Element::getPositionX() const
{
    return this->_positionX ;
}

int         Element::getPositionY() const
{
    return this->_positionY ;
}

int         Element::getType() const
{
    return this->_type;
}

int         Element::getVisability() const
{
    return this->_visability;
}


void        Element::setPositionX(const int x, const int width)
{
    if (x > 0 && x < width)
        this->_positionX = x;
    else
        this->_positionX = 0;
}

void         Element::setPositionY(const int y, const int height)
{
    if (y > 0 && y < height)
        this->_positionY = y;
    else
        this->_positionY = 0;
}


void         Element::setType(const int type)
{
     if(type < MAX_TYPE)
         this->_type = type;
     else
         this->_type = MAX_TYPE;
}


void        Element::setVisability(const int vis)
{
    if (vis)
        this->_visability = 1;
    else
        this->_visability = 0;
}
