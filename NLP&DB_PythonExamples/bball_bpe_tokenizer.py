# This script will:
# 1. Recreate the "basketball_sample.txt" file with the 100 facts.
# 2. Train a BPE model (with a limited number of merges) on that file.
# 3. Tokenize the first line ("Basketball Fact #1: ...") using the learned merges.
# Along the way, comments explain each step.

import re
from collections import Counter

# 1. Recreate basketball_sample.txt
facts = [
    "Basketball Fact #1: The first game of basketball was played with a soccer ball.",
    # (We only need the first line for tokenization demonstration,
    #  but for training, we'll include all 100 as before)
    "Basketball Fact #2: Dr. James Naismith invented basketball in 1891.",
    "Basketball Fact #3: The original basket was a peach basket hung on a balcony.",
    "Basketball Fact #4: The NBA was founded in 1946 as the BAA.",
    "Basketball Fact #5: The first official NBA game was played on November 1, 1946.",
    "Basketball Fact #6: The Boston Celtics have won the most NBA championships (17).",
    "Basketball Fact #7: Wilt Chamberlain scored 100 points in a single game in 1962.",
    "Basketball Fact #8: The shot clock was introduced in 1954 to speed up play.",
    "Basketball Fact #9: The three-point line debuted in the NBA in 1979.",
    "Basketball Fact #10: Michael Jordan won 6 NBA Finals with the Chicago Bulls.",
    "Basketball Fact #11: The WNBA was founded in 1996.",
    "Basketball Fact #12: Kobe Bryant scored 81 points in a single game in 2006.",
    "Basketball Fact #13: The youngest NBA MVP was Derrick Rose at age 22.",
    "Basketball Fact #14: The tallest player ever was Manute Bol at 7'7\".",
    "Basketball Fact #15: The shortest player ever was Muggsy Bogues at 5'3\".",
    "Basketball Fact #16: Kareem Abdul-Jabbar is the NBA's all-time leading scorer.",
    "Basketball Fact #17: LeBron James has been to 10 straight NBA Finals.",
    "Basketball Fact #18: The Chicago Bulls won 72 games in the 1995-96 season.",
    "Basketball Fact #19: Shaquille O'Neal won 4 NBA championships.",
    "Basketball Fact #20: Hakeem Olajuwon is the only player with 200 blocks and 200 steals in a season.",
    "Basketball Fact #21: The Lakers and Celtics rivalry is the most storied in the NBA.",
    "Basketball Fact #22: The ABA merged with the NBA in 1976.",
    "Basketball Fact #23: Julius Erving popularized the slam dunk.",
    "Basketball Fact #24: The NBA MVP trophy is named after Michael Jordan.",
    "Basketball Fact #25: Dirk Nowitzki is the highest-scoring foreign-born player.",
    "Basketball Fact #26: The Lakers moved from Minneapolis to Los Angeles in 1960.",
    "Basketball Fact #27: Playoffs expanded to 16 teams in 1984.",
    "Basketball Fact #28: The Finals MVP award was first given in 1969.",
    "Basketball Fact #29: Bill Russell won 11 championships in 13 seasons.",
    "Basketball Fact #30: The slam dunk contest began in 1976.",
    "Basketball Fact #31: The NBA introduced instant replay in 2002.",
    "Basketball Fact #32: The NBA All-Star Game started in 1951.",
    "Basketball Fact #33: The 24-second shot clock was invented by Danny Biasone.",
    "Basketball Fact #34: The U.S. won the first Olympic gold in basketball in 1936.",
    "Basketball Fact #35: Kareem's skyhook is one of the most unstoppable shots.",
    "Basketball Fact #36: The “Triangle Offense” was popularized by Phil Jackson.",
    "Basketball Fact #37: The Toronto Raptors are Canada's only NBA team.",
    "Basketball Fact #38: The Spurs have the highest regular-season win percentage since 1997.",
    "Basketball Fact #39: The NBA plays an 82-game regular season.",
    "Basketball Fact #40: Bob Cousy was known as “The Houdini of the Hardwood.”",
    "Basketball Fact #41: The Harlem Globetrotters formed in 1926.",
    "Basketball Fact #42: The first basketball hoops had closed bottoms.",
    "Basketball Fact #43: The NCAA men’s tournament is called March Madness.",
    "Basketball Fact #44: Bill Walton won NBA Finals MVP in 1977.",
    "Basketball Fact #45: The first women's college game was played in 1892.",
    "Basketball Fact #46: Oscar Robertson averaged a triple-double in 1961-62.",
    "Basketball Fact #47: The Dream Team dominated the 1992 Olympics.",
    "Basketball Fact #48: The Phoenix Suns lost the longest NBA Finals in games (7).",
    "Basketball Fact #49: James Naismith originally used 13 rules for the game.",
    "Basketball Fact #50: The Miami Heat won back-to-back titles in 2012 and 2013.",
    "Basketball Fact #51: Stephen Curry shattered the single-season 3PT record in 2015-16.",
    "Basketball Fact #52: The dunk was illegal in NCAA from 1967 to 1976.",
    "Basketball Fact #53: The NBA G League began in 2001 as the NBDL.",
    "Basketball Fact #54: Pau Gasol won 2 NBA championships with the Lakers.",
    "Basketball Fact #55: The NBA Finals trophy is named the Larry O’Brien Trophy.",
    "Basketball Fact #56: Dennis Rodman led the league in rebounds for 7 consecutive seasons.",
    "Basketball Fact #57: The NBA Draft Lottery was introduced in 1985.",
    "Basketball Fact #58: Allen Iverson was known for his crossover dribble.",
    "Basketball Fact #59: The Seattle SuperSonics relocated to become the Oklahoma City Thunder.",
    "Basketball Fact #60: Dražen Petrović was the first European to lead the NBA in scoring.",
    "Basketball Fact #61: The shot clock was introduced to prevent stalling.",
    "Basketball Fact #62: The NBA has 30 teams split into 2 conferences.",
    "Basketball Fact #63: Fox Sports and ESPN share national TV rights in the U.S.",
    "Basketball Fact #64: The “Hack-a-Shaq” strategy targets poor free-throw shooters.",
    "Basketball Fact #65: Yao Ming was the first Chinese player in the NBA draft lottery.",
    "Basketball Fact #66: The shortest player in NBA history was Muggsy Bogues.",
    "Basketball Fact #67: LeBron is the first player with 30,000 points, 8,000 rebounds, and 8,000 assists.",
    "Basketball Fact #68: RJ Barrett was drafted 3rd overall in 2019.",
    "Basketball Fact #69: The NBA Play-In Tournament began in 2021.",
    "Basketball Fact #70: The San Antonio Spurs won 5 championships between 1999 and 2014.",
    "Basketball Fact #71: The NBA uses Spalding basketballs.",
    "Basketball Fact #72: The first televised NBA game was in 1940.",
    "Basketball Fact #73: The Indiana Pacers dominated the ABA before the merger.",
    "Basketball Fact #74: Klay Thompson once scored 37 points in a single quarter.",
    "Basketball Fact #75: Reggie Miller scored 8 points in 9 seconds in 1995.",
    "Basketball Fact #76: NBA players’ peak salary was Calvin Murphy’s $8 million in 1983.",
    "Basketball Fact #77: The first slam dunk by a woman in NCAA was in 2002.",
    "Basketball Fact #78: Muggsy Bogues blocked Michael Jordan in 1997.",
    "Basketball Fact #79: The NCAA Women’s Final Four is growing in popularity.",
    "Basketball Fact #80: The EuroLeague is Europe's top club competition.",
    "Basketball Fact #81: Dirk Nowitzki is the highest-scoring foreign-born player in NBA history.",
    "Basketball Fact #82: Giannis Antetokounmpo won MVP in 2019 and 2020.",
    "Basketball Fact #83: Luka Dončić was drafted 3rd overall in 2018.",
    "Basketball Fact #84: Nikola Jokić won back-to-back MVP in 2021 and 2022.",
    "Basketball Fact #85: The Harlem Globetrotters once beat an NBA team (Rochester Royals).",
    "Basketball Fact #86: The NBA All-Star weekend features a celebrity game.",
    "Basketball Fact #87: Zion Williamson was the number-one pick in 2019.",
    "Basketball Fact #88: The NCAA introduced the 3-point line in 1986.",
    "Basketball Fact #89: The NBA's “Bubble” season was played in Orlando in 2020.",
    "Basketball Fact #90: The WNBA MVP trophy is named after Kim Perrot.",
    "Basketball Fact #91: The FIBA World Cup occurs every 4 years.",
    "Basketball Fact #92: Basketball became an Olympic sport in 1936.",
    "Basketball Fact #93: The Portsmouth Invitational showcases NCAA seniors.",
    "Basketball Fact #94: Shannon Miller dunked in an exhibition in 1999.",
    "Basketball Fact #95: The Basketball Hall of Fame is in Springfield, Massachusetts.",
    "Basketball Fact #96: Oscar Schmidt holds the record for most points in an international career.",
    "Basketball Fact #97: The Naismith Memorial Basketball Hall of Fame opened in 1959.",
    "Basketball Fact #98: John Stockton holds the all-time NBA assist record.",
    "Basketball Fact #99: Kareem Abdul-Jabbar's skyhook shot was nearly impossible to block.",
    "Basketball Fact #100: The NBA introduced coach’s challenges in 2019."
]

with open("basketball_sample.txt", "w", encoding="utf-8") as f:
    for fact in facts:
        f.write(fact + "\n")


# 2. BPE training functions (same as before):
def load_corpus(file_path):
    vocab = Counter()
    with open(file_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip().lower()
            if not line:
                continue
            words = line.split()
            for word in words:
                symbols = list(word) + ["</w>"]
                vocab[tuple(symbols)] += 1
    return vocab

def get_pair_frequencies(vocab):
    pairs = Counter()
    for symbols, freq in vocab.items():
        for i in range(len(symbols) - 1):
            pair = (symbols[i], symbols[i+1])
            pairs[pair] += freq
    return pairs

def merge_pair_in_vocab(pair_to_merge, vocab):
    merged_sym = ''.join(pair_to_merge)
    new_vocab = Counter()
    bigram = re.escape(pair_to_merge[0]) + r'\s+' + re.escape(pair_to_merge[1])
    pattern = re.compile(r'(?<!\S)' + bigram + r'(?!\S)')
    for symbols, freq in vocab.items():
        symbol_str = ' '.join(symbols)
        new_symbol_str = pattern.sub(merged_sym, symbol_str)
        new_symbols = tuple(new_symbol_str.split())
        new_vocab[new_symbols] += freq
    return new_vocab

def train_bpe(vocab, num_merges):
    merges = []
    for _ in range(num_merges):
        pair_freqs = get_pair_frequencies(vocab)
        if not pair_freqs:
            break
        best_pair, best_freq = pair_freqs.most_common(1)[0]
        if best_freq < 1:
            break
        merges.append(best_pair)
        vocab = merge_pair_in_vocab(best_pair, vocab)
    return merges, vocab

# 3. Perform BPE training on the full corpus with a limited number of merges:
NUM_MERGES = 500  # adjust as needed
vocab = load_corpus("basketball_sample.txt")
merges, final_vocab = train_bpe(vocab, NUM_MERGES)

# 4. Save merge rules to "bpe_merges.txt" for inspection (optional):
with open("bpe_merges.txt", "w", encoding="utf-8") as f:
    for a, b in merges:
        f.write(f"{a} {b}\n")


# 5. Tokenize the first line using the learned merges:

# Function to tokenize a single word given the merges
def tokenize_word(word, merges):
    """
    Tokenize 'word' (string) into BPE subword tokens using the merge rules (in order).
    Returns a list of subword tokens.
    """
    # Initialize as a list of characters plus end-of-word marker
    symbols = list(word.lower()) + ["</w>"]
    
    # We'll repeatedly apply merges in the given order, if the pair exists
    for merge in merges:
        i = 0
        while i < len(symbols) - 1:
            # If symbols[i], symbols[i+1] matches the merge rule, merge them
            if (symbols[i], symbols[i+1]) == merge:
                symbols[i] = symbols[i] + symbols[i+1]
                del symbols[i+1]
                # After a merge, stay at the same index i to catch cascading merges
            else:
                i += 1
    
    # Remove the end-of-word marker before returning tokens
    tokens = [sym for sym in symbols if sym != "</w>"]
    return tokens

# Read the first line from the file:
with open("basketball_sample.txt", "r", encoding="utf-8") as f:
    first_line = f.readline().strip()

# Split the first line into words and tokenize each one
tokenized_first_line = []
for word in first_line.split():
    subwords = tokenize_word(word, merges)
    tokenized_first_line.append(subwords)

# 6. Print results:
print("First line:", first_line)
print("\nTokenization (each word -> list of BPE subwords):")
for word, subwords in zip(first_line.split(), tokenized_first_line):
    print(f"{word}  →  {subwords}")
