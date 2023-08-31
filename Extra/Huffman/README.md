# Huffmancodering

Huffmancodering is een algoritme bedacht in 1952 door David Huffman terwijl hij nog een student was aan het MIT om een tekstuele data zoanig te coderen dat het bestand minder plaats inneemt. Het is een relatief eenvoudig algoritme dat vandaag de dag nog veel toepassingen heeft, vaak als onderdeel van grotere algoritmes zoals [DEFLATE](https://en.wikipedia.org/wiki/Deflate) of bestandsformaten zoals [JPEG](https://en.wikibooks.org/wiki/JPEG_-_Idea_and_Practice/The_Huffman_coding) en [MP3](http://www.mp3-tech.org/tech.html#huffman).

Een normaal tekstbestand gebruikt een standaard formaat van 8 bits per karakter om karakters voor te stellen in ASCII-formaat. Huffmancodering laat dat standaard formaat van 8-bits-per-karakter los en gebruikt een variabel aantal bits per karakter. Door karakters die meer voorkomen een kortere bit-voortstelling toe te kennen (vb. de veelvoorkomende letter `e` een korte voorstelling geven) kan een Huffman-gecodeerd bestand kleiner zijn dan een klassiek ASCII-tekstbestand.

De tabel hieronder toont het verschil tussen een klassieke ASCII-codering en een mogelijke Huffman-codering voor een stukje tekst. Veelvoorkomende letters zoals `e` hebben een kortere codering dan minder gebruikte letters zoals `x`:


| Letter | ASCII Nummer | Bitvoorstelling | Huffmancode |
|--------|--------------|-----------------|-------------|
| a      | 97           | 01100001        | 1000        |
| b      | 98           | 01100010        | 00001       |
| e      | 101          | 01100101        | 001         |
| x      | 120          | 01111000        | 010110001   |

Om een tekstbestand te encoderen via de Huffmancode zijn er 4 stappen nodig:

1. Frequenties van karakters bepalen (`maakFrequentieTabel`)
2. Een Huffmanboom opstellen (`maakHuffmanboom`)
3. Een karakter-coderings-tabel opstellen (`maakCoderingsTabel`)
4. Het encoderen van het tekst (`encodeerTekst`)

## 1. Frequenties van karakters bepalen

Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:
```cpp

/**
 * Stelt een frequentietabel die het aantal keer dat een karakter 
 * voorkomt in een opgegeven tekst teruggeeft.
 */
map<uchar, uint> maakFrequentieTabel(istream &s);

```

Voor de gegeven tekst "abracadabra" geeft deze functie dus volgende frequentietabel terug:

```
{'a': 5, 'b': 2, 'c': 1, 'd': 1, 'r':2 }
```

Voeg hier vervolgens de constante PSEUDO_EOF (cfr. [huffman.h](include/huffman.h)) met frequentie 1 aan toe.
Zo kan je deze PSEUDO_EOF straks ook terugvinden in de huffmanboom en coderingstabel, om zo het correcte
einde van de tekst terug te vinden.

## 2. Een Huffmanboom opstellen


Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:

```cpp
/**
 * Berekent een Huffmanboom voor een opgegeven frequentietabel van karaketers
 * 
 * @param freq een woordenboek die elk karakter afbeeldt op het aantal 
 *             keer dat het voorkomt in de tekst.
 * 
 * @returns de wortel van een Huffmanboom.
 * 
 */
shared_ptr<HuffmanKnoop> huffman(const map<uchar, uint> &freq);

```

Waarbij `HuffmanKnoop` de volgende struct is:

```cpp
struct HuffmanKnoop {
   uint gewicht;
};
```

Breid deze struct uit met de nodige extra velden om een volwaardige Huffmanboom voor te stellen.

Je krijgt van ons een prioriteitswachtrij cadeau die Huffmanknopen kan sorteren volgens het
gewicht dat in deze struct gedefinieerd is. Deze prioriteitswachtrij maak je aan mbv de functie `maak_priority_queue()`.

Om het beheer van de levensduur van deze Knoop-objecten te vergemakkelijken is de
`priority_queue` van het type `priority_queue<shared_ptr<HuffmanKnoop>>` ipv `priority_queue<HuffmanKnoop>`.
(We gebruiken `shared_ptr` in plaats van `unique_ptr` omdat de `top`-operatie van `priority_queue`
een `const`-referentie teruggeeft, en daarom niet geschikt is voor een `move`-operatie).

Een voorbeeld van hoe je deze queue gebruikt:

```cpp
auto queue = maak_priority_queue();

queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{6}));
queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{1}));
queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{7}));
queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{3}));
queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{4}));
queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{2}));
queue.push(make_shared<HuffmanKnoop>(HuffmanKnoop{5}));

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

## 3. Een karakter-coderings-tabel opstellen


Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:

```cpp
/**
 * Berekent een Huffmancodering aan de hand van een Huffmanboom
 * 
 * @param wortel De wortel van de Huffmanboom
 * 
 * @returns een woordenboek die een karakter afbeeldt op een Huffmancode
 * 
 */
map<uchar, HuffmanCode> maakCoderingsTabel(const HuffmanKnoop* wortel);

```

Hierbij is `HuffmanCode` als volgt gedefineerd:

```cpp
struct HuffmanCode {
    uint lengte;
    uint voorstelling;

};
```

## 4. Het encoderen van een tekst

Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:

```cpp
/**
 * Codeert de gegeven input aan de hand van de gegeven Huffmancodering.
 * 
 */
std::string codeerTekst(istream& input, const map<char, HuffmanCode>& codering);
```

Je krijgt van ons de hulpklasse [`obitstream`](include/bitstream.h) om gemakkelijk bit per bit te kunnen schrijven.

Voeg op het einde van de input nog een geëncodeerd PSEUDO_EOF karakter toe aan het resultaat, zodat je straks bij de
decodeerstap correct kunt deduceren wanneer het einde van de stream bereikt is.

## 5. Het decoderen van een tekst.

Om onze encodering te kunnen controleren, dienen we ook een decodeerfunctie te schrijven.

Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:

```cpp
void decodeerTekst(const std::string& input, const HuffmanKnoop* wortel, ostream& output);
```

Je krijgt van ons de hulpklasse [`ibitstream`](include/bitstream.h) om gemakkelijk bit per bit te kunnen lezen.
