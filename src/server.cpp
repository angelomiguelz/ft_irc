#include "server.hpp"

server::server(std::string port, std::string pass) : _port(port), _pass(pass){
	std::cout << "Server constructer called\n";
}

server::~server(){
	std::cout << "Server destructer called\n";
}

void server::server_setup(){
	struct sockaddr_in _serverAddress;
	_serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(4200);
    _serverAddress.sin_addr.s_addr = inet_addr(_port.c_str());
    memset(&(_serverAddress.sin_zero), 0, 8);
	this->serverAddress = _serverAddress;
}

void server::createSocket(){
	int _mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_mySocket < 0)
        std::cout << "Error creating socket" << std::endl;
     std::cout << "Socket Created" << std::endl;
	this->mySocket = _mySocket;
}

std::string server::get_port(){
	return this->_port;
}

std::string server::get_pass(){
	return this->_pass;
}

sockaddr_in	server::get_serverAdd(){
	return this->serverAddress;
}

int	server::get_mySocket(){
	return this->mySocket;
}

void server::server_init(){
	server_setup();
	createSocket();
	if (bind(mySocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
		 std::cout << "Error binding" << std::endl;
	std::cout << "Binded" << std::endl;
	if (listen(mySocket, 10) < 0)
		std::cout << "Error listening" << std::endl;
	std::cout << "listening" << std::endl;
	FD_ZERO(&fr);
    FD_SET(mySocket, &fr);
    int highest_fd = mySocket + 1;
	std::cout << highest_fd << std::endl;
	server_loop(highest_fd, fr);
	close(mySocket);
}

void server::server_new_clients(int highest_fd, fd_set fr_tmp){
	for (int i = 0; i <= highest_fd; i++){
		if (FD_ISSET(i, &fr_tmp)){
			if (i == highest_fd - 1){
				client tmp(accept(mySocket, NULL, NULL));
				FD_SET(tmp.get_fd(), &fr_tmp);
				clients.push_back(tmp);
				std::cout << clients.size() << std::endl;
				send(tmp.get_fd(), "Welcome!\n", 11, 0);
				//send(tmp.get_fd(), "/join #OLA\n", 13, 0);
				highest_fd += 1;
			}
		}
	}
}


void server::server_loop(int highest_fd, fd_set fr){
	while (true){
		fd_set tmp = fr;
		if (select(highest_fd, &tmp, NULL, NULL, NULL) < 0){
			std::cout << "Error in select()" << std::endl;
			break;
		}
		server_new_clients(highest_fd, tmp);
	}
}