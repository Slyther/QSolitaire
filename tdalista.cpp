#include "tdalista.h"

template<typename nvalue>
TDALISTA<nvalue>::TDALISTA()
{
    length=0;
    beginning=0;
    ending=beginning;
    current = beginning;
}

template<typename nvalue>
int TDALISTA<nvalue>::insert(int pos, nvalue elem)
{
    if(pos>length || pos<0)
        return -1;
    noded<nvalue>* newElement = new noded<nvalue>(elem);
    noded<nvalue>* pointer = beginning;
    int posit = 0;
    if(posit == pos){
        newElement->next = pointer;
        beginning = newElement;
        current = beginning;
        length++;
        return 0;
    }
    while(posit < pos-1)
    {
        pointer = pointer->next;
        posit++;
    }
    newElement->next = pointer->next;
    pointer->next = newElement;
    current = newElement;
    length++;
    return 0;
}

template<typename nvalue>
int TDALISTA<nvalue>::add(nvalue elem)
{
    if(size() != 0)
    {
        ending->next = new noded<nvalue>(elem);
        ending = ending->next;
        current = ending;
        length++;
    }else{
        noded<nvalue>* newElement = new noded<nvalue>(elem);
        beginning = newElement;
        ending = beginning;
        current = beginning;
        length++;
    }
    return 0;
}

template<typename nvalue>
int TDALISTA<nvalue>::size()
{
    return this->length;
}

template<typename nvalue>
nvalue TDALISTA<nvalue>::begin()
{
    if(length > 0)
    {
        current = this->beginning;
        return this->beginning->element;
    }
    return nvalue();
}

template<typename nvalue>
nvalue TDALISTA<nvalue>::end()
{
    if(length > 0)
    {
        current = this->ending;
        return this->ending->element;
    }
    return nvalue();
}

template<typename nvalue>
nvalue TDALISTA<nvalue>::next(int pos)
{
    if(pos >= length-1 || pos < 0)
        return nvalue();
    int posit = 0;
    noded<nvalue>* pointer = beginning;
    while(posit < pos)
    {
        pointer = pointer->next;
        posit++;
    }
    pointer = pointer->next;
    current = pointer;
    return pointer->element;
}

template<typename nvalue>
nvalue TDALISTA<nvalue>::get(int pos)
{
    if(pos>=length || pos<0)
        return nvalue();
    int posit = 0;
    noded<nvalue>* pointer = beginning;
    while(posit < pos)
    {
        pointer = pointer->next;
        posit++;
    }
    current = pointer;
    return pointer->element;
}

template<typename nvalue>
int TDALISTA<nvalue>::remove(int pos)
{
    if(pos>=length || pos<0)
        return -1;
    int posit = 0;
    if(posit == pos){
        noded<nvalue>* todelete = beginning;
        beginning = beginning->next;
        if(current == todelete)
            current = beginning;
        delete todelete;
        length--;
        return 0;
    }
    noded<nvalue>* pointer = beginning;
    while(posit < pos-1)
    {
        pointer = pointer->next;
        posit++;
    }
    noded<nvalue>* todelete = pointer->next;
    pointer->next = todelete->next;
    if(current == todelete)
        current = beginning;
    length--;
    delete todelete;
    return 0;
}

template<typename nvalue>
bool TDALISTA<nvalue>::hasnext()
{
    return current->next != 0;
}

template<typename nvalue>
int TDALISTA<nvalue>::empty()
{
    noded<nvalue>* tmp = beginning;
    beginning = 0;
    ending = 0;
    current = 0;
    length = 0;
    return empty(&tmp);
}

template<typename nvalue>
int TDALISTA<nvalue>::empty(noded<nvalue>** temp)
{
    if(*temp == 0)
        return -1;
    noded<nvalue>* tmp = (*temp)->next;
    delete *temp;
    if(tmp == 0)
        return 0;
    return empty(&tmp);
}
