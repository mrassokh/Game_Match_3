#ifndef LOGIC_H
#define LOGIC_H
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QTranslator>
#include <QtCore/QCoreApplication>
#include <QtCore/QAbstractListModel>
#include <time.h>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <element.h>
#include <match.h>
#include <gameparameters.h>


class Logic: public QAbstractListModel
{
    Q_OBJECT
public:

   enum Roles {
        Type = Qt::UserRole,
        PositionX,
        PositionY,
        Width,
        Height,
        Visible
     };

    explicit Logic(QObject *parent = 0);
    Logic(const Logic &);
    Logic &operator=(const Logic &);
    virtual ~Logic();
    Q_INVOKABLE void        addStepNumber();
    Q_INVOKABLE int         getWidth() const;
    Q_INVOKABLE int         getHeight() const;
    Q_INVOKABLE QString     getResultText();
    Q_INVOKABLE bool        getClicked() const;
    Q_INVOKABLE bool        gameOver();
    Q_INVOKABLE void        setClicked(bool click);
    Q_INVOKABLE int         getStartIndex() const;
    Q_INVOKABLE int         getVisible(int index) const;
    Q_INVOKABLE void        setUnVisible(int index) const;
    Q_INVOKABLE void        setStartIndex(int index);
    Q_INVOKABLE int         getEndIndex() const;
    Q_INVOKABLE void        setEndIndex(int index);
    Q_INVOKABLE void        swapElements(int startIndex, int endIndex);
    Q_INVOKABLE void        bubbleSwapEmptyElements();
    Q_INVOKABLE void        reType();
    Q_INVOKABLE void        refresh();
    Q_INVOKABLE int         checkMatches();
    Q_INVOKABLE bool        checkMove(int startIndex, int endIndex);

private:
    int                     rowCount(const QModelIndex & parent) const override;
    QVariant                data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray>  roleNames() const override;
    void                    parseJsoneConfigFile(QString &path,  GameParameters &parameters);
    int                     getRandomType(int size);
    void                    setInitialize();
    void                    deleteElements();
    void                    clearMatches();
    int                     findByPosition(int x, int y);
    int                     findMatches();
    void                    deleteMatches();
    void                    clear();
    bool                    _clicked;
    int                     _startIndex;
    int                     _endIndex;
    int                     _stepNumber;
    int                     _score;
    GameParameters          _parameters;
    QList<Element *>        _elements;
    QList<Match *>          _matches;
};

#endif // LOGIC_H
