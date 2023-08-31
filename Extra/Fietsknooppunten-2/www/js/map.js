var map = L.map("map").setView([51.0, 3.7], 13);

var tiles = L.tileLayer("https://tile.openstreetmap.org/{z}/{x}/{y}.png", {
  maxZoom: 19,
  attribution:
    '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>',
}).addTo(map);

const colorScale = chroma.scale('YlGnBu');

const point_layers = {};
const linestring_layers = {};
let dieptes = {};

function resetMarkerStyles() {
  Object.values(point_layers).forEach((marker) => {
    marker.setStyle({
      fillColor: "gray",
    });
  });

  Object.values(linestring_layers).forEach((line) =>
    line.setStyle({ color: "gray" })
  );
}

async function breedteEerstZoeken(geoid) {
  map.closePopup();
  resetMarkerStyles();

  const max_diepte = document.getElementById("diepte").value;

  var bez = await fetch(
    `/api/breedte_eerst_zoeken/${geoid}/${max_diepte}`
  ).then((response) => response.json());

    dieptes = {};

  const latlngs = [];

  bez.forEach((gzs) => {
    dieptes[gzs.geoid] = gzs.diepte;

    const point_layer = point_layers[gzs.geoid];
    point_layer.setStyle({
      fillColor: colorScale(gzs.diepte / max_diepte),
    });
    latlngs.push(point_layer.getLatLng());

    if (gzs.tak_nr != -1) {
      linestring_layers[gzs.tak_nr].setStyle({
        color: colorScale(gzs.diepte / max_diepte),
      });
    }
  });

  // Zoom out to show all points within BFS area
  map.flyToBounds(L.latLngBounds(latlngs));
}


function pointPopup({naam, geoid, knoopnr}){
  return`<div class="knooppunt-popup"> 
  <h4>Geo ID ${geoid}</h4>
  <h5>Knooppunt ${naam} ${knoopnr}</h5>

  ${dieptes[knoopnr] ? `<p>Diepte: ${dieptes[knoopnr]}</p>`: ''}

  <div><button onClick="breedteEerstZoeken(${geoid})">Breedte Eerst Zoeken vanaf hier</button></div>
</div>`;

}

function onEachFeature(feature, layer) {
  if (feature.geometry.type === "Point") {
    point_layers[feature.properties.geoid] = layer;
    layer.bindPopup(()=>pointPopup(feature.properties));
  } else if (feature.geometry.type === "LineString") {
    linestring_layers[feature.properties.taknr] = layer;
  }
}

async function loadGraaf(map) {
  var graaf = await fetch("/graaf.geojson").then((response) => response.json());

  //sort sot that Points are rendered last (and thus appear on top of the lines)
  graaf.features.sort((a, b) => {
    if (a.geometry.type === "Point") {
      return b.geometry.type === "Point" ? 0 : 1;
    } else {
      return b.geometry.type !== "Point" ? 0 : -1;
    }
  });

  L.geoJSON(graaf, {
    pointToLayer: function (feature, latlng) {
      return L.circleMarker(latlng, {
        radius: 8,
        fillColor: "#ff7800",
        color: "#000",
        weight: 1,
        opacity: 1,
        fillOpacity: 1,
      });
    },
    style: function (feature) {
      if (feature.geometry.type == "LineString")
        return {
          color: "red",
          weight: 3,
          opacity: 0.65,
        };
      else return {};
    },
    onEachFeature: onEachFeature,
  }).addTo(map);
}

loadGraaf(map);
