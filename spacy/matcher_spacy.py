import spacy
nlp = spacy.load('en_core_web_sm')

# Import spaCy Matcher
from spacy.matcher import Matcher

# Initialize the matcher with the spaCy vocabulary
matcher = Matcher(nlp.vocab)

doc = nlp("Some people start their day with lemon water")

# Define rule
pattern = [{'TEXT': 'lemon'}, {'TEXT': 'water'}]

# Add rule
matcher.add('rule_1', [pattern])

matches = matcher(doc)
# Extract matched text
for match_id, start, end in matches:
    # Get the matched span
    matched_span = doc[start:end]
    print(matched_span.text)

doc1 = nlp("You read this book")
doc2 = nlp("I will book my ticket")

pattern = [{'TEXT': 'book', 'POS': 'NOUN'}]

# Initialize the matcher with the shared vocab
matcher = Matcher(nlp.vocab)
matcher.add('rule_2', [pattern])
