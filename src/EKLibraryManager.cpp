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
		std::cout << "Please set more parameters. E.g.: eklm install\n";
	} 
	
	if (msg[1] == "help") {
		std::string str;

		std::cout << "\n\n--------------------------------------------------------------\n";
		std::cout << "----------- EK Library Manager CMD Version -------------------\n";
		std::cout << "--------------------------------------------------------------\n\n";
		
		std::cout << "1. You Can See All Libraries in data.ek.\n";
		std::cout << "2. This is a initial student project to high school final exam.\n";
		std::cout << "3. I would be happy if you give me a feedback in github!\n";
		std::cout << "4. THANKS!\n\n";
		std::cout << "Made by: Eriksander Pereira da Silva | github.com/ekfx/EKLibraryManager\n\n";
			
	} else if (msg[1] == "install") {
		if (argc <= 2) {
			std::cerr << "Please define the library.\n";

		} else {
			std::string lbry = msg[2];
			std::filesystem::path fdir = std::filesystem::path("C:/EKLMD/");
			std::filesystem::path ddir = std::filesystem::path("C:\\Users\\black\\Documents\\EKLM\\data\\data.ek");
	
			core.SetDataDir(ddir.string()); 
			core.SetDir(fdir.string()); 
			core.SetKey(lbry);
	
			std::cout << "Initializing Download and Uncompressing.\n";
			core.Init();
			core.Run();
			core.Delete();
			std::cout << "\nFinished Download.\n";
		}
	} else if (msg[1] == "--version") {
		std::cout << "EK Library Manager v1.0 | Made by Eriksander P. Silva.\n";
	}

	if (msg[1] == "install" && msg[3] == "--debug") {
		core.PrintAllInfo();
	}

	return 0;
}