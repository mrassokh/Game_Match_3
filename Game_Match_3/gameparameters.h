#ifndef GAMEPARAMETERS_H
#define GAMEPARAMETERS_H
#include <QtCore/QList>

#define MAX_WIDTH 15
#define DEFAULT_WIDTH 10
#define MAX_HEIGHT 15
#define DEFAULT_HEIGHT 10
#define DEFAULT_MIN_SCORE 1000
#define DEFAULT_MAX_MOVES 100
#define DEFAULT_ELEMENT_SCORE 60


class GameParameters
{
public:
    GameParameters();
    GameParameters(const  GameParameters &);
    GameParameters &operator=(const  GameParameters &);
    virtual ~ GameParameters();

    int         getHeight() const;
    int         getElementScore() const;
    int         getMaxMoves() const;
    int         getMinScore() const;
    QList<int>  getTypes() const;
    int         getWidth() const;
    void        setHeight(const int height);
    void        setElementScore(const int elementScore);
    void        setMaxMoves(const int maxMoves);
    void        setMinScore(const int minScore);
    void        setTypeItems(const int type_item);
    void        setWidth(const int width);

private:
    int          _width;
    int          _height;
    int          _elementScore;
    int          _minScore;
    int          _maxMoves;
    QList<int>   _types;
};

#endif // GAMEPARAMETERS_H
