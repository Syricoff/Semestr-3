from game_character import GameCharacter


class Mage(GameCharacter):
    def __init__(self, name):
        super().__init__(name)

    def run(self):
        return f"{self.name} бегает, используя магию для ускорения."

    def swim(self):
        return f"{self.name} может плавать, используя магические заклинания."

    def jump(self):
        return f"{self.name} делает волшебный прыжок."
