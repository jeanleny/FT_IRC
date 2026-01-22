#include "Server/Server.hpp"

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		Server	servInstance(argv[1], argv[2]);
		try 
		{
			servInstance.initServer();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		servInstance.runningServer();
	}
}
