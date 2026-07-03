#ifndef EKW_H
#define EKW_H

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <utility>
#include "EKR.h"

namespace EKLM {
	class EKW {
	private:
		std::ofstream file;
		EKLM::EKR EKR;
		std::string	INFO;

	public:
		EKW();
		~EKW();

		int RegisterInFile(const std::string& path, const std::string& key, const std::string& value);
	};
};

#endif // EKW_H

