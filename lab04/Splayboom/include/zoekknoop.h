#ifndef __Zoekknoop_H
#define __Zoekknoop_H
#include "zoekboom.h"

template <class Sleutel, class Data>
class ZoekKnoop
{
	friend class ZoekBoom<Sleutel, Data>;

public:
	ZoekKnoop() : ouder(0) {}
	ZoekKnoop(const Sleutel &sl, const Data &d) : sleutel{sl}, data(d), ouder(0){};
	ZoekKnoop(Sleutel &&sl, Data &&d) : sleutel{move(sl)}, data(move(d)), ouder(0){};

	ZoekBoom<Sleutel, Data> &geefKind(bool links);
	bool isLinkerKind();
	ZoekKnoop<Sleutel, Data> *geefOuder();
	void wijzigData(Data &&data);
	Data geefData();

	
	Sleutel sleutel;
	Data data;
	ZoekKnoop<Sleutel, Data> *ouder;
	ZoekBoom<Sleutel, Data> links, rechts;
};

template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data> &ZoekKnoop<Sleutel, Data>::geefKind(bool linkerkind)
{
	if (linkerkind)
		return links;
	else
		return rechts;
};

template <class Sleutel, class Data>
bool ZoekKnoop<Sleutel, Data>::isLinkerKind()
{
	return (*this).ouder->links.get() == this;
};

template <class Sleutel, class Data>
ZoekKnoop<Sleutel, Data> *ZoekKnoop<Sleutel, Data>::geefOuder()
{
	return (*this).ouder;
};

template <class Sleutel, class Data>
void ZoekKnoop<Sleutel, Data>::wijzigData(Data &&data)
{
	this->data = data;
};

template <class Sleutel, class Data>
Data ZoekKnoop<Sleutel, Data>::geefData()
{
	return this->data;
};

#endif