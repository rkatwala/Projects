from flask import Flask, jsonify, request
import requests

app = Flask(__name__)

@app.route('/launches-summary', methods=['GET'])
def launches_summary():
    # Query parameters
    limit = request.args.get("limit", default=10, type=int)
    success_raw = request.args.get("success")  # e.g., "true,false" or "true"

    # Normalize multiple success values to a set of booleans
    success_set = None
    if success_raw:
        success_set = set()
        for value in success_raw.split(","):
            v = value.strip().lower()
            if v == "true":
                success_set.add(True)
            elif v == "false":
                success_set.add(False)
            elif v != "":
                return jsonify({"error": "Invalid value for 'success'. Use true,false or combinations thereof."}), 400

    try:
        url = "https://api.spacexdata.com/v4/launches"
        response = requests.get(url, timeout=5)
        response.raise_for_status()
        launches = response.json()
    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"Failed to fetch launches: {str(e)}"}), 500

    results = []

    for launch in launches:
        launch_success = launch.get("success")  # could be True, False, or None

        # If filtering and the launch's success doesn't match any allowed values
        if success_set is not None and launch_success not in success_set:
            continue

        results.append({
            "name": launch.get("name"),
            "date_utc": launch.get("date_utc"),
            "success": launch_success,
            "rocket_id": launch.get("rocket"),
            "flight_number": launch.get("flight_number")
        })

    # Sort by most recent (highest flight_number first)
    results.sort(key=lambda x: x["flight_number"], reverse=True)

    # Return up to the requested limit
    return jsonify(results[:limit])


@app.route("/rocket/<string:rocket_id>", methods=["GET"])
def route(rocket_id):

    try:
        url = f"https://api.spacexdata.com/v4/rockets/{rocket_id}"
        res = requests.get(url, timeout=5)
        res.raise_for_status()
        info = res.json()

    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"failed to fetch list: {str(e)}"}), 500


    '''
      "name": ,
      "first_flight": ,
      "country": ,
      "cost_per_launch": ,
      "description": ""

    '''
    sol = []
    
    rocket = info  
    sol.append({
            "name": rocket["name"],
            "first_flight": rocket["first_flight"],
            "country": rocket["country"],
            "cost_per_launch": rocket["cost_per_launch"],
            "description": rocket["description"],
        })

    return jsonify(sol)

if __name__=='__main__':
    app.run(debug=True)


    

    
               
