import spacy
nlp = spacy.load('en_core_web_sm')

# Create an nlp object
doc = nlp("He went to play basketball")

nlp.pipe_names

Output:['tagger','parser','ner']

# Iterate over the tokens
for token in doc:
    # Print the token and its part-of-speech tag
    print(token.text, "-->", token.pos_)

# Iterate over the tokens
for token in doc:
    # Print the token and its ner 
    print(token.text, "-->", token.norm_)

# Iterate over the tokens
for token in doc:
    # Print the token and its ner 
    print(token.text, "-->", token.dep_)


doc = nlp("Indians spent over $71 billion on clothes in 2018")
 
for ent in doc.ents:
    print(ent.text, ent.label_)
