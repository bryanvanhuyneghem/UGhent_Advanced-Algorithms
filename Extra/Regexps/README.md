# Automaten uit Reguliere Expressies

In tal van toepassing zal je moeten zoeken in een tekst naar bepaalde woorden. In plaats van het zoeken naar vaste woorden, kan je ook gebruik maken van een reguliere expressie. Op deze manier kan je naar verschillende schrijfwijzen van hetzelfde patroon zoeken (bv. met of zonder hoofdletter of een afkorting). Een veelgebruikte toepassing van het zoeken met reguliere expressies in een bestand of lijn is grep. Deze command-line tool gaat op zoek naar patronen in een tekst.

## Inleiding

Voor dit labo is de klasse Regexp in [`regexp.h`](regexp.h) gegeven, deze klasse parset reguliere expressies. Er is gebruik gemaakt van een zeer eenvoudige taal om reguliere expressies weer te geven. Alle karakters staan voor zichzelf, behalve:

- `()`: ronde haakjes
- `|` de "of"-streep
- `*` de herhalingsoperator die aangeeft dat voorgaande (een gewoon karakter of een uitdrukking tussen haakjes) 0 of meer keer herhaald mag worden.
  
Concatenatie krijgen we door gewoon achter elkaar te schrijven. Intern wordt een concatenatie voorgesteld door een `_`.

Prioriteit van operatoren is `*`, `_`, `|`. Zo is `aa*` hetzelfde als `a_(a)*`, `a|b*` is `a|(b)*`, en `ba|ok` is `(b_a)|(o_k)`.

Als je in de code van Regexp kijkt dan zie je dat een Regexp recursief is opgebouwd: een Regexp is een operator met nul (letter) één (ster) of twee (en en of) argumenten, waarin de argumenten Regexps zijn. Dit kan helpen bij het opbouwen van de automaat.

Voor alle duidelijkheid heeft Regexp een uitschrijfoperatie die met vierkante haakjes de volgorde van operaties aangeeft. Probeer maar eens met [`regexp_voorbeeld.cpp`](src/regexp_voorbeeld.scp).

De foutdetectie van Regexp is vrij beperkt.

## Opgave

Tijdens dit labo zullen we van uit een Regexp een deterministische automaat op te bouwen die deze Regexp kan detecteren. Een reguliere expressie naar een deterministische automaat omzetten op een algemene manier is vrij lastig, een niet-deterministische automaat is sneller op te stellen uit de Regexp.

Vul de constructor van de klasse NA verder aan, zodat de niet-deterministische automaat opgebouwd worden uit de reguliere expressie. Om deze automaat op te bouwen zal je nog extra attributen moeten toevoegen aan de klasse. Denk vooraf na over welke datastructuur je zal gebruiken. In principe kan je een automaat voorstellen als een graaf, en dus lijkt overerving van een of ander graaftype logisch.
  Is dit wel zo? Er zijn twee soorten bewerking waarvoor de voorstelling van een automaat geschikt moet zijn:
  
  1. De opbouw van de automaat uitgaande van een Regexp.
  2. Het gebruik van de automaat om strings te herkennen.

  Is de voorstelling van de structuur in de Graafklassen geschikt voor beide bewerkingen?
  Is het een goed idee om voor beide functies dezelfde voorstelling te gebruiken?

```cpp
  NA::NA(const Regexp&)
```

Na het opstellen van de NA kan je deze automaat omzetten naar een DA. Hiervoor zijn er 2 zaken nodig in de klasse NA. Voeg eerst deze functies toe.

1. Het vinden van de epsilonsluiting van een bepaalde set toestandsnummers van de NA.
2. Het vinden van de nieuwe ge-activeerde toestand na een inputkarakter.

Deze krijgt in de constructor een Regexp:

```cpp
    DA::DA(const Regexp&)
```

en heeft een lidfunctie

```cpp
    bool DA::zitInTaal(const string&);
```
