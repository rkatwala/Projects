from flask import Flask, jsonify
import requests

app = Flask(__name__)

@app.route('/doctor-load', methods=['GET'])
def doctor_load():
    try:
        # Step 1: Fetch all doctors
        users_url = "https://jsonplaceholder.typicode.com/users"
        users_res = requests.get(users_url, timeout=5)
        users_res.raise_for_status()
        doctors = users_res.json()
    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"Failed to fetch doctors: {str(e)}"}), 500

    city_groups = {}

    for doctor in doctors:
        doctor_id = doctor.get("id")
        doctor_name = doctor.get("name")
        doctor_email = doctor.get("email")
        city = doctor.get("address", {}).get("city", "Unknown")

        # Step 2: Fetch todos for this specific doctor
        try:
            todos_res = requests.get(
                "https://jsonplaceholder.typicode.com/todos",
                params={"userId": doctor_id},
                timeout=5
            )
            todos_res.raise_for_status()
            todos = todos_res.json()
        except requests.exceptions.RequestException as e:
            return jsonify({"error": f"Failed to fetch todos for user {doctor_id}: {str(e)}"}), 500

        # Step 3: Count todos
        total = len(todos)
        completed = len([t for t in todos if t.get("completed")])
        pending = total - completed

        doctor_summary = {
            "id": doctor_id,
            "name": doctor_name,
            "total_appointments": total,
            "completed_appointments": completed,
            "pending_appointments": pending
        }

        # Step 4: Group by city
        if city not in city_groups:
            city_groups[city] = {
                "doctors": [],
                "completed_total": 0
            }

        city_groups[city]["doctors"].append(doctor_summary)
        city_groups[city]["completed_total"] += completed

    # Step 5: Format final output
    result = []
    for city, data in sorted(city_groups.items()):
        doctor_list = data["doctors"]
        avg_completed = round(data["completed_total"] / len(doctor_list), 1) if doctor_list else 0.0

        result.append({
            "city": city,
            "doctors": doctor_list,
            "average_completed": avg_completed
        })

    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)
