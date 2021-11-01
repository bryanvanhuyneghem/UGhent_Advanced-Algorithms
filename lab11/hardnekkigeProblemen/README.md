# Labo 11: Hardnekkige problemen

## Opgave

De kerstman heeft het druk dezer dagen. Hij moet pakjes afleveren in 179 knooppunten. Gelukkig gaan alle pakjes in één slee. De nodige coördinaten staan opgeslagen in kerstnet.xml. Wat is de kortste weg die de kerstman kan nemen?

Dit probleem is te groot om alle oplossingen te bekijken en daaruit de beste te selecteren, daarom gebruiken we enkele technieken om een aanvaardbare oplossingen te vinden. De eerste techniek zal op een probabilistische wijze op zoek gaan naar een oplossing, als tweede techniek gebruiken we simulated annealing.

**Opmerking**: De optimale oplossing voor dit probleem is niet triviaal te vinden, de beste tot nu toe gevonden oplossing voor een circuit langs alle knopen was 578.24 lang. Er zijn enkele basistesten voorzien tijdens het programmeren om van te vertrekken maar hoe dichter bij deze gevonden oplossing, hoe beter natuurlijk.

## Willekeurige oplossingen

- Via de abstracte klasse [`ProbProb.h`](include/PropProb.h)is er al een structuur gegeven om die het functies voorziet om algemene problemen op te lossen. Voor dit problemen zullen we via overerving het probleem van de kerstman oplossen met behulp van deze klasse. Voeg dus daarom de functies toe in [`kerstman_prob.cpp`](src/kerstman_prob.cpp):

  ```c++
      virtual double f(const vector<int> &oplossing)
      virtual bool isOplossing(const vector<int> &deeloplossing)
      virtual vector<pair<int, double>> geefVolgendePunt(const   vector<int> &deeloplossing)
  
  ```
  
  **TIP**: een voorbeeld implementatie van het gebruik van de klasse `ProbProb` is gegeven in de klasse `Dom` uit [`probprob_voorbeeld.cpp`](src/probprob_voorbeeld.cpp) die op zoek gaat naar het kleinste getal van **n** cijfers. Het spreekt voor zich dat dit een heel slechte implementatie is voor dit probleem.

- Deze oplossing zal meestal nog ver van een goede oplossing zitten. Implementeer daarom de functie `PickAtRandom()` bij in de klasse die een nieuwe oplossing zal maken door enkele punten van plaats te wisselen.

- Om naar een lokaal maximum te gaan, kan je verschillende punten wisselen totdat er geen betere oplossing meer gevonden kan worden door punten te wisselen in je oplossing.

## Simulated annealing

Dit probleem kan ook met simulated annealing opgelost worden. Voor die probleem is simulated annealing een goede metaheuristiek om een oplossing te gaan zoeken waar we ook uit lokale oplossingen kan emigreren naar betere oplossingen. De basiscode van simulated annealing uit de cursus is al te vinden in de abstracte klasse [`simulatedannealing.h`](include/simulatedannealing.h). Voor dit probleem zullen we hier van overerven en de nodige functies definieren in [`kerstman_sa`](src/kerstman_sa.cpp).

### Best gevonden:
* T0 = 1'000'000'000;
* Tk = T0*0.999999^k;
* Tstop = 0.00001;
hardnekkigeProblemen/test/test.cpp:48: FAILED:
  REQUIRE( annealing.f(annealingOplossing) < 625.0 )
with expansion:
  709.8327902557 < 625.0