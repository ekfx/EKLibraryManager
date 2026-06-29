#include "LD_Windows.h"

EKLM::LDW::LDW() {};
EKLM::LDW::~LDW() {};

void EKLM::LDW::Start() {
	INFO += "EKLM::LDW::START::STARTING_LD\n";
};

int EKLM::LDW::SetDir(std::string dir) {
	if (!dir.empty()) {
		DIR_TGT = dir;
	}
	else {
		INFO += "EKLM::LDW::SETDIR::EMPTY_STRING\n";
		return -1;
	}

	return 0;
}

int EKLM::LDW::SetLink(std::string link) {
	if (!link.empty()) {
		URL_TGT = link;
	}
	else {
		INFO += "EKLM::LDW::SETLINK::EMPTY_STRING\n";
		return -1;
	}

	size_t start = URL_TGT.rfind('/');
	for (size_t i = start + 1; i < URL_TGT.length() - 1; i++) {
		ARCHIVE_NAME += URL_TGT[i];
	}

	return 0;
};

int EKLM::LDW::FuseCmd() {	// depends of a filesystem class to give security
	
	FCMD = CMD_1 + URL_TGT + CMD_2 + "\'" + DIR_TGT + "\\" + ARCHIVE_NAME + "'\"";

	INFO += FCMD + "\n";

	return 0;
}

int EKLM::LDW::DownloadCall() {
	FuseCmd();

	int result = system(FCMD.c_str());	// syntax error
	if (result != 0) {
		return -1;
	}

	std::string cmd_t = "if exist \"" + DIR_TGT + "\\" + ARCHIVE_NAME + "\"" + "exit /b 1 else exit /b 0";
	if (system(cmd_t.c_str()) != 0) {
		INFO += "EKLM::LDW::DOWNLOADCALL::COULDNT_CREATE_ARCHIVE\n";
	} 
};

void EKLM::LDW::Delete() {
};

void EKLM::LDW::PrintInfo() {
	std::cerr << INFO;
}