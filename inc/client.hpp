#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "iostream"

class client
{
	private:
		int fd;
		
	public:
		client(int _fd);
		~client();
		int get_fd();
};


#endif