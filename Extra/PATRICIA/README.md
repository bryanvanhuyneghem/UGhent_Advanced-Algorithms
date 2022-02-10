# Patricia

## Introductie

Een PATRICIA trie (Practical Algorithm to Retrieve Information Coded in Alphanumeric) is een optimalisatie van een binaire trie waarbij onnodige lege kettingen van knopen worden vermeden.

## De gegeven klasses

### [StringMetBits](include/stringmetbits.h)

Bij een Patriciatrie worden strings bit per bit vergeleken. Voor de sleutels in de Patriciatrie krijg je van ons dan ook de klasse `StringMetBits` die daarvoor de nodige voorzieningen heeft. De klasse erft over van de std::string klasse en heeft volgende extra functies:
- bit(int i) om de bit op index i in een StringMetBit op te vragen.
- geefAantalBits() om het aantal bits in een StringMetBit op te vragen.
- verschilplaats(const StringMetBits& sb) om de index waarop 2 StringMetBitsen verschillen te bepalen.

Merk op dat `StringMetBits`en impliciet worden aangevuld met oneindig veel nulbits zodat je bits kan vergelijken op plaatsen waar eigenlijk geen bits zijn. 

### [Pknoop](include/patriciaknoop.h)

Een Patriciatrie is opgebouwd uit verschillende knopen die de eigenlijke data zullen bevatten. In een knoop worden sleutel (StringMetBit), data (int), een index(int) en 2 pointers naar kinderen opgeslagen. Een extra functie `inorder` is ook toegevoegd om de gehele patriciatrie inorder te kunnen overlopen en dat gebruikt kan worden op de Patriciatrie uit te schrijven. In deze implementatie wordt het `data` attribuut van de klasse gebruikt om te tellen hoe vaak een sleutel is toegevoegd aan de boom. Op het moment de knoop aangemaakt wordt en dus al zeker eenmaal in de boom zit, zal het geinitialiseerd worden op 1. 

### [Pboom](include/patricia.h)

Hier bevindt zich de eigenlijke code van de Patriciatrie. Een boom is gedefineerd door zijn wortelknoop. 

Een aantal hulpfuncties oa knopen aan te maken, het aantal knopen in de boom te tellen en de boom uit te schrijven is al gegeven.  De functies zoek, voegtoe en top20 zullen deel zijn van de opgave.

## Opdracht

1. Een van de basisoperaties van een `Patrica.h` trie is het zoeken van sleutels en bijhorende data. Vul de functie `zoek()` aan om de `data` bij een knoop op te vragen. Om de werking van de zoek-functie te kunnen testen, kan je gebruik maken van 1 van de test cases. In deze test case wordt een vooraf gedefineerde Patriciatrie aangemaakt en kunnen de verschillende sleutels opgezocht worden.

1. Breidt de klasse `patricia.h` nu ook uit om sleutels te kunnen toevoegen aan de boom. Hier kan je gebruik maken van de hiervoor geschreven zoek() functie om te kijken of de knoop al in de trie aanwezig is. Als de sleutel al aanwezig is in de boom, is het voldoende om het `data` veld in de knoop met 1 te verhogen.

1. [Optioneel] Gebruik je trie om alle woorden van [de bijbel, King James' version](bible.txt) op te slaan, en te tellen hoeveel maal ze voorkomen. Schrijf daarna op het scherm uit welke 20 woorden het meest voorkomen, samen met het aantal keer dat ze erin staan, en dit in dalende volgorde van frequentie. Maak hierbij gebruik van een priority-queue van `Wordcount` objecten. Zo zal je vinden dat `the` het vaakst zal voorkomen.

## Opmerkingen bij de implementatie

In een PATRICIA trie zijn de relaties tussen knopen behoorlijk complex: de `links` en `rechts` pointer van een knoop kunnen immers verwijzen naar een knoop hogerop in de boom. Dit zorgt voor circulaire verwijzingen, wat het schrijven van een correcte destructor niet bepaald gemakkelijk maakt.

Om de gegeven code simpel en leesbaar te houden, opteren we ervoor om voor de "boekhouding" van de levenscyclus van de `Pknoop` objecten gebruik te maken van een `unique_ptr` voor elk aangemaakt knoopobject. Deze `unique_ptr` worden bijgehouden in een vector in de klasse `Pboom`. Hierdoor worden alle knopen van een boom automatisch opgekuist wanneer de destructor van `Pboom` wordt opgroepen.

Dit zorgt natuurlijk strikt gezien voor een onnodige overhead van 1 extra verwijzing naar elke knoop in een `Pboom` object. Dit kan vermeden worden door in de destructoren van `Pboom` en `Pknoop` de nodige extra logica toe te voegen. We laten dit echter als een oefening voor de gemotiveerde lezer.
