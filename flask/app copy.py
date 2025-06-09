from flask import Flask, render_template, request, jsonify, url_for
import requests
import os
import random

app = Flask(__name__)

# Artsy API credentials (replace with actual values)
#CLIENT_ID = "4cb390318e034016d92a"
#CLIENT_SECRET = "8feee6b594115cb681114a7159320995"
#
## ✅ RESTORED: Hardcoded Artsy Token
#ARTSY_TOKEN = "eyJhbGciOiJIUzI1NiJ9.eyJyb2xlcyI6IiIsInN1YmplY3RfYXBwbGljYXRpb24iOiI4Y2E1NjA4Yi0xNWJmLTQwMWMtYTM3Mi0wNTdjNmViMzgyZjgiLCJleHAiOjE3NDA5OTI2MjQsImlhdCI6MTc0MDM4NzgyNCwiYXVkIjoiOGNhNTYwOGItMTViZi00MDFjLWEzNzItMDU3YzZlYjM4MmY4IiwiaXNzIjoiR3Jhdml0eSIsImp0aSI6IjY3YmMzNWYwNmRmNmNiMDAxMzdmOGY2MyJ9.irkf_krRhD6wws7518X7eZsgfFB7Tv9RWG8ZYGivYhA"

CLIENT_ID = "29b4419ecf790501de25"
CLIENT_SECRET = "467c025b8120a835ec30a219213d12eb"

# ✅ RESTORED: Hardcoded Artsy Token
ARTSY_TOKEN = "eyJhbGciOiJIUzI1NiJ9.eyJyb2xlcyI6IiIsInN1YmplY3RfYXBwbGljYXRpb24iOiI3NzU4YWEwZS1kNzk0LTRmYTctOTk3MC0xODViNThmNDVlNDQiLCJleHAiOjE3NDE2MjczNTQsImlhdCI6MTc0MTAyMjU1NCwiYXVkIjoiNzc1OGFhMGUtZDc5NC00ZmE3LTk5NzAtMTg1YjU4ZjQ1ZTQ0IiwiaXNzIjoiR3Jhdml0eSIsImp0aSI6IjY3YzVlNTVhM2NjMTQ3MDAwZjA2NmEzMSJ9.o2SUbyvf3qlr-XQWKIWteEYYMH30r8WupjXwxNTMvew"

def get_artsy_token():
    """Fetch a new authentication token from Artsy API if needed."""
    global ARTSY_TOKEN
    if not ARTSY_TOKEN:  # Only fetch if missing
        url = "https://api.artsy.net/api/tokens/xapp_token"
        data = {"client_id": CLIENT_ID, "client_secret": CLIENT_SECRET}
        response = requests.post(url, json=data)
        if response.status_code == 200:
            ARTSY_TOKEN = response.json().get("token")
        else:
            print("Error fetching Artsy token")

# ✅ Token is already set, so no need to fetch it on startup

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
    
    headers = {"X-XAPP-Token": ARTSY_TOKEN}
    search_url = f"https://api.artsy.net/api/search?q={query}&size=10&type=artist"
    response = requests.get(search_url, headers=headers)

    if response.status_code == 200:
        return jsonify(response.json())
    else:
        return jsonify({"error": "Failed to fetch search results"}), 500

@app.route("/artist/<artist_id>", methods=["GET"])
def get_artist_details(artist_id):
    """Fetch detailed artist information."""
    headers = {"X-XAPP-Token": ARTSY_TOKEN}
    artist_url = f"https://api.artsy.net/api/artists/{artist_id}"
    response = requests.get(artist_url, headers=headers)

    if response.status_code == 200:
        return jsonify(response.json())
    else:
        return jsonify({"error": "Failed to fetch artist details"}), 500

if __name__ == "__main__":
    app.run(debug=True)
