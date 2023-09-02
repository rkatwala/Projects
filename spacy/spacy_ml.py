import spacy
nlp = spacy.load("en_core_web_sm")

text = "The rain in Spain falls mainly on the plain."
doc = nlp(text)

for token in doc:
    print(token.text, token.lemma_, token.pos_, token.is_stop)

import pandas as pd
cols = ("text", "lemma", "POS", "explain", "stopword")
rows = []
for t in doc:
    row = [t.text, t.lemma_, t.pos_, spacy.explain(t.pos_), t.is_stop]
    rows.append(row)
df = pd.DataFrame(rows, columns=cols)
print(df)

from spacy import displacy
displacy.render(doc, style="dep")

text = "We were all out at the zoo one day, I was doing some acting, walking on the railing of the gorilla exhibit. I fell in.Everyone screamed and Tommy jumped in after me, forgetting that he had blueberries in his front pocket. The gorillas just went wild."
doc = nlp(text)
for sent in doc.sents:
    print(">", sent)

for sent in doc.sents:
    print(">", sent.start, sent.end)

doc[48:54]

token = doc[51]
print(token.text, token.lemma_, token.pos_)

import sys
import warnings
warnings.filterwarnings("ignore")


from bs4 import BeautifulSoup
import requests
import traceback
def get_text (url):
    buf = []
    try:
        soup = BeautifulSoup(requests.get(url).text, "html.parser")
        for p in soup.find_all("p"):
            buf.append(p.get_text())
        return "".join(buf)
    except:
        print(traceback.format_exc())
        sys.exit(-1)


lic = {}lic["mit"] = nlp(get_text("https://opensource.org/licenses/MIT"))
lic["asl"] = nlp(get_text("https://opensource.org/licenses/Apache-20"))
lic["bsd"] = nlp(get_text("https://opensource.org/licenses/BSD-3-Clause"))

for sent in lic["bsd"].sents:
    print(">", sent)


, parse, then compare similarity metrics among them:

pairs = [
    ["mit", "asl"],
    ["asl", "bsd"],
    ["bsd", "mit"]]

for a, b in pairs:
    print(a, b, lic[a].similarity(lic[b]))

text = "Steve Jobs and Steve Wozniak incorporated Apple Computer on January 3, 1977, in Cupertino, California."
doc = nlp(text)

for chunk in doc.noun_chunks:
    print(chunk.text)


for ent in doc.ents:
    print(ent.text, ent.label_)

displacy.render(doc, style="ent")

import nltk
nltk.download("wordnet")

from spacy_wordnet.wordnet_annotator import WordnetAnnotator
print("before", nlp.pipe_names)
if "WordnetAnnotator" not in nlp.pipe_names:
    nlp.add_pipe(WordnetAnnotator(nlp.lang), after="tagger")print("after", nlp.pipe_names)


token = nlp("withdraw")[0]
token._.wordnet.synsets()

["astronomy","school","telegraphy","industry","psychology","ethnology","ethnology","administration","school","finance","economy","exchange","banking","commerce","medicine","ethnology","university",
…

to consider NLU results that are within Finance and Banking:

domains = ["finance", "banking"]
sentence = nlp("I want to withdraw 5,000 euros.")

enriched_sent = []

for token in sentence:
    # get synsets within the desired domains
    synsets = token._.wordnet.wordnet_synsets_for_domain(domains)

    if synsets:
        lemmas_for_synset = []

        for s in synsets:
        # get synset variants and add to the enriched sentence
            lemmas_for_synset.extend(s.lemma_names())
            enriched_sent.append("({})".format("|".join(set(lemmas_for_synset))))
    else:
        enriched_sent.append(token.text)
print(" ".join(enriched_sent))

import scattertext as st

if "merge_entities" not in nlp.pipe_names:
    nlp.add_pipe(nlp.create_pipe("merge_entities"))

if "merge_noun_chunks" not in nlp.pipe_names:
    nlp.add_pipe(nlp.create_pipe("merge_noun_chunks"))

convention_df = st.SampleCorpora.ConventionData2012.get_data()
corpus = st.CorpusFromPandas(convention_df, category_col="party", text_col="text", nlp=nlp).build()


html = st.produce_scattertext_explorer(corpus, category="democrat", 
                                       category_name="Democratic",
                                       not_category_name="Republican",
                                       width_in_pixels=1000,
                                       metadata=convention_df["speaker"])

from IPython.display import IFrame

file_name = "foo.html"

with open(file_name, "wb") as f:
    f.write(html.encode("utf-8"))

IFrame(src=file_name, width = 1200, height=700)


