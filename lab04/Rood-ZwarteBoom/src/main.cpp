
#include "rzwknoop.h"
#include <sstream>

// Toepassing 1: antwoord: diepte van de boom O(lgn)
// Toepassing 2: verwijderen, status: niet geïmplementeerd
// Toepassing 3: teller bijhouden die telt hoeveel keer je een bepaald woord toevoegt. Data class in template van knoopklasse

template <class Sleutel>
void repOKZoekboom(const RZWboom<Sleutel> &boom)
{
	Sleutel *vorige = 0; //houdt ref naar eerder gezien sleutel bij.
	if (boom.get()->ouder != 0)
		throw "wortel heeft geen null-ouder\n";
	boom.inorder([&vorige](const RZWknoop<Sleutel> &knoop) {
		//volgorde sleutels
		if (vorige && knoop.sleutel < *vorige)
		{
			throw "Verkeerde volgorde\n";
		};

		//ouderpointers
		for (const RZWknoop<Sleutel> *kind : {knoop.links.get(), knoop.rechts.get()})
			if (kind != 0 && kind->ouder != &knoop)
			{
				std::ostringstream fout;
				fout << "Ongeldige ouderpointer bij knoop " << kind->sleutel << "\n";
				fout << " wijst niet naar " << knoop.sleutel << "\n";
				throw fout.str();
			};
	});
}

int main()
{
  
  RZWboom<int> boom;
  //   std::cout << "punten toevoegen aan boom2: " << std::flush;
  for (int i = 0; i < 100; i++)
  {
    //std::stringstream ss;
    //ss << "boom" << i << ".gv";
    boom.voegtoe(i);
    if(i == 31 )
      boom.tekenAlsBinaireBoom("boom.gv");  
    

  }

  repOKZoekboom(boom);

  assert(boom.geefKleur() == zwart);
  assert(boom.get()->sleutel == 31);
  assert(boom.geefDiepte() == 11);
  

  return 0;
  /*
  
  // boom 2 (eenvoudige boom): 
  std::cout << "Eenvoudige boom : " << std::endl;
  RZWboom<int> boom;
  int punten[10] = {8,4,2,1,3,6,5,7,12, 10}; 
  for (int i:punten) {
    boom.voegtoe(i);
  }

  boom.schrijf(std::cout);
  boom.tekenAlsBinaireBoom("boom2.dot");


  /// Deel woordenboom
  RZWboom<string> woordenboom;
  string bestandsnaam = "Ovidius", woord;
  std::ifstream file;
  file.open (bestandsnaam);
  int teller = 0, toegevoegd = 0;
  if (!file.is_open()){ std::cout << "Fout bij openen bestand";}
  else{
    while (file >> woord){
        if (!woordenboom.zoekSleutel(woord)){
          woordenboom.voegtoe(woord);
          toegevoegd++;
        }
        teller++;
    }
  }
  std::cout << "Je voegde " << toegevoegd << " unieke woorden toe aan de boom!\n"; 
  std::cout << "De boom van de tekst heeft nu diepte: " << woordenboom.geefDiepte() << std::endl;

  
  return 0;
  */
}