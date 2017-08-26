#include "logic.h"

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
{
    //std::cout << "Logic constructor called" << std::endl;
    QString path = ":/config.json";
    this->parseJsoneConfigFile(path,this->_parameters);
    this->setInitialize();
    this->_clicked = false;
    this->_stepNumber = 0;
    this->_score = 0;
}

Logic::Logic(const Logic &rhs)
{
    this->setClicked(rhs.getClicked());
    this->setStartIndex(rhs.getStartIndex());
    this->setEndIndex(rhs.getEndIndex());
    this->_stepNumber = rhs._stepNumber;
    this->_score = rhs._score;
    this->_parameters = rhs._parameters;
    this->_elements = rhs._elements;
    this->_matches = rhs._matches;
}

Logic &Logic::operator=(const Logic &rhs)
{
    if (this == &rhs)
        return *this;
    this->setClicked(rhs.getClicked());
    this->setStartIndex(rhs.getStartIndex());
    this->setEndIndex(rhs.getEndIndex());
    this->_stepNumber = rhs._stepNumber;
    this->_score = rhs._score;
    this->_parameters = rhs._parameters;
    this->deleteElements();
    this->clear();
    this->_elements = rhs._elements;
    this->clearMatches();
    this->_matches = rhs._matches;
    return *this;
}

Logic:: ~Logic()
{
    //std::cout <<"Logic dectructor called" << std::endl;
    this->deleteElements();
    this->clear();
    this->clearMatches();
}



void                    Logic::clear()
{
    beginResetModel();
    this->_elements.clear();
    endResetModel();
}

void                    Logic::deleteElements()
{
    for (int i(0); i < this->_elements.size(); ++i) {
        delete(this->_elements[i]);
        this->_elements[i] = NULL;
    }
}

void                    Logic::clearMatches()
{
    for (int i(0); i < this->_matches.size(); ++i) {
        delete(this->_matches[i]);
        this->_matches[i] = NULL;
    }
    this->_matches.clear();
}
int                     Logic::rowCount(const QModelIndex &) const
{
    return this->_elements.size();
}


QVariant                Logic::data(const QModelIndex & modelIndex, int role) const
{
    if (!modelIndex.isValid()) {
        return QVariant();
     }

    int index = static_cast<int>(modelIndex.row());
    if (index >= this->_elements.size() || index < 0) {
       return QVariant();
    }

    Element &element = *(this->_elements[index]);

     switch (role) {
       case Roles::Type:      return element.getType();
       case Roles::PositionX: return element.getPositionX();
       case Roles::PositionY: return element.getPositionY();
       case Roles::Width:     return this->_parameters.getWidth();
       case Roles::Height:    return this->_parameters.getHeight();
       case Roles::Visible:   return this->getVisible(index);
     }
     return QVariant();
}

QHash<int, QByteArray>  Logic::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(Roles::Type    ,   "type");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    names.insert(Roles::Width    ,  "boardWidth");
    names.insert(Roles::Height    , "boardHeight");
    names.insert(Roles::Visible   , "vis");
    return names;
}


void                     Logic::parseJsoneConfigFile(QString &path,
                                                     GameParameters &parameters)
{
    QFile file(path);

    if (!file.exists()) {
        qDebug() << "NO FILE HERE";
        exit(0) ;
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject item =  d.object();
    QJsonValue subobj = item["width"];
    parameters.setWidth(subobj.toInt());
    subobj = item["height"];
    parameters.setHeight(subobj.toInt());
    subobj = item["elementScore"];
    parameters.setElementScore(subobj.toInt());
    subobj = item["minScore"];
    parameters.setMinScore(subobj.toInt());
    subobj = item["maxMoves"];
    parameters.setMaxMoves(subobj.toInt());
    QJsonArray types = item["types"].toArray();

    for(int i = 0; i < types.size(); i++){
        parameters.setTypeItems(types[i].toInt());
    }
}

int                       Logic::getRandomType(int  size)
{
    int     random;

    random = rand() % size;
    return this->_parameters.getTypes()[random];
}

void                      Logic::setInitialize()
{
    int     elementsSize;
    int     typeSize;
    int     type;
    int     width;
    int     height;

    width = this->_parameters.getWidth();
    height = this->_parameters.getHeight() *2;
    elementsSize = width * height;
    typeSize = this->_parameters.getTypes().size();
    srand (time(NULL));
    for (int i = 0; i < elementsSize; ++i){
        type = this->getRandomType(typeSize);
        Element *element = new Element(type, i % width, i / width, width, height);
        this->_elements.append(element);
    }
    while(this->checkMatches()){
           this->bubbleSwapEmptyElements();
           this->reType();
    }
}

int                       Logic::getWidth() const
{
    return this->_parameters.getWidth();
}

int                       Logic::getHeight() const
{
    return this->_parameters.getHeight();
}

void                      Logic::swapElements(int startIndex, int endIndex)
{
    QModelIndex topLeft ;
    QModelIndex bottomRight;
    int         swapX;
    int         swapY;
    int size = this->_elements.size();

    if ((startIndex == endIndex) || (startIndex < 0) || (startIndex > size)
            || (endIndex < 0) || (endIndex > size)){
        return;
    }
    swapX = this->_elements[startIndex]->getPositionX();
    swapY = this->_elements[startIndex]->getPositionY();
    this->_elements[startIndex]->setPositionX(this->_elements[endIndex]->getPositionX(),
                                              this->_parameters.getWidth());
    this->_elements[endIndex]->setPositionX(swapX, this->_parameters.getWidth());
    this->_elements[startIndex]->setPositionY(this->_elements[endIndex]->getPositionY(),
                                              this->_parameters.getHeight() *2);
    this->_elements[endIndex]->setPositionY(swapY, this->_parameters.getHeight() *2 );
    topLeft = createIndex(startIndex, 0);
    bottomRight = createIndex(startIndex, 0);
    emit dataChanged(topLeft, bottomRight);
    topLeft = createIndex(endIndex, 0);
    bottomRight = createIndex(endIndex, 0);
    emit dataChanged(topLeft, bottomRight);
}

int                       Logic::checkMatches()
{
    int         deleteMatches = 0;

    deleteMatches  =  this->findMatches();
    if (deleteMatches)
        this->deleteMatches();

    return (deleteMatches);
}

bool                      Logic::getClicked() const
{
    return this->_clicked;
}

void                      Logic::setClicked(bool click)
{
    this->_clicked = click;
}

int                       Logic::getStartIndex() const
{
    return this->_startIndex;
}

void                      Logic::setEndIndex(int index)
{
    if (index >= 0)
        this->_endIndex = index;
}


int                       Logic::getEndIndex() const
{
    return this->_endIndex;
}

void                      Logic::setStartIndex(int index)
{
    if (index >= 0)
        this->_startIndex = index;
}

int                       Logic::getVisible(int index) const
{
    return this->_elements[index]->getVisability();
}

void                      Logic::setUnVisible(int index) const
{
    this->_elements[index]->setVisability(0);
}


int                       Logic::findByPosition(int x, int y)
{
    for (int i(0); i < this->_elements.size(); ++i) {
        if (this->_elements[i]->getPositionX() != x ||
            this->_elements[i]->getPositionY() != y) {
                continue;
        }
        return i;
    }
    return -1;
}

 int                      Logic::findMatches()
 {
     int index;
     int indexNext;
     int ret = 0;

     for (int i(this->_parameters.getHeight());
          i < this->_parameters.getHeight() *2 ; ++i) {
          for (int j(0); j < this->_parameters.getWidth() - 1 ; ++j){
              index = this->findByPosition(j,i);
              indexNext = this->findByPosition(j + 1, i );
              if (index < 0 || indexNext < 0)
                 return (0);
              Match * match = new Match();
              match->appendMatchIndexes(index);

              while (j < this->_parameters.getWidth() - 1
                     && this->_elements[index]->getType() == this->_elements[indexNext]->getType()
                        && this->_elements[index]->getType() != -1){
                  match->appendMatchIndexes(indexNext);
                  index = indexNext;
                  indexNext = this->findByPosition(++j + 1, i );
              }
              if (match->getMatchIndexes().size() > 2){
                  this->_matches.append(match);
                  ret++;
              } else {
                delete match;
              }
            }
     }

     for (int i(0); i < this->_parameters.getWidth(); ++i) {
         for (int j(this->_parameters.getHeight());
              j < this->_parameters.getHeight() * 2 -1; ++j){
             index = this->findByPosition(i,j);
             indexNext = this->findByPosition(i, j + 1 );
             if (index < 0 || indexNext < 0)
                return (0);
             Match * match = new Match();
             match->appendMatchIndexes(index);
             while (j < this->_parameters.getHeight() * 2 -1
                    && this->_elements[index]->getType() == this->_elements[indexNext]->getType()
                        && this->_elements[index]->getType() != -1){
                 match->appendMatchIndexes(indexNext);
                 index = indexNext;
                 indexNext = this->findByPosition(i, ++j + 1);
             }
             if (match->getMatchIndexes().size() > 2){
                 this->_matches.append(match);
                 ret++;
             } else {
                delete match;
             }
          }
     }

    return (ret);
}

void                        Logic::deleteMatches()
{
    QModelIndex topLeft ;
    QModelIndex bottomRight;

    for (int i(0); i < this->_matches.size(); ++i) {
        for (int j(0); j < this->_matches[i]->getMatchIndexes().size(); ++j){
            int index = this->_matches[i]->getMatchIndexes()[j];
            if (this->getVisible(index)){
                this->setUnVisible(index);
                topLeft = createIndex(index, 0);
                bottomRight = createIndex(index, 0);
                emit dataChanged(topLeft, bottomRight);
                this->_score += this->_parameters.getElementScore();
           }
        }
    }
}

void                        Logic::bubbleSwapEmptyElements()
{
    int     upperY;
    int     upperX;
    int     matchSize;
    int     matchIndexesSize;

    matchSize = this->_matches.size();

    for (int i(0); i < matchSize ; ++i) {
        matchIndexesSize = this->_matches[i]->getMatchIndexes().size();
        for (int j(0); j < matchIndexesSize; ++j){
            int index = this->_matches[i]->getMatchIndexes()[j];
            while ((this->_elements[index]->getPositionY()) != 0){
                upperY = this->_elements[index]->getPositionY() - 1;
                upperX = this->_elements[index]->getPositionX();
                int upperIndex = this->findByPosition(upperX, upperY);
                this->swapElements(index,upperIndex);
            }
        }
     }
     this->clearMatches();
}

void                        Logic::reType()
{
    QModelIndex topLeft ;
    QModelIndex bottomRight;

    for (int i(0); i < this->_parameters.getWidth(); ++i){
        for (int j(0); j < this->_parameters.getHeight(); ++j){
            int index = this->findByPosition(i,j);
            if (!this->_elements[index]->getVisability()){
                this->_elements[index]->setType(this->getRandomType
                                                (this->_parameters.getTypes().size()));
                this->_elements[index]->setVisability(1);
            }
            topLeft = createIndex(index, 0);
            bottomRight = createIndex(index, 0);
            emit dataChanged(topLeft, bottomRight);
        }
    }
}

bool                      Logic::gameOver()
{
    if (this->_stepNumber >= this->_parameters.getMaxMoves())
        return true;
    return false;
}

void                      Logic::addStepNumber()
{
    this->_stepNumber++;
}

bool                      Logic::checkMove(int startIndex, int endIndex)
{
    int     dx;
    int     dy;

    dx = this->_elements[startIndex]->getPositionX()
            - this->_elements[endIndex]->getPositionX();
    dy = this->_elements[startIndex]->getPositionY()
            - this->_elements[endIndex]->getPositionY();
    if (dx && dy)
        return false;
    else if(abs(dx) > 1)
        return false;
    else if(abs(dy) > 1)
        return false;

    return true;
}

void                      Logic::refresh()
{
    for (int i(0); i < this->_elements.size(); ++i){
        this->_elements[i]->setType(this->getRandomType
                                    (this->_parameters.getTypes().size()));
        this->_elements[i]->setVisability(1);
    }

    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(
                this->_elements.size() - 1, 0);
    emit dataChanged(topLeft, bottomRight);
    while(this->checkMatches()){
        this->bubbleSwapEmptyElements();
        this->reType();
    }
    this->_score = 0;
    this->_stepNumber = 0;
}

QString          Logic::getResultText()
{
    QString resultText;

    if (this->_score < this->_parameters.getMinScore())
        resultText = "Sorry, but you lost. Try again?";
    else
        resultText = "Congratulation, you win!!! Try again?";

    return resultText;
}

