from flask import Flask, jsonify, request
import requests

app = Flask(__name__)

@app.route("/brewery", methods=["GET"])
def route():
    

    try:
        url = "https://api.openbrewerydb.org/v1/breweries"
        res = requests.get(url, timeout=5)
        res.raise_for_status()
        breweries = res.json()

    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"failed to fetch list: {str(e)}"}), 500

    '''
        name

        brewery_type

        city

        state

        website_url
    '''
                       
    limit = request.args.get("limit", default=30, type=int)
    filters = request.args.get("type", default="")
    
    
    sol = []
    for brewery in breweries:

        if filters!="" and filters!=brewery.get("brewery_type"):
            continue
        sol.append({
            "name": brewery.get("name"),
            "brewery_type": brewery.get("brewery_type"),
            "city": brewery.get("city"),
            "state": brewery.get("state"),
            "url": brewery.get("url")
            })

    sol.sort(key=lambda x: x["city"], reverse=False)
    return jsonify(sol[:limit])



@app.route("/brewery/<string:brewery_id>", methods=['GET'])
def single(brewery_id):
    try:
        url = f"https://api.openbrewerydb.org/v1/breweries/{brewery_id}"
        res = requests.get(url, timeout=5)
        res.raise_for_status()
        info = res.json()

    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"failed to fetch list: {str(e)}"}), 500


    '''
    name

    brewery_type

    street

    city

    state

    phone

    website_url
    '''


    sol = []
    sol.append({
        'name': info.get("name"),
        'brewery_type': info.get("brewery_type"),
        'address': f"{info.get('street')}, {info.get('city')}, {info.get('state')}",
        'phone': info.get("phone"),
        'url': info.get("website_url")
    })


    return jsonify(sol)
        


if __name__== '__main__':
    app.run(debug=True)
  
        





    

    
               
