#pragma once
class CServer
{
public:
	CServer(size_t processCount, size_t iterationCount);

	void StartServer();

private:
	size_t m_processCount;
	size_t m_iterationsCount;
};

