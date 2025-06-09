import pandas as pd
import json

# ---------------------------- Sample JSON Data ----------------------------
# This represents a list of one basketball player's stats with nested fields
json_data = """
[
  {
    "name": "LeBron James",
    "age": 39,
    "is_active": true,
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
    }
  }
]
"""

# ---------------------------- Load JSON into DataFrame ----------------------------
# Load the JSON string into Python as a list of dicts
player_list = json.loads(json_data)

# Use json_normalize to flatten the nested structure into columns
df = pd.json_normalize(player_list)

# Print the entire DataFrame
print("Full DataFrame:")
print(df, "\n")

# ---------------------------- Accessing Data ----------------------------
# Get a simple column
print("Player Name:", df["name"].iloc[0])

# Get a nested column (flattened key)
print("Regular Season Points Per Game:", df["career_stats.regular_season.points_per_game"].iloc[0])
print("Playoff Rebounds Per Game:", df["career_stats.playoffs.rebounds_per_game"].iloc[0])

# Get a list of teams
print("Teams Played For:", df["teams"].iloc[0])         # Returns full list
print("Second Team:", df["teams"].iloc[0][1])           # Index into list directly

# ---------------------------- Modifying Data ----------------------------
# Change the player's age
df.at[0, "age"] = 40
print("\nModified Age:", df["age"].iloc[0])

# Add a new column: 'career_length'
df["career_length"] = [21]
print("Added Column 'career_length':")
print(df[["name", "career_length"]])

# Add a new nested stat (manually inserted)
df["career_stats.all_star.appearances"] = [20]
df["career_stats.all_star.mvp_awards"] = [3]
print("Added All-Star Stats:")
print(df[["career_stats.all_star.appearances", "career_stats.all_star.mvp_awards"]])

# ---------------------------- Removing Data ----------------------------
# Drop a column
df = df.drop(columns=["is_active"])
print("\nRemoved Column 'is_active':")
print(df.columns)

# ---------------------------- Converting Back to JSON ----------------------------
# Convert back to nested JSON structure (orient='records')
reconstructed_json = df.to_json(orient="records", indent=4)
print("\nReconstructed JSON from DataFrame:")
print(reconstructed_json)

# ---------------------------- Filtering / Querying ----------------------------
# Example filter: all players with playoff PPG > 28
filtered_df = df[df["career_stats.playoffs.points_per_game"] > 28]
print("\nFiltered Players with Playoff PPG > 28:")
print(filtered_df[["name", "career_stats.playoffs.points_per_game"]])

# ---------------------------- Exporting to File ----------------------------
df.to_json("updated_player_df.json", orient="records", indent=4)
print("\nSaved updated DataFrame as 'updated_player_df.json'")
