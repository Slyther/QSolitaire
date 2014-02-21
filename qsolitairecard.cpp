#include "qsolitairecard.h"
#include "qcardlist.h"

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

void QSolitaireCard::mouseDoubleClickEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        if(this != parentList->cardList->end())
            return;
        for(int i = 0; i < relations->size(); i++){
            if(relations->get(i)->type == 'A'){
                std::map <char, int> chars;
                chars['A'] = 1;chars['2'] = 2;chars['3'] = 3;chars['4'] = 4;chars['5'] = 5;chars['6'] = 6;
                chars['7'] = 7;chars['8'] = 8;chars['9'] = 9;chars['0'] = 10;chars['J'] = 11;chars['Q'] = 12;
                chars['K'] = 13;
                if(relations->get(i)->cardList->size() == 0){
                    if(this->number == 'A'){
                        parentList->cardList->end()->offset = relations->get(i)->offset;
                        parentList->cardList->end()->move(parentList->cardList->end()->offset);
                        parentList->cardList->end()->raise();
                        relations->get(i)->cardList->add(parentList->cardList->end());
                        parentList->cardList->remove(parentList->cardList->size()-1);
                        parentList->updateList();
                        relations->get(i)->updateList();
                        savedoffset = offset;
                        return;
                    }
                    continue;
                }else{
                    if(this->type == relations->get(i)->cardList->end()->type &&
                         chars[this->number] == chars[relations->get(i)->cardList->end()->number]+1){
                         parentList->cardList->end()->offset = relations->get(i)->offset;
                         parentList->cardList->end()->move(parentList->cardList->end()->offset);
                         parentList->cardList->end()->raise();
                         relations->get(i)->cardList->add(parentList->cardList->end());
                         parentList->cardList->remove(parentList->cardList->size()-1);
                         parentList->updateList();
                         relations->get(i)->updateList();
                         savedoffset = offset;
                         return;
                    }
                    continue;
                }
            }
        }
    }
}

void QSolitaireCard::mousePressEvent(QMouseEvent *event)
{
    if(islocked)
        return;
    savedoffset = offset;
    offset = event->pos();
    raise();
    if(this != parentList->cardList->end()){
        int n = parentList->cardList->indexOf(this);
        event->pos().setY(event->pos().y()+20);
        parentList->cardList->get(n+1)->mousePressEvent(event);
    }
}

void QSolitaireCard::mouseMoveEvent(QMouseEvent *event)
{
    if(islocked)
        return;
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
        if(this != parentList->cardList->end()){
            int n = parentList->cardList->indexOf(this);
            event->pos().setY(event->pos().y()+20);
            parentList->cardList->get(n+1)->mouseMoveEvent(event);
        }
    }
}

void QSolitaireCard::mouseReleaseEvent(QMouseEvent *event)
{
    int currentx = mapToParent(offset).x();
    int currenty = mapToParent(offset).y();
    for(int i = 0; i < relations->size(); i++){
        if(relations->get(i)->type == 'O' || relations->get(i)->type == 'M')
            continue;
        if(relations->get(i)->cardList->size() == 0){
            if(currentx > relations->get(i)->offset.x() &&
                    currentx < relations->get(i)->offset.x()+79 &&
                    currenty > relations->get(i)->offset.y() &&
                    currenty < relations->get(i)->offset.y()+105){
                if(isdigit(relations->get(i)->type) && this->number == 'K'){
                    int pos = parentList->cardList->indexOf(this);
                    parentList->cardList->get(pos)->offset = relations->get(i)->offset;
                    parentList->cardList->get(pos)->move(parentList->cardList->get(pos)->offset);
                    parentList->cardList->get(pos)->raise();
                    relations->get(i)->cardList->add(parentList->cardList->get(pos));
                    int cycle = 0;
                    for(int j = pos+1; j < parentList->cardList->size(); j++, cycle++){
                        parentList->cardList->get(j)->offset = relations->get(i)->cardList->end()->offset+ parentList->releasedcardoffset;
                        parentList->cardList->get(j)->move(parentList->cardList->get(j)->offset);
                        parentList->cardList->get(j)->raise();
                        relations->get(i)->cardList->add(parentList->cardList->get(j));
                    }
                    for(int j = 0; j <= cycle; j++){
                        parentList->cardList->remove(parentList->cardList->size()-1);
                    }
                    parentList->updateList();
                    relations->get(i)->updateList();
                    return;
                }
                if(relations->get(i)->type == 'A' && this->number == 'A'){
                    if(this != parentList->cardList->end())
                        break;
                    parentList->cardList->end()->offset = relations->get(i)->offset;
                    parentList->cardList->end()->move(parentList->cardList->end()->offset);
                    parentList->cardList->end()->raise();
                    relations->get(i)->cardList->add(parentList->cardList->end());
                    parentList->cardList->remove(parentList->cardList->size()-1);
                    parentList->updateList();
                    relations->get(i)->updateList();
                    return;
                }
                break;
            }
            continue;
        }
        if(currentx > relations->get(i)->offset.x() &&
                currentx < relations->get(i)->offset.x()+79 &&
                currenty > relations->get(i)->offset.y() &&
                currenty < relations->get(i)->cardList->end()->offset.y()+105){
            std::map <char, int> chars;
            chars['A'] = 1;chars['2'] = 2;chars['3'] = 3;chars['4'] = 4;chars['5'] = 5;chars['6'] = 6;
            chars['7'] = 7;chars['8'] = 8;chars['9'] = 9;chars['0'] = 10;chars['J'] = 11;chars['Q'] = 12;
            chars['K'] = 13;
            if(isdigit(relations->get(i)->type)){
                if(this->color != relations->get(i)->cardList->end()->color &&
                        chars[this->number] == chars[relations->get(i)->cardList->end()->number]-1){
                    int pos = parentList->cardList->indexOf(this);
                    int cycle = 0;
                    for(int j = pos; j < parentList->cardList->size(); j++, cycle++){
                        parentList->cardList->get(j)->offset = relations->get(i)->cardList->end()->offset+ parentList->releasedcardoffset;
                        parentList->cardList->get(j)->move(parentList->cardList->get(j)->offset);
                        parentList->cardList->get(j)->raise();
                        relations->get(i)->cardList->add(parentList->cardList->get(j));
                    }
                    for(int j = 0; j < cycle; j++){
                        parentList->cardList->remove(parentList->cardList->size()-1);
                    }
                    parentList->updateList();
                    relations->get(i)->updateList();
                    return;
                }
            }else{
                if(this->type == relations->get(i)->cardList->end()->type &&
                        chars[this->number] == chars[relations->get(i)->cardList->end()->number]+1){
                    if(this != parentList->cardList->end())
                        break;
                    parentList->cardList->end()->offset = relations->get(i)->offset;
                    parentList->cardList->end()->move(parentList->cardList->end()->offset);
                    parentList->cardList->end()->raise();
                    relations->get(i)->cardList->add(parentList->cardList->end());
                    parentList->cardList->remove(parentList->cardList->size()-1);
                    parentList->updateList();
                    relations->get(i)->updateList();
                    return;
                }
            }
        }
    }
    if(!savedoffset.isNull()){
        offset = savedoffset;
        move(offset);
        if(this != parentList->cardList->end()){
            int n = parentList->cardList->indexOf(this);
            for(int i = n+1; i < parentList->cardList->size(); i++){
                parentList->cardList->get(i)->offset = parentList->cardList->get(i)->savedoffset;
                parentList->cardList->get(i)->move(parentList->cardList->get(i)->offset);
            }
        }
    }
}
