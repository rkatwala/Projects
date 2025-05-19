import os              # OS utilities (not strictly needed here but kept for parity)
import sys             # For command‐line argument access
import re              # Regular expressions
import sqlite3         # SQLite3 database adapter

# Path to your SQLite database file; change as needed
DB_PATH = 'concepts.db'

def get_text(filename):
    """
    Read the entire contents of a text file.
    """
    with open(filename, 'r') as f:
        text = f.read()
    return text

def get_synonyms(imuid):
    """
    Query the SQLite database for synonyms of a given concept ID.
    """
    # Connect to the SQLite database file
    connection = sqlite3.connect(DB_PATH)
    cursor = connection.cursor()

    # Parameterized query: use ? placeholder for safety
    cursor.execute(
        "SELECT STR FROM CONCEPT_SYNONYMS WHERE concept_id = ?",
        (imuid,)
    )

    # fetchall() returns a list of rows; each row is a tuple
    rows = cursor.fetchall()
    synonyms = [row[0] for row in rows]  # extract the STR from each row

    # Clean up
    cursor.close()
    connection.close()

    return synonyms

def get_regex_pattern(imuid):
    """
    Build a compiled regular expression to match any synonym for the given ID.
    """
    synonyms = get_synonyms(imuid)
    # Escape any regex‐special characters in the synonyms themselves
    escaped = [re.escape(s) for s in synonyms]
    # Join them with '|' to form an alternation group
    regex = '(' + '|'.join(escaped) + ')'
    print("Compiled regex:", regex)
    return re.compile(regex, re.IGNORECASE)

def annotate(text, pattern):
    """
    Find all occurrences of the pattern in the text and record their spans.
    """
    annotations = []
    for m in pattern.finditer(text):
        annotations.append([m.start(), m.end()])
    return annotations

def write_html(text, annotations, html_filename):
    """
    Generate an HTML file that highlights each matched span in red.
    """
    with open(html_filename, 'w') as f:
        f.write('<html><body>')
        i = 0
        for start, end in annotations:
            # write any text before this match
            if start > i:
                f.write(text[i:start].replace('\n', '<br>'))
            # highlight the matched text
            f.write('<font color="#CC0000">')
            f.write(text[start:end])
            f.write('</font>')
            i = end
        # write any remaining text
        if i < len(text):
            f.write(text[i:].replace('\n', '<br>'))
        f.write('</body></html>')

def main():
    """
    Entry point: parse args, perform annotation, and write HTML.
    """
    # Expect two args: 1) concept ID, 2) input text filename
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <concept_id> <textfile>")
        sys.exit(1)

    imuid = int(sys.argv[1])
    filename = sys.argv[2]
    html_filename = f"{os.path.splitext(filename)[0]}-{imuid}.html"

    print("Annotating", filename, "for concept", imuid, "→", html_filename)

    text = get_text(filename)
    pattern = get_regex_pattern(imuid)
    annotations = annotate(text, pattern)
    write_html(text, annotations, html_filename)

if __name__ == '__main__':
    main()

