# Задание  1.  Определить,  сколько  раз  в  тексте  встречается  заданное слово
def count_word_occurrences(text, word):
    return text.lower().split().count(word.lower())


text = "Это пример текста. Этот текст предназначен для проверки текста."
word = "текста"
count = count_word_occurrences(text, word)
print(count)
