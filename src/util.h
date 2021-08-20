#pragma once
#include <iostream>

#ifdef _WIN32
#define _WIN_ENVIROMENT 1
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#endif

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
}

namespace netutil
{
	bool is_domain_name(const char *s);
	bool get_host_by_name(char *dst, const char *name);

	extern WSADATA* wsa_ptr;
	void wsa();
}