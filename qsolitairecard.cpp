#include "qsolitairecard.h"

QSolitaireCard::QSolitaireCard(char type, char number, QPoint offset, QWidget* parent) : QLabel()
{
    this->type = type;
    this->number = number;
    this->setParent(parent);
    if(type == 'H' || type == 'D')
        this->color = 'R';
    else
        this->color = 'B';
    this->offset = offset;
    char strings[14] = {':', '/', 'c', 'a', 'r', 'd', 's', '/', number, type, '.', 'p', 'n', 'g'};
    QString imgname = QString::fromUtf8(strings);
    img = QPixmap(imgname);
    backimg = QPixmap(":/cards/CardGlow.png");
    isflipped = true;
    this->setPixmap(img);
    this->move(offset);
}

void QSolitaireCard::flip()
{
    if(isflipped){
        this->setPixmap(backimg);
        isflipped = false;
    }else{
        this->setPixmap(img);
        isflipped = true;
    }
}

void QSolitaireCard::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
    flip();
}

void QSolitaireCard::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
    }
}
