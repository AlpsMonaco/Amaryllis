#pragma once
#include "util.h"

#ifdef _WIN32
#define _WIN_ENVIROMENT 1
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

namespace Amaryllis
{
	typedef int ERR_CODE;

	enum CLIENT_ERR_CODE
	{
		CLIENT_SUC = ERR_CODE(0),
		ERR_INVALID_CLIENT_SOCKET,
		ERR_DNS_LOOKUP_FAILED,
		ERR_CLIENT_CONNECT_FAILED,
	};

	/* ------------------------------------------------------------ */
	class client_base
	{
	public:
		client_base(const char *remote_ip, int remote_port);
		int remote_addr_size();
		void remote_addr(char *addr);

		virtual ERR_CODE connect() = 0;
		virtual void receive(char *buf, int buf_size) = 0;
		virtual void send(char *data, int data_size) = 0;

	protected:
		char *remote_ip;
		int remote_port;
	};

	/* ------------------------------------------------------------ */
	class client_win : public client_base
	{
	public:
		ERR_CODE connect();

	protected:
		SOCKET s;
	};

#ifdef _WIN_ENVIROMENT
	using client = client_win;
#else
	using client = client_linux;
#endif

}
