#ifndef ELEMENT_H
#define ELEMENT_H
#define MAX_TYPE 8

class Element
{
public:
    Element();
    Element(int type, int x, int y, int width, int height);
    Element(const Element &);
    Element &operator=(const Element &);
    virtual ~Element();
    int         getPositionX() const;
    int         getPositionY() const;
    int         getType() const;
    int         getVisability() const;
    void        setPositionX(const int x, const int width);
    void        setPositionY(const int y, const int width);
    void        setType(const int type);
    void        setVisability(const int vis);


private:
    int         _type;
    int         _visability;
    int         _positionX;
    int         _positionY;
};

#endif // ELEMENT_H
