# De Bruijnreeksen

## Introductie

Een _de Bruijnreeks_ van orde `N` over een bepaald alfabet is de kortste _circulaire_ reeks die elke mogelijke reeks van lengte `N` als (aaneensluitende) deelreeks bevat.  
Bijvoorbeeld:

*   een de Bruijnreeks van orde `N=2` over een alfabet `{a,b}` is bijvoorbeeld "aabb" want "aa", "ab", "ba" en "bb" komen erin voor als aaneensluitende deelreeks (indien je de reeks circulair opvat!)
*   een de Bruijnreeks van orde `N=3` over een alfabet `{a,b}` is bijvoorbeeld "abbbabaa".
*   een de Bruijnreeks van orde `N=2` over een alfabet `{a,b,c}` is bijvoorbeeld "aacbbccab".

De grootte van het alfabet noemen we `M`. Vaak neemt men de eerste `M` letters van het alfabet, maar computationeel is het soms voordeliger gehele getallen vanaf 0 te nemen (alfabet: `0` t.e.m. `M-1`).

Men kan aantonen dat de lengte van elke de Bruijnreeks <code>M<sup>N</sup></code> is.

Om het ingewikkelde manipuleren met strings te vermijden is het handig om strings van lengte `N` te beschouwen als getallen met `N` cijfers in het `M`-tallig stelsel: in plaats van a, b, c, ... neem je 0, 1, 2, ... . Als `M=10` en `3`, bijvoorbeeld, heb je dan alle natuurlijke getallen nodig kleiner dan 1000 (eventueel nullen vooraan toevoegen). Als je liever letters ziet dan cijfers kan je bij het uitschrijven natuurlijk 0 terug omzetten naar a, 1 naar b, en zo voorts. De nummers zijn in feite hashcodes die efficiënt berekend kunnen worden d.m.v. de regel van Horner. Er zijn <code>M<sup>N</sup></code> mogelijke woorden van lengte `N` uit een alfabet met `M` letters. De hashcodes liggen dus in het interval <code>[0,M<sup>N</sup>[</code>.  
Omgekeerd kan uit elk getal uit dit interval een woord afgeleid worden ("unhash").

## Opgave

*   Aan welke voorwaarden moet een gerichte graaf voldoen opdat er een Eulercircuit zou bestaan? En wat voor een ongericht graaf? Tip: kijk in de cursus

    Implementeer deze voorwaarden via volgende functies in `euler.cpp`:
    
    ```cpp
    bool heeft_eulercircuit(const Graaf<ONGERICHT>& g);

    bool heeft_eulercircuit(const Graaf<GERICHT>& g);
    ```

*   Wat is het verband tussen De Bruijnreeksen en Eulercircuits? 
  
    **Tip**: kijk naar de `N`-strings die in een De Bruijnreeks verscholen zitten. 
    Voor `N=3` bevat bijvoorbeeld "abbbabaa". de strings "abb", "bbb", "bba", en zo voorts. 
    Wanneer kunnen twee strings op achter mekaar staan in zo'n uitgeschreven lijstje? 
    Let erop dat een Eulercircuit alle verbindingen juist één keer bezoekt, maar niet noodzakelijk alle knopen.

*   Toon aan dat de lengte van elke de Bruijnreeks <code>M<sup>N</sup></code> is.

*   Implementeer in `euler.cpp` een functie die een willekeurig Euler-circuit teruggeeft:

    ```cpp

    std::vector<int> eulercircuit(const Graaf<GERICHT>& g);
    ```

*   Implementeer in `test/test.cpp` een functie die controleert of een string een geldige de Bruijnreeks voorstelt:
    
    ```cpp
    bool controleer_debruijnreeks(const std::string dbr, int lengte_alfabet, int orde){}
    ```
     
    Doe dit op een zo eenvoudig mogelijke manier, gebruik hierbij dus niet `graaf.hpp`.

*   Implementeer in `debruijnreeks.cpp` een functie die een de Bruijnreeks genereert met de 
    opgegeven alfabetlengte (waarbij het alfabet altijd start vanaf 'a') en orde. 
    
    ```cpp
    std::string genereer_debruijnreeks(int lengte_alfabet, int orde){}
    ```
