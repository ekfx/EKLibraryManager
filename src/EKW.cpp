#include "../include/EKW.h"

EKLM::EKW::EKW() 
{
}

EKLM::EKW::~EKW() 
{
}

int EKLM::EKW::RegisterInFile(const std::string& path, const std::string& key, const std::string& value) {	
    EKR.Init(path);
    if (!EKR.Exists(key)) {
        // ou seja, se nao existe
        file.open(path, std::ios::app);

        if (file.is_open()) {
            std::string line = key + "=" + value + "\n";
            file.write(line.c_str(), line.size());

        } else {
            INFO += "EKLM::EKW::REGISTERINFILE::COULDNT_CREATE_OR_OPEN_FILE\n";
            std::cerr << "EKLM::EKW::REGISTERINFILE::COULDNT_CREATE_OR_OPEN_FILE\n";
            return -1;
        }
        
        file.close();
        return 0;

    } else {
        /*
            por enquanto eu vou apenar avisar e não fazer nada,
            não imagino que remover a chave ou atualizar seja de escolha
            do programa;	
        */
        INFO += "EKLM::EKW::REGISTERINFILE::THIS_KEY_ALREADY_EXISTS\n";
        std::cerr << "EKLM::EKW::REGISTERINFILE::THIS_KEY_ALREADY_EXISTS\n";
        return -1;
    }

    
}