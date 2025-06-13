from flask import Flask, jsonify
import requests


app = Flask(__name__)


@app.route('/region-stats', methods=['GET'])
def region():
    try:
        url = 'https://restcountries.com/v3.1/all?fields=name,region,population,area,languages'
        region_res = requests.get(url, timeout=5)
        region_res.raise_for_status()
        regions = region_res.json()

    except requests.exceptions.RequestException as e:
        return jsonify({"error": f"Failed to fetch regions: {str(e)}"}), 500


    region_groups = {}

        
    for arr in regions:
        if arr.get("region") not in region_groups:
            region_groups[arr.get("region")] = {
                "pop": 0,
                "countries":0,
                "languages": {},
                "area": 0
            }

        region_groups[arr.get("region")]["pop"] = region_groups[arr.get("region")]["pop"] + arr["population"]
        region_groups[arr.get("region")]["area"] = region_groups[arr.get("region")]["pop"] / (region_groups[arr.get("region")]["area"] + arr["area"])
        region_groups[arr.get("region")]["countries"] = region_groups[arr.get("region")]["countries"] + 1
        for lang in arr.get("languages", {}).values():
            if lang not in region_groups[arr.get("region")]["languages"]:
                region_groups[arr.get("region")]["languages"][lang] = 1
            else:
                region_groups[arr.get("region")]["languages"][lang] += 1




    result = []

    for reg, stats in region_groups.items():
        top_langs = sorted(
            stats["languages"].items(),
            key=lambda x: x[1],
            reverse=True
        )[:3]

        top_language_names = [lang[0] for lang in top_langs]

        result.append({
            "region": reg,
            "population": stats["pop"],
            "area": round(stats["area"], 1),
            "countries": stats["countries"],
            "top_languages": top_language_names
        })

    return jsonify(result)



if __name__ == '__main__':
    app.run(debug=True)

        
                    


            
        
