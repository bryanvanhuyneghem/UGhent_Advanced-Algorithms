## Eigen repository aanmaken van de opgave:

Voor de start van het labo zal je een private repository per groep van de git-repository moeten aanmaken en ons 
(`twalcari` en `bvherbru`) en je labopartner hier aan moeten toevoegen. Volg hiervoor volgend stappenplan: 

1. Maak een kopie van de opgave git in je ubuntu terminal via:
```
git clone --bare https://github.ugent.be/GevAl/Splayboom.git
```
 2. Maak op github.ugent.be bij je eigen account een nieuwe lege repository aan, bij zichtbaarheid duid je hier private 
    aan. In de volgende stap gebruik je git-url van deze nieuwe repository 
    (bv. https://github.ugent.be/<user_name>/RoodZwarteBoom.git).

3. Voer nu volgende commandos uit in je ubuntu terminal, <user_name> vervang je uiteraard door je eigen github-naam. 
   De juist geclonede versie van de opgave zal je nu pushen naar je nieuw aangemaakte repository.

```
cd Rood-ZwarteBoom.git
git push --mirror https://github.ugent.be/<user_name>/Splayboom.git
cd ..
rm -rf Rood-ZwarteBoom.git
```

4. Nu kan je de github naar je eigen ubuntu clonen op de plaats in de terminal waar je volgend commando uitvoert:

```
git clone https://github.ugent.be/<user_name>/Splayboom.git
```

5. Om eventuele aanpassingen van de opgave git te blijven ontvangen, moet je nu de opgave ook als remote toevoegen aan 
   je eigen repository. Ga hiervoor in de repository en voer volgend git commando uit:

```
git remote add upstream https://github.ugent.be/GevAl/Splayboom.git
```

6. Als laatste voeg je ons (`twalcari` en `bvherbru`) en je labo-partner toe aan de repository en voeg je de link ook in 
   je ufora-groep. Als je nu aanpassingen in de opgave-repository wil updaten in je eigen repository, kan je gebruik 
   maken van de commandos:
```
git fetch upstream
git rebase upstream/master
```