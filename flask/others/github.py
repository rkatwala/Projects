import requests

def get_top_starred_repo(username):
    url = f"https://api.github.com/users/{username}/repos"
    response = requests.get(url)

    if response.status_code != 200:
        print(f"Error: {response.status_code}")
        return None

    repos = response.json()
    if not repos:
        return None

    top_repo = max(repos, key=lambda repo: repo['stargazers_count'])
    return {
        "name": top_repo["name"],
        "stars": top_repo["stargazers_count"]
    }

# Run it
username = "torvalds"
result = get_top_starred_repo(username)
print(result)

