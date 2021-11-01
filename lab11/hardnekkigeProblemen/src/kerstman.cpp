#include "kerstman.h"

using std::vector;
using std::pair;
using std::sqrt;

void DEZBezoekpre(
    pugi::xml_node n, std::function<void(pugi::xml_node)> bezoekKnoop = [](pugi::xml_node) {})
{
    bezoekKnoop(n);
    for (auto &&k : n.children())
        DEZBezoekpre(k, bezoekKnoop);
};

std::vector<std::pair<double, double>> leesKnooppunten(pugi::xml_document &n)
{
    vector<pair<double, double>> knooppunt;
    DEZBezoekpre(n, [&knooppunt](pugi::xml_node nn) {
        if (strcmp(nn.name(), "knooppunt") == 0)
        {
            double x = 0, y = 0;
            for (auto &&att : nn.attributes())
            {
                if (strcmp(att.name(), "xcoordinaat") == 0)
                    x = atof(att.value());
                else if (strcmp(att.name(), "ycoordinaat") == 0)
                    y = atof(att.value());
            };
            knooppunt.emplace_back(x, y);
        };
    });
    return knooppunt;
};

vector<vector<double>> berekenAfstanden()
{
    pugi::xml_document doc;
    if (!doc.load_file("kerstnet.xml"))
        throw "probleem met bestand";
    vector<std::pair<double, double>> knooppunt = leesKnooppunten(doc);
    int aantal = knooppunt.size();
    vector<std::vector<double>> afst(aantal, std::vector<double>(aantal));
    for (int i = 0; i < aantal; i++)
    {
        for (int j = i + 1; j < aantal; j++)
        {
            double dx = knooppunt[i].first - knooppunt[j].first;
            double dy = knooppunt[i].second - knooppunt[j].second;
            afst[i][j] = afst[j][i] = sqrt(dx * dx + dy * dy);
        }
    }
    return afst;
}




