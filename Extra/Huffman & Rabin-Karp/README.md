## Opgave

### Vraag 1: Huffmancodering

Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:

```cpp
/**
 * Berekent de optimale Huffmancodering voor een tekst waarin de
 * karakters voorkomen met de opgegeven frequenties.
 * 
 * @param freq een woordenboek die elk karakter afbeeldt op het aantal 
 *             keer dat het voorkomt in de tekst.
 * 
 * @returns een woordenboek die elk karakter afbeeldt op zijn optimale binaire
 *          voorstelling. We gebruiken voor het gemak een `string` hiervoor.
 * 
 */
map<uchar, string> huffman(const map<uchar, uint> &freq);
```

Je krijgt een prioriteitswachtrij cadeau die structs kan sorteren volgens het
gewicht dat in deze struct gedefinieerd is:

```cpp
struct Knoop {
   uint gewicht;
};
```

Deze prioriteitswachtrij maak je aan mbv de functie `maak_priority_queue()`.

Om het beheer van de levensduur van deze Knoop-objecten te vergemakkelijken is de
`priority_queue` van het type `priority_queue<shared_ptr<Knoop>>` ipv `priority_queue<Knoop>`.
(We gebruiken `shared_ptr` in plaats van `unique_ptr` omdat de `top`-operatie van `priority_queue`
een `const`-referentie teruggeeft, en daarom niet geschikt is voor een `move`-operatie).

Een voorbeeld van hoe je deze queue gebruikt:

```cpp
auto queue = maak_priority_queue();

queue.push(make_shared<Knoop>(Knoop{6}));
queue.push(make_shared<Knoop>(Knoop{1}));
queue.push(make_shared<Knoop>(Knoop{7}));
queue.push(make_shared<Knoop>(Knoop{3}));
queue.push(make_shared<Knoop>(Knoop{4}));
queue.push(make_shared<Knoop>(Knoop{2}));
queue.push(make_shared<Knoop>(Knoop{5}));

while(!queue.empty()){
   auto k = queue.top();
   queue.pop();

   std::cout << k->gewicht << "\n";
}
```

Dit levert als output:

```
1
2
3
4
5
6
7
```

Breid deze `Knoop`-struct uit met de nodige extra velden om de optimale huffmancodering te kunnen 
berekenen.
 
**Tip:** denk bijvoorbeeld aan het toevoegen van enkele pointers om een boom van knopen op te stellen. 
Is er een verschil in inhoud tussen bladknopen en niet-bladknopen?

### Vraag 2: Rabin-Karp

Een mogelijke methode om een bepaald patroon te zoeken in de tekst maakt is het algoritme van Karp en Rabin. 
Implementeer hiervoor in [`vraag2.cpp`](src/vraag2.cpp) de zoekfunctie:

```cpp

queue<int> zoek_rabinkarp(const string& naald, const string &hooiberg, int priemgetal = 997){}

```

Gebruik als hashfunctie `modulo <priemgetal>` (zoals het voorbeeld uit de slides, en uitgelegd in de cursus). 
Een karakter wordt voorgesteld door 8 bits. Het alfabet is dus 2^8 = 256 karakters groot (cfr. constante `ALFABET_GROOTTE`).

**Tip:** Een eerste versie zonder *rolling hash* kan handig zijn om de rest van je code te valideren. Rabin-Karp is echter pas efficient als 
de berekende hash voor de vorige positie in de hooiberg wordt hergebruikt voor de volgende positie. Vermijd daarom in je finale versie om 
de hash elke keer vanaf 0 terug te berekenen.
