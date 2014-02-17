#ifndef QSOLITAIRECARD_H
#define QSOLITAIRECARD_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>

class QSolitaireCard : public QLabel
{
public:
    QSolitaireCard(char type, char number, QPoint offset, QWidget *parent);
    char type, number, color;
    QPoint offset;
    QPixmap img, backimg;
    bool islocked;
    void flip();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // QSOLITAIRECARD_H
