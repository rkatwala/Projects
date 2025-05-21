# Extract Sentences with spaCy

This repository provides a simple Python script (`extract_with_spacy.py`) to extract sentences from a text file using spaCy’s natural language processing.

## Features

* Reads an input text file of arbitrary length.
* Uses spaCy’s pre-trained English model (`en_core_web_sm`) to accurately detect sentence boundaries.
* Writes each extracted sentence on its own line in `solution.txt`.

## Prerequisites

* Python 3.6 or higher
* pip
* spaCy library
* spaCy English model (`en_core_web_sm`)

## Installation

1. (Optional) Create and activate a virtual environment:

   ```bash
   python -m venv venv
   source venv/bin/activate  # Windows: venv\Scripts\activate
   ```
2. Install spaCy:

   ```bash
   pip install spacy
   ```
3. Download the English model:

   ```bash
   python -m spacy download en_core_web_sm
   ```

## Usage

1. Place your input text in a file, e.g., `input.txt`.
2. Run the script:

   ```bash
   python extract_with_spacy.py input.txt
   ```
3. After execution, `solution.txt` will contain one sentence per line.

## Example

Given `input.txt`:

```
SpaCy is an open-source library for NLP. It excels at tokenization, POS tagging, and parsing! Let's extract sentences accurately?
```

Run:

```bash
python extract_with_spacy.py input.txt
```

`solution.txt` will contain:

```
SpaCy is an open-source library for NLP.
It excels at tokenization, POS tagging, and parsing!
Let's extract sentences accurately?
```

## Script: ``'textToSentencesSpacy`.py``

```python
#!/usr/bin/env python3
import sys
import spacy

# Load spaCy English model (ensure you've run: python -m spacy download en_core_web_sm)
nlp = spacy.load("en_core_web_sm")

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <input.txt>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = "solution.txt"

    # Read the entire input file
    with open(input_path, "r", encoding="utf-8") as f:
        text = f.read()

    # Process text to get sentences
    doc = nlp(text)
    sentences = [sent.text.strip() for sent in doc.sents if sent.text.strip()]

    # Write each sentence to solution.txt
    with open(output_path, "w", encoding="utf-8") as f:
        for sent in sentences:
            f.write(sent + "\n")

    print(f"Wrote {len(sentences)} sentences to {output_path}")

if __name__ == "__main__":
    main()
```

## License

MIT License
