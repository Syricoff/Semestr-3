#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string>
#include <fstream>
#include <ctime>
#include <iostream>

class FileLogging
{
public:
	FileLogging(std::string fileName);
	void Logging(std::string message);
	void PrintFile();

private:
	std::string getTime();
	std::string fileName;
};