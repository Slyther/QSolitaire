#ifndef QCARDLIST_H
#define QCARDLIST_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include "tdalista.h"
#include "qsolitairecard.h"

class MainWindow;
class QCardList : public QLabel
{
public:
    QCardList(char type, QPoint offset, QWidget *parent, MainWindow* window);
    char type;
    QPoint offset, lockedcardoffset, releasedcardoffset;
    MainWindow* parentWindow;
    TDALISTA<QCardList*> *relations;
    TDALISTA<QSolitaireCard*> *cardList;
    void mousePressEvent(QMouseEvent *event);
    void populate();
    void updateList();
};

#endif // QCARDLIST_H
