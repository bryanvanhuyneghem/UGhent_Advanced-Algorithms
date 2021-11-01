//
// Created by Thijs on 10/19/2020.
//

#include "zoekboom.h"

#ifndef LABO_SPLAYBOOM_TEST_UTILS_H
#define LABO_SPLAYBOOM_TEST_UTILS_H

void vulZoekboom(ZoekBoom<int, int> &boom, int grootte);


/**
 * Representation Invariant test
 *
 * Deze functie test of het gegeven RZWboom-object een geldige rood-zwart boom voorstelt.
 *
 * Het test:
 * - Of de boom een geldige binaire boom is: zijn alle pointers geldig ingevuld?
 * - Of de sleutels in volgorde staan.
 */
template<class Sleutel, class Data>
void repOKZoekboom(const ZoekBoom<Sleutel, Data> &boom){
    Sleutel *vorige = nullptr; //houdt ref naar eerder gezien sleutel bij.
    if (boom.get()->ouder != nullptr)
        throw std::runtime_error("wortel heeft geen null-ouder");
    boom.inorder([&vorige](const ZoekKnoop<Sleutel, Data> &knoop) {
        //volgorde sleutels
        if (vorige && knoop.sleutel < *vorige) {
            throw std::runtime_error("Verkeerde volgorde");
        };

        //ouderpointers
        for (const ZoekKnoop<Sleutel, Data> *kind : {knoop.links.get(), knoop.rechts.get()})
            if (kind != 0 && kind->ouder != &knoop) {
                std::ostringstream fout;
                fout << "Ongeldige ouderpointer bij knoop " << kind->sleutel << "\n";
                fout << " wijst niet naar " << knoop.sleutel << "\n";
                throw std::runtime_error(fout.str());
            };
    });
}


#endif //LABO_SPLAYBOOM_TEST_UTILS_H
