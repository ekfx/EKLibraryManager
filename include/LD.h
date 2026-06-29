#ifndef LD_H
#define LD_H

#include <Windows.h>
#include <string>
#include <map>
#include <iostream>
#include <utility>

namespace EKLM {
	// Library Downloader
	class LD {
	protected:
		std::string				ARCHIVE_NAME = "";
		std::string				DIR_NAME = "";
		std::string				URL_TGT = "";
		std::string				DIR_TGT = "";
		std::string				CMD_1 = "";
		std::string				CMD_2 = "";
		std::string				FCMD = "";
		std::string				INFO = "";

	public:
		LD() {};
		~LD() {};

		virtual void Start() = 0;
		virtual int SetDir(std::string dir) = 0;
		virtual int SetLink(std::string link) = 0;
		virtual int FuseCmd() = 0;
		virtual int DownloadCall() = 0;
		virtual void Delete() = 0;
		virtual void PrintInfo() = 0;
	};
};

#endif // LD_H