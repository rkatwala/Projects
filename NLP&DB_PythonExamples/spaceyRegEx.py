#!/usr/bin/env python3
import sys
import re
import spacy

def find_regex_matches(text, pattern):
    """
    Return a list of tuples (match_text, start, end) for every regex match in `text`.
    """
    return [(m.group(0), m.start(), m.end()) for m in pattern.finditer(text)]

def main():
    # Expect exactly two arguments: the raw regex (in quotes) and the input filename
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <regex> <input.txt>")
        sys.exit(1)

    raw_pattern = sys.argv[1]   # e.g. r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b"
    infile       = sys.argv[2]   # e.g. sample.txt

    # Compile the user-supplied regex, exiting on errors
    try:
        pattern = re.compile(raw_pattern)
    except re.error as e:
        print(f"Invalid regex `{raw_pattern}`:\n  {e}")
        sys.exit(1)

    # Load spaCy English model (so we can split into sentences)
    # Note: you must have run `python -m spacy download en_core_web_sm` first
    nlp = spacy.load("en_core_web_sm")

    # Read the entire input file into one string
    with open(infile, 'r', encoding='utf-8') as f:
        text = f.read()

    # Process text with spaCy to get sentences
    doc = nlp(text)

    # Find all matches in the raw text
    matches = find_regex_matches(text, pattern)
    if not matches:
        print("No matches found.")
        return

    # For each match, locate and print its sentence context
    for match_text, start, end in matches:
        # Find the first sentence whose char span contains the match start
        sent = next(
            (s for s in doc.sents if s.start_char <= start < s.end_char),
            None
        )
        context = sent.text.strip() if sent else text[max(0, start-30):end+30]
        print(f"Match `{match_text}` at [{start}:{end}]")
        print(f"  → Context: {context}\n")

if __name__ == "__main__":
    main()

