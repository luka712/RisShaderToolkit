#include "process/process.hpp"
#if _WIN32
#include <windows.h>
#endif

#include <vector>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

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

	bool Process::launchMac(std::string command, std::string& output) {
#if __APPLE__

		// Parse command into arguments
		std::vector<std::string> args;
		std::stringstream ss(command);
		std::string arg;
		while (ss >> arg) {
			args.push_back(arg);
		}

		// Convert to char* array for execvp
		std::vector<char*> argv;
		for (auto& a : args) {
			argv.push_back(const_cast<char*>(a.c_str()));
		}
		argv.push_back(nullptr); // Null-terminate the array

		pid_t pid = fork();
		if (pid == -1) {
			std::cerr << "Fork failed: " << strerror(errno) << std::endl;
			return false;
		} else if (pid == 0) {
			// Child process
			execvp(argv[0], argv.data());
			std::cerr << "execvp failed: " << strerror(errno) << std::endl;
			return false;
		} else {
			int status;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status)) {
				std::cout << "Child exited with status " << WEXITSTATUS(status) << std::endl;
				return WEXITSTATUS(status) == 0;
			}
			return false;
		}
#endif
		output = "Not implemented on this platform.";
		return false;
	}

std::string Process::launch(std::string command) {
    std::string output;
#if _WIN32
    launchWin(command, output);
#elif __APPLE__
    launchMac(command, output);
#else
    output = "Not implemented on this platform.";
#endif
    return output;
}
}
