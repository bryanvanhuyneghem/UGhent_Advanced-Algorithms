// Deze header bevat de code voor de klassen:
//
//
//    Graaf<RichtType>: basisklasse met grafen zonder tak- of knoopdata
//    GraafMetTakdata<RichtType,TakDatatype>
//    GraafMetKnoopdata<RichtType,KnoopDatatype>
//    GraafMetKnoopEnTakdata<RichtType,KnoopDatatype,Takdatatype>
//
// Evenals de bijbehorende klasse van GraafExcepties.

#ifndef __GRAAF_H
#define __GRAAF_H

#include <algorithm>
#include <cassert>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

enum RichtType { GERICHT, ONGERICHT };

/**
 * @brief Fout bij het uitvoeren van een operatie op een graaf
 *
 */
class GraafExceptie : public std::logic_error {
 public:
  GraafExceptie(const std::string &boodschap_) : std::logic_error(boodschap_) {}
};

std::ostream &operator<<(std::ostream &os, const GraafExceptie &exc) {
  return os << exc.what();
}

/**
 * @class Graaf
 *
 * @tparam RT: Duidt aan of de graaf gericht is of niet. Dit beinvloedt functies
 * ivm verbindingen
 *
 * @brief Graaf is de basisklasse voor een hiërarchie van ijlegraafklassen.
 * Deze hiërarchie zal klassen bevatten voor grafen met data behorend bij knopen
 * en/of takken. Deze data worden opgeslagen in vectoren, zodat kan worden
 * opgezocht op index.
 *
 * *Knopen:* Deze zijn opeenvolgend genummerd. Knopen kunnen niet individueel
 * verwijderd worden. Wel kunnen alle knopen samen verwijderd worden (door
 * wis()), en kunnen knopen één voor één toegevoegd worden.
 *
 * *Verbindingen:* Deze kunnen naar hartenlust toegevoegd en verwijderd worden.
 * Als een verbinding wordt verwijderd, wordt het nummer op de stack van
 * `vrijgekomenVerbindingsnummers` gezet. Worden verbindingen toegevoegd, dan
 * worden eerst deze vrijgekomen nummers opnieuw gebruikt, alvorens nieuwe
 * nummers worden toegevoegd. `hoogsteVerbindingsnummer` kan nooit verkleinen,
 * en de vector met `takdata` zal altijd `hoogsteVerbindingsnummer` elementen
 * bevatten.
 *
 * *Tekenen met GraphViz:* etiketten mogen, bij uitschrijven geen
 * aanhalingsteken bevatten.
 *
 */
template <RichtType RT>
class Graaf {
 public:
  /// beeldt knoopnummer (van buur) af op verbindingsnummer
  typedef std::map<int, int> Burenlijst;

  /// Construeert een graaf met gegeven RichtType en aantal knopen (default 0),
  /// zonder verbindingen.
  Graaf(int n = 0);
  /// Geeft true indien het richttype GERICHT is, false indien het ONGERICHT is.
  bool isGericht() const;

  /**
   * @brief Voegt een nieuwe 'lege' knoop toe, d.w.z. zonder verbindingen.
   *
   * @return int Geeft knoopnummer van toegevoegde knoop terug (begint bij 0).
   */
  virtual int voegKnoopToe();

  /**
   * @brief Voegt verbinding toe tussen knoopnummers 'van' en 'naar'.
   *
   * Bij ongerichte graaf wordt terugverbinding ook toegevoegd (met zelfde
   * verbindingnummer!)
   *
   * Gooit GraafExceptie indien verbinding al bestaat of knoopnummers ongeldig
   * zijn.
   *
   * @param van knoopnummer van beginknoop
   * @param naar knoopnummer van eindknoop
   * @return int Geeft verbindingsnummer van toegevoegde verbinding terug
   * (begint bij 0).
   */
  virtual int voegVerbindingToe(int van, int naar);

  /**
   * @brief Verwijdert de verbinding tussen knoopnummers 'van' en 'naar', incl.
   * de terugverbinding indien ongericht.
   *
   * Gooit GraafExceptie indien knoopnummers ongeldig zijn.
   *
   * Geen exceptie indien de verbinding niet bestond.
   *
   * Andere verbindingen worden niet 'hernummerd'. Er komen dus mogelijks
   * "gaten" in de verbindingsnummers.
   *
   * @param van knoopnummer van beginknoop
   * @param naar knoopnummer van eindknoop
   */
  virtual void verwijderVerbinding(int van, int naar);

  /// Geeft het aantal knopen van de graaf.
  int aantalKnopen() const;

  /**
   * @return int Geeft het aantal verbindingen van de graaf.
   * Bij ongerichte graaf worden verbindingen NIET dubbel geteld!
   */
  int aantalVerbindingen() const;

  // Geeft het verbindingsnummer van de verbinding tussen 'van' en 'naar'.
  // Geeft -1 indien die verbinding niet bestaat.
  // Gooit een GraafExceptie indien knoopnummers ongeldig zijn.
  // Opgelet: performantie is O(log(v)) waarbij v aantal verbindingen vanuit
  // 'van' is.

  /**
   * @return int Geeft het verbindingsnummer van de verbinding tussen 'van' en
   * 'naar'.
   *
   * Gooit een GraafExceptie indien knoopnummers ongeldig zijn
   *
   * Geeft -1 indien die verbinding niet bestaat.
   *
   * *Opgelet:* performantie is O(log(v)) waarbij v aantal verbindingen vanuit
   * 'van' is.
   *
   * @param van knoopnummer van beginknoop
   * @param naar knoopnummer van eindknoop
   */
  int verbindingsnummer(int van, int naar) const;

  /// Verwijdert alle knopen en verbindingen en herstart de verbindingsnummer
  virtual void wis();

  // Toegang tot de burenlijsten:

  /**
   * @brief Geeft toegang tot de burenlijst van een knoop
   *
   * @param i knoopnummer
   * @return const Burenlijst& Afbeelding van knoopnummer buur of
   * verbindingsnummer
   */
  const Burenlijst &operator[](int i) const { return burenlijsten[i]; }
  /**
   * @brief Niet-const toegang tot burenlijst van knoop. Zo kan deze ook als
   * lvalue gebruikt worden.
   *
   * @param i knoopnummer
   * @return Burenlijst&  Afbeelding van knoopnummer buur of verbindingsnummer
   */
  Burenlijst &operator[](int i) {
    return burenlijsten[i];
  }  // deze kan als lvalue gebruikt worden

  /// Schrijft de gegevens van de volledige graaf naar outputstream os.
  virtual void schrijf(std::ostream &os) const;

  /// Genereer een .dot bestand dat met Graphviz kan worden omgezet in een
  /// afbeelding.
  virtual void teken(const char *bestandsnaam) const;

  /// Schrijf een knoop uit (hulpfunctie voor `schrijf`)
  virtual std::string knooplabel(int i) const {
    std::ostringstream uit;
    uit << i;
    return uit.str();
  };

  /// Schrijft een knoop uit (hulpfunctie voor `schrijf`)
  virtual std::string taklabel(int i) const { return ""; };
  /// Schrijft de gegevens van de knoop met knoopnummer k naar outputstream os.
  virtual void schrijfKnoop(std::ostream &os, int k) const;

  /// Schrijft de gegevens van de verbinding met verbindingsnummer v naar
  /// outputstream os.
  virtual void schrijfVerbinding(std::ostream &os, int v) const;

 protected:
  // hulpfuncties
  void controleerKnoopnummer(int k) const;  // throw indien k ongeldig
  void voegVerbindingToeInDatastructuur(int van, int naar,
                                        int verbindingsnummer);
  void verwijderVerbindingUitDatastructuur(int van, int naar);

 protected:
  // datavelden
  std::vector<Burenlijst> burenlijsten;
  int hoogsteVerbindingsnummer;
  RichtType richttype;
  std::stack<int> vrijgekomenVerbindingsnummers;
};

template <RichtType RT>
std::ostream &operator<<(std::ostream &os, const Graaf<RT> &g);

// --- implementatie ---

template <RichtType RT>
void Graaf<RT>::controleerKnoopnummer(int k) const {
  if (k < 0 || (size_t)k >= burenlijsten.size()) {
    std::ostringstream out;
    out << "Ongeldig knoopnummer " << k << ". Moet >= 0 en < "
        << burenlijsten.size() << " zijn.";
    throw GraafExceptie(out.str());
  }
}

template <RichtType RT>
Graaf<RT>::Graaf(int n) : burenlijsten(n), hoogsteVerbindingsnummer(0){};

template <RichtType RT>
bool Graaf<RT>::isGericht() const {
  return true;
}  // voor gerichte graaf

template <>
bool Graaf<ONGERICHT>::isGericht() const {
  return false;
}  // voor ongerichte graaf

template <RichtType RT>
int Graaf<RT>::voegKnoopToe() {
  int n = burenlijsten.size();
  burenlijsten.resize(n + 1);  // default constructor voor nieuwe knoop wordt
                               // opgeroepen (hier lege map)
  return n;
}

template <RichtType RT>
int Graaf<RT>::voegVerbindingToe(int van, int naar) {
  controleerKnoopnummer(van);
  controleerKnoopnummer(naar);

  if (burenlijsten[van].count(naar) > 0) {
    std::ostringstream out;
    out << "verbinding " << van << "-" << naar << " bestaat al";
    throw GraafExceptie(out.str());
  } else {
    int verbindingsnummer;
    if (!vrijgekomenVerbindingsnummers.empty()) {
      verbindingsnummer = vrijgekomenVerbindingsnummers.top();
      vrijgekomenVerbindingsnummers.pop();
    } else
      verbindingsnummer = hoogsteVerbindingsnummer++;
    voegVerbindingToeInDatastructuur(van, naar, verbindingsnummer);
    return verbindingsnummer;
  }
}

template <RichtType RT>  // voor gerichte graaf
void Graaf<RT>::voegVerbindingToeInDatastructuur(int van, int naar,
                                                 int verbindingsnummer) {
  burenlijsten[van][naar] = verbindingsnummer;
}

template <>
void Graaf<ONGERICHT>::voegVerbindingToeInDatastructuur(int van, int naar,
                                                        int verbindingsnummer) {
  burenlijsten[van][naar] = verbindingsnummer;
  burenlijsten[naar][van] = verbindingsnummer;
}

template <RichtType RT>
void Graaf<RT>::verwijderVerbinding(int van, int naar) {
  controleerKnoopnummer(van);
  controleerKnoopnummer(naar);
  if (burenlijsten[van].find(naar) !=
      burenlijsten[van].end()) {  // verbinding bestaat
    vrijgekomenVerbindingsnummers.push(burenlijsten[van][naar]);
    verwijderVerbindingUitDatastructuur(van, naar);
  }
  // (geen exception indien verbinding niet bestaat)
}

template <RichtType RT>
void Graaf<RT>::verwijderVerbindingUitDatastructuur(int van, int naar) {
  burenlijsten[van].erase(naar);
}

template <>
void Graaf<ONGERICHT>::verwijderVerbindingUitDatastructuur(int van, int naar) {
  burenlijsten[van].erase(naar);
  burenlijsten[naar].erase(van);
}

template <RichtType RT>
int Graaf<RT>::aantalKnopen() const {
  return burenlijsten.size();
}

template <RichtType RT>
int Graaf<RT>::aantalVerbindingen() const {
  return hoogsteVerbindingsnummer - vrijgekomenVerbindingsnummers.size();
}

template <RichtType RT>
int Graaf<RT>::verbindingsnummer(int van, int naar) const {
  controleerKnoopnummer(van);
  controleerKnoopnummer(naar);
  Burenlijst::const_iterator verbindingit = burenlijsten[van].find(naar);

  if (verbindingit == burenlijsten[van].end())
    return -1;
  else
    return (*verbindingit).second;
}

template <RichtType RT>
void Graaf<RT>::wis() {
  burenlijsten.clear();
  hoogsteVerbindingsnummer = 0;
  while (!vrijgekomenVerbindingsnummers.empty())
    vrijgekomenVerbindingsnummers.pop();
}

template <RichtType RT>
void Graaf<RT>::schrijf(std::ostream &os) const {
  os << "Graaf: " << aantalKnopen() << " knopen en " << aantalVerbindingen()
     << " verbindingen:" << std::endl;
  for (int k = 0; k < aantalKnopen(); k++) schrijfKnoop(os, k);
}

template <RichtType RT>
void Graaf<RT>::teken(const char *bestandsnaam) const {
  std::ofstream uit(bestandsnaam);
  assert(uit);
  std::string pijl;
  if (isGericht()) {
    uit << "digraph {\n";
    pijl = "->";
  } else {
    uit << "graph {\n";
    pijl = "--";
  };
  for (int k = 0; k < aantalKnopen(); k++) {
    if (burenlijsten[k].empty())
      uit << knooplabel(k) << ";\n";
    else {
      for (auto &[buur, tak] : this->burenlijsten[k]) {
        if (isGericht() || buur >= k)
          uit << knooplabel(k) << " " << pijl << " " << knooplabel(buur)
              << taklabel(tak) << ";\n";
      };
    };
  };
  uit << "}";
  uit.close();
};

template <RichtType RT>
void Graaf<RT>::schrijfKnoop(std::ostream &os, int k) const {
  os << "Burenlijst " << k << "::\n";
  for (auto &[buur, tak] : this->burenlijsten[k]) {
    os << "  ->" << buur;
    schrijfVerbinding(os, tak);
  }
}

template <RichtType RT>
void Graaf<RT>::schrijfVerbinding(std::ostream &os, int v) const {
  os << " via verbinding nr. " << v << std::endl;
}

template <RichtType RT>
std::ostream &operator<<(std::ostream &os, const Graaf<RT> &g) {
  g.schrijf(os);
  return os;
}

/**
 * @brief  Deelklasse van Graaf, met data bij elke tak.
 *
 * @tparam RT Duidt aan of de graaf gericht is of niet. Dit beinvloedt functies
 * ivm verbindingen
 * @tparam Takdata Klasse met info over elke tak
 */
template <RichtType RT, class Takdata>
class GraafMetTakdata : public virtual Graaf<RT> {
 public:
  GraafMetTakdata(int n = 0) : Graaf<RT>(n){};

  /**
   * @brief Noot: toevoegfunctie zonder takdata op te geven kan alleen gebruikt
   * als de klasse Takdata een defaultconstructor heeft.
   */
  virtual int voegVerbindingToe(int van, int naar);
  virtual int voegVerbindingToe(int van, int naar, const Takdata &);

  // Noot: verwijderVerbinding wordt ongewijzigd overgenomen van Graaf!

  /**
   * @return const Takdata* const pointer voor takdata
   *
   * Geeft nullpointer als tak niet bestaat
   *
   * *Noot*: pointers teruggegeven door geefTakdata worden ongeldig
   * door toevoegen van een tak.
   *
   * @param van knoopnummer van beginknoop
   * @param naar knoopnummer van eindknoop
   */

  const Takdata *geefTakdata(int van, int naar) const;
  /**
   * @return Takdata* wijzigbare pointer naar takdata
   *
   * Geeft nullpointer als tak niet bestaat
   *
   * @param van knoopnummer van beginknoop
   * @param naar knoopnummer van eindknoop
   */
  Takdata *geefTakdata(int van, int naar);

  virtual std::string taklabel(int i) const {
    std::ostringstream uit;
    uit << "[label=\"" << takdatavector[i] << "\"]";
    return uit.str();
  };

  virtual void wis();

  /// Schrijft de gegevens van de verbinding met verbindingsnummer v naar
  /// outputstream os.
  virtual void schrijfVerbinding(std::ostream &os, int v) const;

 protected:
  std::vector<Takdata> takdatavector;
};

template <RichtType RT, class Takdata>
int GraafMetTakdata<RT, Takdata>::voegVerbindingToe(int van, int naar) {
  return this->voegVerbindingToe(van, naar, Takdata());
}

template <RichtType RT, class Takdata>
int GraafMetTakdata<RT, Takdata>::voegVerbindingToe(int van, int naar,
                                                    const Takdata &td) {
  bool isnieuwtaknummer = this->vrijgekomenVerbindingsnummers.empty();
  int taknummer = Graaf<RT>::voegVerbindingToe(van, naar);
  if (isnieuwtaknummer)
    takdatavector.push_back(td);
  else
    takdatavector[taknummer] = td;
  return taknummer;
}

template <RichtType RT, class Takdata>
const Takdata *GraafMetTakdata<RT, Takdata>::geefTakdata(int van,
                                                         int naar) const {
  int taknummer = this->verbindingsnummer(van, naar);
  if (taknummer != -1)
    return &takdatavector[taknummer];
  else
    return 0;
}

template <RichtType RT, class Takdata>
Takdata *GraafMetTakdata<RT, Takdata>::geefTakdata(int van, int naar) {
  int taknummer = this->verbindingsnummer(van, naar);
  if (taknummer != -1)
    return &takdatavector[taknummer];
  else
    return 0;
}

template <RichtType RT, class Takdata>
void GraafMetTakdata<RT, Takdata>::wis() {
  Graaf<RT>::wis();
  takdatavector.clear();
}

template <RichtType RT, class Takdata>
void GraafMetTakdata<RT, Takdata>::schrijfVerbinding(std::ostream &os,
                                                     int v) const {
  os << " via verbinding nr. " << v << " (Data: " << takdatavector[v] << ")"
     << std::endl;
}

/**
 * @brief Deelklasse van Graaf, met data bij elke tak.
 *
 * @tparam RT Duidt aan of de graaf gericht is of niet. Dit beinvloedt functies
 * ivm verbindingen
 * @tparam Knoopdata  Klasse met info over elke knoop
 */
template <RichtType RT, class Knoopdata>
class GraafMetKnoopdata : public virtual Graaf<RT> {
 public:
  // Construeert een graaf met gegeven RichtType, en lijst van Knoopdata;
  template <class InputIterator>
  GraafMetKnoopdata(InputIterator start, InputIterator eind);
  GraafMetKnoopdata() : Graaf<RT>(){};

  virtual int voegKnoopToe();
  virtual int voegKnoopToe(const Knoopdata &);

  const Knoopdata *geefKnoopdata(int knoopnr) const;
  Knoopdata *geefKnoopdata(int knoopnr);
  virtual std::string knooplabel(int i) const {
    std::ostringstream uit;
    uit << '"' << i << ":" << knoopdatavector[i] << '"';
    return uit.str();
  };

  virtual void wis();
  virtual void schrijfKnoop(std::ostream &os, int k) const;

 protected:
  // datavelden
  std::vector<Knoopdata> knoopdatavector;
};
template <RichtType RT, class Knoopdata>
template <class InputIterator>
GraafMetKnoopdata<RT, Knoopdata>::GraafMetKnoopdata(InputIterator start,
                                                    InputIterator eind)
    : Graaf<RT>(0) {
  for (; start != eind; start++) voegKnoopToe(*start);
}

template <RichtType RT, class Knoopdata>
int GraafMetKnoopdata<RT, Knoopdata>::voegKnoopToe() {
  return this->voegKnoopToe(Knoopdata());
}

template <RichtType RT, class Knoopdata>
int GraafMetKnoopdata<RT, Knoopdata>::voegKnoopToe(const Knoopdata &kd) {
  int ret = Graaf<RT>::voegKnoopToe();
  knoopdatavector.push_back(kd);
  return ret;
}

template <RichtType RT, class Knoopdata>
const Knoopdata *GraafMetKnoopdata<RT, Knoopdata>::geefKnoopdata(
    int knoopnummer) const {
  this->controleerKnoopnummer(knoopnummer);
  return &knoopdatavector[knoopnummer];
}

template <RichtType RT, class Knoopdata>
Knoopdata *GraafMetKnoopdata<RT, Knoopdata>::geefKnoopdata(int knoopnummer) {
  this->controleerKnoopnummer(knoopnummer);
  return &knoopdatavector[knoopnummer];
}

template <RichtType RT, class Knoopdata>
void GraafMetKnoopdata<RT, Knoopdata>::wis() {
  Graaf<RT>::wis();
  knoopdatavector.clear();
}

template <RichtType RT, class Knoopdata>
void GraafMetKnoopdata<RT, Knoopdata>::schrijfKnoop(std::ostream &os,
                                                    int k) const {
  os << "knoop " << k << "(Data: " << knoopdatavector[k] << "):" << std::endl;
  for (auto &[buur, tak] : this->burenlijsten[k]) {
    os << "  ->" << buur;
    this->schrijfVerbinding(os, tak);
  }
}

/**
 * @brief Deelklasse van Graaf, met data bij elke knoop en elke tak.
 *
 * @tparam RT Duidt aan of de graaf gericht is of niet. Dit beinvloedt functies
 * ivm verbindingen
 * @tparam Knoopdata  Klasse met info over elke knoop
 * @tparam Takdata  Klasse met info over elke tak
 */
template <RichtType RT, class Knoopdata, class Takdata>
class GraafMetKnoopEnTakdata : public GraafMetKnoopdata<RT, Knoopdata>,
                               public GraafMetTakdata<RT, Takdata> {
 public:
  template <class InputIterator>
  GraafMetKnoopEnTakdata(InputIterator start, InputIterator eind)
      : GraafMetKnoopdata<RT, Knoopdata>(start, eind){};
  GraafMetKnoopEnTakdata() : GraafMetKnoopdata<RT, Knoopdata>(){};
  virtual void wis() {
    GraafMetKnoopdata<RT, Knoopdata>::wis();
    this->takdatavector.clear();
  }
};

#endif  // __GRAAF_H
