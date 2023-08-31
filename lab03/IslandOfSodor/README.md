# Min cut/max flow in een stroomnetwerk - Island of Sodor

## Introductie

In een graaf kan de max-flow-min-cut-stelling gebruikt worden voor verschillende 
interessante toepassingen: om de bottleneck in een netwerk te bepalen, om vraag
en aanbod maximaal met elkaar te verbinden, enzovoort.

## Opgave

Vervolledig de implementatie voor het zoeken van de min-cut/max-flow in een stroomnetwerk. 

Je krijgt een aantal bouwstenen van ons:

In [`stroomnet.h`](include/stroomnet.h) vind je volgende klassen:

* `Stroomnetwerk<T>`: deze klasse erft over van `GraafMetTakdata<GERICHT,T>`,
en krijgt ook een `van` en `naar` knoop opgegeven. De functie `geefStroom()` geeft
een Stroomnetwerk terug waarbij de waarde van elke tak in de graaf weergeeft hoeveel
*stroom* er door die tak passert zodat de *stroom* van de `van`-knoop naar de `naar`-knoop
maximaal is. `geefCapaciteit()` geeft terug hoeveel de totale stroom tussen de twee opgegeven knopen
bedraagt.

* `Pad<T>` erft over van `vector<int>`, en bevat de knoopnummers van een pad in de graaf.
De functie `geefCapaciteit` vertelt hoeveel stroom er over dit pad kan lopen.

* `VergrotendpadZoeker` is een hulpklasse die een vergrotend pad zoekt in een stroomnetwerk.


De functie `geefStroom` ziet eruit als volgt:

```cpp
template <class T>
Stroomnetwerk<T> Stroomnetwerk<T>::geefStroom() {
  Stroomnetwerk<T> oplossing(this->aantalKnopen(), van, naar);
  Stroomnetwerk<T> restnetwerk(*this);
  Vergrotendpadzoeker<T> vg(restnetwerk);
  Pad<T> vergrotendpad = vg.geefVergrotendPad();
  while (vergrotendpad.size() != 0) {
    restnetwerk -= vergrotendpad;
    oplossing += vergrotendpad;
    vergrotendpad = vg.geefVergrotendPad();
  }
  return oplossing;
}
```

Om deze code te doen werken, moeten er 2 operators worden geimplementeerd:

```
template <class T>
Stroomnetwerk<T>& Stroomnetwerk<T>::operator-=(const Pad<T>& pad)}{

template <class T>
Stroomnetwerk<T>& Stroomnetwerk<T>::operator+=(const Pad<T>& pad)
}
```  

Test dit uit met volgende graaf:

![](images/eenvoudig-stroomnetwerk.svg)
 

## Toepassing

Het eiland van Sodor omvat een groot aantal dorpen en steden, met elkaar verbonden via een extensief spoorwegennet. 
Recent werden enkele gevallen van een zeer besmettelijke ziekte (de varkenspest of een zombievirus, de filmpjes op 
sociale media zijn erg verwarrend) geraporteerd in de gemeente Ffarquhar. De uitbater van de "Sodor railway" plant
daarom om enkele treinstations te sluiten om zo te vermijden dat de ziekte zich kan verspreiden naar zijn thuisstad
Tidmouth. Geen enkele trein kan door een gesloten station rijden. Om de kosten te beperken (en verdere paniek te 
vermijden) wil hij zo weinig mogelijk stations sluiten. Hij kan echter het station van Ffarquhar niet sluiten, 
omdat dit hem aan de ziekte zou blootstellen, net zoals het station van Tidmouth, omdat hij anders niet meer naar
zijn favoriete café kan gaan.

Beschrijf en analyseer een algoritme om het minimale aantal stations te vinden dat hij moet sluiten om alle reizen
tussen Ffarquhar en Tidmouth onmogelijk te maken.

Het spoorwegennet van Sodor is voorgesteld als een ongerichte graaf in [sodor-trainnetwork.json](sodor-trainnetwork.json).
Let op: elke verbinding wordt 2x vermeld in dit bestand.

Om dit JSON-bestand in te lezen gebruiken we de populaire bibliotheek [nlohmann/json](https://github.com/nlohmann/json). 
Je krijgt van ons de code die deze JSON-file parset en omzet naar `structs` gedefinieerd in [network-reader.h](include/network-reader.h).

1. Construeer een graaf waarmee je bovenstaande opgave kan oplossen als een klassiek stroomnetwerk-probleem. Van welke 
   eigenschap van stroomnetwerken kan je gebruik maken?

   Implementeer hiervoor volgende functie in `sodor.cpp`:

   ```cpp
   int zoekMinimaleStationsluitingen(const std::vector<sodor::TrainStation> &stations,
                                    const std::string &startStationNaam, const std::string &eindStationNaam);
   ```


2. **Bonusopgave:** geef een lijst terug met de namen van de stations die dienen gesloten te worden. Definieer 
   hiervoor zelf de nodige extra functies.


#### Bronnen

[Jeff Erickson - CS 473: Algorithms](https://jeffe.cs.illinois.edu/)
