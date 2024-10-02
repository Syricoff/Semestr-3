from abc import ABC, abstractmethod


class CharacterAbilities(ABC):
    @abstractmethod
    def run(self):
        pass

    @abstractmethod
    def swim(self):
        pass

    @abstractmethod
    def jump(self):
        pass
