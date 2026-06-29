#include "../include/EKR.h"

EKLM::EKR::EKR()
{
}

EKLM::EKR::~EKR()
{
}

void EKLM::EKR::Start(const char* path)
{
	INFO += "EKLM::EKR::START::STARTING_EKR\n";
	std::string line = "";
	std::string key = "";
	std::string value = "";
	bool trigger_equal = false;

	eka.open(path);
	if (eka.is_open()) {
		while (std::getline(eka, line)) {
			for (unsigned int i = 0; i < line.length(); i++) {

				if (line[i] == '=') {
					trigger_equal = true;
				}

				if (!trigger_equal) {
					key += line[i];
				}
				else {
					if (line[i] == '=') {
					}
					else {
						value += line[i];
					}
				}
			}

			data.insert({ key, value });
			auto it = data.find(key);

			key = "";
			value = "";
			trigger_equal = false;
		}
	}
	else {
		INFO += "EKLM::EKR::START::COULDNT_OPEN_ARCHIVE\n";
		INFO += "EKLM::EKR::START::CURRENT_PATH::" + std::filesystem::current_path().string() + "\n";
	}
	eka.close();
}

std::string EKLM::EKR::GetValue(std::string key)
{
	auto it = data.find(key);

	if (it != data.end()) {
		return it->second;
	}
	else {
		INFO += "EKLM::EKR::GETPAIR::COULDNT_NOT_FOUND_CONFIG\n";
		return "EKLM::EKR::GETPAIR::COULDNT_NOT_FOUND_CONFIG";
	}
}

std::pair<std::string, std::string> EKLM::EKR::GetPair(std::string key) {
	auto it = data.find(key);

	if (it != data.end()) {
		return {it->first, it->second };
	}
	else {
		INFO += "EKLM::EKR::GETPAIR::COULDNT_NOT_FOUND_CONFIG\n";
		return { "0", "0" };	
	}
}

void EKLM::EKR::Delete()
{
}