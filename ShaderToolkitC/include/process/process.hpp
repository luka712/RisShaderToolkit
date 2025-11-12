#ifndef PROCESS_H
#define PROCESS_H

#include <string>

namespace ris_shader_toolkit {
	class Process {

	public:
		//! Launches a command using Windows API.
		//! @param command The command to launch.
		//! @return The output of the command.
		static bool launchWin(std::string command, std::string& output);

		//! Launches a command using MacOS API.
		//! @param command The command to launch.
		//! @return The output of the command.
		static bool launchMac(std::string command, std::string& output);

		//! Launches a command and returns the output as a string.
		//! @param command The command to launch.
		static std::string launch(std::string command);
	};
}



#endif //PROCESS_H
