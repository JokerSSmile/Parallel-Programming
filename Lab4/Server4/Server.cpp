#include "stdafx.h"
#include "Server.h"
#include "../Client4/PipeHelper.h"

const std::string READY_PIPE = "\\pipe\\readypipe";
const std::string START_PIPE = "\\pipe\\startpipe";
const std::string WORK_PIPE = "\\pipe\\workpipe";

CServer::CServer(size_t processCount, size_t iterationCount)
	: m_processCount(processCount)
	, m_iterationsCount(iterationCount)
{
}

void CServer::StartServer()
{
	std::vector<std::string> messageList;

	CClient::Wait(std::vector<std::string>(), m_processCount, READY_PIPE);
	std::cout << "All clients connected" << std::endl;
	std::cout << "Calculating...\n" << std::endl;///

	for (auto i = 0; i < m_processCount; ++i)
	{
		CClient::Send(std::to_string(m_iterationsCount), START_PIPE);
	}

	CClient::Wait(std::ref(messageList), m_processCount, WORK_PIPE);
}