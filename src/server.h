#pragma once
#include <exception>
#include "util.h"

#ifdef _WIN32
#define _WIN_ENVIROMENT 1
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

namespace Amaryllis
{
	typedef int ERR_CODE;

	enum SERVER_ERR_CODE
	{
		SUC = ERR_CODE(0),
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
		server_base(const char *addr, int port);
		ERR_CODE start();

	protected:
		int port;
		char addr[16];
		virtual ERR_CODE bind_and_listen() = 0;
	};

	/* ------------------------------------------------------------ */

	class server_win : public server_base
	{
	public:
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
	};

	/* ------------------------------------------------------------ */

}