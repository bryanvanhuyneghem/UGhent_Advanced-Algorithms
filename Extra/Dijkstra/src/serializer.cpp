#include "serializer.h"

std::string geojson(const KnooppuntGraaf &g)
{
    std::stringstream ss;
    ss << "{\n\t\"type\": \"FeatureCollection\",\n\t\"features\": [\n";

    for (int k = 0; k < g.aantalKnopen(); k++)
    {
        const Fietsknooppunt *knp = g.geefKnoopdata(k);
        ss << "\t\t{\n";
        ss << "\t\t\t\"type\": \"Feature\",\n";
        ss << "\t\t\t\"geometry\": { \"type\": \"Point\", \"coordinates\": [" << knp->lon << "," << knp->lat << "] },\n";
        ss << "\t\t\t\"properties\": { \"geoid\": " << knp->geoid << ", \"knoopnr\": " << knp->knoopnr << ", \"naam\": \"" << knp->naam << "\" }\n";
        ss << "\t\t},\n";

        for (auto &[buur, tak] : g[k])
        {
            if (buur >= k)
            {

                const Fietsknooppunt *buur_knp = g.geefKnoopdata(buur);
                ss << "\t\t{\n";
                ss << "\t\t\t\"type\": \"Feature\",\n";
                ss << "\t\t\t\"geometry\": { \"type\": \"LineString\", \"coordinates\": [ [" << knp->lon << ", " << knp->lat << "], [" << buur_knp->lon << ", " << buur_knp->lat << " ]] },\n";
                ss << "\t\t\t\"properties\": { \"taknr\": " << tak << " }\n";
                ss << "\t\t},\n";
            }
        };
    }

    // laatste comma terug verwijderen
    ss.seekp(-2, ss.cur);

    ss << "\n]\n}";

    return ss.str();
};

std::string graaf_kortste_pad_json(const KnooppuntGraaf &g, const std::list<KortstePadStap>& stappen)
{
    std::stringstream ss;

    ss << "[\n";

    std::list<KortstePadStap>::const_iterator it = stappen.begin();
    while(it != stappen.end())
    {
        auto zs = *it;
        ss << "\t{\"geoid\": " << g.geefKnoopdata(zs.knoopnr)->geoid << ", \"tak_nr\": " << zs.tak_nr << " }";

        ++it;
        if (it != stappen.end())
        {
            ss << ",";
        }

        ss << "\n";
    }

    ss << "]\n";

    return ss.str();
}

std::string permanente_knopen_json(const KnooppuntGraaf &g, const std::vector<int>& knoopnrs)
{
    std::stringstream ss;

    ss << "[\n";

    auto it = knoopnrs.begin();
    while(it != knoopnrs.end())
    {
        int knoopnr = *it;
        ss << g.geefKnoopdata(knoopnr)->geoid;

        ++it;
        if (it != knoopnrs.end())
        {
            ss << ", ";
        }

        ss << "\n";
    }

    ss << "]\n";

    return ss.str();
}