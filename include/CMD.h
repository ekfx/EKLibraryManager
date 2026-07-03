#ifndef CMD_H
#define CMD_H

#include <filesystem>
#include <iostream>
#include <string>

namespace EKLM {
	class CMD {
	private:
		std::string					INFO = "";
		std::filesystem::path		DIR;
		// C:/EKLMD/SFML

	public:
		CMD();
		~CMD();

		int SetDir(std::filesystem::path dir);
		int CreateDir();
		int DeleteDir();
		void PrintInfo();
		std::filesystem::path GetDir();
	};
};




#endif // CMD_H