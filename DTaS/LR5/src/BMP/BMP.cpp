#include "BMP.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>

// Конструктор: загрузка BMP-файла
BMP::BMP(const std::string &filename)
{
    loadFile(filename);
}

// Метод для изменения интенсивности цветов
void BMP::adjustColorIntensity(float factor)
{
    for (size_t i = 0; i < pixelData.size(); i++)
    {
        int newValue = static_cast<int>(pixelData[i] * factor);
        pixelData[i] = static_cast<uint8_t>(std::clamp(newValue, 0, 255));
    }
}

// Метод сохранения в файл
void BMP::save(const std::string &outputFilename) const
{
    std::ofstream outFile(outputFilename, std::ios::binary);
    if (!outFile)
    {
        throw std::runtime_error("Unable to open output file");
    }

    // Заголовок файла
    uint32_t reserved = 0;
    uint32_t headerSize = 40;
    uint32_t compression = 0;
    uint32_t rowSize = ((width * 3 + 3) & ~3); // Выравнивание строки
    uint32_t imageSize = rowSize * height;

    outFile.write(reinterpret_cast<const char *>(&fileType), sizeof(fileType));
    outFile.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
    outFile.write(reinterpret_cast<const char *>(&reserved), sizeof(reserved)); // Reserved
    outFile.write(reinterpret_cast<const char *>(&dataOffset), sizeof(dataOffset));

    // Заголовок изображения
    outFile.write(reinterpret_cast<const char *>(&headerSize), sizeof(headerSize));
    outFile.write(reinterpret_cast<const char *>(&width), sizeof(width));
    outFile.write(reinterpret_cast<const char *>(&height), sizeof(height));

    uint16_t planes = 1; // Всегда 1
    outFile.write(reinterpret_cast<const char *>(&planes), sizeof(planes));
    outFile.write(reinterpret_cast<const char *>(&bitsPerPixel), sizeof(bitsPerPixel));
    outFile.write(reinterpret_cast<const char *>(&compression), sizeof(compression));
    outFile.write(reinterpret_cast<const char *>(&imageSize), sizeof(imageSize));
    uint32_t ppm = 2835; // 72 DPI в пикселях на метр
    outFile.write(reinterpret_cast<const char *>(&ppm), sizeof(ppm));
    outFile.write(reinterpret_cast<const char *>(&ppm), sizeof(ppm));
    uint32_t colorsUsed = 0;
    uint32_t importantColors = 0;
    outFile.write(reinterpret_cast<const char *>(&colorsUsed), sizeof(colorsUsed));
    outFile.write(reinterpret_cast<const char *>(&importantColors), sizeof(importantColors));

    // Сохранение пикселей с учётом выравнивания
    std::vector<uint8_t> padding(rowSize - width * 3, 0);
    for (int y = 0; y < height; ++y)
    {
        size_t rowStart = y * width * 3;
        outFile.write(reinterpret_cast<const char *>(&pixelData[rowStart]), width * 3);
        outFile.write(reinterpret_cast<const char *>(padding.data()), padding.size());
    }
}

// Вспомогательный метод загрузки файла
void BMP::loadFile(const std::string &filename)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open input file");
    }

    // Чтение заголовка файла
    inFile.read(reinterpret_cast<char *>(&fileType), sizeof(fileType));
    if (fileType != 0x4D42)
    { // Проверка "BM" в начале файла
        throw std::runtime_error("Unsupported file format");
    }

    inFile.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
    inFile.ignore(4); // Пропуск резервированных байтов
    inFile.read(reinterpret_cast<char *>(&dataOffset), sizeof(dataOffset));

    // Чтение заголовка изображения
    uint32_t headerSize;
    inFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
    if (headerSize != 40)
    {
        throw std::runtime_error("Unsupported BMP header size");
    }

    inFile.read(reinterpret_cast<char *>(&width), sizeof(width));
    inFile.read(reinterpret_cast<char *>(&height), sizeof(height));
    inFile.ignore(2); // Пропуск количества цветовых плоскостей
    inFile.read(reinterpret_cast<char *>(&bitsPerPixel), sizeof(bitsPerPixel));
    if (bitsPerPixel != 24)
    {
        throw std::runtime_error("Only 24-bit BMP files are supported");
    }

    inFile.ignore(24); // Пропуск оставшейся части заголовка
    // Чтение пиксельных данных
    uint32_t rowSize = ((width * 3 + 3) & ~3); // Выравнивание строки
    size_t pixelDataSize = rowSize * height;
    pixelData.resize(pixelDataSize);
    inFile.seekg(dataOffset, std::ios::beg);

    // Считываем строки с учётом padding
    for (int y = 0; y < height; ++y)
    {
        inFile.read(reinterpret_cast<char *>(&pixelData[y * width * 3]), width * 3);
        inFile.ignore(rowSize - width * 3); // Пропуск padding
    }
}