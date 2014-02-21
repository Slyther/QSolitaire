#ifndef QSOLITAIRECARD_H
#define QSOLITAIRECARD_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include "tdalista.h"

class QCardList;
class QSolitaireCard : public QLabel
{
public:
    QSolitaireCard(char type, char number, QPoint offset, QWidget *parent);
    char type, number, color;
    QPoint offset, savedoffset;
    QPixmap img, backimg;
    bool islocked;
    void flip();
    TDALISTA<QCardList*> *relations;
    QCardList *parentList;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // QSOLITAIRECARD_H
