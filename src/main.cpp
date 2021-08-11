#include "server.h"

// static const int listen_port = 65445;
// static const char *listen_addr = "127.0.0.1";

// int demo(int argc, char **argv)
// {
// 	WSADATA wsaData;
// 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
// 	{
// 		println("failed:WSAStartup error");
// 		return 1;
// 	};

// 	//server thread.
// 	std::thread([]() -> int
// 				{
// 					println("server starting...");

// 					SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
// 					if (s == INVALID_SOCKET)
// 					{
// 						println("failed:INVALID_SOCKET");
// 						return 1;
// 					}

// 					sockaddr_in sin;
// 					sin.sin_family = AF_INET;
// 					sin.sin_port = htons(listen_port);
// 					sin.sin_addr.S_un.S_addr = INADDR_ANY;

// 					if (bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
// 					{
// 						println("failed:SOCKET_ERROR");
// 						return 1;
// 					}

// 					if (listen(s, 5) == SOCKET_ERROR)
// 					{
// 						println("failed:listen()");
// 						return 1;
// 					}

// 					println("server started");

// 					SOCKET c;
// 					sockaddr_in cin;
// 					int addrlen = sizeof(cin);
// 					int read_size = 0;
// 					int count = 0;
// 					char buf[255];

// 					while (true)
// 					{
// 						if (count > 10)
// 							break;

// 						c = accept(s, (SOCKADDR *)&cin, &addrlen);
// 						count++;
// 						if (c == INVALID_SOCKET)
// 						{
// 							println("accept error!");
// 							continue;
// 						}

// 						read_size = recv(c, buf, 255, 0);
// 						if (read_size > 0)
// 						{
// 							buf[read_size] = '\0';
// 							println("server recv:");
// 							println(buf);
// 						}

// 						const char *ret = "ok!";
// 						send(c, ret, strlen(ret), 0);
// 						closesocket(c);
// 					}

// 					closesocket(s);
// 					WSACleanup();
// 					return 0;
// 				})
// 		.detach();

// 	for (int i = 0; i < 10; i++)
// 	{
// 		SOCKET c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
// 		if (c == INVALID_SOCKET)
// 		{
// 			return 1;
// 		}

// 		sockaddr_in svr_addr;
// 		svr_addr.sin_family = AF_INET;
// 		svr_addr.sin_port = htons(listen_port);
// 		svr_addr.sin_addr.S_un.S_addr = inet_addr(listen_addr);

// 		if (connect(c, (sockaddr *)&svr_addr, sizeof(svr_addr)) == SOCKET_ERROR)
// 		{
// 			closesocket(c);
// 			return 1;
// 		}

// 		std::string data;
// 		std::cin >> data;

// 		send(c, data.c_str(), data.size(), 0);

// 		char buf[255];
// 		int ret = recv(c, buf, 255, 0);
// 		if (ret > 0)
// 		{
// 			buf[ret] = '\0';
// 			println("client recv:");
// 			println(buf);
// 		}

// 		closesocket(c);
// 	}
// }

int main(int argc, char **argv)
{
	auto s = new Amaryllis::server_win("0.0.0.0", 33123);
	s->test();
}