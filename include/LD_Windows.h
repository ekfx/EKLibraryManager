#ifndef LD_WINDOWS_H
#define LD_WINDOWS_H

#include "LD.h"
#include <Windows.h>
#include <winerror.h>
#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <filesystem>

namespace EKLM {	// uses powershell and batch -> strongly dependent
	// Library Downloader
	class LDW : public LD {	
	private:
		std::string				ARCHIVE_NAME = "";
		std::string				DIR_NAME = "";
		std::string				URL_TGT = "";
		std::string				CMD_1 = "powershell -Command \"Invoke-WebRequest -Uri ";
		std::string				CMD_2 = " -OutFile ";
		std::string				DIR_TGT = "C:\\EKLMD\\";
		std::string				FCMD = "";
		std::string				INFO = "";

	public:
		LDW();
		~LDW();

		void Start();
		int SetDir(std::string dir);
		int SetLink(std::string link);
		int FuseCmd();
		int DownloadCall();
		void Delete();
		void PrintInfo();
		std::string GetArchiveName();
	};
};

#endif // LD_WINDOWS_H