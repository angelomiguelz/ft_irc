#include <../includes/irc.h>

//Client

Client::Client() {};

Client::~Client() {};

//Server

Server::Server() {};

Server::~Server() {};

void Server::AcceptNewClient() {
	Client client;
	struct sockaddr_in Addr;
	struct pollfd Poll;
	socklen_t len = sizeof(Addr);

	int ClientFd = accept(ServerSocketFd, (sockaddr *)&(Addr), &len); // accepts the new client
	if (ClientFd == -1)
		std::cout << std::endl << "Accept Failed" << std::endl;
	if (fcntl(ClientFd, F_SETFL, O_NONBLOCK) == -1)
		std::cout << std::endl << "Fcntl Failed" << std::endl;
	Poll.fd = ClientFd;
	Poll.events = POLLIN;
	Poll.revents = 0;
	
	client.SetFd(ClientFd);
	client.SetIp(inet_ntoa((Addr.sin_addr)));
	Clients.push_back(client);
	fds.push_back(Poll);

	std::cout << "Client :" << ClientFd << " connected." << std::endl;
}

void Server::ReceiveNewData(int fd)
{
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer)); //clear buffer

	ssize_t bytes = recv(fd, buffer, sizeof(buffer) - 1, 0); // receive data from givin fd

	if (bytes <= 0){ //if client disconnected
		std::cout << std::endl << "Client Disconnected" << std::endl;
		close(fd);
	}
	else { //print the receive data
		buffer[bytes] = 0;
		std::cout << "Client: " << fd << "> Data: " << buffer << std::endl;
	}
}

void Server::ServerSocket() {
	struct sockaddr_in Addr;
	struct pollfd Poll;

	Addr.sin_family = AF_INET; // sets the addr to ipv4
	Addr.sin_port = htons(this->ServerPort);
	Addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ServerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocketFd == -1)
		std::cout << std::endl << "Failed creating server socket" << std::endl;
	int en = 1;
	if (setsockopt(ServerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		std::cout << std::endl << "Failed to set option REUSE on socket" << std::endl;
	if (fcntl(ServerSocketFd, F_SETFL, O_NONBLOCK) == -1)
		std::cout << std::endl << "Failed to set option NONBLOCK on socket" << std::endl;
	if (bind(ServerSocketFd, (struct sockaddr *)&Addr, sizeof(Addr)) == -1)
		std::cout << std::endl << "Failed to bind socket" << std::endl;
	if (listen(ServerSocketFd, SOMAXCONN) == -1)
		std::cout << std::endl << "Failed listening" << std::endl;
	Poll.fd = ServerSocketFd;
	Poll.events = POLLIN; // sets event for reading data
	Poll.revents = 0;
	fds.push_back(Poll); // add the server socket to the pollfd
};

void Server::ServerStart() {
	this->ServerPort = 6969;
	ServerSocket();

	std::cout << "Server listening on port " << this->ServerPort << "...\n";

	while (1) {
		if (poll(&fds[0], fds.size(), -1) == -1) //waits for an event
			std::cout << std::endl << "Poll failed" << std::endl;
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents && POLLIN) // check if theres data to read
			{
				if (fds[i].fd == ServerSocketFd)
					AcceptNewClient();
				else
					ReceiveNewData(fds[i].fd);
			}
		}
	}
};