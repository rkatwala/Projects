import json

# Sample Python object about a basketball player (serializable to JSON)
# Initial structure:
# {
#   "name": "LeBron James",
#   "age": 39,
#   "is_active": True,
#   "teams": [...],
#   "career_stats": { ... },
#   "awards": None
# }
player = {
    "name": "LeBron James",
    "age": 39,
    "is_active": True,
    "teams": ["Cavaliers", "Heat", "Lakers"],
    "career_stats": {
        "regular_season": {
            "points_per_game": 27.2,
            "assists_per_game": 7.3,
            "rebounds_per_game": 7.5
        },
        "playoffs": {
            "points_per_game": 28.7,
            "assists_per_game": 7.1,
            "rebounds_per_game": 9.0
        }
    },
    "awards": None
}

# ---------------------------- Write JSON to file ----------------------------
# Save the original JSON object to a file
with open("player.json", "w") as f:
    json.dump(player, f, indent=4, sort_keys=True)
    print("JSON data written to player.json\n")

# ---------------------------- Read JSON from file ---------------------------
# Load JSON data back into Python as a dictionary
with open("player.json", "r") as f:
    loaded_player = json.load(f)
    print("Loaded from file:")
    print(loaded_player, "\n")

# ---------------------------- Accessing values ------------------------------
# Access a top-level string value
print("Player Name:", loaded_player["name"])  # "LeBron James"

# Access a list
print("Teams Played For:", loaded_player["teams"])  # ["Cavaliers", "Heat", "Lakers"]

# Example: Get second team from list (index 1)
second_team = loaded_player["teams"][1]
print("Second Team:", second_team)  # Should print "Heat"

# Access deeply nested values
print("Regular Season PPG:", loaded_player["career_stats"]["regular_season"]["points_per_game"])
print("Playoff RPG:", loaded_player["career_stats"]["playoffs"]["rebounds_per_game"], "\n")

# ---------------------------- Modifying values ------------------------------
# Change the player's age (updates the "age" key)
loaded_player["age"] = 40

# Add a new nested dictionary under "career_stats"
# Adds:
# "all_star_games": {
#     "appearances": 20,
#     "mvp_awards": 3
# }
loaded_player["career_stats"]["all_star_games"] = {
    "appearances": 20,
    "mvp_awards": 3
}
print("Modified age and added All-Star stats\n")

# ---------------------------- Adding new key -------------------------------
# Adds a new top-level key "hobbies"
# Before: no "hobbies"
# After:
# "hobbies": ["Philanthropy", "Movie Acting", "Business"]
loaded_player["hobbies"] = ["Philanthropy", "Movie Acting", "Business"]
print("Added hobbies\n")

# ---------------------------- Removing a key --------------------------------
# Deletes the "is_active" key entirely
# After: "is_active" is no longer in the JSON
del loaded_player["is_active"]
print("Removed is_active\n")

# ---------------------------- Pretty print JSON -----------------------------
# Prints the updated JSON in human-readable form with indentations
print("Pretty printed JSON:")
print(json.dumps(loaded_player, indent=4))

# ---------------------------- Convert to JSON string ------------------------
# Converts the updated dictionary into a JSON string (compact)
json_string = json.dumps(loaded_player)
print("\nJSON string (compact):")
print(json_string)

# ---------------------------- Load JSON from string -------------------------
# Simulates loading JSON from an external source (like an API response)
json_text = '{"team": "Warriors", "championships": 4}'
parsed_team = json.loads(json_text)
print("\nLoaded from string:")
print(parsed_team)

# ---------------------------- Working with lists ----------------------------
# Loops through the list of teams
print("\nTeams Played For:")
for team in loaded_player["teams"]:
    print("-", team)

# Check if a specific value exists in a list
has_movie_acting = "Movie Acting" in loaded_player["hobbies"]
print("\nHas done Movie Acting?", has_movie_acting)

# ---------------------------- Sorting keys ----------------------------------
# Shows the entire dictionary with sorted keys alphabetically
print("\nSorted keys:")
print(json.dumps(loaded_player, indent=2, sort_keys=True))

# ---------------------------- Save updated JSON -----------------------------
# Final updated object is saved to a new file
with open("updated_player.json", "w") as f:
    json.dump(loaded_player, f, indent=4)
    print("\nSaved updated JSON to updated_player.json")
