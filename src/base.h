#pragma once
#include "util.h"

namespace Amaryllis
{
	typedef int ERR_CODE;
	static const char *LOCAL_ADDR = "127.0.0.1";
	static const char *ANY_ADDR = "0.0.0.0";

	enum CLIENT_ERR_CODE
	{
		CLIENT_SUC = ERR_CODE(0),
		ERR_INVALID_CLIENT_SOCKET,
		ERR_DNS_LOOKUP_FAILED,
		ERR_CLIENT_CONNECT_FAILED,
	};

	class client_base
	{
	public:
		client_base(const char *remote_ip, int remote_port);
		int remote_addr_size();
		void remote_addr(char *addr);

		virtual ERR_CODE connect() = 0;
		virtual int receive(char *buf, int buf_size) = 0;
		virtual int send(char *data, int data_size) = 0;

	protected:
		char remote_ip[16];
		int remote_port;
	};

	enum SERVER_ERR_CODE
	{
		SERVER_SUC = ERR_CODE(0),
		ERR_INVALID_SERVER_SOCKET,
		ERR_BIND_FAILED,
		ERR_LISTEN_FAILED,
		ERR_WSA_STARTUP_FAILED
	};

	class server_base
	{
	public:
		server_base(int port);
		server_base(const char *addr, int port);
		ERR_CODE serve();
		virtual client_base *accept() = 0;

	protected:
		int port;
		char addr[16];
		virtual ERR_CODE bind_and_listen() = 0;
	};
}