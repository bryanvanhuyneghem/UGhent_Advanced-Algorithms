#include "probprob_voorbeeld.h"

bool Dom::isOplossing(const vector<char> &deeloplossing)
{
    return deeloplossing.size() == aantal; // kijken of oplossing juiste aantal cijfers heeft
};

double Dom::f(const vector<char> &oplossing)
{
    int totaal = oplossing[0] - '0';
    for (int i = 1; i < oplossing.size(); i++)
    {
        totaal *= 10;
        totaal += oplossing[i] - '0';
    }
    return totaal;
};

vector<pair<char, double>> Dom::geefVolgendePunt(const vector<char> &deeloplossing)
{
    vector<pair<char, double>> voortzetting;

    for (int i = 0; i < 10; i++)
    {
        voortzetting.emplace_back('0' + i, 10 - i);
    }
    return voortzetting;
};

int main()
{
    // "Domme" implementatie voor het zoeken van een zo klein mogelijk getal met 5 cijfers:
    srand(time(0));
    Dom getal(5);
    vector<char> beste = getal.geefOptimum(500);
    cout << "Eindoplossing:\n";
    for (auto &&c : beste)
    {
        cout << " " << c;
    }
    cout << "\n";

    return 0;
}