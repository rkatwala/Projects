# Import necessary modules from Flask and requests library
from flask import Flask, request, jsonify  # Flask: web framework, request: to access query params, jsonify: to return JSON
import requests  # Used to make external API calls (e.g., to OpenWeather)

# Create a Flask application instance
app = Flask(__name__)

# Replace this with your actual API key from OpenWeatherMap
OPENWEATHER_API_KEY = 'a7f79489fc2641eba2d5a63fe5462e83'

# A list of keywords that indicate unsafe weather conditions for home visits
UNSAFE_KEYWORDS = ['storm', 'snow', 'thunder', 'heavy rain', 'hail']

# Define a route that handles GET requests to /check-weather
@app.route('/check-weather', methods=['GET'])
def check_weather():
    # Get the value of 'city' from the query string (e.g., ?city=Chicago)
    city = request.args.get('city')

    # If city is not provided, return a 400 Bad Request error
    if not city:
        return jsonify({"error": "Missing 'city' parameter"}), 400

    # Define the URL and query parameters for the OpenWeatherMap API
    url = "https://api.openweathermap.org/data/2.5/weather"
    params = {
        "q": city,  # City name passed by the user
        "appid": OPENWEATHER_API_KEY,  # Your API key
        "units": "metric"  # Return temperature in Celsius
    }

    try:
        # Make a GET request to the weather API with the parameters
        res = requests.get(url, params=params, timeout=5)

        # Raise an exception if the response has a bad status (e.g., 404, 500)
        res.raise_for_status()

        # Parse the JSON response from the weather API
        data = res.json()

        # Extract the weather description and temperature
        description = data["weather"][0]["description"]
        temp = data["main"]["temp"]

        # Check if the description contains any unsafe keyword (case-insensitive)
        is_safe = not any(keyword in description.lower() for keyword in UNSAFE_KEYWORDS)

        # Build the final result dictionary
        result = {
            "city": city,
            "description": description,
            "temperature": temp,
            "is_safe_to_visit": is_safe
        }

        # Return the result as a JSON response
        return jsonify(result)

    # If there was a network error or bad response
    except requests.exceptions.RequestException as e:
        return jsonify({"error": str(e)}), 500

    # If the JSON structure is missing expected fields
    except KeyError:
        return jsonify({"error": "Invalid response structure"}), 500

# Start the Flask server when running this script directly
if __name__ == '__main__':
    app.run(debug=True)  # debug=True enables auto-reload and better error output during development

