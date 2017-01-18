#include "stdafx.h"
#include "PiCalculator.h"
#include "Client.h"
#include <ctime>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid calling client" << std::endl;
		return 1;
	}
	std::string clientName = argv[1];
	std::vector<std::string> messages;

	CClient::Send("Client '" + clientName + "' connected", "\\\\.\\pipe\\readypipe");
	CClient::Wait(messages, 1, "\\\\.\\pipe\\startpipe");

	size_t iterCount = std::atoi(messages[0].c_str());
	std::string str = "Process " + clientName + " has finished\n" + 
		"\tResult: " + std::to_string(calcuator::CalculatePi(iterCount))+ "\n" +
		"\tTime spent:" + std::to_string(float(clock()) / CLOCKS_PER_SEC);
	CClient::Send(str, "\\\\.\\pipe\\workpipe");


	return 0;
}

