#include "fietsnet.h"
#include "serializer.h"
#include <httplib.h>
#include <vector>
using std::vector;

int main()
{
    const auto [g, geoid_naar_knoopnr] = leesGraaf();

    std::cout << "Ingelezen graaf bevat " << g.aantalKnopen() << " knopen en " << g.aantalVerbindingen() << " verbindingen.\n";

    httplib::Server svr;
    vector<int> permanente_knoopnrs;
    svr.Get("/graaf.geojson", [&g](const httplib::Request &req, httplib::Response &res)
            { res.set_content(geojson(g), "application/geo+json"); });

    svr.Get("/api/kortste_pad/(\\d+)/(\\d+)", [&g, &geoid_naar_knoopnr, &permanente_knoopnrs](const httplib::Request &req, httplib::Response &res)
            {
                int van_geoid = stoi(req.matches[1]);
                int naar_geoid = stoi(req.matches[2]);
                if (!geoid_naar_knoopnr.contains(van_geoid) || !geoid_naar_knoopnr.contains(naar_geoid))
                {
                    res.set_content("{ \"status\": 400, \"message\": \"Ongeldig knoopnr\"}", "application/json");
                    res.status = 400;
                }
                else
                {
                    int van_knoopnr = geoid_naar_knoopnr.at(van_geoid); // .at want operator[] is niet const
                    int naar_knoopnr = geoid_naar_knoopnr.at(naar_geoid); // .at want operator[] is niet const
                    res.set_content(graaf_kortste_pad_json(g, kortstePad(g,van_knoopnr, naar_knoopnr, permanente_knoopnrs)), "application/json");
                } });

    svr.Get("/api/kortste_pad_bidirectioneel/(\\d+)/(\\d+)", [&g, &geoid_naar_knoopnr, &permanente_knoopnrs](const httplib::Request &req, httplib::Response &res)
            {
                int van_geoid = stoi(req.matches[1]);
                int naar_geoid = stoi(req.matches[2]);
                if (!geoid_naar_knoopnr.contains(van_geoid) || !geoid_naar_knoopnr.contains(naar_geoid))
                {
                    res.set_content("{ \"status\": 400, \"message\": \"Ongeldig knoopnr\"}", "application/json");
                    res.status = 400;
                }
                else
                {
                    int van_knoopnr = geoid_naar_knoopnr.at(van_geoid); // .at want operator[] is niet const
                    int naar_knoopnr = geoid_naar_knoopnr.at(naar_geoid); // .at want operator[] is niet const
                    res.set_content(graaf_kortste_pad_json(g, kortstePadBidirectioneel(g,van_knoopnr, naar_knoopnr, permanente_knoopnrs)), "application/json");
                } });

    svr.Get("/api/permanente_knopen", [&g, &permanente_knoopnrs](const httplib::Request &req, httplib::Response &res)
            { res.set_content(permanente_knopen_json(g, permanente_knoopnrs), "application/json"); });

    svr.set_mount_point("/", "./www");

    std::cout << "Webserver actief op http://localhost:8080\n";

    svr.listen("0.0.0.0", 8080);

    return 0;
}
