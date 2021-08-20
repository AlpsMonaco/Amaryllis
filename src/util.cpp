#include "util.h"
#include <stdio.h>
#include "stdlib.h"

void exit_with_msg(int exit_code, const char *msg)
{
	println(msg);
	exit(exit_code);
}

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

bool netutil::is_domain_name(const char *s)
{
	int count = 0;
	while (s[count] != '\0')
	{
		if (s[count] > 57)
		{
			return true;
		}
		count++;
	}

	return false;
}

bool netutil::get_host_by_name(char *ip, const char *name)
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		return false;
	}

	struct hostent *remoteHost;
	remoteHost = gethostbyname(name);
	if (remoteHost != nullptr)
	{
		if (!remoteHost->h_addr_list[0])
			return false;

		strlib::strcpy(ip, inet_ntoa(*(struct in_addr *)remoteHost->h_addr_list[0]));
		return true;
	}

	return false;
}

WSADATA* netutil::wsa_ptr = nullptr;

void netutil::wsa()
{
	if (wsa_ptr == nullptr) {
		wsa_ptr = new WSADATA();
		if (WSAStartup(MAKEWORD(2, 2), wsa_ptr) != 0)
		{
			wsa_ptr = nullptr;
		};
	}
}
