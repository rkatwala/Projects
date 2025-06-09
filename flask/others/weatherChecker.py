# flexible_weather_service.py  ───────────────────────────────────────────────
from flask import Flask, request, jsonify
import requests, statistics

API_KEY = "a7f79489fc2641eba2d5a63fe5462e83"
UNSAFE  = {"storm", "snow", "thunder", "heavy rain", "hail"}
DEFAULT_CITIES = ["Chicago", "Los Angeles", "Denver", "New York", "Miami"]

app = Flask(__name__)

# ─────────────────── helper: fetch + normalize one city ---------------------
def fetch_city(city: str) -> dict:
    url    = "https://api.openweathermap.org/data/2.5/weather"
    params = {"q": city, "appid": API_KEY, "units": "metric"}
    r = requests.get(url, params=params, timeout=5)
    r.raise_for_status()
    raw = r.json()

    desc   = raw["weather"][0]["description"]
    temp_c = raw["main"]["temp"]
    temp_f = temp_c * 9 / 5 + 32
    return {
        "city":   city,
        "temp_c": round(temp_c, 1),
        "temp_f": round(temp_f, 1),
        "clouds": raw.get("clouds", {}).get("all"),
        "winds":  raw.get("wind", {}).get("speed"),
        "unsafe": any(k in desc.lower() for k in UNSAFE),
        "desc":   desc,
    }

# ─────────────────── helper: build rows for any list ------------------------
def rows_for(cities: list[str]) -> list[dict]:
    return [fetch_city(c.strip()) for c in cities]

# ─────────────────── helper: generate full stats bundle ---------------------
def full_stats(rows: list[dict]) -> dict:
    safe     = [r for r in rows if not r["unsafe"]]
    avg_c    = statistics.mean(r["temp_c"] for r in rows)
    hottest  = max(rows, key=lambda r: r["temp_c"])
    coldest  = min(rows, key=lambda r: r["temp_c"])
    sorted_r = sorted(rows, key=lambda r: r["temp_c"], reverse=True)
    return {
        "rows": rows,
        "safe_cities": [r["city"] for r in safe],
        "summary": {
            "average_c": round(avg_c, 1),
            "hottest":   {"city": hottest["city"], "temp_c": hottest["temp_c"]},
            "coldest":   {"city": coldest["city"], "temp_c": coldest["temp_c"]},
        },
        "sorted_desc_temp": sorted_r,
    }

# ─────────────────── helper: mini‑stats (Python 3.9‑compatible) -------------
def single_stat(stat: str, rows: list[dict]):
    stat = stat.lower()
    if stat == "raw":
        return rows
    elif stat == "safe":
        return [r for r in rows if not r["unsafe"]]
    elif stat == "unsafe":
        return [r for r in rows if r["unsafe"]]
    elif stat == "average":
        avg = round(statistics.mean(r["temp_c"] for r in rows), 1)
        return {"average_c": avg}
    elif stat == "hottest":
        return max(rows, key=lambda r: r["temp_c"])
    elif stat == "coldest":
        return min(rows, key=lambda r: r["temp_c"])
    elif stat == "sorted":
        return sorted(rows, key=lambda r: r["temp_c"], reverse=True)
    elif stat == "grouped":
        out = {"safe": [], "unsafe": []}
        for r in rows:
            (out["unsafe"] if r["unsafe"] else out["safe"]).append(r)
        return out
    else:
        return {"error": f"unknown stat '{stat}'"}, 400

# ─────────────────── DEFAULT routes ----------------------------------------
@app.route("/default")
def default_all():
    return jsonify(full_stats(rows_for(DEFAULT_CITIES)))

@app.route("/default/<string:stat>")
def default_stat(stat):
    return jsonify(single_stat(stat, rows_for(DEFAULT_CITIES)))

# ─────────────────── SEARCH=<cities> routes ---------------------------------
@app.route("/search=<string:cities>")
def search_all(cities):
    rows = rows_for(cities.split(","))
    return jsonify(full_stats(rows))

@app.route("/search=<string:cities>/<string:stat>")
def search_stat(cities, stat):
    rows = rows_for([c.strip() for c in cities.split(",")])
    return jsonify(single_stat(stat, rows))

# ─────────────────── entry‑point --------------------------------------------
if __name__ == "__main__":
    app.run(debug=True)

