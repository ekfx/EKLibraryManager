// /*/////////////////////////////////////////////////////////////////////////////////////
// 	Name: LibraryManager.cpp
// 	Created: 25/06/2026
// 	Last Modification: 01/07/2026
// 	Description:	This project will handle a small idea of 
// 					library manager, thats reads a file with links
// 					download those source codes, build them and
// 					link in the path. Originally thought to
// 					Windows user who wants to get started in
// 					programming world without many difficulties.
// 					In the future may I add Linux and MAC features.
// 					I hope I could end this project.

// 					Technologies:
// 					- Qt Framework
// 					- C++ 17
// 					- curl
// 					- miniz.h
// 					- CMake

// 					Today (28/06/2026): needs to improve the security
// 					and resistance of directories and urls, and
// 					get system messages.

// 					(01/07/2026): needs to improve existing files and
// 					get users strings

//					made by Eriksander P. Silva: github.com/ekfx/EKLibraryManager

// *//////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../include/EKLM.h"

int main(int argc, char* argv[]) {
	EKLM::CORE core;

	/*
		0 - reservado pro sistema, nome eu acho.
		1 - primeiro comando de fato
		2 - por ai vai
	*/

	std::string msg[argc];
	for (int i = 0; i < argc; i++) {
		msg[i] = argv[i];
	}

	if (argc < 2) {
		std::cout << "Please set more parameters, e.g.: eklm install library\n";
	} 
	
	if (msg[1] == "about") {
		if (argc >= 3) {
			std::cerr << "Too much parameters.\n";
			return -1;

		} else {
			std::string str;
	
			std::cout << "\n\n--------------------------------------------------------------\n";
			std::cout << "----------- EK Library Manager CMD Version -------------------\n";
			std::cout << "--------------------------------------------------------------\n\n";
			
			std::cout << "1. You Can See All Libraries in data.ek.\n";
			std::cout << "2. This is a initial student project to high school final exam.\n";
			std::cout << "3. I would be happy if you give me a feedback in github!\n";
			std::cout << "4. THANKS!\n\n";
			std::cout << "Made by: Eriksander Pereira da Silva | github.com/ekfx/EKLibraryManager\n\n";
		}
	} else if (msg[1] == "install") {
		if (argc <= 2) {
			std::cerr << "Please define the library, e.g.: eklm install library\n";

		} else if (argc > 4) {
			std::cerr << "Too much parameters.\n";
			return -1;

		} else {
			std::string lbry = msg[2];

			EKLM::EKR SRD;

			if (SRD.Init("C:/EKLMD/DATA/settings.ek") != 0) {
				std::cerr << "Couldn't found settings.ek at \"C:/EKLMD/DATA/settings.ek\", please create one or get\nfrom github.com/ekfx/EKLibraryManager.";
				return -1;

			} else {
				std::filesystem::path fdir = SRD.GetValue("download_dir");
				if (!std::filesystem::exists(fdir)) {
					std::filesystem::create_directory(fdir);
				}
	
				std::filesystem::path ddir = SRD.GetValue("source");
				if (!std::filesystem::exists(ddir)) {
					std::filesystem::create_directory(fdir);
				}

				core.SetDataDir(ddir.string()); 
				core.SetDir(fdir.string()); 
				core.SetKey(lbry);
		
				std::cout << "Starting\n";
				core.Init();
				core.Run();
				core.Delete();
				std::cout << "\nFinished\n";
			}
		}
	} else if (msg[1] == "version") {
		if (argc >= 3) {
			std::cerr << "Too much parameters.\n";
			return -1;

		} else {
			std::cout << "EK Library Manager v1.0 | Made by Eriksander P. Silva.\n";

		}
	} else if (msg[1] == "help") {
		if (argc >= 3) {
			std::cerr << "Too much parameters.\n";
			return -1;

		} else {
			std::cout << "EK Library Manager - Help\n";
			std::cout << "eklm                     -> Main program call;\n";
			std::cout << "install library          -> Program install library call;\n";
			std::cout << "debug                    -> Debug parameter;\n";
			std::cout << "version                  -> Show version.\n";
			std::cout << "More info at: github.com/ekfx/EKLibraryManager\n";

		}
	} else if (msg[1] == "line") {
		if (!msg[2].empty()) {
			// msg[2] -> KEY
			std::cerr << core.GetCompileLine(msg[2]) << std::endl;
		} else {
			std::cerr << "Please define the library, e.g.: eklm line library. Or use:\n";
			std::cerr << "g++ -std=c++17 main.cpp -o main\n";

		}
	} else if (msg[1] == "compile") {
		if (!msg[2].empty()) {
			system(core.GetCompileLine(msg[2]).c_str());

		} else {
			system("g++ -std=c++20 main.cpp -o main.exe");

		}
	} else {
		std::cerr << "Unknown Command. See eklm help to more info.\n";

	}

	if (msg[1] == "install" && msg[3] == "debug") {
		core.PrintAllInfo();
	}

	return 0;
}