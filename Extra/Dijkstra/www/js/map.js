var map = L.map("map").setView([51.0, 3.7], 13);

var tiles = L.tileLayer("https://tile.openstreetmap.org/{z}/{x}/{y}.png", {
  maxZoom: 19,
  attribution:
    '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>',
}).addTo(map);

const bidirectioneelInput = document.getElementById("bidirectioneel");
bidirectioneelInput.onchange = shortestPath;

const aantalSpan = document.getElementById("aantal");

const point_layers = {};
const linestring_layers = {};

let from_geoid = null;
let to_geoid = null;

function resetMarkerStyles() {
  Object.entries(point_layers).forEach(([geoid, marker]) => {
    marker.setStyle({
      fillColor:
        geoid == from_geoid ? "green" : geoid == to_geoid ? "red" : "gray",
    });
  });

  Object.values(linestring_layers).forEach((line) =>
    line.setStyle({ color: "gray" })
  );
}

async function zetStart(geoid) {
  from_geoid = geoid;

  await shortestPath();
}

async function zetEind(geoid) {
  to_geoid = geoid;

  await shortestPath();
}

async function shortestPath() {
  map.closePopup();
  resetMarkerStyles();

  if (!from_geoid || !to_geoid) return;

  const bidirectioneel_zoeken = document.getElementById("bidirectioneel").checked;

  var pad = await fetch(`/api/kortste_pad${bidirectioneel_zoeken ? "_bidirectioneel": ""}/${from_geoid}/${to_geoid}`).then(
    (response) => response.json()
  );

  const padGeoIds = new Set();

  pad.forEach((stap) => {
    padGeoIds.add(stap.geoid);

    if (stap.geoid !== from_geoid && stap.geoid !== to_geoid) {
      point_layers[stap.geoid].setStyle({
        fillColor: "blue",
      });
    }

    if (stap.tak_nr != -1) {
      linestring_layers[stap.tak_nr].setStyle({
        color: "blue",
      });
    }
  });

  var permanente_knopen = await fetch(`/api/permanente_knopen`).then(
    (response) => response.json()
  );
  permanente_knopen
    .filter((geoid) => !padGeoIds.has(geoid))
    .forEach((geoid) => {
      point_layers[geoid].setStyle({
        fillColor: "orange",
      });
    });

  aantalSpan.textContent = permanente_knopen.length;
}

function pointPopup({ naam, geoid, knoopnr }) {
  return `<div class="knooppunt-popup"> 
  <h4>Geo ID ${geoid}</h4>
  <h5>Knooppunt ${naam} ${knoopnr}</h5>

  <div><button onClick="zetStart(${geoid})">Pad vanaf hier</button></div>
  <div><button onClick="zetEind(${geoid})">Pad naar hier</button></div>
</div>`;
}

function onEachFeature(feature, layer) {
  if (feature.geometry.type === "Point") {
    point_layers[feature.properties.geoid] = layer;
    layer.bindPopup(() => pointPopup(feature.properties));
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
