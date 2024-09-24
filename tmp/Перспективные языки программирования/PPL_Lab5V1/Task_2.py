import queue
import threading
from threading import Condition, Thread
from queue import Queue
from time import sleep
import random
import string


cond = Condition()
buffer = Queue()


def put_data():
    # Производитель
    global buffer
    new_string = ''.join(random.choice(string.ascii_letters) for _ in range(5))
    buffer.put(new_string)
    print(threading.current_thread().name, new_string)


def get_data():
    # Потребитель
    global buffer
    stop = False
    while not stop:
        with cond:
            while buffer.empty():
                cond.wait()
            order = buffer.get()
            # print(threading.current_thread().name, order)
            print(order)
            if order == 'stop':
                stop = True


threads = list()
for i in range(10):
    new_thread = Thread(target=put_data, args=())
    threads.append(new_thread)
for i in threads:
    i.start()

thread_get_data = Thread(target=get_data, args=())
thread_get_data.start()

for i in range(10):
    buffer.put('stop')
with cond:
    cond.notify_all()