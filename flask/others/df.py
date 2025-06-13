from flask import Flask, jsonify
import pandas as pd
import requests
from io import StringIO

app = Flask(__name__)

@app.route('/covid-data', methods=['GET'])
def covid_data():
    try:
        # Example CSV URL that returns COVID data
        csv_url = "https://people.sc.fsu.edu/~jburkardt/data/csv/hw_200.csv"
        response = requests.get(csv_url)
        response.raise_for_status()

        # Read CSV into DataFrame
        df = pd.read_csv(StringIO(response.text))

        # Clean & rename columns for readability (if needed)
        df.columns = ["Index", "Height(Inches)", "Weight(Pounds)"]

        # Convert to dictionary
        data = df.to_dict(orient="records")

        return jsonify(data)

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    app.run(debug=True)
