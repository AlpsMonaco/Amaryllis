#include <fstream>
#include "util.h"
#include <stdio.h>
#include "stdlib.h"

void exit_with_msg(int exit_code, const char *msg)
{
	println(msg);
	exit(exit_code);
}

//void sleep_ms(int ms)
//{
//#ifdef _WIN_ENVIROMENT
//	Sleep(ms);
//
//#else
//	usleep(1000 * ms);
//#endif
//}

namespace strlib
{
	void strcpy(char *dst, const char *src)
	{
		int i = 0;
		while (true)
		{
			dst[i] = src[i];
			if (src[i] == '\0')
				return;
			i++;
		}
	}

	// src -> dst
	void strcpy(char *dst, int src_size, const char *src)
	{
		for (int i = 0; i < src_size; i++)
		{
			dst[i] = src[i];
			if (dst[i] == '\0')
				break;
		}
	}

	// dst + src
	void strcat(char *dst, int dst_size, const char *src)
	{
		for (int i = 0; i < dst_size; i++)
		{
			if (dst[i] == '\0')
			{
				int j = 0;
				do
				{
					dst[i] = src[j];
					j++;
					if (src[j] == '\0')
					{
						return;
					}
				} while (++i < dst_size);
			}
		}
	}

	void strcat(char *dst, const char *src)
	{
		int i = 0;
		while (dst[i] != '\0')
		{
			i++;
		}

		int j = 0;
		char tmp;
		while (true)
		{
			tmp = src[j];
			dst[i + j] = tmp;
			if (tmp == '\0')
				return;
			j++;
		}
	}

	bool strequ(const char *str1, const char *str2)
	{
		int i = 0;
		while (str1[i] != '\0')
		{
			if (str1[i] != str2[i])
				return false;
			i++;
		}

		return str2[i] == '\0';
	}

	int strlen(const char *src)
	{
		int len;
		for (len = 0; src[len] != '\0'; len++)
		{
		}

		return len;
	}
}
