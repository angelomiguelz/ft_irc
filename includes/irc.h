#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()

class Client {
	public:
		Client();
		~Client();
		int GetFd(){return fd;};
		void SetFd(int fd) {this->fd = fd;};
		void SetIp(std::string ip) {this->ip = ip;};
	private:
		int fd;
		std::string ip;
};

class Server {
	public:
		Server();
		~Server();
		void ServerStart();
		void ServerSocket();
		void AcceptNewClient();
		void ReceiveNewData(int fd);
	private:
		int ServerPort;
		int ServerSocketFd;
		std::vector<Client> Clients;
		std::vector<struct pollfd> fds;
};