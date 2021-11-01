#ifndef __RZWknoopH
#define __RZWknoopH
#include "rzwboom.h"

template <class Sleutel>
class RZWknoop {
    friend class RZWboom<Sleutel>;
    public:
        RZWknoop():ouder(0){}
        RZWknoop(const Sleutel& sl):sleutel{sl},ouder(0),kleur(rood){};  
        RZWknoop(Sleutel&& sl):sleutel{move(sl)},ouder(0),kleur(rood){};
        
        RZWboom<Sleutel>& geefKind(bool links);

        Sleutel sleutel;
        RZWknoop<Sleutel>* ouder; // gewone pointer naar een knoop
        RZWboom<Sleutel> links,rechts; // 2 unique pointers
        RZWkleur kleur;
};

template <class Sleutel>
RZWboom<Sleutel>& RZWknoop<Sleutel>:: geefKind(bool linkerkind){
    if (linkerkind)
        return links;
    else
        return rechts;
};



#endif