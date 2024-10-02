from abc import ABC, abstractmethod


class Person(ABC):
    def __init__(self, full_name):
        self.full_name = full_name

    @abstractmethod
    def display_info(self):
        pass
