#include "base.h"

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
	sprintf(addr, "%s:%d", this->remote_ip, this->remote_port);
}

Amaryllis::server_base::server_base(int port)
{
	this->port = port;
	strlib::strcpy(this->addr, ANY_ADDR);
}

Amaryllis::server_base::server_base(const char *addr, int port)
{
	this->port = port;
	strlib::strcpy(this->addr, addr);
}

Amaryllis::ERR_CODE Amaryllis::server_base::serve()
{
	ERR_CODE code;
	code = this->bind_and_listen();
	if (code != SERVER_SUC)
	{
		return code;
	}

	return SERVER_SUC;
}
