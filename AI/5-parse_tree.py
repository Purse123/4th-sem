#
# dependency: [ nltk ]
#

import nltk
# print(dir(nltk))
from nltk import CFG
# print(help(CFG))

nltk.download('punkt')          # punkt tokenizer model download

grammar = CFG.fromstring("""
  S -> NP VP
  NP -> Det N | Det N PP
  VP -> V NP | V NP PP | V
  PP -> P NP
  Det -> 'the' | 'a'
  N -> 'cat' | 'dog' | 'park' | 'telescope'
  V -> 'saw' | 'walked' | 'slept'
  P -> 'in' | 'with'
""")

parser = nltk.ChartParser(grammar)

# Take sentence input from user
sentence = input("Enter a sentence: ").lower()
tokens = nltk.word_tokenize(sentence)

# Parse and draw tree
for tree in parser.parse(tokens):
    print(tree)         # Print tree in text form
    tree.pretty_print() # Pretty print in console
    tree.draw()         # Opens a window with the parse tree
