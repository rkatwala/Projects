from flask import Flask, jsonify, request
import requests

app = Flask(__name__)

'''
id

symbol

name

current_price

market_cap

price_change_percentage_24h
'''


@app.route("/coins", methods=['GET'])
def coins():
    try:
        url = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd"
        res = requests.get(url, timeout=5)
        res.raise_for_status()
        coins=res.json()

    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"failed to fetch list: {str(e)}"}), 500

    limit=request.args.get("limit", default = len(coins), type=int)
    price = request.args.get("price", default=-1, type=int)
    solution = []
    for coin in coins:
        if price != -1 and coin.get("current_price")< price:
            continue
        solution.append({
            "id": coin.get("id"),
            "symbol": coin.get("symbol"),
            "name": coin.get("name"),
            "current_price": coin.get("current_price"),
            "market_cap": coin.get("market_cap"),
            "price_change_percentage_24h": coin.get("price_change_percentage_24h")
        })


    solution.sort(key=lambda x:x["current_price"], reverse=True)
    return jsonify(solution[:limit])
    

if __name__== '__main__':
    app.run(debug=True)
  
        





    

    
               
