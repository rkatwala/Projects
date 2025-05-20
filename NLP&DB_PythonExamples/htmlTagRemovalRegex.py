#!/usr/bin/env python3
import sys
import re

def strip_tags_regex(html):
    """
    Remove all HTML tags from the input string by replacing anything
    that looks like <...> with an empty string.
    """
    # First, optionally remove script/style blocks entirely:
    html = re.sub(r'(?is)<(script|style).*?>.*?</\1>', '', html)
    # Then remove all other tags:
    clean = re.sub(r'<[^>]+>', '', html)
    return clean

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input.html> <output.txt>")
        sys.exit(1)

    in_path  = sys.argv[1]
    out_path = sys.argv[2]

    # Read the full HTML file
    with open(in_path, 'r', encoding='utf-8') as f:
        html_content = f.read()

    # Strip tags via regex
    text = strip_tags_regex(html_content)

    # Optionally collapse multiple whitespace/newlines:
    text = re.sub(r'\s+', ' ', text).strip()

    # Write the plain‐text output
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write(text)

    print(f"Stripped HTML tags: {in_path} → {out_path}")

if __name__ == '__main__':
    main()


