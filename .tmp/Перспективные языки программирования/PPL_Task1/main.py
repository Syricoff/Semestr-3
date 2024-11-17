import csv
import xml.etree.ElementTree as ET
import json
import os


def write_csv_file(file_name):
    n = int(input('Введите количество записей, которые вы хотите добавить в файл: '))
    titles = ['Имя', 'Фамилия', 'Дата рождения', 'Город проживания']
    flag = os.path.exists(file_name)
    with open(file_name, 'a', newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        if not flag:
            writer.writerow(titles)
        for i in range(n):
            str_data = ', '.join(titles)
            data = input(f'Введите данные о студенте через пробел ({str_data}): ').split()
            writer.writerow(data)


def read_csv_file(file_name):
    print(f'{file_name}:')
    with open(file_name, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            print(','.join(row))


def convert_from_csv_to_xml_file(csv_file):
    root = ET.Element('root')
    with open(csv_file, 'r', encoding='utf-8') as f:
        for i, row in enumerate(csv.reader(f)):
            if i != 0:
                student = ET.SubElement(root, 'Student')
                ET.SubElement(student, 'First_name').text = row[0]
                ET.SubElement(student, 'Second_name').text = row[1]
                ET.SubElement(student, 'Birth_date').text = row[2]
                ET.SubElement(student, 'City').text = row[3]
    xml_file = csv_file[:-3] + 'xml'
    ET.ElementTree(root).write(xml_file)


def read_xml_file(xml_file):
    print(f'{xml_file}:')
    tree = ET.parse(xml_file)
    root = tree.getroot()
    count_space = 4
    tab = ' ' * count_space
    print('<' + root.tag + '>')
    for elem in root:
        print(tab, end='')
        print('<' + elem.tag + '>')
        for sub_elem in elem:
            print(tab * 2, end='')
            print('<' + sub_elem.tag + '>', end='')
            print(sub_elem.text, end='')
            print('</' + sub_elem.tag + '>')
        print(tab, end='')
        print('</' + elem.tag + '>')
    print('</' + root.tag + '>')


def convert_from_csv_to_json_file(csv_file):
    json_file = csv_file[:-3] + 'json'
    lst_data = []
    with open(csv_file, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for i, row in enumerate(reader):
            print(row)
            if i != 0:
                d = {'First_name': row[0], 'Second_name': row[1], 'Birth_date': row[2], 'City': row[3]}
                lst_data.append(d)
    with open(json_file, 'w', encoding='utf-8') as f:
        json.dump(lst_data, f, indent=4)


def read_json_file(json_file):
    print(f'{json_file}:')
    with open(json_file, 'r', encoding='utf-8') as f:
        templates = json.load(f)
        print(str(templates).replace('}, {', '},\n{'))


write_csv_file('data.csv')
read_csv_file('data.csv')
print()

convert_from_csv_to_json_file('data.csv')
read_json_file('data.json')
print()

convert_from_csv_to_xml_file('data.csv')
read_xml_file('data.xml')