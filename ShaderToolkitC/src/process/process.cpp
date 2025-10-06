#include "process/process.hpp"
#if _WIN32
#include <windows.h>
#endif

namespace shader_toolkit {
	bool Process::launchWin(std::string command, std::string& output) {
#if _WIN32
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = NULL;

		HANDLE hRead, hWrite;
		if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
			output = "Failed to create pipe.";
			return false;
		}

		// Ensure read handle is not inherited
		SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

		STARTUPINFOA si = { sizeof(si) };
		PROCESS_INFORMATION pi;

		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdOutput = hWrite;
		si.hStdError = hWrite;

		// Make a writable buffer for CreateProcess
		char cmdline[1024];
		strcpy_s(cmdline, command.c_str());

		if (!CreateProcessA(
			NULL,
			cmdline,
			NULL, NULL,
			TRUE, // Inherit handles
			0, NULL, NULL,
			&si, &pi))
		{
			CloseHandle(hRead);
			CloseHandle(hWrite);
			output = "Failed to create process.";
			return false;
		}

		// Close the write end in our process
		CloseHandle(hWrite);

		// Read output
		std::string out;
		char buffer[256];
		DWORD bytesRead;
		while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
			buffer[bytesRead] = '\0';
			out += buffer;
		}

		// Wait for fxc to finish
		WaitForSingleObject(pi.hProcess, INFINITE);

		DWORD exitCode;
		GetExitCodeProcess(pi.hProcess, &exitCode);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(hRead);

		out += "\nExit code: " + std::to_string(exitCode);
		output = out;
		return exitCode == 0;
#endif
		output = "Not implemented on this platform.";
		return false;
	}
}