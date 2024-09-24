import random
import string
import threading
import time


def fill_file_with_random_characters(file_name: str, string_len: int) -> None:
    with open(file_name, 'w') as f:
        f.write(''.join(random.choice(string.ascii_letters) for i in range(string_len)))


def get_string_from_file(file_name: str) -> str:
    with open(file_name, 'r') as f:
        data = f.read()
        return data


def get_checksum(file_name: str) -> int:
    with open(file_name, 'r') as f:
        return sum([ord(i) for i in f.read()])


def task(file: str, string_len: int, results: dict[str, int]) -> None:
    fill_file_with_random_characters(file, string_len)
    results[file] = get_checksum(file)


def foo_without_threads(files: list[str], string_len: int) -> None:
    results = dict()
    start_time = time.time()
    for f in files:
        task(f, string_len, results)
    for f in files:
        print(f'{f}:{results[f]}')
    print(f'Execution time foo1: {time.time() - start_time}s')


def foo_with_threads(files: list[str], string_len: int) -> None:
    results = dict()
    start_time = time.time()
    threads = list()
    for f in files:
        new_thread = threading.Thread(target=task, args=(f, string_len, results))
        threads.append(new_thread)
        new_thread.start()
    for curr_thread in threads:
        curr_thread.join()
    for f in files:
        print(f'{f}:{results[f]}')
    print(f'Execution time foo2: {time.time() - start_time}s')


def main():
    files = ['data' + str(i) + '.txt' for i in range(20)]
    foo_without_threads(files, 100)
    foo_with_threads(files, 100)


if __name__ == '__main__':
    main()
