#ifndef __zoekBoom_H
#define __zoekBoom_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>
#include <random>

using std::cerr;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;
using std::unique_ptr;
/**********************************************************************

   Class: ZoekBoom

   beschrijving: Binaire ZoekBoom waarin duplicaatsleutels wel of niet zijn toegestaan.

***************************************************************************/

template <class Sleutel, class Data>
class ZoekKnoop;

template <class Sleutel, class Data>
class ZoekBoom : public unique_ptr<ZoekKnoop<Sleutel, Data>>
{
	using unique_ptr<ZoekKnoop<Sleutel, Data>>::unique_ptr;

public:
	// constructors and assignment operators
	ZoekBoom();
	ZoekBoom(const Sleutel &sleutel, const Data &data);
	ZoekBoom(ZoekBoom<Sleutel, Data> &andere);
	ZoekBoom(ZoekBoom<Sleutel, Data> &&andere);

	ZoekBoom(std::unique_ptr<ZoekKnoop<Sleutel, Data>> &&a); // added
	
	ZoekBoom<Sleutel, Data> &operator=(const ZoekBoom<Sleutel, Data> &andere);
	ZoekBoom<Sleutel, Data> &operator=(ZoekBoom<Sleutel, Data> &&andere);


	// Output functies schrijf en teken
	void inorder(std::function<void(const ZoekKnoop<Sleutel, Data> &)> bezoek) const;
	void schrijf(ostream &os) const;
	void teken(const char *bestandsnaam);
	string tekenrec(ostream &uit, int &knoopteller);

	//zoekboom operaties 
	void roteer(bool naarlinks);
    virtual bool zoekSleutel(const Sleutel& sleutel);
	virtual void voegtoe(const Sleutel &sleutel, const Data &data);
	virtual ZoekKnoop<Sleutel, Data> *verwijder(const Sleutel &sleutel); //geeft pointer naar ouder terug
	void maakOnevenwichtig();
	void maakEvenwichtig();

	//zoekboom hulpfuncties
	int aantalKnopen();
	int geefDiepte();
	ZoekBoom<Sleutel, Data> *geefBoomVanKnoop(ZoekKnoop<Sleutel, Data> &knoopptr);
	
	int getDoorzochteDieptie(){
		return totale_doorzochte_diepte;
	}
	void resetDoorzochteDiepte(){
		totale_doorzochte_diepte = 0;
	}

protected:
	int totale_doorzochte_diepte = 0;
	struct ZoekResultaat
	{
		ZoekBoom<Sleutel, Data> *plaats;
		ZoekKnoop<Sleutel, Data> *ouder;
	};
	/**
     * Deze functie zoekt sleutel en geeft de plaats in de boom terug waar de sleutel zich
     * bevindt, of indien afwezig: waar de sleutel zich zou moeten bevinden. 
     * 
     * Om deze functie ook in `voegtoe` te kunnen gebruiken geven we ook de ouder terug van 
     * de gevonden plaats. Deze referentie kan dan gebruikt worden om `ouder` in te vullen
     * in de nieuwe - aan te maken - knoop.
     *
     * Tip: maak gebruik van structured binding om het resultaat van deze functie in twee
     *      variabelen op te slaan. Zo kan je voorkomen dat je de struct `ZoekResultaat`
     *      dient te manipuleren.
     *
     *      auto [plaats,ouder] = zoek(sleutel);
     * 
     * Noot: alhoewel de functie niets verandert aan de boom is ze geen const functie, 
     * omdat ze een niet-const pointer naar het inwendige van de boom teruggeeft.
     */
	ZoekResultaat zoek(const Sleutel &sleutel);
	void maakEvenwichtigRec();

	ZoekBoom<Sleutel, Data> *subtreeMinimum(ZoekBoom<Sleutel, Data>* node);

	ZoekBoom<Sleutel, Data> *nextInorder(ZoekBoom<Sleutel, Data>* node);
};

/*****************************************************************************

	Implementatie

*****************************************************************************/

/*
Constructors en assignment operators
*/
template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>::ZoekBoom() {}

// added
template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>::ZoekBoom(std::unique_ptr<ZoekKnoop<Sleutel, Data>> &&a) : unique_ptr<ZoekKnoop<Sleutel, Data>>(move(a)) {
	
}

template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>::ZoekBoom(const Sleutel &sleutel, const Data &data) {
	*this = std::make_unique<ZoekKnoop<Sleutel, Data>>(ZoekKnoop<Sleutel,Data>(sleutel, data));
}
/**
 * Copy contructor
 */
template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>::ZoekBoom(ZoekBoom<Sleutel, Data> &andere) : std::unique_ptr<ZoekKnoop<Sleutel, Data>>{nullptr}
{
	if (andere)
	{
		(*this) = std::make_unique<ZoekKnoop<Sleutel, Data>>(*andere);
	}
}

/**
 * Move contructor
 */
template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>::ZoekBoom(ZoekBoom<Sleutel, Data> &&andere)
	: std::unique_ptr<ZoekKnoop<Sleutel, Data>>{std::move(andere)}
{
}

/**
 * Move assignment operator
 */
template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data> &ZoekBoom<Sleutel, Data>::operator=(ZoekBoom<Sleutel, Data> &&andere)
{
	this->swap(andere);
	return *this;
}

/**
 * Copy assignment operator
 */
template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data> &ZoekBoom<Sleutel, Data>::operator=(const ZoekBoom<Sleutel, Data> &andere)
{
	ZoekBoom<Sleutel, Data> temp(andere);
	temp.swap(*this);
	return *this;
}


/*
Output functies schrijf en teken
*/
template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::inorder(std::function<void(const ZoekKnoop<Sleutel, Data> &)> bezoek) const
{
	if (*this)
	{
		(*this)->links.inorder(bezoek);
		bezoek(**this);
		(*this)->rechts.inorder(bezoek);
	};
}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::schrijf(ostream &os) const
{
	inorder([&os](const ZoekKnoop<Sleutel, Data> &knoop) {
		if (knoop.ouder)
		{
			os << "(" << knoop.sleutel << " -> " << knoop.data << "/ ouder: " << knoop.ouder->sleutel << ")";
		}
		else
		{
			os << "(" << knoop.sleutel << " -> " << knoop.data << "/ wortel)";
		}
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

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::teken(const char *bestandsnaam)
{
	ofstream uit(bestandsnaam);
	assert(uit);
	int knoopteller = 0; //knopen moeten een eigen nummer krijgen.
	uit << "digraph {\n";
	this->tekenrec(uit, knoopteller);
	uit << "}";
}

template <class Sleutel, class Data>
string ZoekBoom<Sleutel, Data>::tekenrec(ostream &uit, int &knoopteller)
{
	ostringstream wortelstring;
	wortelstring << '"' << ++knoopteller << '"';
	if (!*this)
	{
		uit << wortelstring.str() << " [shape=point];\n";
	}
	else
	{
		uit << wortelstring.str() << "[label=\"" << (*this)->sleutel << ":" << (*this)->data << "\"]";
		uit << ";\n";
		string linkskind = (*this)->links.tekenrec(uit, knoopteller);
		string rechtskind = (*this)->rechts.tekenrec(uit, knoopteller);
		uit << wortelstring.str() << " -> " << linkskind << ";\n";
		uit << wortelstring.str() << " -> " << rechtskind << ";\n";
	};
	return wortelstring.str();
}


/*
	Zoekboom operaties
*/

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::roteer(bool naarLinks)
{
	// indien de wortel niet bestaat
    if(!*this){
        return;
    }
    // indien het nodige kind niet bestaat
    if(!(*this)->geefKind(!naarLinks)){
        return;
    }

    ZoekKnoop<Sleutel, Data>* ouder_root = (*this)->ouder; // hou de ouder van de root bij
    // Rotatie
    // zie figuur https://en.wikipedia.org/wiki/Tree_rotation#/media/File:Tree_Rotations.gif
    // 1
    ZoekBoom<Sleutel, Data> pivot(std::move((*this)->geefKind(!naarLinks)));

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

}

template <class Sleutel, class Data>
bool ZoekBoom<Sleutel, Data>::zoekSleutel(const Sleutel &sleutel){
    auto [plaats,ouder] = zoek(sleutel);
	assert(plaats != nullptr);
    return (*plaats != nullptr);
}

template <class Sleutel, class Data>
typename ZoekBoom<Sleutel, Data>::ZoekResultaat ZoekBoom<Sleutel, Data>::zoek(const Sleutel &sleutel)
{
	// pointer naar huidige boom bijhouden
    // links of rechts afdalen
    // pointer verzetten
    ZoekBoom<Sleutel, Data>* huidige_boom = this;
    ZoekKnoop<Sleutel, Data>* huidige_ouder = nullptr;

    while(huidige_boom->get()){ // get() vraagt raw pointer op
        totale_doorzochte_diepte++;
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

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::voegtoe(const Sleutel &sleutel, const Data &data)
{
	auto [kind, ouder] = zoek(sleutel);
	
	if(kind->get() != nullptr){ 
        return;
    }
    // sleutel bestaat niet
    *kind = ZoekBoom<Sleutel, Data>(std::make_unique<ZoekKnoop<Sleutel, Data>>(sleutel, data));
    kind->get()->ouder = ouder; // ouder instellen van deze knoop

}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel,Data>::maakOnevenwichtig(){
    //Alles van links naar boven duwen
	const bool alles_naar_rechts = true;
	
    while((*this)->geefKind(alles_naar_rechts)){ // linkerkind opvragen
        roteer(!alles_naar_rechts); // roteer naar rechts
    }  
    // Boom gladstrijken rechts
    if ((*this)->geefKind(!alles_naar_rechts)){
        (*this)->geefKind(!alles_naar_rechts).maakOnevenwichtig();
    }
}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::maakEvenwichtigRec(){
	if(*this) {
		int diepte = this->geefDiepte();
		if( (*this)->geefKind(false)){ // heeft hij een rechterkind?
			for(int i = 0; i < diepte / 2; i++){
				roteer(true);
			}
		}
		else if ( (*this)->geefKind(true)) {
			for(int i = 0; i < diepte / 2; i++){
				roteer(false);
			}
		}
		// maak beide kinderen evenwichtig
		(*this)->geefKind(true).maakEvenwichtigRec();
		(*this)->geefKind(false).maakEvenwichtigRec();
	}
}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::maakEvenwichtig(){
    maakOnevenwichtig(); // maakt een onevenwichtige boom rechts
	maakEvenwichtigRec();
}


// zie slide 8, efficientezoekbomen_deel1
template <class Sleutel, class Data>
ZoekKnoop<Sleutel, Data> *ZoekBoom<Sleutel, Data>::verwijder(const Sleutel &sleutel)
{
	auto [z, ouder] = zoek(sleutel);
	if(z->get() == nullptr){
		return nullptr;
	}
	const bool heeftlinker = z->get()->links.get() != nullptr;
    const bool heeftrechter = z->get()->rechts.get() != nullptr;

	// twee kinderen
	if(heeftlinker && heeftrechter){
		ZoekBoom<Sleutel, Data>* y = nextInorder(z);
		ZoekBoom<Sleutel, Data>* v = &(y->get()->rechts);

		// v zijn nieuwe ouder (q) instellen
		if(v->get() != nullptr){
			v->get()->ouder  = y->get()->ouder; 
		}

		// knoop van y bijhouden
		ZoekKnoop<Sleutel, Data>* y_knoop = y->release();

		// v in y moven
		if(v->get() != nullptr){
			*y = std::move(*v);
		}
		
		// wissel gegevens knoop y naar knoop z
		std::swap(z->get()->sleutel, y_knoop->sleutel);
		std::swap(z->get()->data, y_knoop->data);

		ZoekKnoop<Sleutel, Data>* ouder_verwijderde_knoop = y_knoop->ouder;
		delete y_knoop;

		return ouder_verwijderde_knoop;	
	}
	// geen kinderen
	else if(!heeftlinker && !heeftrechter){
		ZoekKnoop<Sleutel, Data>* z_knoop = z->release();
		ZoekKnoop<Sleutel, Data>* ouder_verwijderde_knoop = z_knoop->ouder;
		delete z_knoop;

		return ouder_verwijderde_knoop;
	}
	// 1 kind
	else {

		// kind zijn nieuwe ouder (q) instellen
		z->get()->geefKind(heeftlinker ? true : false).get()->ouder  = z->get()->ouder; 

		// knoop van z bijhouden
		ZoekKnoop<Sleutel, Data>* z_knoop = z->release();

		// move het kind van z in z; zo hangt het kind van z onmiddellijk op de juiste positie (links of rechts) waar z vroeger aan q hing
		*z = std::move(z_knoop->geefKind(heeftlinker ? true : false));

		ZoekKnoop<Sleutel, Data>* ouder_verwijderde_knoop = z_knoop->ouder;
		delete z_knoop;

		return ouder_verwijderde_knoop;
	}
 
}

/*
hulpfuncties
*/

template <typename Sleutel, typename Data>
ZoekBoom<Sleutel, Data> *ZoekBoom<Sleutel, Data>::subtreeMinimum(ZoekBoom<Sleutel, Data>* node)
{
    // adapted from: https://github.com/llvm/llvm-project/blob/978fbd8268ce5f5cd01ae9fc41cd03ea7a08dabe/libcxx/include/__tree#L145
    // opvolger bestaat enkel als node rechterkind heeft
    assert(node->get() != nullptr);

    while(node->get()->links.get() != nullptr){
        node = &node->get()->links;
    }

    return node;
}

template <typename Sleutel,typename Data> 
ZoekBoom<Sleutel, Data> *ZoekBoom<Sleutel, Data>::nextInorder(ZoekBoom<Sleutel, Data>* node)
{
    // adapted from: https://github.com/llvm/llvm-project/blob/978fbd8268ce5f5cd01ae9fc41cd03ea7a08dabe/libcxx/include/__tree#L168
    
    // opvolger bestaat enkel als node rechterkind heeft
    assert(node->get() != nullptr);

    // opvolger is min in rechter kindboom als deze bestaat
    if(node->get()->rechts.get() != nullptr){
        return subtreeMinimum(&(node->get()->rechts));
    }
    // Zo lang next niet het linkerkind is van zijn ouder (en dus een kleinere sleutel heeft als zijn ouder)
    // of next de root is en ouder een nullptr is
    // dit omdat inorder 1) linkerboom bezoekt 2) root bezoekt) dan rechterboom
    // wanneer we bij een node komen die het linkerkind is zal zijn ouder de inorder opvolger zijn
    ZoekKnoop<Sleutel, Data>* next = node->get();

	while(next->ouder != nullptr && !next->isLinkerKind()){
		next = next->ouder;
	}
	// next is de root
	if(next->ouder == nullptr){
        return nullptr; //geefBoomVanKnoop(*next);
    }
	// next is linkerkind van ouder dus ouder is inorder opvolger
	else {
		return geefBoomVanKnoop(*(next->ouder));
	}
    
}


template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data> *ZoekBoom<Sleutel, Data>::geefBoomVanKnoop(ZoekKnoop<Sleutel, Data> &knoop)
{
	assert((*this)->ouder == nullptr); //deze functie mag enkel in de wortel van de boom worden opgeroepen
	if (knoop.ouder == nullptr)
		return this;
	else if (knoop.ouder->links.get() == &knoop)
		return &(knoop.ouder->links);
	else
		return &(knoop.ouder->rechts);
}

template <class Sleutel, class Data>
int ZoekBoom<Sleutel, Data>::geefDiepte()
{
	if (*this)
	{
		return 1 + std::max((*this)->links.geefDiepte(), (*this)->rechts.geefDiepte());
	}
	else
		return 0;
}


template <class Sleutel, class Data>
int ZoekBoom<Sleutel, Data>::aantalKnopen()
{
	if (*this)
	{
		return 1 + (*this)->links.aantalKnopen() + (*this)->rechts.aantalKnopen();
	}
	return 0;
}

#endif