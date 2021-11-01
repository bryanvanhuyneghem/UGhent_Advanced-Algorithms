#ifndef __RZWboom_H
#define __RZWboom_H
#include <iostream>

#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>

using std::cerr;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;
using std::unique_ptr;

enum RZWkleur
{
    rood,
    zwart
};

template <class Sleutel>
class RZWknoop;

// this is een pointer naar een boom; *this is de boom zelf; **this is de knoop


/**
 * Binaire RZWboom waarin geen duplicaatsleutels zijn toegestaan.
 */
template <class Sleutel>
class RZWboom : public unique_ptr<RZWknoop<Sleutel>>
{
public:
    using unique_ptr<RZWknoop<Sleutel>>::unique_ptr;

    RZWboom(unique_ptr<RZWknoop<Sleutel>> &&a);
    RZWboom() : unique_ptr<RZWknoop<Sleutel>>(){};

    //Gegeven
    void inorder(std::function<void(const RZWknoop<Sleutel> &)> bezoek) const;
    void schrijf(ostream &os) const;
    void tekenAls234Boom(const char *bestandsnaam) const;
    string tekenrec234(ostream &uit, int &nullteller, int &knoop34teller) const;
    void tekenAlsBinaireBoom(const char *bestandsnaam) const;
    string tekenrecBinair(ostream &uit, int &nullteller) const;
    RZWboom<Sleutel> *geefBoomVanKnoop(RZWknoop<Sleutel> &knoop);

    //te implementeren
    bool zoekSleutel(const Sleutel& sleutel);
    void roteer(bool naarlinks);
    int geefDiepte() const;
    RZWkleur geefKleur() const;
    void zetKleur(RZWkleur kl);
    void voegtoe(const Sleutel &sleutel); //noot: functie mag alleen opgeroepen worden bij hoofdboom (bij wortel), niet bij deelboom!

    bool isKnoopLeeg();
    
    void bottomUpFixup(RZWboom<Sleutel>& kind);

    bool verwijderSleutel(const Sleutel& sleutel);
protected:
    struct ZoekResultaat
    {
        RZWboom<Sleutel> *kind;
        RZWknoop<Sleutel> *ouder;
    };
    /**
     * Deze functie zoekt sleutel en geeft de kind in de boom terug waar de sleutel zich
     * bevindt, of indien afwezig: waar de sleutel zich zou moeten bevinden. 
     * 
     * Om deze functie ook in `voegtoe` te kunnen gebruiken geven we ook de ouder terug van 
     * de gevonden kind. Deze referentie kan dan gebruikt worden om `ouder` in te vullen
     * in de nieuwe - aan te maken - knoop.
     * 
     * Tip: maak gebruik van structured binding om het resultaat van deze functie in twee
     *      variabelen op te slaan. Zo kan je voorkomen dat je de struct `ZoekResultaat`  
     *      dient te manipuleren.
     * 
     *      auto [kind,ouder] = zoek(sleutel);
     * 
     * Noot: alhoewel de functie niets verandert aan de boom is ze geen const functie, 
     *       omdat ze een niet-const pointer naar het inwendige van de boom teruggeeft.
     */
    ZoekResultaat zoek(const Sleutel &sleutel);
};

template <class Sleutel>
RZWboom<Sleutel>::RZWboom(unique_ptr<RZWknoop<Sleutel>> &&a) : unique_ptr<RZWknoop<Sleutel>>(move(a)) {}

template <class Sleutel>
void RZWboom<Sleutel>::inorder(std::function<void(const RZWknoop<Sleutel> &)> bezoek) const
{
    if (*this) 
    {
        (*this)->links.inorder(bezoek);
        bezoek(**this);
        (*this)->rechts.inorder(bezoek);
    };
}

template <class Sleutel>
void RZWboom<Sleutel>::schrijf(ostream &os) const
{
    inorder([&os](const RZWknoop<Sleutel> &knoop) {
        os << "(" << knoop.sleutel << " ";
        if (knoop.kleur == rood)
            os << "rood";
        else
        {
            os << "zwart";
        }
        os << ")";
        os << "\n  Linkerkind: ";
        if (knoop.links)
            os << knoop.links->sleutel;
        else
            os << "-----";
        os << "\n  Rechterkind: ";
        if (knoop.rechts)
            os << knoop.rechts->sleutel;
        else
            os << "-----";
        os << "\n";
    });
}

template <class Sleutel>
void RZWboom<Sleutel>::tekenAls234Boom(const char *bestandsnaam) const
{
    ofstream uit(bestandsnaam);
    assert(uit);
    int nullteller = 0;    //nullknopen moeten een eigen nummer krijgen.
    int knoop34teller = 0; //3-knopen en 4-knopen worden ook genummerd
    uit << "digraph {\n";
    this->tekenrec234(uit, nullteller, knoop34teller);
    uit << "}";
}

template <class Sleutel>
string RZWboom<Sleutel>::tekenrec234(ostream &uit, int &nullteller, int &knoop34teller) const
{
    ostringstream wortelstring;
    if (!*this)
    {
        wortelstring << "null" << ++nullteller;
        uit << wortelstring.str() << " [shape=point];\n";
    }
    else
    {
        wortelstring << '"' << (*this)->sleutel << '"';
        uit << wortelstring.str() << "[label=\"" << (*this)->sleutel << "\"]";
        if (this->geefKleur() == rood)
            uit << "[color=red]";
        uit << ";\n";
        string linkskind = (*this)->links.tekenrec234(uit, nullteller, knoop34teller);
        ;
        string rechtskind = (*this)->rechts.tekenrec234(uit, nullteller, knoop34teller);
        ;
        if ((*this)->links.geefKleur() == rood ||
            (*this)->rechts.geefKleur() == rood)
        {
            uit << "subgraph cluster_" << ++knoop34teller << " {\n   { rank=\"same\"; ";
            if ((*this)->links.geefKleur() == rood)
                uit << linkskind << " , ";
            if ((*this)->rechts.geefKleur() == rood)
                uit << rechtskind << " , ";
            uit << wortelstring.str() << "}\n";
            if ((*this)->links.geefKleur() == rood)
                uit << "   " << linkskind << " ->" << wortelstring.str() << "[dir=back];\n";
            if ((*this)->rechts.geefKleur() == rood)
                uit << "   " << wortelstring.str() << " -> " << rechtskind << ";\n";
            uit << "color=white\n}\n";
        };
        if ((*this)->links.geefKleur() == zwart)
            uit << wortelstring.str() << " -> " << linkskind << ";\n";
        if ((*this)->rechts.geefKleur() == zwart)
            uit << wortelstring.str() << " -> " << rechtskind << ";\n";
    };
    return wortelstring.str();
}

template <class Sleutel>
void RZWboom<Sleutel>::tekenAlsBinaireBoom(const char *bestandsnaam) const
{
    ofstream uit(bestandsnaam);
    assert(uit);
    int nullteller = 0; //nullknopen moeten een eigen nummer krijgen.
    uit << "digraph {\n";
    this->tekenrecBinair(uit, nullteller);
    uit << "}";
}

template <class Sleutel>
string RZWboom<Sleutel>::tekenrecBinair(ostream &uit, int &nullteller) const
{
    ostringstream wortelstring;
    if (!*this)
    {
        wortelstring << "null" << ++nullteller;
        uit << wortelstring.str() << " [shape=point];\n";
    }
    else
    {
        wortelstring << '"' << (*this)->sleutel << '"';
        uit << wortelstring.str() << "[label=\"" << (*this)->sleutel << "\"]";
        if (this->geefKleur() == rood)
            uit << "[color=red]";
        uit << ";\n";
        string linkskind = (*this)->links.tekenrecBinair(uit, nullteller);
        string rechtskind = (*this)->rechts.tekenrecBinair(uit, nullteller);
        uit << wortelstring.str() << " -> " << linkskind << ";\n";
        uit << wortelstring.str() << " -> " << rechtskind << ";\n";
    };
    return wortelstring.str();
}

// rzwkoop is een gewone knoop en met deze functie ga je de ouder van deze knoop en check je of de knoop die we zoeken het linker- of rechterkind zijn
template <class Sleutel>
RZWboom<Sleutel> *RZWboom<Sleutel>::geefBoomVanKnoop(RZWknoop<Sleutel> &knoop)
{
    assert((*this)->ouder == nullptr); //deze functie mag enkel in de wortel van de boom worden opgeroepen

    if (knoop.ouder == nullptr)
        return this; //wortel
    else if (knoop.ouder->links.get() == &knoop)
        return &(knoop.ouder->links);
    else
        return &(knoop.ouder->rechts);
};

// Te implementeren:
template <class Sleutel>
int RZWboom<Sleutel>::geefDiepte() const
{
    /*
    if(!*this){
        return 0;
    }

    int linker_diepte = 0;
    int rechter_diepte = 0;
    if((*this)->links){
        linker_diepte = (*this)->links.geefDiepte();
    }
    if((*this)->rechts){
        rechter_diepte = (*this)->rechts.geefDiepte();
    }

    return std::max(linker_diepte, rechter_diepte) + 1;
    */
    if (*this)
        return 1 + std::max((*this)->links.geefDiepte(), (*this)->rechts.geefDiepte());
    else
        return 0;
}

template <class Sleutel>
typename RZWboom<Sleutel>::ZoekResultaat RZWboom<Sleutel>::zoek(const Sleutel &sleutel)
{
    // pointer naar huidige boom bijhouden
    // links of rechts afdalen
    // pointer verzetten
    RZWboom<Sleutel>* huidige_boom = this;
    RZWknoop<Sleutel>* huidige_ouder = nullptr;

    while(huidige_boom->get()){ // get() vraagt raw pointer op
        
        const Sleutel& huidige_sleutel = (*huidige_boom)->sleutel;
        if (sleutel == huidige_sleutel){ // sleutel gevonden
            return {huidige_boom, (*huidige_boom)->ouder};
        }
        else {
            huidige_ouder = huidige_boom->get();
            const bool linkerkind = sleutel < huidige_sleutel;
            huidige_boom = &((*huidige_boom)->geefKind(linkerkind));
        }

        assert(huidige_boom != nullptr);
    }

    return {huidige_boom, huidige_ouder};
};

//gebruik makend van zoek()
template <class Sleutel>
bool RZWboom<Sleutel>::zoekSleutel(const Sleutel &sleutel)
{
    auto [kind, ouder] = zoek(sleutel);
    assert(kind != nullptr);

    if(*kind){
        return true;
    }
    return false;
}

//preconditie: wortel en nodige kind bestaan
//FIXME: waarom kloppen pointers niet meer na rotaties?

template <class Sleutel>
void RZWboom<Sleutel>::roteer(bool naarLinks)
{
    // indien de wortel niet bestaat
    if(!*this){
        return;
    }
    // indien het nodige kind niet bestaat
    if(!(*this)->geefKind(!naarLinks)){
        return;
    }

    RZWknoop<Sleutel>* ouder_root = (*this)->ouder; // hou de ouder van de root bij
    // Rotatie
    // zie figuur https://en.wikipedia.org/wiki/Tree_rotation#/media/File:Tree_Rotations.gif
    // 1
    RZWboom<Sleutel> pivot(std::move((*this)->geefKind(!naarLinks)));

    // 2
    if(pivot->geefKind(naarLinks)){
        (*this)->geefKind(!naarLinks) = std::move(pivot->geefKind(naarLinks));
        (*this)->geefKind(!naarLinks)->ouder = this->get();
    }

    // 3
    this->swap(pivot);             // wissel (3) en (5) of dus pivot & root

    //4                          // voorbeeld bij `right rotation`
    (*this)->ouder = ouder_root; // origineel de ouder van de root; de root zijnde nu (3) in het voorbeeld
    pivot->ouder = this->get(); // this->get() is de 3, zijnde de nieuwe ouder van 5 (pivot->ouder is 5->ouder)
    (*this)->geefKind(naarLinks) = std::move(pivot); // pivot is hier (5), zet je als rechterkind van (3)

};

template <class Sleutel>
void RZWboom<Sleutel>::zetKleur(RZWkleur kleur)
{
    if(this->get()){
        (*this)->kleur = kleur;
    }
    else {
        std::cerr << "zetKleur op onbestaande knoop!\n";
    }
};

template <class Sleutel>
RZWkleur RZWboom<Sleutel>::geefKleur() const
{
    // moet dit de hudige kleur teruggeven of de kleur die de knoop zou moeten zitten?
    if(this->get()){
        return (*this)->kleur;
    }
    return RZWkleur::zwart;
}

// Hulpmethode bij voegtoe
template <class Sleutel>
bool RZWboom<Sleutel>::isKnoopLeeg(){
    return !this->get();
}

template <class Sleutel>
void RZWboom<Sleutel>::voegtoe(const Sleutel &sleutel)
{
    auto [kind, ouder] = zoek(sleutel);

    // sleutel bestaat al
    if(!kind->isKnoopLeeg()){ // aanpassing voor bonusvraag 3 (bijhouden hoeveel keer een woord voorkomt)
        return;
    }
    // sleutel bestaat niet
    *kind = RZWboom<Sleutel>(std::make_unique<RZWknoop<Sleutel>>(sleutel));
    kind->get()->ouder = ouder; // ouder instellen van deze knoop

    bottomUpFixup(*kind);
    
}
template <class Sleutel>
void RZWboom<Sleutel>::bottomUpFixup(RZWboom<Sleutel>& kind){
    
    // als de knoop waar we tijdens de recursie bij komen geen ouder heeft, dan is deze knoop de root
    // en moet hij zwart zijn 
    auto ouder = kind->ouder;

    if(ouder == nullptr){
        kind->kleur = RZWkleur::zwart;
        return;
    }
    // als de ouder al zwart is klopt de boom
    else if(ouder->kleur == RZWkleur::zwart){
        return;
    }

    auto grootouder = kind->ouder->ouder;

    // todo: wsl verwijderen
    // als grootouder niet bestaat, dan moeten we ouder zwart kleuren want ouder is de root van de boom
    if(grootouder == nullptr){ 
        std::cout << "Root van boom was rood bij toevoegen\n" 
            <<"kind: " << kind->sleutel << "\n"
            <<"ouder: "<< ouder->sleutel << "\n"
            <<"diepte: " << geefDiepte() << "\n";

        ouder->kleur = RZWkleur::zwart;
        return;
    }
    
    const bool ouderIsLinkerKind = (grootouder->geefKind(true).get() == ouder);
    auto oom = grootouder->geefKind(!ouderIsLinkerKind).get();
    // Scenario 1: oom is rood
    if(oom && oom->kleur == RZWkleur::rood){
        ouder->kleur = RZWkleur::zwart;
        oom->kleur = RZWkleur::zwart;
        grootouder->kleur = RZWkleur::rood;
        // Rood maken van grootouder kan ervoor zorgen dat boom niet klopt als ouder van grootouder ook rood is
        bottomUpFixup(*geefBoomVanKnoop(*grootouder));
    }
    // Scenario 2: oom is zwart; oom->kleur == RZWkleur::zwart
    else {
        assert(oom == nullptr || oom->kleur == RZWkleur::zwart);

        // Als ouder linkerkind is van grootouder moet kind linkerkind zijn van ouder om op een lijn te liggen
        // omgekeerd als ouder rechterkind is van grootouder moet kind rechterkind zijn van ouder
        const bool opEenLijn = (ouder->geefKind(ouderIsLinkerKind).get() == kind.get());
        
        // kind, ouder en grootouder op een lijn leggen
        auto ouderboom = geefBoomVanKnoop(*ouder);
        

        if(!opEenLijn){
            ouderboom->roteer(ouderIsLinkerKind); // rotatie naar links als p linkerkind is en kind rechterkind
        }
        // Vanaf hier liggen kind, ouder en grootouder op één lijn
        // wissel ouder en grootouder van kleur

        //FIXME: waarom kloppen pointers niet meer na rotaties?
        ouderboom->zetKleur(RZWkleur::zwart);
        auto grootouderboom = geefBoomVanKnoop(*grootouder);

        grootouderboom->zetKleur(RZWkleur::rood);
        // Rotatie in de richting zodat ouder de ouder van grootouder wordt
        grootouderboom->roteer(!ouderIsLinkerKind); 
        

        
    }
}

template <typename Sleutel>
bool verwijderSleutel(const Sleutel& sleutel);

#endif
