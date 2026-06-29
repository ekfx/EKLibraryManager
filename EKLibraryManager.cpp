/*/////////////////////////////////////////////////////////////////////////////////////
	Name: LibraryManager.cpp
	Created: 25/06/2026
	Last Modification: 28/06/2026
	Description:	This project will handle a small idea of 
					library manager, thats reads a file with links
					download those source codes, build them and
					link in the path. Originally thought to
					Windows user who wants to get started in
					programming world without many difficulties.
					In the future may I add Linux and MAC features.
					I hope I could end this project.

					Technologies:
					- Qt Framework
					- C++ 17
					- Powershell downloader
					- CMake

					Today (28/06/2026): needs to improve the security
					and resistance of directories and urls, and
					get system messages.
*//////////////////////////////////////////////////////////////////////////////////////

// Docs: https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.utility/invoke-webrequest?view=powershell-7.6
#include <iostream>

#	ifdef _WIN32
#	include "LD_Windows.h"

#	elif __linux__
	
#	elif __APPLE__
	
#	endif

#include "EKR.h" // -> just reads a archive
#include "CMD.h" // -> manages the system paths 

int main() {
	EKLM::EKR datafile;
	EKLM::CMD cmd;

#	ifdef _WIN32
	std::string key = "boost";
	std::string dir = "D:\\EKLMD\\" + key;

	// if (selecionar downloader) -> mais pra frente
	EKLM::LDW source;
	datafile.Start("data.ek");
		source.Start();
		cmd.SetDir(dir);

		source.SetDir(cmd.GetDir().string());
		source.SetLink(datafile.GetValue(key));
		if (cmd.CreateDir()) {
			// if the creation got success
			source.DownloadCall();
		}
		else {
			std::cerr << "EKLM::MAIN::UNABLE_TO_CREATE_DIR\n";
		}

		source.PrintInfo();
		source.Delete();
	datafile.Delete();

#	elif __linux__
	// doesn't have a linux downloader yet
#	elif __APPLE__
	// doesn't have a mac downloader yet
#	endif

	return 0;
}