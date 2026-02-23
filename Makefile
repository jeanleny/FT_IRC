#HEADER

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98 -MMD -MP -g
RM			= rm -f
HEADER		= include
SRC_DIR		= src
BUILD_DIR	= object
NAME		= ircserv
SRC			+= src/main.cpp						\
			   src/Server/Server.cpp			\
			   src/Server/ServerUtils.cpp		\
			   src/Server/ServerChannel.cpp		\
			   src/Server/ServerGame.cpp		\
			   src/Exception/Exception.cpp		\
			   src/Client/Client.cpp			\
			   src/Commands/PassCommand.cpp		\
			   src/Tools/utils.cpp				\
			   src/Channel/Channel.cpp			\
			   src/Commands/JoinCommand.cpp		\
			   src/Commands/NickCommand.cpp		\
			   src/Commands/UserCommand.cpp		\
			   src/Commands/PrivmsgCommand.cpp	\
			   src/Commands/KickCommand.cpp		\
			   src/Commands/TopicCommand.cpp	\
			   src/Commands/InviteCommand.cpp	\
			   src/Commands/ModeCommand.cpp		\
			   src/Commands/PartCommand.cpp		\
			   src/Commands/PlayCommand.cpp		\
			   src/Signals/Signals.cpp			\

OBJ			= ${SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o}
DEP			= $(OBJ:.o=.d)

all			: $(NAME)

$(NAME)		: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(DEPEND) -o $(NAME)

$(BUILD_DIR)/%.o	:$(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(HEADER) -c $< -o $@

clean				:
	$(RM) -r $(BUILD_DIR)

fclean				:	clean
	$(RM) $(NAME)

re					:	fclean all

.PHONY				:	all clean fclean re
-include $(DEP)
