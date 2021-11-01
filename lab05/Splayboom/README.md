# Labo 05: Splay bomen

Splaybomen zijn, naast rood-zwarte bomen, een andere vorm van efficiënte zoekbomen. Het opeenvolgende zoeken van 
elementen die in elkaars buurt liggen wordt efficient geregeld.

Voor de start van het labo zoek je en nieuwe labopartner en maak je opnieuw een kopie de repository naar je eigen 
GitHub account (1 per groep). Een handleiding hiervoor vind je in [`Repository.md`](Repository.md).

## De startcode

Voor deze implementatie van een splay boom starten we met een normale binaire zoekboom waar we van zullen overerven om 
de splayoperaties bij te implementeren. 
Er zijn er 3 klasses gegeven in [`zoekknoop.h`](include/zoekknoop.h), [`zoekboom.h`](include/zoekboom.h) en 
[`splayboom.h`](include/splayboom.h) met de zoekboom al geimplementeerd en de te implementeren splayboom klasse.

*Tip*: Ook in dit labo kan de bomen tijdens dit labo exporteren en bekijken via de functie `teken` en met behulp van de 
extensie [Graphviz (dot) language support for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=joaompinto.vscode-graphviz) 
ook weergeven in VSCode.

## Zoekboom

Om de klasse ZoekBoom werkende te krijgen zal je eerste enkele functies moeten aanvullen:

1. Schrijf/kopieer de functies `roteer` en `zoek` voor een zoekboom.
2. Om de performantie van onze splayboom te kunnen testen willen we deze kunnen toetsen aan twee uiterste scenario's:
   aan het ene uiterste een binaire boom die zo onevenwichtig mogelijk is (hoe ziet die eruit?), en aan het andere 
   uiterste een volledig gebalanceerde binaire boom. Implementeer daarvoor de functies `maakOnevenwichtig` en 
   `maakEvenwichtig`. Gebruik de meest eenvoudige methode om deze functies te implementeren. Maak dus geen gebruik van
   concepten zoals dynamisch programmeren.

   *Tip*: Een van de 2 functies zal je handig kunnen gebruiken in je andere functie.

## Splay-operaties

Een aantal specifieke splay-operaties gaan toegevoegd moeten worden aan de klasse `Splayboom`:

1. De functie `splay` die de splayoperaties zal doorvoeren en het laatst toegevoegde/gezochte element in de wortel zal 
   plaatsen.

2. De functie `zoek` die een element in de splay boom zal zoeken.

3. Voeg nu knopen "bottom-up" toe aan de splaytree, via de functie `voegtoe`.

   *Tip*: maak hier gebruik van de functies `zoek` en `roteer`.

4. Implementeer de `verwijder`-functie om knopen terug uit de splayboom te verwijderen.

## Toepassing

Het EK en WK voetbal zijn steeds hoogtepunten voor de voetballiefhebbers. Een aantal weken lang zijn er meerde matchen 
per dag te zien. Elke match moet uiteraard ook van professionele commentaar voorzien worden waarbij er gedurende 90 
minuten zowel over het huidige wedstrijdverloop als over statistieken van de landen die spelen/ deelnemen aan het 
tornooi. Een maand voor de aanvang van het tornooi komt een medewerker van de sportdienst naar jou met de vraag of er 
een efficiënte gegevensstructuur bestaat om een aantal statistieken in op te slaan en waar er regelmatig gezocht gaat 
worden. Hij geeft ook al een bestand met alle interland uitslagen ([`voetbal_resultaten.csv`](voetbal_resultaten.csv)) 
sinds 1872. Tijdens een wedstrijd zullen commentators ook meerdere malen hetzelfde land opzoeken. Jij twijfelt geen 
seconde en denkt dat splaybomen hier heel efficient voor zijn.

1. Schrijf in [src/leeslanden.cpp](src/leeslanden.cpp) de functies `doelpunten` en `overwinningen` die de doelpunten van een land en de 
   overwinningen van een land zullen behouden. Bij een gelijkspel is er geen winnaar en wordt de wedstrijd bij `gelijkspel` geteld.

2. Pas de zoekfunctie in `ZoekBoom` aan zodat hij de totale doorzochte diepte zal bijhouden van zoeken in de boom. Na het opzoeken van knopen 
   die zich op resp. dieptes 2,4,5 en 1 bevonden dient deze teller dus op 12 te staan. Tel nu hoe "diep" volgende sequenties zich bevinden in de boom. 
   Wat valt je op aan de gemiddelde zoekhoogte van de boom voor onderstaande zoeksequenties?

      1. `{"gelijkspel", "France", "Faroe Islands", "France", "Gambia", "Greece", "Finland", "gelijkspel", "gelijkspel", "gelijkspel" }`
      2. `{"gelijkspel", "Faroe Islands", "Finland", "France", "France", "Gambia", "gelijkspel", "gelijkspel", "gelijkspel", "Greece" }`
      3. `{"gelijkspel", "Belgium", "France", "United States", "Canada", "Russia", "China", "gelijkspel", "Belgium", "England" }`