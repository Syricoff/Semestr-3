from game_character import GameCharacter


class Warrior(GameCharacter):
    def __init__(self, name):
        super().__init__(name)

    def run(self):
        return f"{self.name} быстро бегает с оружием."

    def swim(self):
        return f"{self.name} не очень хорошо плавает."

    def jump(self):
        return f"{self.name} делает мощный прыжок."
