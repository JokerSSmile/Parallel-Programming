#include "stdafx.h"
#include "Server.h"
#include "../Client4/Client.h"

CServer::CServer(size_t processCount, size_t iterationCount)
	: m_processCount(processCount)
	, m_iterationsCount(iterationCount)
{
}

void CServer::StartServer()
{
	std::vector<std::string> messageList;

	CClient::Wait(std::vector<std::string>(), m_processCount, "\\\\.\\pipe\\readypipe");
	std::cout << "All clients connected" << std::endl;
	std::cout << "Calculating...\n" << std::endl;///

	for (auto i = 0; i < m_processCount; ++i)
	{
		CClient::Send(std::to_string(m_iterationsCount), "\\\\.\\pipe\\startpipe");
	}

	CClient::Wait(std::ref(messageList), m_processCount, "\\\\.\\pipe\\workpipe");
}