#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "client.hpp"
#include <vector>

class server
{
	private:
		std::string _port;
		std::string _pass;
		sockaddr_in serverAddress;
		int			mySocket;
		std::vector<client> clients;
		fd_set 		fr;

		
	public:
		server(std::string port, std::string pass);
		~server();
		std::string get_port();
		std::string get_pass();
		sockaddr_in	get_serverAdd();
		int			get_mySocket();
		void		server_setup();
		void 		createSocket();
		void 		server_init();
		void 		server_loop(int highest_fd, fd_set fr);
		void		server_new_clients(int highest_fd, fd_set tmp);
};


#endif