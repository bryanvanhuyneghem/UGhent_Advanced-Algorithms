# B-trees

B-trees worden gebruikt om grote hoeveelheden data op te slaan op een opslagmedium. Bij het zoeken door deze data zal slechts een gedeelte van het opslagmedium in het geheugen van de computer ingeladen moeten worden wat handig is voor grote hoeveelheden data.
Een [visualisatie](https://www.cs.usfca.edu/~galles/visualization/BTree.html) over de werking van BTree is online ook beschikbaar.

## Opgave

Het opslagmedium dat we hier zullen gebruiken is geimplementeerd is de `Schijf`-klasse uit het bestand [`schijf.h`](include/schijf.h). Deze klasse simuleert de werking van een schijf en een schijf kan knopen (`bknoop.h`) opslaan, verwijderen en teruggeven. Elke knoop die op de schijf geschreven is, zal een unieke `blokindex` krijgen die gebruikt wordt om knopen van de schijf te lezen.
Een schrijfoperatie die een nieuwe knoop wegschrijft geeft een `blokindex` terug.

1. In de klasse `bknoop.h` schrijf je de functie `voegsleuteltoe` die een sleutel zal toevoegen aan de knoop, tesamen met zijn data en indien de knoop geen blad zal zijn, een blokindex van zijn kind.
2. Voor je kan starten met toevoegen in de BTree, zal je de functie `zoek` moeten aanvullen die op zoek gaat naar de sleutel in de BTree. De functie geeft een kopie van de data uit de knoop terug. Tesamen met de private `zoek` functie implementeer je ook de public functies `geefData`en `zoekSleutel` die gebruik maken van de `zoek`-functie en respectievelijk de data horend bij de sleutel teruggeven en aangeven dat de sleutel al dan niet in de BTree zit.
3. Vul de functie `voegToe` aan in de klasse `BTree`, die nieuwe gegevens zal toevoegen aan de BTree.

Tips:

* Je mag nooit meer dan drie knopen in het geheugen (dus: buiten de schijf) hebben, probeer hier ook rekening mee te houden.
* Een `BKnoop` daarentegen kent geen `Schijf`. Alle schrijf- en leesoperaties worden dus verzorgd in de klasse `BTree`.

## Toepassing

In de bijgeleverde csv zitten een hoop gegevens over de airBnB in de stad New York. Je wil een platform dat snel op zoek kan gaan naar gegevens maar zou graag het aantal gegevens in je RAM-geheugen beperkt houden en denkt ook al aan uitbreiding van je dienst naar andere grote steden. Je zal dus opteren om de data op een schijf te plaatsen mbv een BTree.

1. Construeer een boom die na zoeken van de airbnb-id, de prijs zal kunnen opzoeken. Elke knoop van de BTree zal 100 sleutels kunnen bevatten. Deze constructie voor je uit in de file `airbnb.cpp`.
2. Breid deze functionaliteit, in een tweede functie, nu uit dat de boom niet enkel de prijs zal bevatten maar de volgende informatie: naam, buurt, prijs, het aantal reviews en de beschikbaarheid. Elke knoop van de BTree zal nu beperkt worden tot 10 gegevens.

![New York](figuren/New_York_City.png)
