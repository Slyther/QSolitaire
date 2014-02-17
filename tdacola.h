#ifndef TDACOLA_H
#define TDACOLA_H
#include "noded.h"

template<typename n>
class TDACOLA
{
public:
    TDACOLA();
    int size();
    n begin();
    n end();
    int push(n elem);
    n pop();
    int purge();
    bool hasnext();

private:
    int length;
    noded<n>* beginning;
    noded<n>* ending;
    noded<n>* current;
};

#endif // TDACOLA_H
