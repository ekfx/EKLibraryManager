#include "CMD.h"

EKLM::CMD::CMD()
{
};

EKLM::CMD::~CMD()
{
};

int EKLM::CMD::SetDir(std::filesystem::path dir) {
	if (dir.string().empty()) {
		INFO += "EKLM::CMD::SETDIR::EMPTY_STRING\n";
		return -1;
	}
	else {
		DIR = dir;
	}

	return 0;	// 0 -> success
}

int EKLM::CMD::CreateDir() {
	if (std::filesystem::create_directories(DIR.string())) {
		return 1;	// success and new created
	}
	else {
		if (std::filesystem::exists(DIR.string())) {
			INFO += "EKLM::CMD::CREATEDIR::DIRECTORY_ALREADY_EXISTS\n";
			INFO += "EKLM::CMD::CREATEDIR::DELETING_DIRECTORY\n";
			std::filesystem::remove_all(DIR.string());
			if (std::filesystem::create_directories(DIR.string())) {
				return 1;	// success and new created
			}
		}
	}

	return -1;
}

void EKLM::CMD::PrintInfo() {
	std::cerr << INFO;
}

std::filesystem::path EKLM::CMD::GetDir() {
	return DIR;
}