# Annotate Synonyms in Text with SQLite3

This project provides a simple Python script to annotate occurrences of concept synonyms within a text file. It uses an SQLite3 database to store
`CONCEPT_SYNONYMS` and highlights matches in the output HTML.

## Features

* Stores concept synonyms in an SQLite3 table.
* Builds a case-insensitive regex from all synonyms for a given concept ID.
* Scans a plain text file for matches and records start/end spans.
* Generates an HTML file where matched terms are highlighted in red.

## Prerequisites

* Python 3.x
* SQLite3
* Python modules:

  * `sqlite3` (included with Python)
  * `re`

## Setup

1. **Clone or copy the repository** to your local machine.

2. **Prepare the SQLite database**:

   ```bash
   sqlite3 concepts.db < create_concept_synonyms.sql
   ```

   This will create the `CONCEPT_SYNONYMS` table and insert sample data.

3. **Create a sample text** (e.g. `sample.txt`):

   ```txt
   I love eating an apple every morning.
   Sometimes I prefer a RED APPLE with my cereal.
   Did you know the scientific name is malus domestica?
   Oranges and bananas are delicious too.
   ```

## Usage

Run the annotation script with the concept ID and the text file path:

```bash
python annotate_sqlite.py <concept_id> <textfile>
```

* **`<concept_id>`**: Integer ID of the concept in `CONCEPT_SYNONYMS`.
* **`<textfile>`**: Path to a plain text file to annotate.

For example, to highlight concept `1` in `sample.txt`:

```bash
python annotate_sqlite.py 1 sample.txt
```

This generates an HTML file named `sample-1.html` in the same directory, with all matches highlighted.

## Customization

* **Database Path**: By default, the script connects to `concepts.db` in the current folder. You can modify the `DB_PATH` constant at the top of `annotate_sqlite.py` to point elsewhere.

* **HTML Output**: The output filename is derived from the input file by appending `-<concept_id>.html`. You can change this logic in `main()` if needed.

## Sample Table Script

The file `create_concept_synonyms.sql` contains SQL to create and populate the table:

```sql
DROP TABLE IF EXISTS CONCEPT_SYNONYMS;
CREATE TABLE CONCEPT_SYNONYMS (
  concept_id INTEGER NOT NULL,
  STR        TEXT    NOT NULL
);
-- sample data here...
```

## License

This project is released under the MIT License. Feel free to use, modify, and redistribute as needed.
