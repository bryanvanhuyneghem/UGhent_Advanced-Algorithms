# Labo Dynamisch Programmeren

## Toepassing

Een bedrijf dat gespecialiseerd is in het bezorgen van pakjes heeft onlangs geinvesteerd in 5 verschillende soorten voertuigen om pakjes te transporteren. Gaan ze met de fiets, dan kunnen ze slechts 1 pakje meenemen. Met de bakfiets kunnen ze er 4 meenemen. Met de auto geraken ze aan 17 pakjes, de kleine bestelwagen kan er 18 meenemen en in de grote vrachtwagen kunnen 75 pakjes. Elke dag zal er een verschillend aantal pakjes bezorgd moeten worden en verdeeld over de verschillende vervoersmogelijkheden. De eigenaar van het bedrijf heeft echter 2 eisen opgelegd waar de verdeling aan moet voldoen:

* Hij wil enkel dat er volledig volle voertuigen vertrekken uit het magazijn.
* Hij wil dat er zo weinig mogelijk voertuigen gebruikt zullen worden om de levensduur van de zijn wagenpark te kunnen verlengen.

Verder mag je veronderstellen dat het wagenpark groot genoeg is om elke mogelijke combinatie van aantal vervoersmiddelen te gebruiken. Als er geen voertuigen beschikbaar zijn, geeft het programma -1 terug als aantal.

## Opgave

1. Implementeer door middel van dynamisch programmeren een efficiente manier om elke dag de verdeling van het aantal pakjes over de verschillende voertuigen te behandelen.

    * Op dag 1, moeten er 75 pakjes verdeeld worden.
    * Op dag 2, moeten er 17 pakjes verdeeld worden.
    * Op dag 3, moeten er 18 pakjes verdeeld worden.
    * Op dag 4, moeten 4 pakjes verdeeld worden.
    * Op dag 5, moet er maar 1 pakje verdeeld worden.
    * Op dag 6, moeten er 21 pakjes verdeeld worden.
    * Op dag 7, moeten er 86 pakjes verdeeld worden.
    * Op dag 8, moeten er 1516 pakjes verdeeld worden.
    * Op dag 9, moeten er 38 pakjes verdeeld worden.
    * Op dag 10, moeten er 115 pakjes verdeeld worden

    Er bestaan ook gulzigere algoritmen die een zo groot mogelijke voertuig als eerste gaan kiezen en zo tot een oplossing zullen komen. Wat zullen dergelijke algoritmen voorstellen?

    -> hij vindt wel een lokaal minimum maar we zijn niet zeker dat dit het absolute minimum is

2. De eigenaar van het bedrijf wil graag nog een elektrische optie toevoegen aan zijn wagenpark. Hier heeft hij 3 even dure opties, een met een capaciteit van 9 pakjes, de tweede met een capaciteit van 10 pakjes en een derde grotere van 35 pakjes. Wat is de beste keuze en waarom? Om een eerlijke vergelijking te maken, mag je veronderstellen dat de kans voor elk aantal pakjes tussen 0 en 100 even groot zal zijn.

    aantal keren dat de opties de beste zijn: 
    * optie1: 3
    * optie2: 74
    * optie3: 24

    -> optie 2 is gemiddeld het beste (wagen met cap 10)

3. Op dag 8 is er wat verwarring. Men is niet zeker of er 1515, 1516 of 1517 pakjes geleverd zullen worden. Bekijk voor alle 3 de mogelijke scenarios, ligt dit in de lijn van wat je verwacht?

    -> omdat 1500 een veelvoud  is van 75 krijgen we bij 1517 een optimale oplossing door het gebruik van de wagen met capaciteit 17 tov 1516

4. Door het stijgende aantal ongevallen met bakfietsen, beslist de eigenaar om deze uit zijn wagenpark te halen. Verandert dit iets aan zijn keuze voor vraag 2? Welke invloed heeft dit op vraag3 ?

   aantal keren dat de opties de beste zijn: 
    * optie1: 7
    * optie2: 86
    * optie3: 8
    -> neen optie 2 wordt zelfs beter

    vraag3:
    -> omdat 1500 een veelvoud  is van 75 krijgen we bij 1516 geen optimale oplossing omdat er geen wagen van 4 capaciteit is 
