#pragma once
#include "base.h"

namespace Amaryllis
{
	class client_win : public client_base
	{
	public:
		client_win(SOCKET c, sockaddr_in cin, const char *ip, int port);
		client_win(const char *ip, int port);
		ERR_CODE connect();
		int receive(char *buf, int buf_size);
		int send(const char *data, int data_size);

		static void get_ip(char *dst, sockaddr_in *sin);
		static int get_port(sockaddr_in *sin);

	protected:
		SOCKET client_socket;
		sockaddr_in client_addr;
	};

	class server_win : public server_base
	{
	public:
		server_win(int port);
		server_win(const char *addr, int port);
		client_win *accept();

	protected:
		SOCKET server_socket;
		sockaddr_in server_addr;
		ERR_CODE bind_and_listen();
	};

}