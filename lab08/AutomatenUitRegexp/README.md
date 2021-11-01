# Automaten uit Regulier Expressies

## Inleiding

De klasse Regexp in [`regexp.h`](regexp.h) parset reguliere expressies. Er is gebruik gemaakt van een zeer eenvoudige taal om reguliere expressis weer te geven. Alle karakters staan voor zichzelf, behalve:
- `()`: ronde haakjes 
-  `|` de "of"-streep
-  `*` de herhalingsoperator die aangeeft dat voorgaande (een gewoon karakter of een uitdrukking tussen haakjes) 0 of meer keer herhaald mag worden.

//-  `+` de herhalingsoperator die aangeeft dat voorgaande minstens 1 keer herhaald moet worden, die aangeeft dat het voorgaande 
  
Concatenatie krijgen we door gewoon achter elkaar te schrijven. Intern wordt een concatenatie voorgesteld door een `_`.

Prioriteit van operatoren is `*`, `_`, `|`. Zo is `aa*` hetzelfde als `a_(a)*`, `a|b*` is `a|(b)*`, en `ba|ok` is `(b_a)|(o_k)`.

Voor alle duidelijkheid heeft Regexp een uitschrijfoperatie die met vierkante haakjes de volgorde van operaties aangeeft. Probeer maar eens met [`regexp_voorbeeld.cpp`](src/regexp_voorbeeld.cpp). 

De foutdetectie van Regexp is vrij beperkt.

## Opgave

Schrijf je een klasse DA die een Regexp kan omzetten in een deterministische automaat. 

Deze krijgt in de constructor een Regexp:

```cpp
    DA::DA(const Regexp&)
```

en heeft een lidfunctie

```cpp
    bool DA::zitInTaal(const string&);
```

Enkele tips:

* Als je in de code van Regexp kijkt dan zie je dat een Regexp recursief is opgebouwd: 
  een Regexp is een operator met nul (letter) één (ster) of twee (en en of) argumenten, waarin de argumenten Regexps zijn. 
  Dit kan helpen bij het opbouwen van de automaat.

* De cursus beschrijft geen methode om rechtstreeks een DA op te bouwen vanuit een reguliere expressie. Ze beschrijft wel
  hoe je een niet-deterministische automaat (NA) kan opbouwen vanuit een reguliere expressie met de methode van Thomason.
  Daarnaast beschrijft ze ook hoe je een DA kan opstellen vanuit een NA.

* In principe kan je een automaat voorstellen als een graaf, en dus lijkt overerving van een of ander graaftype logisch. 
  Is dit wel zo? Er zijn twee soorten bewerking waarvoor de voorstelling van een automaat geschikt moet zijn:
  
  1. De opbouw van de automaat uitgaande van een Regexp.
  2. Het gebruik van de automaat om strings te herkennen.

  Is de voorstelling van de structuur in de Graafklassen geschikt voor beide bewerkingen? 
  Is het een goed idee om voor beide functies dezelfde voorstelling te gebruiken?