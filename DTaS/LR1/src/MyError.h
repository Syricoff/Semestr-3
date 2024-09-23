#ifndef MYERROR_H
#define MYERROR_H
#include <string>
#include <string_view>

class MyError
{
public:
	MyError(std::string error);
	static std::string m_file;
	const char *getError() const;

private:
	void logging();
	std::string m_error;
};

#endif // MYERROR_H