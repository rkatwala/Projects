#!/usr/bin/env bash
# init_books.sh

DB_FILE="books.db"

# Remove any existing DB for a clean start
rm -rf "$DB_FILE"

# Execute the SQL commands
sqlite3 "$DB_FILE" <<'EOF'
-- 1. Create the BOOKS table
CREATE TABLE BOOKS (
  name TEXT NOT NULL,
  price REAL NOT NULL,
  qty   INTEGER NOT NULL
);

-- 2. Insert 10 sample books
INSERT INTO BOOKS (name, price, qty) VALUES
  ('The Great Gatsby',      10.99,  3),
  ('1984',                   8.50,   5),
  ('To Kill a Mockingbird', 12.00,  2),
  ('A Brief History of Time',15.95,  4),
  ('The Art of War',         7.99,   7),
  ('Clean Code',             32.99,  1),
  ('The Pragmatic Programmer',28.50, 2),
  ('Deep Learning',          59.99,  1),
  ('Introduction to Algorithms',99.95,1);

-- 3. (Optional) Verify contents
SELECT rowid AS id, * FROM BOOKS;
EOF

echo "Database '$DB_FILE' initialized with 10 sample books."
