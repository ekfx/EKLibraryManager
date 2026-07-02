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
// *//////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../include/EKLM.h"

int main() {
	EKLM::CORE core;
	std::string str;

	std::cout << "Digite uma biblioteca: ";
	std::getline(std::cin, str);
	core.SetKey(str);

	std::cout << "Digite endereco destino: ";
	std::getline(std::cin, str);	// aceita espaços, essa eu nao conhecia
	core.SetDownloadDir(str);

	core.Init();
	core.Run();
	core.Delete();

	return 0;
}