#include "irc.hpp"

/* int main(int ac, char **av){
	(void)av;
	if (ac != 3) {
		exit(1);
	}
	irc ola(av[1], av[2]);

	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0){
		std::cout << "error creating socket\n";
		exit (1);
	}
	std::string ip = "127.0.0.1";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(2021);
	inet_pton(AF_INET, ip.c_str(), &address.sin_addr.s_addr);

	if (bind(socket_fd, (const sockaddr*) &address, sizeof address) == 0){
		std::cout << "bind worked\n";
	}
	int connec = connect(socket_fd, (const sockaddr*) &address, sizeof address);

	if (connec == 0)
		std::cout << "worked\n";
	std::cout << connec << std::endl;
		
	while (1){
		std::string buffer = "ola\n";
		send(socket_fd, buffer.c_str(), buffer.length(), 0);

		char rec_buffer[1024];
		recv(socket_fd, rec_buffer, 1024, 0);

		if (rec_buffer)
			std::cout << "response was -> " << rec_buffer << std::endl;
	}
} */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

struct sockaddr_in serverAddress;
fd_set fr, fw, fe;

int main()
{
    // Create a socket
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket < 0)
        std::cout << "Error creating socket" << std::endl;
    else
        std::cout << "Socket Created" << std::endl;

    // Initialize the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4200);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(serverAddress.sin_zero), 0, 8);
    // bind
    int ret = bind(mySocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (ret < 0)
        std::cout << "Error binding" << std::endl;
    else
        std::cout << "Binded" << std::endl;
    // listens
    ret = listen(mySocket, 5);
    if (ret < 0)
        std::cout << "Error listening" << std::endl;
    else
        std::cout << "Listening" << std::endl;

    FD_ZERO(&fr);
    FD_SET(mySocket, &fr);
    int highest_fd = mySocket + 1;
    while (1)
    {
        fd_set tmp = fr;

        //std::cout << "Waiting for activity..." << std::endl;
        std::cout << "test" << std::endl;
        ret = select(mySocket + 1, &tmp, NULL, NULL, NULL);
        std::cout << "test" << std::endl;
        if (ret < 0) {
            std::cout << "Error in select()" << std::endl;
            break;
        }
        for (int i = 0; i < highest_fd; ++i){
            if (FD_ISSET(i, &tmp)) {
                if (i == mySocket){
                    int new_client_fd = accept(mySocket, NULL, NULL);
                    if (new_client_fd <= 0)
                        std::cout << "Error accepting new client" << std::endl;
                    else {
                        std::cout << "New client connected" << std::endl;
                        FD_SET(new_client_fd, &fr);
                        if (new_client_fd >= highest_fd) {
                            highest_fd = new_client_fd + 1;
                        }
                        std::string msg = "Welcome!\n";
                        //send(new_client_fd, msg.c_str(), msg.size(), 0);
                    }
                }
            } 
            else {
                char buff[1024];
                int bytesrecive = recv(i, buff, sizeof(buff), 0);
                if (bytesrecive < 0) {
                    //close(i);
                    FD_CLR(i, &fr);
                    //std::cout << "ola\n";
                } 
                else {
                    for (int j = mySocket + 1; j < highest_fd; ++j) {
                        if (FD_ISSET(j, &fr) && j != i) {
                            std::cout << buff;
                            send(j, buff, bytesrecive, 0);
                        }
                    }
                }
            }
        }
    }
    close(mySocket);
}