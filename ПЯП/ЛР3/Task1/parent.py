class Parent:
    def __init__(self, grow):
        self.grow = grow

    def colorEye(self):
        return "У меня зеленые глаза."

    def changeGrow(self, change):
        self.grow += change

    def printGrow(self):
        print(f"Мой рост: {self.grow} см.")
