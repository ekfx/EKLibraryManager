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
#	include "../include/LD_Windows.h"

#	elif __linux__
	
#	elif __APPLE__
	
#	endif

#include "../include/EKR.h" // -> just reads a archive
#include "../include/CMD.h" // -> manages the system paths 
#include "../include/UZIP.h" // -> unzip library

int main() {
	std::cerr << "EKLM::MAIN::INITIALIZING\n";

	EKLM::EKR datafile;
	EKLM::CMD cmd;
	EKLM::UZIP zip;

	std::cerr << "EKLM::MAIN::ALLOCATED_MEMORY\n";

#	ifdef _WIN32

	std::cerr << "EKLM::MAIN::_WIN32\n";
	std::string key = "imgui";
	std::string dir = "D:\\EKLMD\\" + key;
	std::string cadd = "";

	// if (selecionar downloader) -> mais pra frente
	EKLM::LDW source;
	std::cerr << "EKLM::MAIN::ALLOCATING_DOWNLOAD_SOURCE\n";

	datafile.Start("data/data.ek");	// relativo a pasta do projeto
	std::cerr << "EKLM::MAIN::READING_DATA\n";
	/*
		Ending studies today. Tomorrow, please read this and
		cleanup and make a diagram or document that explain
		how it works; for my mind and who gonna see this.

		needs add comments syntax to .ek and improve this 
		unzipping system.
	*/
		source.Start();
		cmd.SetDir(dir);

		source.SetDir(cmd.GetDir().string());
		source.SetLink(datafile.GetValue(key));
		datafile.PrintInfo();
		if (cmd.CreateDir()) {
			std::cerr << "EKLM::MAIN::CREATING_DIRECTORY\n";
			// if the creation got success
			if (source.DownloadCall() == 0) {
				std::cerr << "EKLM::MAIN::DOWNLOADING\n";
				cadd = dir + "\\" + source.GetArchiveName();

				std::cout << dir << std::endl;

				if (zip.Unzip(cadd, dir) == 0) {
					std::cerr << "EKLM::MAIN::UNZIPPING\n";
					
				}
				zip.GetInfo();
			}
			source.PrintInfo();
		}
		else {
			std::cerr << "EKLM::MAIN::UNABLE_TO_CREATE_DIR\n";
		}

		source.Delete();
	datafile.Delete();
	std::cerr << "EKLM::MAIN::DELETING_MEMORY\n";

	//system("pause");

#	elif __linux__
	// doesn't have a linux downloader yet
#	elif __APPLE__
	// doesn't have a mac downloader yet
#	endif

	return 0;
}