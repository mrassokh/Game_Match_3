#include "match.h"

Match::Match()
{

}

Match::Match(const Match &rhs)
{
    this->_matchIndexes = rhs.getMatchIndexes();
}

Match &Match::operator=(const Match &rhs)
{
    if (this == &rhs)
         return *this;

    this->clear();
    this->_matchIndexes = rhs.getMatchIndexes();

    return *this;
}

Match:: ~Match()
{
    this->clear();
}


void        Match::appendMatchIndexes(int index)
{
    this->_matchIndexes.append(index);
}

QList<int>  Match::getMatchIndexes() const
{
    return this->_matchIndexes;
}

void        Match::clear()
{
    this->_matchIndexes.clear();
}
