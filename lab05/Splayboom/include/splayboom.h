
#ifndef Splayboom_H
#define Splayboom_H

#include "zoekknoop.h"
#include "zoekboom.h"

template <class Sleutel, class Data>
class Splayboom : public ZoekBoom<Sleutel, Data>
{

public: 
	
    Splayboom() : ZoekBoom<Sleutel, Data>() {}
	Splayboom(const Sleutel &sleutel, const Data &data) : ZoekBoom<Sleutel, Data>(sleutel, data) {}
	Splayboom(ZoekBoom<Sleutel, Data> &andere) : ZoekBoom<Sleutel, Data>(andere) {}
	Splayboom(ZoekBoom<Sleutel, Data> &&andere): ZoekBoom<Sleutel, Data>(std::move(andere)) {}
    
    Splayboom(std::unique_ptr<ZoekKnoop<Sleutel, Data>> &&andere): ZoekBoom<Sleutel, Data>(std::move(andere)) {} // added

    bool zoekSleutel(const Sleutel& sleutel) override;
    void voegtoe(const Sleutel &sleutel, const Data &data) override;
    ZoekKnoop<Sleutel, Data> *verwijder(const Sleutel &sleutel) override;
private:
    using ZoekBoom<Sleutel, Data>::geefBoomVanKnoop;
    void splay(ZoekKnoop<Sleutel, Data>* locatie);
};

/******************************************************************************/

template <class Sleutel, class Data>
bool Splayboom<Sleutel, Data>::zoekSleutel(const Sleutel &sleutel)
{
    if(*this == nullptr) 
        return false;

    auto [plaats, ouder] = this->ZoekBoom<Sleutel,Data>::zoek(sleutel);

    if(!*plaats){
        if(ouder){
            //ZoekBoom<Sleutel, Data> *next = ZoekBoom<Sleutel, Data>::nextInorder(geefBoomVanKnoop(*ouder));
            //assert(next != nullptr);
            //splay(next->get());
            splay(ouder);
        }
        return false;
    }

    splay(plaats->get());
    return true;

}

template <class Sleutel, class Data>
void Splayboom<Sleutel, Data>::voegtoe(const Sleutel &sleutel, const Data &data)
{
    auto [plaats, ouder] = ZoekBoom<Sleutel,Data>::zoek(sleutel);

    if(*plaats){
        (*plaats)->data = data;
    }
    else {
        *plaats = Splayboom<Sleutel, Data>(std::make_unique<ZoekKnoop<Sleutel, Data>>(sleutel, data));
        plaats->get()->ouder = ouder;
    }

    splay(plaats->get());
}

template <class Sleutel, class Data>
ZoekKnoop<Sleutel, Data> *Splayboom<Sleutel, Data>::verwijder(const Sleutel &sleutel)
{
    ZoekKnoop<Sleutel, Data> * ouder_verwijderde_knoop = ZoekBoom<Sleutel, Data>::verwijder(sleutel);

    if(ouder_verwijderde_knoop != nullptr){
        splay(ouder_verwijderde_knoop);
    }
    return ouder_verwijderde_knoop;
}

template <class Sleutel, class Data>
void Splayboom<Sleutel, Data>::splay(ZoekKnoop<Sleutel, Data>* locatie){
    
    
    if(locatie == nullptr){ 
        std::cerr << "nullptr loc\n";
        return;
    }

    ZoekKnoop<Sleutel, Data>* kind = locatie;

    //std::cout << "before\n";
    // zolang de sleutel niet in de root zit
    
    while(kind->ouder != nullptr){
        ZoekKnoop<Sleutel, Data>* ouder = kind->ouder;
        
        const bool kind_links_ouder = kind->isLinkerKind();

        // Als ouder niet de wortel is
        // dus kind heeft een grootouder
        ZoekKnoop<Sleutel, Data>* grootouder = ouder->ouder;
        if(grootouder != nullptr){

            const bool ouder_links_grootouder = ouder->isLinkerKind();
            // ZIGZAG
            if(ouder_links_grootouder != kind_links_ouder){
                geefBoomVanKnoop(*ouder)->roteer(!kind_links_ouder);
                geefBoomVanKnoop(*grootouder)->roteer(!ouder_links_grootouder);
            } 
            // ZIGZIG
            // ouder_links_grootouder == kind_links_ouder
            else {
                geefBoomVanKnoop(*grootouder)->roteer(!ouder_links_grootouder);
                geefBoomVanKnoop(*ouder)->roteer(!ouder_links_grootouder); // kan ook kind_links_ouder zijn
            }
        } 
        // Kind is kind van de wortel, dus roteer kind naar wortel
        // ZIG
        else {
            geefBoomVanKnoop(*ouder)->roteer(!kind_links_ouder);
            
        }
    }
}

#endif