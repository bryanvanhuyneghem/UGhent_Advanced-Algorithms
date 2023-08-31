#include "fietsnet.h"
#include "serializer.h"
#include <httplib.h>

int main()
{
    const auto [g, geoid_naar_knoopnr] = leesGraaf();

    std::cout << "Ingelezen graaf bevat " << g.aantalKnopen() << " knopen en " << g.aantalVerbindingen() << " verbindingen.\n";

    httplib::Server svr;

    svr.Get("/graaf.geojson", [&g](const httplib::Request &req, httplib::Response &res)
            { res.set_content(geojson(g), "application/geo+json"); });

    svr.Get("/api/breedte_eerst_zoeken/(\\d+)/(\\d+)", [&g, &geoid_naar_knoopnr](const httplib::Request &req, httplib::Response &res)
            {
                int geoid = stoi(req.matches[1]);
                if (!geoid_naar_knoopnr.contains(geoid))
                {
                    res.set_content("{ \"status\": 400, \"message\": \"Ongeldig knoopnr\"}", "application/json");
                    res.status = 400;
                }
                else
                {
                    int max_diepte = stoi(req.matches[2]);
                    int start_nr = geoid_naar_knoopnr.at(geoid); // .at want operator[] is niet const
                    res.set_content(graaf_zoek_stappen_json(breedte_eerst_zoeken(g, start_nr , max_diepte)), "application/json");
                } });

    svr.set_mount_point("/", "./www");

    std::cout << "Webserver actief op http://localhost:8080\n";

    svr.listen("0.0.0.0", 8080);

    return 0;
}
