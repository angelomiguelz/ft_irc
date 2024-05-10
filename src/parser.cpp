#include <../includes/irc.h>
#include <cstdlib>

std::vector<std::string> ft_split(std::string &s, char c) {
    std::vector<std::string> line_words;
    std::string token;
    size_t start = 0, end = 0;
    while ((end = s.find(c, start)) != std::string::npos) {
        token = s.substr(start, end - start);
        line_words.push_back(token);
        start = end + 1;
    }
    // Push the last token (or the only token if there is no delimiter)
    token = s.substr(start);
  	line_words.push_back(token);
    return line_words;
}

int filter_cmd(std::string line){
	std::vector<std::string> line_words = ft_split( line, ' ');
	std::string command = line_words.at(0);
	///////////////////////////////////////////////////////////////
	std::string tmp = "JOIN,KICK,BAN,"; //add others while we do the commands
	std::vector<std::string> commands = ft_split(tmp, ',');
	///////////////////////////////////////////////////////////////////////
	for (int i = 0;	i < (int)commands.size(); i++){
		//std::cout << "comparar ->> " << command << " ->>" << commands.at(i) << std::endl;
		if (command.compare(commands.at(i)) == 0){
			return (i);
		}
	}

	//command.erase(command.find_first_not_of(" ") command.s);
	//std::cout << command << std::endl;
	return (-1);
}


/// just for test i think we only need a func for each diff num of words that one command can take
/// send its not working idk why
void join(std::vector<std::string> line_words, int fd){
	if (line_words.size() != 2)
		send(fd, "Wrong size of words!!", 22, 0);
	else{
		std::string ola(line_words.at(0) + " " + line_words.at(1));
		send(fd, ola.c_str(), ola.size(), 0);
		std::cout << "ENTREI AQUI!!\n";
	}
}


/// adding when we start doing more comands
void execute(int num, std::vector<std::string> line_words, int fd){
	switch (num)
	{
	case 0:
		join(line_words, fd);
		break;
	/* case 1:
		kick(line_words);
		break;
	case 2:
		ban(line_words);
		break; */
	case -1:
		return;
	}
}

