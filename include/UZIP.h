#ifndef UZIP_H
#define UZIP_H

#include <string>
#include <iostream>
#include <filesystem>

namespace EKLM {
	class UZIP {
	private:
		std::string INFO = "";

	public:
		UZIP();
		~UZIP();

		int Unzip(const std::string& path_source, const std::string& dest_path);
		void GetInfo();
	};
};

#endif // UZIP_H