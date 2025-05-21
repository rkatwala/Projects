#!/usr/bin/env python3
import sys
import re

def split_sentences(text):
    """
    Split `text` into sentences on any of the delimiters: . ? !
    A delimiter is kept at the end of each sentence.
    """
    # The regex looks for a sequence of characters ending in . ? or !
    # (?<=...) is a lookbehind to include the delimiter in the split.
    # \s+ matches the following whitespace that we split on.
    pattern = r'(?<=[\.\?\!])\s+'
    # Use re.split to break on that whitespace, keeping punctuation
    parts = re.split(pattern, text)
    # Strip leading/trailing whitespace from each part
    return [p.strip() for p in parts if p.strip()]

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <input.txt>")
        sys.exit(1)

    input_path  = sys.argv[1]
    output_path = 'solution.txt'

    # Read the entire input file
    with open(input_path, 'r', encoding='utf-8') as f:
        text = f.read()

    # Split into sentences using our regex-based function
    sentences = split_sentences(text)

    # Write each sentence on its own line in solution.txt
    with open(output_path, 'w', encoding='utf-8') as f:
        for sent in sentences:
            f.write(sent + '\n')

    print(f"Wrote {len(sentences)} sentences to {output_path}")

if __name__ == '__main__':
    main()

