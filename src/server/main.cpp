#include "../server.h"
#include "../client.h"
#include "thread"

struct chat_client
{
	int id;
	Amaryllis::client *c;
};

//2006-01-02 15:04:050
void current_time_str(char *dst)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	sprintf(dst, "%d-%d-%d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
}

const char *msgFmt = "%d\t%s\r\n%s";
chat_client client_container[10];
int id = 0;

void send_to_others(int srcCid, const char *msg)
{
	int msg_size = strlen(msg);
	char buf[2048];
	for (int i = 0; i < id; i++)
	{
		if (srcCid == i)
		{
			continue;
		}

		char timeStr[20];
		current_time_str(timeStr);
		sprintf(buf, msgFmt, srcCid, timeStr, msg);

		client_container[i].c->send(buf, strlen(buf));
	}
}

void new_client(Amaryllis::client *c)
{
	print("new client");
	println(id);
	chat_client cc{id, c};
	client_container[id] = cc;
	int cId = id++;

	std::thread t([cId]() -> void
				  {
					  chat_client cc = client_container[cId];
					  char buf[1024];
					  int read_size = 0;
					  for (;;)
					  {
						  read_size = cc.c->receive(buf, 1024);
						  if (read_size > 0)
						  {
							  buf[read_size] = '\0';
							  send_to_others(cId, buf);
						  }
					  }
				  });

	t.detach();
}

void start_server()
{
	println("server mode");
	Amaryllis::server s(Amaryllis::LOCAL_ADDR, 65444);
	if (s.serve() != Amaryllis::SERVER_SUC)
	{
		return;
	}

	for (;;)
	{
		Amaryllis::client *c = s.accept();
		new_client(c);
	}
}

void client_mode()
{
	auto c = new Amaryllis::client(Amaryllis::LOCAL_ADDR, 65444);
	if (c->connect() != Amaryllis::CLIENT_SUC)
	{
		print("connect error");
		return;
	}

	std::thread t([c]() -> void
				  {
					  char buf[2048];
					  for (;;)
					  {
						  int size = c->receive(buf, 2048);
						  if (size > 0)
						  {
							  buf[size] = '\0';
							  println("got message");
							  println(buf);
						  }
					  }
				  });

	for (;;)
	{
		char buf[2048];
		println("input your msg");
		std::cin.getline(buf, 2048);
		c->send(buf, strlen(buf));
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		println("need param c/s");
		return 1;
	}

	switch (argv[1][0])
	{
	case 'c':
		client_mode();
		break;

	case 's':
		start_server();
		break;

	default:
		println("error param");
		break;
	}
}