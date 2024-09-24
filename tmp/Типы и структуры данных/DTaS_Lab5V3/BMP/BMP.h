#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>

class BMP
{
public:
	// ����������� � �����������. ��������� ��������� ����������� � �����
	// @param file_path ���� � ����� ����������� � ����������� bmp
	explicit BMP(const std::string& file_path);

	// ����������� � �����������. ������� ��������� �����������
	// @param width - ������ ���������� �����������
	// @param height - ������ ���������� �����������
	// @param has_alpha - ������� ������ ������������
	BMP(int32_t width, int32_t height, bool has_alpha = true);

	// �������� ���������� ����������� � �����
	// @param file_path - ���� ��� ��������
	void load(const std::string& file_path);

	// ���������� ���������� ����������� �� ����
	// @param file_path - ���� ��� ������
	void save(const std::string& file_path);

	// ���������� ��������� ������� ��������� ������
	// @param x0 - ���������� ��� ������ ������� �� ��� �
	// @param y0 - ���������� ��� ������ ������� �� ��� y
	// @param width - ������ ����������� �������
	// @param height - ������ ����������� �������
	// @param R - �������� ������ ��������
	// @param G - �������� ������ ��������
	// @param B - �������� ������ ������
	// @param A - �������� ������ ������������
	void fillRegion(uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint8_t R,
		uint8_t G, uint8_t B, uint8_t A);

	// ��������������� ���������� �����������
	// @param new_width - ������, �� ������� ����� ���������� ���������������
	// @param new_height - ������, �� ������� ����� ���������� ���������������
	void scale(int32_t new_width, int32_t new_height);

	// ��������� ������ ���������� �����������
	// @return - ������� ������ �����������
	int32_t getWidth() const;

	// ��������� ������ ���������� �����������
	// @return - ������� ������ ���������� �����������
	int32_t getHeight() const;

	// ��������� ��������
	// @param file_path - ���� ��� ������
	void getNegative(const std::string& file_path);

protected:
#pragma pack(push, 1)
	struct FileHeader
	{
		// ������� ��� ������� ������� �� ������ (��������� �������). ����� ���������
		// ������������ �������� 0�4D42
		uint16_t file_type{0x4D42};
		// ������ ����� � ������
		uint32_t file_size{};
		// ����������������� ����. ������ ������ ��������� ����
		uint16_t reserved1{};
		// ����������������� ����. ������ ������ ��������� ����
		uint16_t reserved2{};
		// ��������� ���������� ������ ������������ ������ ������ ���������
		uint32_t offset_data{};
	};
#pragma pack(pop)

	struct InfoHeader
	{
		// ������ ������ ��������� � ������, ����������� ����� �� ������ ���������
		uint32_t size{};
		// ������ ���������� ����������� � ��������
		int32_t width{};
		// ������ ���������� ����������� � ��������
		int32_t height{};
		// ���������� �������� ����������. ������ ������ ���� ����� �������
		uint16_t planes{1};
		// ���������� ��� �� �������
		uint16_t bit_count{};
		// ������ �������� ��������
		uint32_t compression{};
		// ������ ���������� ������ � ������
		uint32_t size_image{};
		// ���������� �������� �� ���� �� �����������
		int32_t x_pixels_per_meter{};
		// ���������� �������� �� ���� �� ���������
		int32_t y_pixels_per_meter{};
		// ���������� ������ � �������� �������
		uint32_t colors_used{};
		// �����, ������������ ��������� ������������
		uint32_t colors_important{};
	};

	struct ColorHeader
	{
		// ������� ����� ��� ������ ��������
		uint32_t red_mask{ 0x00ff0000 };
		// ������� ����� ��� ������ ��������
		uint32_t green_mask{ 0x0000ff00 };
		// ������� ����� ��� ������ ������
		uint32_t blue_mask{ 0x000000ff };
		// ������� ����� ��� �����-������
		uint32_t alpha_mask{ 0xff000000 };
		// ��� ��������� ������������. �� ��������� sRGB (0x73524742)
		uint32_t color_space_type{ 0x73524742 };
		// �������������� ������ ��� ��������� ������������ sRGB
		uint32_t unused[16]{};
	};

	// ������������ ��������� �������� ���������� �����������
	FileHeader m_file_header;
	// �������������� ��������� �������� ���������� �����������
	InfoHeader m_info_header;
	// �������� ��������� �������� ���������� �����������
	ColorHeader m_color_header;
	// ��������� ��� ���������� � ��������
	std::vector<uint8_t> m_data;
	// ���������� �������� ����
	uint32_t m_row_stride;
	
	// �������� ������� ����� �� ������������ �������� ������
	// @param color_header - ColorHeader � ��������� �������� �������
	// � ����� ��������� ������������
	void _checkColorHeader(ColorHeader& color_header);
	// ������������ ����� ������
	// @param align_stride - ����������� ������������
	// @return - ����� ����������� ������
	uint32_t _makeStrideAligned(uint32_t align_stride) const;
	// ������ ���������� �� ����
	// @param stream - ����� ��� ������
	void _writeHeaders(std::ofstream& stream);
	// ������ ���������� � ���������� � �������� �� ����
	// @param stream - ����� ��� ������
	void _writeHeadersAndData(std::ofstream& stream);
};
#endif