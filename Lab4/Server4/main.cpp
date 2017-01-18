// Server.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Server.h"
namespace
{

	void PrintHelp()
	{
		std::cout << "Usage Server.exe <iterations count> <process count>" << std::endl;
	}
}

int main(int argc, char *argv[])
{
	if(argc > 1 && argv[0] == "/?")
	{
		PrintHelp();
		return 0;
	}
	if (argc == 3)
	{
		CServer server(std::atoi(argv[2]), std::atoi(argv[1]));
		server.StartServer();
		return 0;
	}
}

