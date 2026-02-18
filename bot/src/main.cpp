#include <BotGameMaster.hpp>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Please enter the first argument as the server port and the second as password" << std::endl;
		return (0);
	}
	BotGameMaster gm(argv[1], argv[2]);
	gm.initBot();
	gm.connectServer();
	return (1);
}
