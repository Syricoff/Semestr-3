import threading
import time
import random


class Buffer:
    def __init__(self, size):
        self.size = size
        self.buffer = []
        self.condition = threading.Condition()

    def produce(self, item):
        with self.condition:
            while len(self.buffer) >= self.size:
                print("Буфер полон. Производитель ждет...")
                self.condition.wait()
            self.buffer.append(item)
            print(f"Производитель добавил: {item}")
            self.condition.notify_all()

    def consume(self):
        with self.condition:
            while not self.buffer:
                print("Буфер пуст. Потребитель ждет...")
                self.condition.wait()
            item = self.buffer.pop(0)
            print(f"Потребитель извлек: {item}")
            self.condition.notify_all()
            return item


class Producer(threading.Thread):
    def __init__(self, buffer):
        super().__init__()
        self.buffer = buffer

    def run(self):
        for _ in range(3):
            item = random.randint(1, 100)
            self.buffer.produce(item)
            time.sleep(random.uniform(0.2, 0.6))


class Consumer(threading.Thread):
    def __init__(self, buffer):
        super().__init__()
        self.buffer = buffer

    def run(self):
        for _ in range(9):
            item = self.buffer.consume()
            time.sleep(random.uniform(0.4, 0.7))


if __name__ == "__main__":
    buffer_size = 5
    buffer = Buffer(buffer_size)

    producers = [Producer(buffer) for _ in range(3)] 
    consumer = Consumer(buffer)

    for producer in producers:
        producer.start()

    consumer.start()

    for producer in producers:
        producer.join()

    consumer.join()

    print("Все операции завершены.")
