# TODO

import cs50
import sys

def main():
    Text = cs50.get_string("Enter the text: ")

    L = count_letters(Text)
    W = count_words(Text)
    S = count_sentences(Text)

    index = 0.0588 * (100 * L / W) - 0.296 * (100 * S / W) - 15.8

    if index >= 16:
        print("Grade 16+")

    elif index <= 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(index)}")

def count_letters(Text):
    # Initialize letters to 0
    letters = 0

    for letter in Text:
        if letter.isalpha():
            letters += 1
    return letters

def count_words(Text):
    # Split the text into words and return the number of words
    words = len(Text.split())

    return words


def count_sentences(Text):
    # Initialize sentence
    sentences = 0

    for char in Text:
        if char in ["!", "?", "."]:
            sentences += 1
    return sentences

if __name__ == "__main__":
    main()
