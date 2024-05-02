#include "irc.hpp"

irc::irc(std::string port, std::string pass) : _port(port), _pass(pass){
	std::cout << "IRC constructer called\n";
}

irc::~irc(){
	std::cout << "IRC destructer called\n";
}

std::string irc::get_port(){
	return _port;
}

std::string irc::get_pass(){
	return _pass;
}

