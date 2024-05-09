#include <../includes/irc.h>

int main()
{
	Server server;
	std::cout << "Server started" << std::endl;
	try {
		server.ServerStart();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Server stopped" << std::endl;
}
