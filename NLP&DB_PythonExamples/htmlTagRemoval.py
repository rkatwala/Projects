import sys
from html.parser import HTMLParser

class MLStripper(HTMLParser):
    """
    Subclass HTMLParser to collect text data and ignore tags.
    """
    def __init__(self):
        super().__init__()
        self.reset()           # initialize base parser
        self.fed = []          # list to collect text fragments

    def handle_data(self, data):
        """
        Called for each chunk of text between tags.
        """
        self.fed.append(data)

    def get_data(self):
        """
        Join all collected text into one string.
        """
        return ''.join(self.fed)

def strip_tags(html):
    """
    Strip HTML tags from the `html` string and return plain text.
    """
    s = MLStripper()
    s.feed(html)
    return s.get_data()

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input.html> <output.txt>")
        sys.exit(1)

    in_path, out_path = sys.argv[1], sys.argv[2]

    # Read the HTML file
    with open(in_path, 'r', encoding='utf-8') as f:
        html_content = f.read()

    # Strip tags
    text = strip_tags(html_content)

    # Optionally, collapse multiple whitespace/newlines:
    # import re
    # text = re.sub(r'\s+', ' ', text).strip()

    # Write plain text out
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write(text)

    print(f"Stripped HTML tags from {in_path} → {out_path}")

if __name__ == '__main__':
    main()

