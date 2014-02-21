#ifndef QSOLITAIRECARD_H
#define QSOLITAIRECARD_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include "tdalista.h"

class MainWindow;
class QCardList;
class QSolitaireCard : public QLabel
{
public:
    QSolitaireCard(char type, char number, QPoint offset, QWidget *parent, MainWindow* window);
    char type, number, color;
    QPoint offset, savedoffset;
    MainWindow *parentWindow;
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
