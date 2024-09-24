class Book:
    author = ''
    id = None

    def __init__(self, author, _id):
        self.author = author
        self.id = _id

    def order(self, book):
        if not isinstance(self.id, type(book.id)):
            print("Невозможно сравнить различные типы id")
        else:
            if self.id > book.id:
                print("1-ая книга должна стоять после 2-ой")
            else:
                print("1-ая книга должна стоять перед 2-ой")


b1 = Book("Пушкин", "Евгений Онегин")
b2 = Book("Толстой", "Война и мир")
b1.order(b2)
