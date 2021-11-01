# Boyer-Moore

## Opgave

In dit labo vergelijken we de performantie van de verschillende heuristieken die Boyer-Moore gebruikt. Voor deze heuristieken moet er veel werk verzet worden voor het eigenlijke zoeken kan beginnen. Vandaar dat dit gebeurt in de constructor. Dit is efficiënt als je dezelfde naald verschillende keren moet zoeken. De hoofding vind je in [`boyermoore.h`](include/boyermoore.h). Je ziet dat de verschillende zoekoperaties een queue teruggeven met plaatsen: je gebruikt de methode meestal om alle plaatsen waar de naald voorkomt op te zoeken. Meestal worden die plaatsen daarna in volgorde verwerkt. Dus gebruik je een queue en geen gewone list.

### Enkel met heuristiek van het verkeerde karakter

In normale omstandigheden is het de heuristiek van het verkeerde karakter die ervoor zorgt dat Boyer-moore snel is. Implementeer in een eerste versie alleen de eerste heuristiek.

```cpp
std::queue<int> BMVerkeerdeKarakter::zoek(const string& hooiberg);
``` 

Je mag ervan uitgaan dat het alfabet beperkt is tot alle karakters die kunnen worden voorgesteld in een `unsigned char`. Deze is 1 byte groot.

Om te testen of je de implementatie zo effient als mogelijk is, hou je bij hoeveel keer je een karaktervergelijking doet tussen naald en hooiberg. Sla dit op in het veld `laatsteAantalKaraktervergelijkingen`. 


### Varianten van Horspool en Sunday

Kopieer je code van BMVerkeerdeKarakter naar de klassen `BMHorspool` en `BMSunday`. Pas de constructor en zoek-functie in deze klassen aan zodat deze de varianten van Horspool en Sunday implementeren.

## Benchmarking van de implementaties

Hoe verhoudt de performantie van de verschillende functies zich onderling, en in vergelijking met de `string::find`-functie uit de STL?

Je kan hiervoor de benchmarks gedefinieerd in [`benchmark.cpp`](test/benchmark.cpp) gebruiken. 

**TIP**: je kan het aantal *samples* (het aantal keer dat de code gedefinieerd in de benchmark na elkaar wordt uitgevoerd) beinvloeden door de vlag
`--benchmark-samples <# samples>` door te geven aan het programma `boyer_moore_test`. De standaardwaarde daarvan is 100, wat afhankelijk van je 
systeem voor behoorlijk lange uitvoertijden kan zorgen (zeker voor de worst-case testen!). Wil je dit aanpassen naar bijv. 5, dan doe je dit dus als volgt:

```bash
/home/student/boyer-moore$ build/test/boyer_moore_test --benchmark-samples 5
```

**TIP 2**: laat de worst-case benchmark eerst nog even in commentaar staan, en voer deze uit met maximaal een sample-grootte 1.

Zijn de resultaten naar verwachting?

Er zit echter nog een grote adder onder het gras: de instellingen van de compiler.

In [`CMakeLists.txt`](CMakeLists.txt) vind je volgende regels:

```
# Deze flags zetten de address sanitizer aan
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-omit-frame-pointer")

# Optimaliseer voor een korte compile-tijd ipv een korte uitvoerings-tijd
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# Gebruike deze flags om te compileren met aggressieve optimalisaties door de compiler:
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3 -march=native" )
```

Speel eens met deze compiler flags: zet de address sanitizer eens uit, zet de aggressieve optimalisaties eens aan, etc. 
Wat heeft de grootste invloed: het uitzetten van de address sanitizer, of de agressieve compiler-optimalisaties gebruiken?

 - De adress sanitizer maakt het grootste verschil, veel meer dan tussen O0 en O3.
 

## Optimaliseer je code

Probeer je code te optimaliseren. 

Wat gebeurt er met de uitvoeringstijd als je alle manipulaties voor 
`laatsteAantalKaraktervergelijkingen` in commentaar zet? 

Kan je de uitvoeringstijd verminderen door je tabel met de laatste positie van elk karakter anders in te vullen? 
Bij welke varianten kan je deze tabel invullen met de verschuiving die moet gebeuren ipv de positie van het laatste karakter?

- Ja, we kunnen de uitvoeringstijd kunnen we een beetje verminderen door de tabel in te vullen met de verschuiving die moet gebeuren ipv de positie van het laatste karakter.
De stddev lijkt echter veel hoger te zijn.
