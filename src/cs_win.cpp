#include "cs_win.h"

using namespace Amaryllis;

ERR_CODE client_win::connect()
{
	this->client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->client_socket == INVALID_SOCKET)
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

	if (::connect(this->client_socket, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		closesocket(this->client_socket);
		return ERR_CLIENT_CONNECT_FAILED;
	}

	return CLIENT_SUC;
}

int client_win::send(const char *data, int data_size)
{
	return ::send(this->client_socket, data, data_size, 0);
}

int client_win::receive(char *buf, int buf_size)
{
	return ::recv(this->client_socket, buf, buf_size, 0);
}

client_win::client_win(const char *ip, int port) : client_base(ip, port)
{
	netutil::wsa();
	this->client_addr = {0};
	this->client_socket = NULL;
};

Amaryllis::server_win::server_win(int port) : server_base(port){
	this->server_socket = NULL;
	this->server_addr = { 0 };
};
Amaryllis::server_win::server_win(const char *addr, int port) : server_base(addr, port){
	this->server_socket = NULL;
	this->server_addr = { 0 };
};

Amaryllis::ERR_CODE Amaryllis::server_win::bind_and_listen()
{
	netutil::wsa();

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

client_win *server_win::accept()
{
	SOCKET c;
	sockaddr_in cin;
	int addrlen = sizeof(cin);

	c = ::accept(this->server_socket, (SOCKADDR *)&cin, &addrlen);
	char ip[1024];
	client_win::get_ip(ip, &cin);

	return new client_win(c, cin, ip, client_win::get_port(&cin));
}

client_win::client_win(SOCKET c, sockaddr_in cin, const char *ip, int port) : client_base(ip, port)
{
	this->client_socket = c;
	this->client_addr = cin;
}

void client_win::get_ip(char *dst, sockaddr_in *sin)
{
	strlib::strcpy(dst, inet_ntoa(sin->sin_addr));
}

int client_win::get_port(sockaddr_in *sin)
{
	auto port = sin->sin_port;
	return int(port);
}