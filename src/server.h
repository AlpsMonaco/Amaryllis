#pragma once
#include "client.h"

namespace Amaryllis
{
	static const char *LOCAL_ADDR = "127.0.0.1";
	static const char *ANY_ADDR = "127.0.0.1";

	enum SERVER_ERR_CODE
	{
		SERVER_SUC = ERR_CODE(0),
		ERR_INVALID_SERVER_SOCKET,
		ERR_BIND_FAILED,
		ERR_LISTEN_FAILED,
		ERR_WSA_STARTUP_FAILED

	};

	/* ------------------------------------------------------------ */
	// server base class.
	class server_base
	{
	public:
		server_base(int port);
		server_base(const char *addr, int port);
		ERR_CODE serve();

	protected:
		int port;
		char addr[16];
		virtual ERR_CODE bind_and_listen() = 0;
		virtual client_base *accept() = 0;
	};

	/* ------------------------------------------------------------ */

	class server_win : public server_base
	{
	public:
		server_win(int port);
		server_win(const char *addr, int port);
		void test()
		{
			println(this->port);
			println(this->addr);
		}

	protected:
		static WSADATA *wsaData;
		SOCKET server_socket;
		sockaddr_in server_addr;
		ERR_CODE bind_and_listen();
		// client *accept();
	};

	/* ------------------------------------------------------------ */

#ifdef _WIN_ENVIROMENT
	using server = server_win;
#else
	using server = server_linux;
#endif

}