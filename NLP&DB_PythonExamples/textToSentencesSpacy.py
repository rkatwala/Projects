#!/usr/bin/env python3
import sys
import spacy

def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <input.txt>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = "solution.txt"

    # Load spaCy English model (make sure you've run: python -m spacy download en_core_web_sm)
    nlp = spacy.load("en_core_web_sm")

    # Read the entire input file
    with open(input_path, "r", encoding="utf-8") as f:
        text = f.read()

    # Process text to get a spaCy Doc (with sentence boundaries)
    doc = nlp(text)

    # Extract sentences
    sentences = [sent.text.strip() for sent in doc.sents if sent.text.strip()]

    # Write each sentence to solution.txt
    with open(output_path, "w", encoding="utf-8") as f:
        for sent in sentences:
            f.write(sent + "\n")

    print(f"Wrote {len(sentences)} sentences to {output_path}")

if __name__ == "__main__":
    main()

