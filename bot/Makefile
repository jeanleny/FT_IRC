#HEADER

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98 -MMD -MP -g
RM			= rm -f
HEADER		= include
SRC_DIR		= src
BUILD_DIR	= object
NAME		= GM
SRC			+= src/main.cpp						\
			   src/BotGameMaster.cpp			\
			   src/BotCommandManager.cpp		\
			   src/BotCorridorManager.cpp		\
			   src/BotRoom1Manager.cpp			\
			   src/BotRoom2Manager.cpp			\
			   src/BotCmdParsing.cpp			\
			   src/BotInit.cpp					\
			   src/BotAsciiArt.cpp				\
			   src/BotSignals.cpp				\
			   src/Player.cpp

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
