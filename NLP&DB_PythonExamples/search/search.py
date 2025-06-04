import os
import json
import re
import sys

from lunr import lunr
from lunr.index import Index

def load_or_build_index():
    """
    Loads an existing index.json if it exists; otherwise, builds a new index
    by reading all files in the current directory (splitting basketball_sample.txt
    into separate docs, one per nonempty line). Returns (idx, is_new).
    """
    if os.path.exists("index.json"):
        with open("index.json", "r", encoding="utf-8") as f:
            serialized = json.load(f)
        idx = Index.load(serialized)
        print("Loaded existing index.json\n")
        return idx, False
    else:
        docs = []
        for filename in os.listdir("."):
            if not os.path.isfile(filename) or filename == "index.json":
                continue

            if filename == "basketball_sample.txt":
                with open(filename, "r", encoding="utf-8", errors="ignore") as f:
                    lines = f.read().splitlines()

                for i, line in enumerate(lines, start=1):
                    if not line.strip():
                        continue
                    docs.append({
                        "id": f"basketball_{i}",
                        "title": f"basketball_{i}",
                        "body": line
                    })
            else:
                with open(filename, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                docs.append({
                    "id": filename,
                    "title": filename,
                    "body": content
                })

        idx = lunr(
            ref="id",
            fields=("title", "body"),
            documents=docs
        )

        serialized = idx.serialize()
        with open("index.json", "w", encoding="utf-8") as out:
            json.dump(serialized, out, ensure_ascii=False, indent=2)

        print("Built a new index and wrote to index.json\n")
        return idx, True

def build_doc_text_map():
    """
    Creates and returns a dictionary mapping each doc ID to its full text (body).
    For basketball_N docs, pulls the specific line from basketball_sample.txt.
    For other docs, reads the entire file with that filename.
    """
    doc_texts = {}

    # First, check if basketball_sample.txt exists
    basketball_lines = []
    if os.path.exists("basketball_sample.txt"):
        with open("basketball_sample.txt", "r", encoding="utf-8", errors="ignore") as f:
            basketball_lines = f.read().splitlines()

    for filename in os.listdir("."):
        if not os.path.isfile(filename) or filename == "index.json":
            continue

        if filename == "basketball_sample.txt":
            # Map each basketball_<i> ID to the corresponding nonempty line
            idx_line = 1
            for line in basketball_lines:
                if not line.strip():
                    continue
                doc_id = f"basketball_{idx_line}"
                doc_texts[doc_id] = line
                idx_line += 1
        else:
            with open(filename, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read()
            doc_texts[filename] = content

    return doc_texts

def extract_sentences_containing_terms(text, terms):
    """
    Splits the given text into sentences (on . ? !), then returns a list of
    sentences that contain at least one of the terms (case-insensitive).
    """
    sentences = re.split(r'(?<=[\.\?\!])\s+', text)
    matched = []
    lower_sentences = [s.lower() for s in sentences]

    for term in terms:
        term_lower = term.lower()
        for i, s_lower in enumerate(lower_sentences):
            if term_lower in s_lower and sentences[i].strip() not in matched:
                matched.append(sentences[i].strip())
    return matched

# ---- Main Execution ----

idx, is_new = load_or_build_index()
doc_texts = build_doc_text_map()

# 2) Run a query composed from command-line arguments
query = " ".join(sys.argv[1:]).strip()
if not query:
    print("Please supply at least one search term, e.g.:")
    print("    python search.py basketball NBA")
    sys.exit(1)

results = idx.search(query)
print(f"Search results for “{query}”:\n")

# Determine which key Lunr uses for match data
sample_hit = results[0] if results else {}
match_data_key = "match_data" if "match_data" in sample_hit else "matchData"

for hit in results:
    doc_id = hit["ref"]
    score = hit.get("score", 0)

    # Extract matched terms from the hit's match data.
    # The MatchData object may expose a .metadata attribute whose keys are the terms.
    raw_md = hit.get(match_data_key, {})
    if isinstance(raw_md, dict):
        matched_terms = list(raw_md.keys())
    elif hasattr(raw_md, "metadata"):
        matched_terms = list(raw_md.metadata.keys())
    else:
        matched_terms = []

    # Fetch the full text (body) for this doc ID
    full_text = doc_texts.get(doc_id, "")
    if not full_text:
        sentences_to_print = []
    else:
        # Extract sentences containing any of the matched terms
        sentences_to_print = extract_sentences_containing_terms(full_text, matched_terms)

    print(f"doc={doc_id}\tscore={score:.2f}")
    if sentences_to_print:
        for sentence in sentences_to_print:
            print(f"  → {sentence}")
    else:
        print("  → (no matching sentence found)")
    print()

print("Index is now available in index.json")
