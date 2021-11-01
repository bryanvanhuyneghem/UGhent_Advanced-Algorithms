# De Langste Woordketting

## Introductie

In deze oefening gaan we kringkettingen van kettingwoorden vormen. Hierbij gaan we uit van het Groene Boekje. 
Er is een tak van een woord naar een tweede woord als er een derde woord is, langer dan elk van de twee eerste,
dat het eerste woord als prefix heeft, en het tweede als suffix. Zo
is er een tak van zwijn naar wijnachtig, want het woord zwijnachtig
staat in het Groene Boekje. In het bestand 
[woordenlijst.txt](woordenlijst.txt) vind je een lijst met alle 
woorden die met een ander woord verbonden zijn, in 
[takkenlijst.txt](takkenlijst.txt) een lijst met alle takken. Het
spelletje bestaat eruit om te proberen een kettingwoord te maken
van begin naar einde uitgaande van twee woorden. Een voorbeeld: om
van `aal` naar `hond` te gaan hebben we twee stappen nodig:
`aalbessengelei` en `geleidehond`. Je kan ook proberen terug te
gaan: dit kan met `honderdmaal`. Zo krijgen we de kringketting
`aalbessengeleidehonderdmaal` .

[![](https://mermaid.ink/img/eyJjb2RlIjoiZ3JhcGggVERcbmFhbCAtLT58YWFsYmVzc2VuZ2VsZWl8IGdlbGVpXG5nZWxlaSAtLT58Z2VsZWlkZWhvbmR8IGhvbmRcbmhvbmQgLS0-fGhvbmRlcmRtYWFsfCBhYWwiLCJtZXJtYWlkIjp7InRoZW1lIjoiZGVmYXVsdCJ9LCJ1cGRhdGVFZGl0b3IiOmZhbHNlfQ)](https://mermaid-js.github.io/mermaid-live-editor/#/edit/eyJjb2RlIjoiZ3JhcGggVERcbmFhbCAtLT58YWFsYmVzc2VuZ2VsZWl8IGdlbGVpXG5nZWxlaSAtLT58Z2VsZWlkZWhvbmR8IGhvbmRcbmhvbmQgLS0-fGhvbmRlcmRtYWFsfCBhYWwiLCJtZXJtYWlkIjp7InRoZW1lIjoiZGVmYXVsdCJ9LCJ1cGRhdGVFZGl0b3IiOmZhbHNlfQ)


## Opgave

We willen berekenen welke combinaties van woorden kunnen voorkomen in een kringketting. We berekenen hiervoor de *sterk samenhangende componenten* in deze graaf.

Gegeven is de klasse `Graaf` uit [graaf.hpp](src/graaf.hpp). Implementeer in [componenten.cpp](src/componenten.cpp) de volgende functie: 
```cpp
/**
 * Bereken de sterk geconnecteerde componenten van een gegeven graaf.
 * 
 * @param[g] De opgegeven graaf
 * 
 * @returns Een afbeelding van elke knoop op zijn componentnummer. 
 *          De componentnummers zijn een aaneensluitende lijst van getallen,
 *          startende bij 0.
 */ 
vector<int> sterk_geconnecteerde_componenten(Graaf<GERICHT> g);

```

Voor de implementatie dien je diepte-eerst-zoeken toe te passen. Implementeer hiervoor volgende functie:

```cpp
template <RichtType RT, typename PreOrderFunc, typename PostOrderFunc>
void diepte_eerst_zoeken(const Graaf<RT> &g, PreOrderFunc pre_order_func, PostOrderFunc post_order_func);
```

Waarbij `pre_order_func` en `post_order_func` allebei lambda-functies zijn die worden opgeroepen voor 
en na het verwerken van een knoop, met als enige argument het knoop-nummer. 

Bijvoorbeeld:

```cpp

diepte_eerst_zoeken(g, 
                    [](int knoop_nr) { cout << "Nu voor knoop "<< knoop_nr << endl; }, 
                    [](int knoop_nr) { cout << "Nu na knoop "<< knoop_nr << endl; });

```


Hoeveel van deze componenten bestaan er?

Wat is de grootste groep van woorden die met elkaar kan worden gecombineerd to kringkettingen? ie. Hoe groot is de grootste *sterk samenhangende component*?

Gegeven deze grootste groep, stel een kringketting op als volgt:
- start bij het woord dat alfabetisch als eerste voorkomt (eg. aagt < aai)
- kies steeds de verbinding met de buur uit dezelfde sterk geconnecteerde component die alfabetisch eerst voorkomt.
- herhaal tot je terug bij het eerste woord uitkomt.

(**TIP**: `woordenlijst.txt` en `takkenlijst.txt` zijn alfabetisch gesorteerd. Is het dan wel nodig om de alfabetische volgorde van knopen/takken ten opzicht van elkaar te testen?)

Implementeer hiervoor volgende functie in [woordspel.cpp](src/woordspel.cpp): 

```cpp
/**
 * Bereken de sterk geconnecteerde componenten van een gegeven graaf.
 * 
 * @param[g] De graaf opsteld met leesGraaf
 * @param[g] De component-nummers van de overeenkomstige knopen
 * @param[g] De component voor dewelke een kringketting moet worden bepaald.
 * 
 * @returns De eerste alfabetisch voorkomende kringketting in de component met nummer `component_nr`
 */ 
Keten eersteKringKetting(const GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> &g,
                         const vector<int> &component_nrs,
                         int component_nr);

```

Gebruik de klasse [`Keten`](src/keten.hpp) om deze ketting van woorden af te drukken.

Wat is het woord als je steeds het laatste ipv het eerste woord neemt?