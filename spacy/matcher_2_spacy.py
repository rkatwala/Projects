doc1 = nlp("You read this book")
doc2 = nlp("I will book my ticket")

pattern = [{'TEXT': 'book', 'POS': 'NOUN'}]

# Initialize the matcher with the shared vocab
matcher = Matcher(nlp.vocab)
matcher.add('rule_2', [ pattern])

matches = matcher(doc1)
matches
matches=matcher(doc2)
matches
