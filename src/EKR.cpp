#include "../include/EKR.h"

EKLM::EKR::EKR()
{
}

EKLM::EKR::~EKR()
{
}

int EKLM::EKR::Init(std::filesystem::path path)
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
				if (line[0] == '#' || line[0] == ' ') {

				}
				else {
					if (line[i] == ' ') {
						line.erase(line.begin() + i);
					}

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

			}

			if (line[0] != '#' || line[0] != ' ') {
				data.insert({ key, value });
				// std::cout << key << std::endl;
				auto it = data.find(key);
			}

			key = "";
			value = "";
			trigger_equal = false;
		}
	}
	else {
		INFO += "EKLM::EKR::START::COULDNT_OPEN_ARCHIVE\n";
		INFO += "EKLM::EKR::START::CURRENT_PATH::" + std::filesystem::current_path().string() + "\n";
		return -1;
	}
	eka.close();
	return 0;
}

std::string EKLM::EKR::GetValue(const std::string& key)
{
	auto it = data.find(key);

	if (it != data.end()) {
		return it->second;
	}
	else {
		std::cerr << "EKLM::EKR::GETVALUE::COULDNT_NOT_FOUND_KEY\n";
		INFO += "EKLM::EKR::GETVALUE::COULDNT_NOT_FOUND_KEY\n";
		return "EKLM::EKR::GETVALUE::COULDNT_NOT_FOUND_KEY";
	}
}

std::pair<std::string, std::string> EKLM::EKR::GetPair(const std::string& key) {
	auto it = data.find(key);

	if (it != data.end()) {
		return {it->first, it->second };
	}
	else {
		INFO += "EKLM::EKR::GETPAIR::COULDNT_NOT_FOUND_KEY\n";
		return { "0", "0" };	
	}
}

int EKLM::EKR::Exists(const std::string& key) {
	auto it = data.find(key);

	if (it != data.end()) {
		return 1;
	}
	else {
		INFO += "EKLM::EKR::GETPAIR::COULDNT_NOT_FOUND_KEY\n";
		return 0;	
	}
}

void EKLM::EKR::Delete()
{
}

void EKLM::EKR::PrintInfo() {
	std::cerr << INFO;
}
