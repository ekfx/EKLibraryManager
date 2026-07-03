#ifndef EKR_H
#define EKR_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <utility>

namespace EKLM {
	// ek reader
	class EKR {
	private:
		// usar const char* não funciona, há comparação de 'maior que' debaixo do programa
		// string é o mais correto e seguro, e não é taaao pesado. Usar na inicialização
		std::map<std::string, std::string>	data;
		std::ifstream						eka;
		std::string							INFO;

	public:
		EKR();
		~EKR();

		int Init(std::filesystem::path path);
		std::string GetValue(const std::string& key);
		std::pair<std::string, std::string> GetPair(const std::string& key);
		int Exists(const std::string& key);
		void Delete();
		void PrintInfo();
	};
};

#endif // EKR_H

