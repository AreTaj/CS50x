

def count_letters(text):
    letters = 0
    for char in text:
        if char.isalpha():
            letters += 1
    return letters


def count_words(text):
    words = 1
    for char in text:
        if (char == ' '):
            words += 1
    return words


def count_sentences(text):
    sentences = 0
    for char in text:
        if char == '.' or char == '!' or char == '?':
            sentences += 1
    return sentences


def main():
    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1\n")

    elif (index > 16):
        print("Grade 16+\n")

    else:
        print(f"Grade {index}\n")


if __name__ == "__main__":
    main()
