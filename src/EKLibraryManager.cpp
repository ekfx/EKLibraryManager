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

int main() {
	EKLM::CORE core;
	std::string str;

	std::cout << "--------------------------------------------------------------\n";
	std::cout << "----------- EK Library Manager CLI Version -------------------\n";
	std::cout << "--------------------------------------------------------------\n\n";

	std::cout << "1. You Can See All Libraries in data.ek.\n";
	std::cout << "2. This is a initial student project to high school final exam.\n";
	std::cout << "3. I would be happy if you give me a feedback in github!\n";
	std::cout << "4. THANKS!\n\n";
	std::cout << "Made by: Eriksander Pereira da Silva | github.com/ekfx/EKLibraryManager\n\n";

	std::cout << "Digite Uma Biblioteca: \n";
	std::cout << "Select a Library: \n";
	std::getline(std::cin, str);
	core.SetKey(str);
	std::cout << "\n";

	std::cout << "Endereco Destino / Final Address: \n";
	std::getline(std::cin, str);	// aceita espaços, essa eu nao conhecia
	core.SetDir(str); 
	std::cout << "\n";

	std::cout << "Endereco Relativo EK Data / EK Data Relative Address: \n";
	std::getline(std::cin, str);	
	core.SetDataDir(str);
	std::cout << "\n";

	core.Init();
	core.Run();
	core.Delete();

	core.PrintAllInfo();

	system("pause");

	return 0;
}