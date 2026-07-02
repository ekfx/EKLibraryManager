#ifndef EKLM_H
#define EKLM_H

#include "../include/LD.h"
#include "../include/EKR.h" // -> just reads a archive
#include "../include/CMD.h" // -> manages the system paths 
#include "../include/UZIP.h" // -> unzip library

namespace EKLM {
    class CORE {
    private:
        EKLM::EKR DATA;
	    EKLM::CMD CMD;
	    EKLM::UZIP UZIP;
        EKLM::LDP LD;
        //EKLM::EKR SETTINGS;

        bool INITIALIZED                 = 0;                    
        bool INIT_KEY                    = 0;
        bool INIT_DIR                    = 0;
        bool INIT_DATA                   = 0;
        std::string KEY                  = "";
        std::filesystem::path DATA_NAME  = "data/data.ek";
        std::filesystem::path DIR        = "";
        std::filesystem::path FILE_DIR   = "";

        std::string INFO;
    public:
        CORE();
        ~CORE();

        int Init();
        int SetDataDir(const std::string& data);
        int SetKey(const std::string& key);
        int SetDir(const std::string& dir);
        int Run();
        void PrintInfo();
        void PrintAllInfo();
        void Delete();

    };
};

#endif // EKLM_H