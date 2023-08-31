#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::string;

struct TZKnoop;

struct TZKnoop {
    std::unique_ptr<TZKnoop> kleiner, gelijk, groter;
    char c;
    bool in_boom;

    std::string tekenKnoop(std::ostream &uit, int &knoopteller);
};

class TernaireZoekboom {

  public:
    TernaireZoekboom();
    void voegtoe(string woord);
    bool zoek(string woord);
    void teken(const char *bestandsnaam) const;

    std::vector<string> auto_complete(string prefix);
    std::vector<string> auto_complete_wildcard(string prefix);

  private:
    bool zoek_woord(TZKnoop *knoop, string woord, int pos);

    void auto_complete_rec(string prefix, TZKnoop *knoop, string woord, std::vector<string> &resultaten);
    void auto_complete_wildcard_rec(string prefix, TZKnoop *knoop, string woord, std::vector<string> &resultaten);

    std::unique_ptr<TZKnoop> wortel;
};
