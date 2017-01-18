#include "stdafx.h"
#include "Client.h"


void CClient::Wait(std::vector<std::string>& messages, size_t messageCount, const std::string& pipeName)
{
	std::wstring wStrName(pipeName.begin(), pipeName.end());
	HANDLE hPipe = CreateNamedPipe(wStrName.data(),					//lpName
		PIPE_ACCESS_DUPLEX,											//dwOpenMode
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,		//dwPipeMode
		PIPE_UNLIMITED_INSTANCES,									//nMaxInstances
		1024,														//nOutBufferSize
		1024,														//nInBufferSize
		5000,														//nDefaultTimeOut
		NULL);														//lpSecurityAttributes

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to create pipe" << std::endl;
		return;
	}

	size_t currentMessageCount = 0;
	while (currentMessageCount < messageCount)
	{
		if (ConnectNamedPipe(hPipe, NULL))
		{
			char buffer[1024];
			DWORD dwRead;
			if (ReadFile(hPipe,			//hFile
				buffer,					//lpBuffer
				sizeof(buffer),			//nNumberOfBytesToRead
				&dwRead,				//lpNumberOfBytesRead
				NULL))					//lpOverlapped
			{
				buffer[dwRead] = '\0';
			}
			messages.push_back(buffer);
			++currentMessageCount;

			std::cout << buffer << std::endl;
		}

		DisconnectNamedPipe(hPipe);
	}
	CloseHandle(hPipe);
}

void CClient::Send(const std::string& message, const std::string& pipeName)
{
	HANDLE hPipe;
	std::wstring wName(pipeName.begin(), pipeName.end());
	hPipe = CreateFile(wName.c_str(),			//lpFileName
		GENERIC_READ | GENERIC_WRITE,			//dwDesiredAccess
		0,										//dwShareMode
		NULL,									//lpSecurityAttributes
		OPEN_EXISTING,							//dwCreationDisposition
		0,										//dwFlagsAndAttributes
		NULL);									//hTemplateFile

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritten = DWORD(message.size());
		WriteFile(hPipe,						//hFile
			message.data(),						//lpBuffer
			dwWritten,							//nNumberOfBytesToWrite
			&dwWritten,							//lpNumberOfBytesWritten
			NULL);								//lpOverlapped
		CloseHandle(hPipe);
	}
}