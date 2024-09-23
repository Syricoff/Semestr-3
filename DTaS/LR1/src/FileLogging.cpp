#include "FileLogging.h"

FileLogging::FileLogging(std::string fileName)
{
	this->fileName = fileName;
}

void FileLogging::Logging(std::string message)
{
	std::ofstream fout(fileName, std::ios::out | std::ios::app);
	if (fout.is_open())
	{
		fout << "[" << getTime() << "]" << message;
	}
	fout.close();
}

std::string FileLogging::getTime()
{
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	std::string currTime = asctime(timeinfo);
	currTime.pop_back();
	return currTime;
}

void FileLogging::PrintFile()
{
	std::ifstream fin(fileName, std::ios::in);
	std::string temp;
	std::cout << fileName << ":\n";
	if (fin.is_open())
	{
		while (std::getline(fin, temp))
		{
			std::cout << temp << std::endl;
		}
	}
}