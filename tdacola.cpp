#include "tdacola.h"

template<typename n>
TDACOLA<n>::TDACOLA()
{
    length=0;
    beginning=0;
    ending=beginning;
    current = beginning;
}

template<typename n>
int TDACOLA<n>::push(n elem)
{
    if(size() != 0)
    {
        ending->next = new noded<n>(elem);
        ending = ending->next;
        current = ending;
        length++;
    }else{
        noded<n>* newElement = new noded<n>(elem);
        beginning = newElement;
        ending = beginning;
        current = beginning;
        length++;
    }
    return 0;
}

template<typename n>
int TDACOLA<n>::size()
{
    return this->length;
}

template<typename n>
n TDACOLA<n>::begin()
{
    if(length > 0)
    {
        current = this->beginning;
        return this->beginning->element;
    }
    return n();
}

template<typename n>
n TDACOLA<n>::end()
{
    if(length > 0)
    {
        current = this->ending;
        return this->ending->element;
    }
    return n();
}

template<typename n>
n TDACOLA<n>::pop()
{
    noded<n>* todelete = beginning;
    if(beginning == 0)
        return n();
    beginning = beginning->next;
    if(current == todelete)
        current = beginning;
    length--;
    n elem = todelete->element;
    delete todelete;
    return elem;
}

template<typename n>
bool TDACOLA<n>::hasnext()
{
    return current->next != 0;
}

template<typename n>
int TDACOLA<n>::purge()
{
    beginning = 0;
    ending = 0;
    current = beginning;
    length = 0;
    return 0;
}
