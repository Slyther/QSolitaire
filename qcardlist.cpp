#include "qcardlist.h"
#include <cstdlib>

QCardList::QCardList(char type, QPoint offset, QWidget *parent)
{
    this->type = type;
    this->offset = offset;
    this->cardList = new TDALISTA<QSolitaireCard*>();
    this->relations = new TDALISTA<QCardList*>();
    this->lockedcardoffset = QPoint(0, 7);
    this->releasedcardoffset = QPoint(0, 20);
    this->setFixedHeight(105);
    this->setFixedWidth(79);
    setParent(parent);
    move(offset);
}

void QCardList::mousePressEvent(QMouseEvent *event)
{
    if(type == 'M'){
        if(cardList->size() != 0){
            cardList->end()->offset = relations->get(0)->offset;
            cardList->end()->move(cardList->end()->offset);
            cardList->end()->flip();
            cardList->end()->raise();
            relations->get(0)->cardList->add(cardList->end());
            cardList->remove(cardList->size()-1);
        }else{
            while(relations->get(0)->cardList->size()!= 0){
                relations->get(0)->cardList->end()->offset = offset;
                relations->get(0)->cardList->end()->move(relations->get(0)->cardList->end()->offset);
                relations->get(0)->cardList->end()->flip();
                relations->get(0)->cardList->end()->raise();
                cardList->add(relations->get(0)->cardList->end());
                relations->get(0)->cardList->remove(relations->get(0)->cardList->size()-1);
            }
            raise();
        }
    }
}

void QCardList::dropEvent(QDropEvent *event)
{

    event->accept();
}

void QCardList::populate()
{
    if(isdigit(type)){
        int torepeat = atoi(&type);
        QPoint extraoffset;
        for(int i = 0; i < torepeat; i++){
        relations->get(0)->cardList->end()->offset = offset + extraoffset;
        relations->get(0)->cardList->end()->move(relations->get(0)->cardList->end()->offset);
        relations->get(0)->cardList->end()->raise();
        cardList->add(relations->get(0)->cardList->end());
        relations->get(0)->cardList->remove(relations->get(0)->cardList->size()-1);
        extraoffset += lockedcardoffset;
        }
        relations->remove(0);
        cardList->end()->flip();
    }
}
