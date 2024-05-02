NAME = ircserv

SRC_NAME = main.cpp irc.cpp client.cpp server.cpp

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g  -std=c++98
RM = rm -f

#$(VERBOSE).SILENT:
INC = -Iinc

SRC_PATH = ./src

OBJ_PATH = ./objects

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(NAME)
	clear

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	mkdir -p objects
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@
	@printf "                                                \n"
	@printf " ********************************************** \n"
	@printf " ********* Very good, Very nice!!! ************ \n"
	@printf " ********************************************** \n"
	@printf "                                                \n"

clean:
	$(RM)	$(SRC:=.o)
	clear
	@echo "                                                "
	@echo " ********************************************** "
	@echo " **********  So Clean It Shines!  ************* "
	@echo " ********************************************** "
	@echo "                                                "

fclean: clean
	$(RM)	$(NAME)

re:	fclean	$(NAME)
