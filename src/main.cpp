#include "client.h"
#include <thread>

int main(int argc, char **argv)
{
	Amaryllis::client* c = new Amaryllis::client(Amaryllis::LOCAL_ADDR, 33123);
	if (c->connect() != Amaryllis::CLIENT_SUC) {
		return 1;
	}

	char buf[] = "hello world";

	for (;;) {
		int size = c->send(buf, 12);
		print("size is ");
		println(size);

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}