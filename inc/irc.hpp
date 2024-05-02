#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>



class irc
{
	private:
		std::string _port;
		std::string _pass;
	public:
		irc(std::string port, std::string pass);
		~irc();
		std::string get_port();
		std::string get_pass();
};


#endif