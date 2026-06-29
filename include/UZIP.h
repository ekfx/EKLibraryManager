#ifndef UZIP_H
#define UZIP_H

#include "miniz.h"
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

		int Unzip(const char* path_source, const char* dest_path);
		void GetInfo();
	};
};

#endif // UZIP_H