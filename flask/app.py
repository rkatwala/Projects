from flask import Flask, render_template, request, jsonify
import requests
import os
import random
from datetime import datetime, timezone, timedelta
import threading

app = Flask(__name__)

# Artsy API credentials (replace with your actual values)
CLIENT_ID = "29b4419ecf790501de25"
CLIENT_SECRET = "467c025b8120a835ec30a219213d12eb"

# Globals to cache token and expiry time
ARTSY_TOKEN = None
TOKEN_EXPIRES_AT = datetime.min.replace(tzinfo=timezone.utc)
LOCK = threading.Lock()

def fetch_artsy_token():
    """Fetch a new Artsy XAPP token and set global cache."""
    global ARTSY_TOKEN, TOKEN_EXPIRES_AT
    url = "https://api.artsy.net/api/tokens/xapp_token"
    data = {
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET
    }
    response = requests.post(url, data=data, timeout=10)
    if response.status_code == 201:
        json_resp = response.json()
        ARTSY_TOKEN = json_resp["token"]
        TOKEN_EXPIRES_AT = datetime.strptime(json_resp["expires_at"], "%Y-%m-%dT%H:%M:%S%z")
    else:
        print("Error fetching token:", response.text)

def get_artsy_token():
    """Return a valid token, refreshing it if expired."""
    with LOCK:
        if ARTSY_TOKEN is None or datetime.now(timezone.utc) >= TOKEN_EXPIRES_AT:
            fetch_artsy_token()
        return ARTSY_TOKEN

@app.route("/")
def home():
    """Serve the main HTML page with cache-busting JS version."""
    return render_template("index.html", version=random.randint(1, 10000))

@app.route("/search", methods=["GET"])
def search_artist():
    """Handle artist search requests."""
    query = request.args.get("query")
    if not query:
        return jsonify({"error": "Missing search query"}), 400

    headers = {"X-XAPP-Token": get_artsy_token()}
    search_url = f"https://api.artsy.net/api/search?q={query}&size=10&type=artist"
    response = requests.get(search_url, headers=headers)

    if response.status_code == 200:
        return jsonify(response.json())
    else:
        return jsonify({"error": "Failed to fetch search results"}), 500

@app.route("/artist/<artist_id>", methods=["GET"])
def get_artist_details(artist_id):
    """Fetch detailed artist information."""
    headers = {"X-XAPP-Token": get_artsy_token()}
    artist_url = f"https://api.artsy.net/api/artists/{artist_id}"
    response = requests.get(artist_url, headers=headers)

    if response.status_code == 200:
        return jsonify(response.json())
    else:
        return jsonify({"error": "Failed to fetch artist details"}), 500

if __name__ == "__main__":
    app.run(debug=True)
