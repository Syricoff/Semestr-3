from parent import Parent


class Masha(Parent):
    def __init__(self, grow):
        super().__init__(grow)

    def colorEye(self):
        return "У меня карие глаза."
