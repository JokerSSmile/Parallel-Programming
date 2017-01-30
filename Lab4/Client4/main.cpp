#include "stdafx.h"
#include "PiCalculator.h"
#include "Client.h"
#include <ctime>

const std::string READY_PIPE =	"\\\\.\\pipe\\readypipe";
const std::string START_PIPE =	"\\\\.\\pipe\\startpipe";
const std::string WORK_PIPE =	"\\\\.\\pipe\\workpipe";

const std::string S_READY_PIPE = "\\\\127.0.0.1\\pipe\\readypipe";
const std::string S_START_PIPE = "\\\\127.0.0.1\\pipe\\startpipe";
const std::string S_WORK_PIPE = "\\\\127.0.0.1\\pipe\\workpipe";

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid calling client" << std::endl;
		return 1;
	}
	std::string clientName = argv[1];
	std::vector<std::string> messages;

	CClient::Send("Client '" + clientName + "' connected", READY_PIPE);
	CClient::Wait(messages, 1, START_PIPE);

	size_t iterCount = std::atoi(messages[0].c_str());
	std::string str = "Process " + clientName + " has finished\n" + 
		"\tResult: " + std::to_string(calcuator::CalculatePi(iterCount))+ "\n" +
		"\tTime spent:" + std::to_string(float(clock()) / CLOCKS_PER_SEC);
	CClient::Send(str, WORK_PIPE);

	return 0;
}

