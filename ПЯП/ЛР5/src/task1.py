import threading


class FileChecksumCalculator:
    def __init__(self, file_path):
        self.file_path = file_path
        self.checksum = 0

    def calculate_checksum(self):
        """Вычисляет контрольную сумму файла."""
        with open(self.file_path, "r", encoding="utf-8") as file:
            for line in file:
                self.checksum += sum(ord(char) for char in line)


class ChecksumManager:
    def __init__(self):
        self.threads = []
        self.checksums = []

    def add_task(self, calculator):
        """Добавляет задачу для выполнения в отдельном потоке."""
        thread = threading.Thread(target=self.run_calculator, args=(calculator,))
        self.threads.append((thread, calculator))
        thread.start()

    def run_calculator(self, calculator):
        """Запускает калькулятор и сохраняет контрольную сумму."""
        calculator.calculate_checksum()
        self.checksums.append(calculator.checksum)

    def wait_for_completion(self):
        """Ожидает завершения всех потоков."""
        for thread, _ in self.threads:
            thread.join()


if __name__ == "__main__":
    files_to_process = ["file1.txt", "file2.txt", "file3.txt"]
    checksum_manager = ChecksumManager()

    for file_path in files_to_process:
        calculator = FileChecksumCalculator(file_path)
        checksum_manager.add_task(calculator)

    checksum_manager.wait_for_completion()

    for i, calculator in enumerate(checksum_manager.threads):
        print(
            f"Контрольная сумма для {files_to_process[i]}: {checksum_manager.checksums[i]}"
        )
