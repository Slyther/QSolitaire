#ifndef QCARDLIST_H
#define QCARDLIST_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include "tdalista.h"
#include "qsolitairecard.h"

class QCardList : public QLabel
{
public:
    QCardList(char type, QPoint offset, QWidget *parent);
    char type;
    QPoint offset, lockedcardoffset, releasedcardoffset;
    TDALISTA<QCardList*> *relations;
    TDALISTA<QSolitaireCard*> *cardList;
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void populate();
    void updateList();
};

#endif // QCARDLIST_H
