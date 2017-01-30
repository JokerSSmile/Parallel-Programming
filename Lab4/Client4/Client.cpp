#include "stdafx.h"
#include "Client.h"
#include <windows.h>
#include <stdio.h>

void CClient::Wait(std::vector<std::string>& messages, size_t messageCount, const std::string& pipeName)
{
	std::wstring wStrName(pipeName.begin(), pipeName.end());
	HANDLE hPipe = CreateNamedPipe(wStrName.data(),					//lpName
		PIPE_ACCESS_DUPLEX | FILE_FLAG_WRITE_THROUGH,				//dwOpenMode
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,		//dwPipeMode
		PIPE_UNLIMITED_INSTANCES,									//nMaxInstances
		1024,														//nOutBufferSize
		1024,														//nInBufferSize
		5000,														//nDefaultTimeOut
		NULL);														//lpSecurityAttributes

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to create pipe" << std::endl;
		//std::cout << GetLastError() << std::endl;
		throw std::exception();
	}

	size_t currentMessageCount = 0;
	while (currentMessageCount < messageCount)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			char buffer[1024];
			DWORD dwRead;
			if (ReadFile(hPipe,			//hFile
				buffer,					//lpBuffer
				sizeof(buffer),			//nNumberOfBytesToRead
				&dwRead,				//lpNumberOfBytesRead
				NULL) == TRUE)					//lpOverlapped
			{
				buffer[dwRead] = '\0';
			}
			messages.push_back(buffer);
			std::cout << buffer << std::endl;
			++currentMessageCount;
		}

		DisconnectNamedPipe(hPipe);
	}
	CloseHandle(hPipe);
}

void CClient::Send(const std::string& message, const std::string& pipeName)
{
	HANDLE hPipe;
	std::wstring wName(pipeName.begin(), pipeName.end());

	do
	{
		hPipe = CreateFile(wName.c_str(),			//lpFileName
			GENERIC_READ | GENERIC_WRITE,			//dwDesiredAccess
			0,										//dwShareMode
			NULL,									//lpSecurityAttributes
			OPEN_EXISTING,							//dwCreationDisposition
			0,										//dwFlagsAndAttributes
			NULL);									//hTemplateFile

	} while (hPipe == INVALID_HANDLE_VALUE);

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritten = DWORD(message.size());

		while (WriteFile(hPipe,					//hFile
			message.data(),						//lpBuffer
			dwWritten,							//nNumberOfBytesToWrite
			&dwWritten,							//lpNumberOfBytesWritten
			NULL) == FALSE						//lpOverlapped
			)
		{

		}

		CloseHandle(hPipe);
	}
}