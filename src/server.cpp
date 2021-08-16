#include "server.h"

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

WSADATA *Amaryllis::server_win::wsaData = nullptr;

Amaryllis::server_win::server_win(int port) : server_base(port){};
Amaryllis::server_win::server_win(const char *addr, int port) : server_base(addr, port){};

Amaryllis::ERR_CODE Amaryllis::server_win::bind_and_listen()
{
	if (wsaData == nullptr)
	{
		wsaData = new WSADATA();
		if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0)
		{
			wsaData = nullptr;
			return ERR_WSA_STARTUP_FAILED;
		};
	}

	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		return ERR_INVALID_SERVER_SOCKET;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);
	server_addr.sin_addr.S_un.S_addr = inet_addr(this->addr);

	if (::bind(server_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		return ERR_BIND_FAILED;
	}

	if (::listen(server_socket, 5) == SOCKET_ERROR)
	{
		return ERR_LISTEN_FAILED;
	}

	return SERVER_SUC;
}

/* ------------------------------------------------------------ */