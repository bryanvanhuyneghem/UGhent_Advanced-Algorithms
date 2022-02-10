#ifndef __PATRICIAKNOOP_H
#define __PATRICIAKNOOP_H
#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>

#include "stringmetbits.h"


class Pknoop
{
    friend class Pboom;

public:
    Pknoop(const StringMetBits &_sleutel, const int _data, int _index)
        : sleutel(_sleutel), data(_data), index(_index) {}
protected:
    StringMetBits sleutel;
    int data;
    int index;
    Pknoop *links, *rechts;

    void inorder(std::function<void(const Pknoop &)> bezoek) const;
};



void Pknoop::inorder(std::function<void(const Pknoop &)> bezoek ) const
{
    if (this)
    {
        if(index < links->index){
            links->inorder(bezoek);
        }
        bezoek(*this);
        if(index < rechts->index){
            rechts->inorder(bezoek);
        }
    }
}

#endif
