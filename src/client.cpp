#include "client.h"

using namespace Amaryllis;

client_base::client_base(const char *remote_ip, int port)
{
	this->remote_port = port;
	strlib::strcpy(this->remote_ip, remote_ip);
}

int client_base::remote_addr_size()
{
	return strlib::strlen(this->remote_ip) + 1 + [](int num) -> int
	{
		if (num < 10)
			return 1;

		if (num < 100)
			return 2;

		if (num < 1000)
			return 3;

		if (num < 10000)
			return 4;

		return 5;
	}(this->remote_port);
}

void client_base::remote_addr(char *addr)
{
	sprintf("%s:%d", this->remote_ip, this->remote_port);
}

ERR_CODE client_win::connect()
{
	this->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->s == INVALID_SOCKET)
	{
		return ERR_INVALID_CLIENT_SOCKET;
	}

	const char *ip;
	if (netutil::is_domain_name(this->remote_ip))
	{
		char temp_char[1024];
		if (!netutil::get_host_by_name(temp_char, this->remote_ip))
		{
			return ERR_DNS_LOOKUP_FAILED;
		}

		ip = temp_char;
	}
	else
	{
		ip = this->remote_ip;
	}

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(this->remote_port);
	sin.sin_addr.S_un.S_addr = inet_addr(ip);

	if (::connect(this->s, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		closesocket(this->s);
		return ERR_CLIENT_CONNECT_FAILED;
	}

	return CLIENT_SUC;
}