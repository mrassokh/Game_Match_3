#include "gameparameters.h"

GameParameters::GameParameters()
{
    this->setWidth(DEFAULT_WIDTH);
    this->setHeight(DEFAULT_HEIGHT);
    this->setMaxMoves(DEFAULT_MAX_MOVES);
    this->setMinScore(DEFAULT_MIN_SCORE);
    this->setElementScore(DEFAULT_ELEMENT_SCORE);
}


GameParameters::GameParameters(const  GameParameters &rhs)
{
    this->setWidth(rhs.getWidth());
    this->setHeight(rhs.getHeight());
    this->setMaxMoves(rhs.getMaxMoves());
    this->setMinScore(rhs.getMinScore());
    this->setElementScore(rhs.getElementScore());
    this->_types = rhs.getTypes();
}

GameParameters &GameParameters::operator=(const  GameParameters &rhs)
{
    if (this == &rhs)
        return *this;

    this->setWidth(rhs.getWidth());
    this->setHeight(rhs.getHeight());
    this->setMaxMoves(rhs.getMaxMoves());
    this->setMinScore(rhs.getMinScore());
    this->setElementScore(rhs.getElementScore());
    this->_types.clear();
    this->_types = rhs.getTypes();

    return *this;
}

GameParameters::~GameParameters()
{
    this->_types.clear();
}

void        GameParameters::setWidth(const int width)
{
    if (width > 0 && width < MAX_WIDTH)
        this->_width = width;
    else
        this->_width = MAX_WIDTH;
}

int         GameParameters::getWidth() const
{
    return this->_width;
}

void        GameParameters::setHeight(const int height)
{
    if (height > 0 && height < MAX_HEIGHT)
        this->_height = height;
    else
        this->_height = MAX_HEIGHT;
}


int         GameParameters::getHeight() const
{
    return this->_height;
}

void        GameParameters::setElementScore(const int elementScore)
{
    if (elementScore > 0 && elementScore < DEFAULT_ELEMENT_SCORE * 100)
        this->_elementScore = elementScore;
    else
        this->_elementScore = DEFAULT_ELEMENT_SCORE;
}

int         GameParameters::getElementScore() const
{
    return  this->_elementScore;
}

void        GameParameters::setMinScore(const int minScore)
{
    if (minScore > 0 && minScore < DEFAULT_MIN_SCORE * 100)
        this->_minScore = minScore;
    else
        this->_minScore = DEFAULT_MIN_SCORE;
}

int         GameParameters::getMinScore() const
{
    return this->_minScore;
}
void        GameParameters::setMaxMoves(const int maxMoves)
{
    if (maxMoves > 0 && maxMoves < DEFAULT_MAX_MOVES * 100)
        this->_maxMoves = maxMoves;
    else
        this->_maxMoves = DEFAULT_MAX_MOVES;
}

int         GameParameters::getMaxMoves() const
{
    return this->_maxMoves;
}

void        GameParameters::setTypeItems(const int type_item)
{
    if(type_item > -1 && this->_types.size() < 8)
        this->_types.append(type_item);
}

QList<int>  GameParameters::getTypes() const
{
    return this->_types;
}
