from flask import Flask, jsonify
import requests


app = Flask(__name__)

@app.route('/type-summary/<string:pokemon_type>', methods=['GET'])
def summary(pokemon_type):
    limit = request.args.get("limit", default=20, type=int)

    try:
        url = f"https://pokeapi.co/api/v2/type/{pokemon_type.lower()}"
        res = requests.get(url, timeout=5)
        res.raise_for_status()
        types = res.json()
    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"failed to fetch list: {str(e)}"}), 500

    sol = {}
    final = []

    for pokemon in types["pokemon"][:limit]:
        shortcut = pokemon["pokemon"]
        name = pokemon["pokemon"]["name"]

        url = shortcut["url"]

        try:
            res = requests.get(url, timeout=5)
            res.raise_for_status()
            mon = res.json()

        except requests.exceptions.RequestException as e:
            return jsonify({"error": f"failed to fetch list:{str(e)}"}), 500
        sol[name] = {}
        sol[name]["height"] = mon["height"]
        sol[name]["weight"] = mon["weight"]
        sol[name]["ability_count"] = len(mon["abilities"])
        final.append(sol)

    return jsonify(final)


if __name__== '__main__':
    app.run(debug=True)


    
                                         

            
