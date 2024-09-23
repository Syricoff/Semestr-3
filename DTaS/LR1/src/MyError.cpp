#define _CRT_SECURE_NO_WARNINGS
#include "MyError.h"
#include <chrono>
#include <fstream>
#include <iostream>

const char *MyError::getError() const
{
	return m_error.c_str();
}

MyError::MyError(std::string error)
{
	m_error = error;
	logging();
}

void MyError::logging()
{
	std::fstream file;
	auto now = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(now);
	file.open(m_file, std::ios::app);
	file << "WARNING: " << m_error.c_str() << "|" << std::ctime(&end_time);
	file.close();
}
