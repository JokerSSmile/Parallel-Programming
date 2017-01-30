#pragma once
class CClient
{
public:
	CClient() = default;
	~CClient() = default;

	static void Wait(std::vector<std::string>& messages, size_t massageNumber, const std::string& pipeName);
	static void Send(const std::string & message, const std::string& pipeName);

private:
	static float m_startTime;
};

