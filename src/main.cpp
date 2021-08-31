#include "server.h"
#include "client.h"
#include <thread>

const int port = 65544;

Amaryllis::server *as_server()
{
	Amaryllis::server *s = new Amaryllis::server(Amaryllis::LOCAL_ADDR, port);
	if (s->serve() != Amaryllis::SERVER_SUC)
	{
		return nullptr;
	}

	return s;
};

Amaryllis::client *as_client()
{
	Amaryllis::client *c = new Amaryllis::client(Amaryllis::LOCAL_ADDR, port);
	if (c->connect() != Amaryllis::CLIENT_SUC)
	{
		return nullptr;
	}

	return c;
};

int main(int argc, char **argv)
{
	char c = 's';

	if (argc > 0)
	{
		if (strlen(argv[1]) > 0)
		{
			c = argv[1][0];
		}
	}

	switch (c)
	{
	case 's':
		println("s");
		break;

	case 'c':
		println("c");
		break;

	default:
		println("default");
		break;
	}
}