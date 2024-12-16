#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>
#include <cstdint>

class BMP {
public:
    BMP(const std::string& filename);
    void adjustColorIntensity(float factor);
    void save(const std::string& outputFilename) const;

private:
    // Вспомогательные методы
    void loadFile(const std::string& filename);
    void validateHeader() const;

    // Данные BMP
    uint16_t fileType;
    uint32_t fileSize;
    uint32_t dataOffset;

    uint32_t width;
    uint32_t height;
    uint16_t bitsPerPixel;

    std::vector<uint8_t> pixelData; // Пиксельные данные
};

#endif // BMP_H