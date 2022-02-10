# Feest bij Ryanair

## Introductie

Ryanair staat erom bekend om elke crisis als een winnaar te boven te komen. Ook
deze keer is dit weer het geval. Om dat te vieren beslist de excentrieke CEO 
Michael O'Leary dat een extravangante mediacampagne op zijn plaats is, en laat
hij een van zijn vliegtuigen van top tot teen in het goud te schilderen. 

Hij wil hiermee elke route uit het netwerk van Ryanair in de verf zetten. Hij 
vraagt aan jou om een vluchtplan uit te tekenen waarmee elke verbinding uit
het Ryanair netwerk minstens een keer wordt aangedaan. Krenterig als hij is, 
wil hij natuurlijk zo weinig mogelijk nutteloze positioneringsvluchten. Hij
belooft daarom een mooie prijs (een waardebon van 10 euro om te besteden in de
Ryanair fanshop) als je deze in zijn geheel kan vermijden.

Je krijgt een bestand `ryanair.txt` waar elke te maken vlucht exact 1x staat 
vermeld. Elke regel bevat de [ICAO airport code](https://en.wikipedia.org/wiki/ICAO_airport_code)
van de vertrek- en bestemmingsluchthaven.

De route Charleroi - Dublin staat dus 2x vermeld: 1 keer als "EBCI  EIDW", en 
eenmaal als "EIDW   EBCI".

![](images/golden-airplane.jpg)

## Opgave

*   Aan welke voorwaarden moet een gerichte graaf voldoen opdat er een Eulercircuit zou bestaan? En wat voor een ongericht graaf?
    Implementeer deze voorwaarden via volgende functies in `euler.cpp`:
    
    ```cpp
    bool heeft_eulercircuit(const Graaf<ONGERICHT>& g);

    bool heeft_eulercircuit(const Graaf<GERICHT>& g);
    ``` 

*   Implementeer in `euler.cpp` een functie die een willekeurig Euler-circuit teruggeeft:

    ```cpp

    std::vector<Hop> eulercircuit(const Graaf<GERICHT>& g);
    ```

    Een `Hop` is een struct die het start-knoopnummer en het verbindingsnummer bevat van elke
    stap die je in je pad zet.

    ```cpp
    struct Hop
    {
        int knoop_nr;
        int verbindings_nr;
    };
    ```

*   Lees in `main.cpp` het bestand `ryanair.txt` in, stel de overeenkomstige 
    graaf op. Is het mogelijk om de felbegeerde prijs in de wacht te slepen?
    Zo ja: geef een voorstel van route aan je CEO.


## Toepassing: PIN-code breken

De flauwe plezanterik op jouw kot heeft in een dronken bui een slotje aangebracht rond de besteklade
in de keuken. Dronken als hij was kan hij zich niet meer herinneren welke PIN-code hij had ingesteld.
Omdat choco op je boterhammen smeren met je wijsvinger toch niet zo'n prettig gevoel is besluit je 
het slotje te proberen forceren. Doorknippen lukt niet, want alle scharen zitten in de besteklade.

Het is een electrisch slotje met 6 toetsen (1 tem. 6), en het toont steeds de laatste 4 cijfers die
je ingaf op zijn schermpje. Je bent dus niet verplicht alle 6^4 combinaties uit te proberen, zolang je 
maar een sequentie ingeeft waarmee alle 4-cijferige combinaties de revue passeren.

Een kleine zoektocht op internet leert je dat een [De Bruynreeks kan gebruikt worden voor zo'n Brute Force
PIN-code aanval](https://en.wikipedia.org/wiki/De_Bruijn_sequence#Uses). Zo'n reeks opstellen kan
aan de hand van een Eulerpad. Ideaal, want je hebt hier vorige week nog maar een labo over gemaakt!

We proberen eerst een eenvoudig voorbeeld te snappen. We gaan uit van een PIN-code van 3 karakters lang,
en met slechts 2 mogelijke cijfers: 1 en 2.

De mogelijke PIN-codes in dat geval zijn: 111, 112, 121, 122, 211, 212, 221 en 222. 

Als je dit bekijkt, dan zie je dat na het ingeven van PIN-code 111 het volstaan om '2' te duwen om direct
PIN-code 112 te controleren. Druk je daarna terug '1' dan test je PIN-code 121, kies je echter voor '2', dan 
test je direct 122, enzovoort.

Onderstaande graaf toont hoe we de aaneensluitende PIN-codes kunnen vinden via het pad in een eulergraaf.
De graaf bevat een knoop voor elke mogelijke sequentie van 2 cijfers lang. (1 korter dan de te kraken PIN-code).
Vanuit elke knoop vertrekt er voor elk mogelijk cijfer een verbinding. De twee cijfers in de knoop, gevolgd door
het cijfer van de verbinding geven een mogelijke PIN-code.

Nu rest de vraag: waar verwijzen deze verbindingen naartoe? Na het invoeren van een cijfer wordt het voorste cijfer
uit de PIN-code geschoven, en wordt het cijfer van de verbinding aan de PIN-code toegevoegd. Als we vanuit
knoop 12 dus verbinding 1 volgen (blauw in de afbeelding), dan komt de meest linkse '1' dus te vervallen, schuift de 
rechtse 2 (blauw) op naar links, en wordt de 1 (rood) uit de gevolgde verbinding het minst 
significante cijfer.

Dit levert ons onderstaande graaf op, als we starten bij de meest links getekende knoop (*), en van daaruit
een Eulerpad opstellen (met voorkeur van het volgen van de verbinding met de laagste cijferwaarde) dan krijgen 
we volgende sequentie om uit te proberen: 1112122211

![](/images/voorbeeld-euler-pin.png)

Schrijf in [`pin.cpp`](src/pin.cpp) de code om de juiste graaf op te stellen om de kortste sequentie van 
in te geven cijfers te vinden voor het slotje met 6 mogelijke cijfers om in te voeren, en een PIN-code van 
4 cijfers lang.
