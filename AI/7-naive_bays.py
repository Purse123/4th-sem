import nltk
from nltk.classify import NaiveBayesClassifier
from nltk.corpus import names
import random

# Sample dataset
training_data = [
    ("Win money now", "spam"),
    ("Claim your free prize", "spam"),
    ("Call now to win", "spam"),
    ("Congratulations, you have won", "spam"),
    ("Are we still meeting today?", "ham"),
    ("Let’s have lunch tomorrow", "ham"),
    ("Can you send me the report?", "ham"),
    ("I will call you later", "ham")
]

# Feature extractor
def extract_features(words):
    return {word.lower(): True for word in words.split()}

# Prepare training set
training_set = [(extract_features(text), label) for (text, label) in training_data]

# Train Naive Bayes classifier
classifier = NaiveBayesClassifier.train(training_set)

# Test with user input
msg = input("Enter a message: ")
features = extract_features(msg)
prediction = classifier.classify(features)

print(f"Message: {msg}")
print(f"Classification: {prediction}")
