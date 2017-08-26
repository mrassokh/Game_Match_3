#ifndef MATCH_H
#define MATCH_H
#include <QtCore/QList>

class Match
{
public:
    Match();
    Match(const Match &);
    Match &operator=(const Match &);
    virtual ~Match();
    void        appendMatchIndexes(int index);
    void        clear();
    QList<int>  getMatchIndexes() const;

private:
    QList<int>  _matchIndexes;
};

#endif // MATCH_H
