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
    backimg = QPixmap(":/cards/CardBack.png");
    islocked = true;
    this->setPixmap(backimg);
    this->move(offset);
}

void QSolitaireCard::flip()
{
    if(islocked){
        this->setPixmap(img);
        islocked = false;
    }else{
        this->setPixmap(backimg);
        islocked = true;
    }
}

void QSolitaireCard::mousePressEvent(QMouseEvent *event)
{
    if(islocked)
        return;
    raise();
    savedoffset = offset;
    offset = event->pos();
}

void QSolitaireCard::mouseMoveEvent(QMouseEvent *event)
{
    if(islocked)
        return;
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
    }
}

void QSolitaireCard::mouseReleaseEvent(QMouseEvent *event)
{
//    for(int i = 0; i < relations->size(); i++){
//        if(mapToParent(event->pos()-offset).x() > relations->get(i)->offset.x() &&
//                mapToParent(event->pos()-offset).x() < relations->get(i)->offset.x()+79 &&
//                mapToParent(event->pos()-offset).y() > relations->get(i)->offset.y() &&
//                mapToParent(event->pos()-offset).y() < relations->get(i)->offset.y()+105+(relations->size()*7)){
//            if(relations->get(i)->type == 'A'){
//                if(relations->get(i)->cardList->size() == 0 && this->number == 'A'){
//                    for(int j = 0; j < this->parentlist->size(); j++){
//                        if(parentlist->get(j) == this){
//                            parentlist->get(j)->offset = relations->get(i)->offset;
//                            parentlist->get(j)->move(parentlist->get(j)->offset);
//                            cardList->end()->raise();
//                            relations->get(i)->cardList->add(parentlist->get(j));
//                            parentlist->remove(j);
//                        }
//                    }
//                }
//            }
//        }
//    }
    if(!savedoffset.isNull()){
        offset = savedoffset;
        move(offset);
    }
}
