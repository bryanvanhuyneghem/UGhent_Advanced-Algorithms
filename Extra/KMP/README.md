# Twitter

## Inleiding

Veel mensen gebruiken bijna dagelijks social media. De frequente gebruikers kunnen enorme aantal tweets in de wereld versturen. Een voorbeeld hiervan is de Amerikaanse ex-president Donald Trump. Tussen 2009 en april 2020 stuurde de man meer dan 43 duizend tweets. Deze tweets bevatten heel wat informatie maar om hier conclusies uit te halen wil een analist graag achterhalen in hoeveel tweets Trump bepaalde zoektermen gebruikt. Deze zoektermen kunnen zowel politieke tegenstanders zijn (Obama, Biden), nieuwstations (CCN, Fox News) of emotionele begrippen (happy, disappointed). Door deze tweets op die manier te bundelen kan men een strategie voor komende verkiezingen beter vormen.

Het zoeken van een bepaald patroon in een tekst kan op een heel naive manier gebeuren. Voor elke letter in de tekst zal begonnen worden de zoekterm karakter per karakter te vergelijken en nadien alle volgende letters. Bij een mismatch begin je met matchen van de volgende letter uit de tekst en eerste karakter van de zoekterm vergelijk je opnieuw tot er een mismatch gebeurd. Dit zoeken in een tekst kan ook efficiënter gebeuren via een deterministische automaat. Via (een variant van) het algoritme van Knuth-Morris-Pratt kan deze automaat opgesteld worden. De zoekterm en de string zullen in voorwaartse zin overlopen worden maar bij een mismatch van het karakter, zal er gebruik gemaakt worden van de kennis van de zoekterm om een efficiënte sprong te maken naar het volgende mogelijke begin van een substring die gelijk is aan de zoekterm.

## Opgave

1. Implementeer in [`automaten.cpp`](src/automaten.cpp) een constructor voor de klasse `DA` die adhv een string (het patroon) een deterministische automaat opstelt volgens de principes van Knuth-Morris-Pratt 
   - Hergebruik je oplossing van de `DA` klasse uit het labo 'automaten uit reguliere expressies' (of gebruik de voorbeeldoplossing);
   - Stel in de constructor eerst de tabel op zoals uitgelegd in de thoerieles†. We gaan ervan uit dat de input enkel ASCII-karakters bevat. Je mag dus uitgaan van een alfabet van 128 karakters.
   - Maak nu aan de hand van deze tabel de juiste overgangen aan in je DA-klasse.
1. Voorzie een functie ``bool DA::zitInTweet(const string &s, int& vergelijkingen)`` die zal bepalen of een bepaalde zoekterm in een tweet voorkomt zodat je alle strings met een zoekterm kan verzamelen. Als het aantal nog te onderzoeken karakters in de tweet lager is dan het nog te doorlopen toestanden in de automaat, mag je het zoeken vroegtijdig afbreken. Als tweede argument wordt een integer meegegeven die je telkens verhoogt als je een karaktervergelijking doet.
1. Knuth-Morris-Pratt is een substring search methode die al een stuk efficienter is dan een naive implemenatie, vooral bij herhaling van lettergroepen in de zoekterm. Voeg een naïve implementatie toe aan je code en vergelijk het aantal vergelijkingen tussen 2 karakters met en zonder het toepassen van Knuth-Morris-Pratt. Hoeveel efficienter is KMP in vergelijking met de naïve methode voor de analist die de zoekterm hahaha wil gebruiken?

**† Tip**: Wat is de relatie tussen de kolom-index en het aantal gematchte karakters uit het patroon? Kan je uitleggen wat de functie is van "kolom x" ? Wat stelt deze voor tijdens het invullen van de verschillende kolommen? Hoe kan je het verplaatsen van de "kolom x" uitleggen? Vraag zeker uitleg aan de begeleider als dit niet duidelijk is!
