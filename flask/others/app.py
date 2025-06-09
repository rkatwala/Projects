from flask import Flask, jsonify, render_template, abort
import sqlite3
from pathlib import Path

app = Flask(__name__, template_folder='templates')
DB_PATH = Path(__file__).parent / 'books.db'


def get_db_connection():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn


@app.route('/books')
def list_books():
    """
    List all books in the database as JSON and HTML.
    """
    conn = get_db_connection()
    books = conn.execute('SELECT rowid AS id, name, price, qty FROM BOOKS').fetchall()
    conn.close()
    # If HTML requested, render list template; otherwise return JSON
    return render_template('book_list.html', books=books)


@app.route('/books/<int:book_id>')
def book_detail(book_id):
    """
    Show information for a single book by ID.
    """
    conn = get_db_connection()
    book = conn.execute(
        'SELECT rowid AS id, name, price, qty FROM BOOKS WHERE rowid = ?',
        (book_id,)
    ).fetchone()
    conn.close()

    if book is None:
        abort(404, description="Book not found")

    return render_template('book_detail.html', book=book)


@app.errorhandler(404)
def not_found(error):
    return render_template('404.html', message=error.description), 404


if __name__ == '__main__':
    app.run(debug=True)

