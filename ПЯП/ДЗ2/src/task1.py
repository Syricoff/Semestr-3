import os
import zipfile


files_starting_with_a = []
test_dir = "test_folder"
zip_filename = "test_folder.zip"

for root, dirs, files in os.walk(test_dir):
    for file in files:
        if file.startswith("a"):
            files_starting_with_a.append(os.path.join(root, file))

with open("files_starting_with_a.txt", "w") as f:
    for file in files_starting_with_a:
        f.write(file + "\n")

with zipfile.ZipFile(zip_filename, "w", zipfile.ZIP_DEFLATED) as zipf:
    for root, dirs, files in os.walk(test_dir):
        for file in files:
            file_path = os.path.join(root, file)
            zipf.write(file_path, os.path.relpath(file_path, test_dir))
