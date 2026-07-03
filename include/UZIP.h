#ifndef UZIP_H
#define UZIP_H

#include <string>
#include <iostream>
#include <filesystem>

namespace EKLM {
	class UZIP {
	private:
		std::string INFO = "";
		std::string ROOT_NAME = "";

	public:
		UZIP();
		~UZIP();

		int Unzip(const std::string& path_source, const std::string& dest_path);
		void PrintInfo();
		std::string GetRootName();
	};
};

#endif // UZIP_H