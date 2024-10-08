#include "BMP.h"

BMP::BMP(const std::string& file_path) : m_row_stride{ 0 }
{
    load(file_path);
}

BMP::BMP(int32_t width, int32_t height, bool has_alpha)
{
    // ��������� �������� ������ � ������
    if (width <= 0 || height <= 0)
    {
        throw std::runtime_error("The image width and height must be positive numbers.");
    }
    m_info_header.width = width;
    m_info_header.height = height;
    // ���� ������ 4 ������ (32-������ �����������)
    if (has_alpha)
    {
        // ���������� ������ ��������������� ������ (InfoHeader � ColorHeader ��������� � ��������������� ������)
        m_info_header.size = sizeof(InfoHeader) + sizeof(ColorHeader);
        // ����������, ����� ������� ���� �� ������ ����� ���������� �������
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(ColorHeader);
        // ����������, ��� �� ������� ���������� 32 ���� ����������
        m_info_header.bit_count = 32;
        // ����������, ��� ����������� �� ������
        m_info_header.compression = 3;
        // ��������� ���������� �������� ����
        m_row_stride = width * 4;
        // ������� ������ ��� �������� ���������� � �������� (������ * ������ * ���������� �������)
        m_data.resize(m_row_stride * height);
        // ���������� ������ ����� (��������� ���������� + ���������� � ��������)
        m_file_header.file_size = m_file_header.offset_data + m_data.size();
    }
    // ���� ������ 3 ������ (24-������ �����������)
    else
    {
        // ���������� ������ ��������������� ������
        m_info_header.size = sizeof(InfoHeader);
        // ����������, ����� ������� ���� �� ������ ����� ���������� �������
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader);
        // ���������� �������� �����������
        m_info_header.bit_count = 24;
        // ���������� ������ �������� ���������� � ��������
        m_info_header.compression = 0;
        // ��������� ���������� �������� ����
        m_row_stride = width * 3;
        // �������� ������ ��� ���������� � ��������
        m_data.resize(m_row_stride * height);
        // ��������� ����� ������ ��� ������������
        uint32_t new_stride{ _makeStrideAligned(4) };
        // ��������� ������ �����
        m_file_header.file_size = m_file_header.offset_data + m_data.size() + m_info_header.height * (new_stride - m_row_stride);
    }
}

void BMP::load(const std::string& file_path)
{
    std::ifstream input{ file_path, std::ios::binary };
    if (!input)
    {
        throw std::runtime_error("Unable to open the input image file!");
    }
    // ��������� ������������ ��������� �����������
    input.read((char*)&m_file_header, sizeof(m_file_header));
    // ��������� ������ �����������
    if (m_file_header.file_type != 0x4D42)
    {
        throw std::runtime_error("Unrecognized file format!");
    }
    // ��������� �������������� �����
    input.read((char*)&m_info_header, sizeof(m_info_header));
    // ���� ����������� 32-������, ����� ��������� � ������� ColorHeader
    if (m_info_header.bit_count == 32)
    {
        // �������� �������� �� ���� ColorHeader (������������ ������ � 32-������ �����������)
        if (m_info_header.size >= (sizeof(InfoHeader) + sizeof(ColorHeader)))
        {
            // ��������� ColorHeader
            input.read((char*)&m_color_header, sizeof(m_color_header));
            // ���������, �������� �� ������� � ������� BGRA � �������� �� �������� ������������ sRGB
            _checkColorHeader(m_color_header);
        }
        // ���� �� �������� - ����������� ����������
        else
        {
            std::cerr << "Warning! The file \"" << file_path << "\" does not seem to contain bit mask information\n";
            throw std::runtime_error("Error! Unrecognized file format!");
        }
    }
    // ������������ � ������ ��������
    input.seekg(m_file_header.offset_data, std::ifstream::beg);
    // � ���� ����, ��� ��������� ������������� �������� � ���� ��������� ����������, ������� ����� �������� ������������,
    // ����� ������ �� �������, ����� ��������� ������ ��������������� ������, ������ ����� � �������, ������ ���������� �������
    // ���� ����������� 32-������
    if (m_info_header.bit_count == 32)
    {
        // ���������� ������ ��������������� ������, �������� ColorHeader
        m_info_header.size = sizeof(InfoHeader) + sizeof(ColorHeader);
        // ����������, ����� ������� ���� �� ������ ����� ���������� �������, �������� ColorHeader
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(ColorHeader);
    }
    // ���� ����������� 24-������
    else
    {
        // ���������� ������ ��������������� ������
        m_info_header.size = sizeof(InfoHeader);
        // ����������, ����� ������� ���� �� ������ ����� ���������� �������
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader);
    }
    // ���������� ������ ����� (��� �� ���� ������ �����, � ���� ��,
    // ������� �������� ������������ ��������� � ��������� ����������)
    m_file_header.file_size = m_file_header.offset_data;
    // ���� ������ ����������� �������� ������������� ������,
    // �� ������ �������� ������� ������-����, ������� � ������� ����� ����

    // ���� ������ ����������� �������� ������������� ������,
    // �� ������ �������� ������� �����-�����, ������� � ������ ����� ����

    // ������ ��������� ����� �� ������ ������� ������ ����� ����

    // �������� ������
    if (m_info_header.height < 0)
    {
        throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
    }
    // ������� ������ ��� �������� ���������� � �������� (������ * ������ * ���������� �������)
    m_data.resize(m_info_header.width * m_info_header.height * m_info_header.bit_count / 8);

    // ������ ����������� BMP ������������, ��� ������ ������ ������ ����� ��������� �� ������� ������� ������ ���
    // ��������� ������, ���� ��� �� ���. ��� ����������� � ����������� 32 ���� �� ������� ������� ������������ ������ �����������.
    // � ������ ����������� � ����������� 24 ���� �� ������� ������� ������������ ����������� ������ � ��� ������,
    // ���� ������ ����������� ������� �� 4, � ��������� ������ ��� ����� ����� ��������� ������ ������.

    // ���� ������ ����������� ������� �� 4
    if (m_info_header.width % 4 == 0)
    {
        // ��������� ���������� � ��������
        input.read((char*)m_data.data(), m_data.size());
        // ��������� ������ ����� (��������� � ���� ��, ������� �������� ���������� � ��������)
        m_file_header.file_size += m_data.size();
    }
    // ���� ������ ����������� �� ������� �� 4
    else
    {
        // ��������� width
        // (���������� �������� � ������ * ���������� ������� = ���������� ���� � ������ (width))
        m_row_stride = m_info_header.width * m_info_header.bit_count / 8;

        // ��������� line_stride
        uint32_t new_stride{ _makeStrideAligned(4) };
        // �������� ������ ��� ������� (line_padding)
        std::vector<uint8_t> padding_row(new_stride - m_row_stride);

        // ���������� �� ������ ������ ��������
        for (int y = 0; y < m_info_header.height; y++)
        {
            // ��������� ���������� �� ������� � ���������� � ��������
            // m_data.data() - ������ �������
            // m_row_stride - ������� ����� ��������, ����� ������� �� ������ �������
            // y - ��������� � ������ ���������� ���������� �������� � ���� ������������������ ���� (��� ���������� ������),
            //     ����� ������ �������� ������������ ����� ���������
            // ���������� ����� ������ ������ m_data
            // ������ ��������� � ���� ���������� � ��������� ��������
            input.read((char*)(m_data.data() + m_row_stride * y), m_row_stride);
            // ���� ��� ��������, ��� ��������� � ��������:
            // 1) ������� ���������� ����
            // 2) ���������� ����������� ��������� �� ��������� ������
            // ����� ��������� ������
            input.read((char*)padding_row.data(), padding_row.size());
        }
        // ��������� ������ ����� (������ �������� + ������ ����������� * ������ �������)
        m_file_header.file_size += m_data.size() + m_info_header.height * padding_row.size();
    }
}

void BMP::getNegative(const std::string& new_file_path)
{
    // ��������� ���������� ������� (������� ����� / 8)
    uint32_t channels = m_info_header.bit_count / 8;
    // ���������� �� �������� �������� �������
    for (uint32_t y = 0; y < m_info_header.height; y++)
    {
        for (uint32_t x = 0; x < m_info_header.width; x++)
        {
            // ������ ���� ������� ���������� ������� � ������� BGRA
            for (int i = 0; i < 3; i++)
            {
                m_data.at(channels * (y * m_info_header.width + x) + i) = 255 - m_data.at(channels * (y * m_info_header.width + x) + i);
            }
            // ���� ����� 4 ������ (32-������ �����������)
            if (channels == 4)
            {
                // ������ ��������� ������������
                m_data.at(channels * (y * m_info_header.width + x) + 3) = m_data.at(channels * (y * m_info_header.width + x) + 3);
            }
        }
    }
    save(new_file_path);
}

void BMP::save(const std::string& file_path)
{
    // ��������� �������� ����� � �������� ������
    std::ofstream output{ file_path, std::ios::binary };
    // ���������, �������� �� ����
    if (!output)
    {
        throw std::runtime_error("Unable to open the input image file!");
    }
    // ���� ����������� 32-������
    if (m_info_header.bit_count == 32)
    {
        _writeHeadersAndData(output);
    }
    // ���� ����������� 24-������
    else if (m_info_header.bit_count == 24)
    {
        // ��� ������ ����������� ������� �� 4
        if (m_info_header.width % 4 == 0)
        {
            // ���������� ��� ���������� �� �����������
            _writeHeadersAndData(output);
        }
        // ��� ������ ����������� �� ������� �� 4
        else
        {
            // ��������� line_stride
            uint32_t new_stride{ _makeStrideAligned(4) };
            // �������� ������ ��� ������� (line_padding)
            std::vector<uint8_t> padding_row(new_stride - m_row_stride);
            // ���������� ������ ������
            _writeHeaders(output);
            for (int y = 0; y < m_info_header.height; y++)
            {
                // ��������� ���������� � ��������
                output.write((const char*)(m_data.data() + m_row_stride * y), m_row_stride);
                // ���������� ������
                output.write((const char*)padding_row.data(), padding_row.size());
            }
        }
    }
    // ����������� ���������� (������ ��������� ������������ ������ 24- ��� 32-������ �����������)
    else
    {
        throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
    }
}

void BMP::fillRegion(uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    // ��������� ���������� ������, ����� ��� ��������������� �������� �����������
    if (x0 + width > (uint32_t)m_info_header.width || y0 + height > (uint32_t)m_info_header.height)
    {
        throw std::runtime_error("The region does not fit in the image!");
    }
    // ��������� ���������� ������� (������� ����� / 8)
    uint32_t channels = m_info_header.bit_count / 8;
    // ���������� �� �������� �������� �������
    for (uint32_t y = y0; y < y0 + height; ++y)
    {
        for (uint32_t x = x0; x < x0 + width; ++x)
        {
            // ������ ���� ������� ���������� ������� � ������� BGRA
            m_data.at(channels * (y * m_info_header.width + x) + 0) = B;
            m_data.at(channels * (y * m_info_header.width + x) + 1) = G;
            m_data.at(channels * (y * m_info_header.width + x) + 2) = R;
            // ���� ����� 4 ������ (32-������ �����������)
            if (channels == 4)
            {
                // ������ ��������� ������������
                m_data.at(channels * (y * m_info_header.width + x) + 3) = A;
            }
        }
    }
}

void BMP::scale(int32_t new_width, int32_t new_height)
{
    // ��������� ����������� ������ ��������� ����������� � ����� ������
    uint32_t x_ratio = ((m_info_header.width << 16) / new_width) + 1;
    // ��������� ����������� ������ ��������� ����������� � ����� ������
    uint32_t y_ratio = ((m_info_header.height << 16) / new_height) + 1;
    // ��������� ���������� �������
    uint32_t channels = m_info_header.bit_count / 8;
    // �������� ������ ��� ���������� � ��������
    std::vector<uint8_t> temp(new_width * new_height * channels);
    uint32_t x_2{}, y_2{};
    for (uint32_t i = 0; i < new_height; ++i)
    {
        for (uint32_t j = 0; j < new_width; ++j)
        {
            // ��������� ������� ��������� ������� �� ��� x
            x_2 = ((j * x_ratio) >> 16);
            // ��������� ������� ��������� ������� �� ��� y
            y_2 = ((i * y_ratio) >> 16);
            // ��������� ����������� ������� � ����� ������
            for (int k = 0; k < 3; k++)
            {
                temp[channels * (i * new_width + j) + k] = m_data[channels * (y_2 * m_info_header.width + x_2) + k];
            }
            if (channels == 4)
            {
                temp[channels * (i * new_width + j) + 3] = m_data[channels * (y_2 * m_info_header.width + x_2) + 3];
            }
        }
    }
    // ��������� ���������� �� �����������
    m_info_header.width = new_width;
    m_info_header.height = new_height;
    m_data = temp;
}

void BMP::_checkColorHeader(ColorHeader& color_header)
{
    ColorHeader expected_color_header{};
    // ��������� ������ �����, ����� �� �������������� BGRA �������
    if (expected_color_header.red_mask != color_header.red_mask ||
        expected_color_header.blue_mask != color_header.blue_mask ||
        expected_color_header.green_mask != color_header.green_mask ||
        expected_color_header.alpha_mask != color_header.alpha_mask)
    {
        throw std::runtime_error("Unexpected color mask format! "
            "The program expects the pixel data to be in the BGRA format!");
    }
    // ��������� �������� ������������, ����� ��� ��������������� sRGB
    if (expected_color_header.color_space_type != color_header.color_space_type)
    {
        throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
    }
}

uint32_t BMP::_makeStrideAligned(uint32_t align_stride) const
{
    // ����� ������� ���������� ���� � ������
    uint32_t new_stride{ m_row_stride };
    // ����������� �� ��� ���, ���� �� ����� �������� �� 4
    while (new_stride % align_stride != 0)
    {
        ++new_stride;
    }
    return new_stride;
}

void BMP::_writeHeaders(std::ofstream& stream)
{
    // ���������� � ���� ������������ ��������� �����������
    stream.write((const char*)&m_file_header, sizeof(m_file_header));
    // ���������� � ���� �������������� ��������� �����������
    stream.write((const char*)&m_info_header, sizeof(m_info_header));
    // ���� ����������� 32-������
    if (m_info_header.bit_count == 32)
    {
        // ���������� � ���� ColorHeader
        stream.write((const char*)&m_color_header, sizeof(m_color_header));
    }
}

void BMP::_writeHeadersAndData(std::ofstream& stream)
{
    // ���������� ������
    _writeHeaders(stream);
    // ���������� � ���� ���������� � ��������
    stream.write((const char*)m_data.data(), m_data.size());
}

int32_t BMP::getWidth() const
{
    return m_info_header.width;
}

int32_t BMP::getHeight() const
{
    return m_info_header.height;
}