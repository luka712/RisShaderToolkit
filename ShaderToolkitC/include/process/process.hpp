#ifndef PROCESS_H
#define PROCESS_H

#include <string>

namespace shader_toolkit {
	class Process {

	public:
		//! Launches a command using Windows API.
		//! @param command The command to launch.
		//! @return The output of the command.
		static bool launchWin(std::string command, std::string& output);

		static std::string launch(std::string command);
	};
}



#endif //PROCESS_H
