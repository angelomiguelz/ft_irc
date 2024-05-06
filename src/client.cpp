#include "client.hpp"

client::client(int _fd){
	std::cout << "Client constructer called\n";
	
	if (fd < 0){
		std::cout << "Error accepting new client" << std::endl;
		this->~client();
	}
	this->fd = _fd;
}

client::~client(){
	std::cout << "Client destructer called\n";
}

int client::get_fd(){
	return fd;
}
