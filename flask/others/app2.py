from flask import Flask, jsonify, abort

import sqlite3

from pathlib import Path
 
app = Flask(__name__)

DB_PATH = Path(__file__).parent / 'books.db'
 
 
def get_db_connection():

    conn = sqlite3.connect(DB_PATH)

    conn.row_factory = sqlite3.Row

    return conn
 
@app.route('/books', methods=['GET'])

def list_books():

    """

    REST endpoint: returns JSON array of all books

    """

    conn = get_db_connection()

    rows = conn.execute('SELECT rowid AS id, name, price, qty FROM BOOKS').fetchall()

    conn.close()

    books = [dict(row) for row in rows]

    return jsonify(books)
 
@app.route('/books/<int:book_id>', methods=['GET'])

def book_detail(book_id):

    """

    REST endpoint: returns JSON object of book by ID

    """

    conn = get_db_connection()

    row = conn.execute(

        'SELECT rowid AS id, name, price, qty FROM BOOKS WHERE rowid = ?',

        (book_id,)

    ).fetchone()

    conn.close()
 
    if row is None:

        abort(404, description='Book not found')
 
    return jsonify(dict(row))
 
@app.errorhandler(404)

def not_found(error):

    response = jsonify({'error': error.description or 'Not found'})

    response.status_code = 404

    return response
 
if __name__ == '__main__':

    app.run(debug=True)

