import pandas as pd
import json

# Your JSON data
data = {
  "coord": {"lon": -121.9886, "lat": 37.5483},
  "weather": [{
    "id": 800,
    "main": "Clear",
    "description": "clear sky",
    "icon": "01d"
  }],
  "base": "stations",
  "main": {
    "temp": 21.21,
    "feels_like": 21.01,
    "temp_min": 18.38,
    "temp_max": 23.06,
    "pressure": 1015,
    "humidity": 62,
    "sea_level": 1015,
    "grnd_level": 1005
  },
  "visibility": 10000,
  "wind": {"speed": 2.24, "deg": 240, "gust": 4.02},
  "clouds": {"all": 2},
  "dt": 1749406594,
  "sys": {
    "type": 2,
    "id": 2033686,
    "country": "US",
    "sunrise": 1749386798,
    "sunset": 1749439668
  },
  "timezone": -25200,
  "id": 5350734,
  "name": "Fremont",
  "cod": 200
}

# Flatten the JSON (weather is a list, take the first element)
flat = {
    "city": data["name"],
    "country": data["sys"]["country"],
    "temp": data["main"]["temp"],
    "feels_like": data["main"]["feels_like"],
    "temp_min": data["main"]["temp_min"],
    "temp_max": data["main"]["temp_max"],
    "humidity": data["main"]["humidity"],
    "pressure": data["main"]["pressure"],
    "weather_main": data["weather"][0]["main"],
    "weather_description": data["weather"][0]["description"],
    "wind_speed": data["wind"]["speed"],
    "wind_deg": data["wind"]["deg"],
    "visibility": data["visibility"],
    "cloudiness": data["clouds"]["all"]
}

# Create DataFrame
df = pd.DataFrame([flat])


print(df.loc[df["temp"]<20])

print(df)

