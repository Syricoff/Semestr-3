from character_abilities import CharacterAbilities


class GameCharacter(CharacterAbilities):
    def __init__(self, name):
        self.name = name

    def run(self):
        return f"{self.name} бегает."

    def swim(self):
        return f"{self.name} плавает."

    def jump(self):
        return f"{self.name} прыгает."
