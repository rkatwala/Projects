from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)
DATABASE = "test.db"

@app.route('/users', methods=['GET'])
def get_users():
    try:
        conn = sqlite3.connect(DATABASE)
        conn.row_factory = sqlite3.Row
        cursor = conn.cursor()

        # Create sample table and insert data (for demo purposes)
        cursor.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)")
        cursor.execute("INSERT INTO users (name, age) VALUES ('Alice', 30)")
        cursor.execute("INSERT INTO users (name, age) VALUES ('Bob', 25)")
        conn.commit()

        # Query data
        cursor.execute("SELECT * FROM users")
        rows = cursor.fetchall()

        # Convert rows to list of dicts
        users = [dict(row) for row in rows]

        return jsonify(users)

    except Exception as e:
        return jsonify({"error": str(e)}), 500

    finally:
        conn.close()

if __name__ == "__main__":
    app.run(debug=True)
