#pragma once
#include <iostream>

//#ifdef _WIN32
//#define _WIN_ENVIROMENT 1
//#include <Windows.h>
//#else
//#include <unistd.h>
//#include <cstring>
//#endif

template <typename T>
void print(T t)
{
	std::cout << t;
}

template <typename T>
void println(T t)
{
	std::cout << t << std::endl;
}

namespace strlib
{
	void strcpy(char *dst, int src_size, const char *src);
	void strcpy(char *dst, const char *src);
	void strcat(char *dst, int dst_size, const char *src);
	void strcat(char *dst, const char *src);
	bool strequ(const char *str1, const char *str2);
	int strlen(const char *src);

	struct charPtrComparator
	{
		bool operator()(const char *a, const char *b) const
		{
			return strcmp(a, b) < 0;
		}
	};

}