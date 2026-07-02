#include "../include/EKLM.h"

EKLM::CORE::CORE() 
{
}

EKLM::CORE::~CORE() 
{
}

int  EKLM::CORE::Init() 
{
    DIR = std::filesystem::path(DIR) / KEY;

    INFO += "EKLM::CORE::INIT::INITIALIZING\n";
    DATA.Init(DATA_NAME.string().c_str());
    
    LD.Init();
    LD.SetURL(DATA.GetValue(KEY), DIR.string());
    
    CMD.SetDir(DIR.string());

    INITIALIZED = true;

    return 0;
}

int EKLM::CORE::SetDataDir(const std::string& data) {
    if (!data.empty()) {
        DATA_NAME = data;
    } else {
        INFO += "EKLM::CORE::SETDATADIR::EMPTY_STRING\n";
        return -1;
    }

    INIT_DATA = true;

    return 0;
}

int  EKLM::CORE::SetKey(const std::string& key) 
{
    if (!key.empty()) {
        KEY = key;
    } else {
        INFO += "EKLM::CORE::SETKEY::EMPTY_STRING\n";
        return -1;
    }

    INIT_KEY = true;

    return 0;
}

int  EKLM::CORE::SetDir(const std::string& dir) 
{
    if (!dir.empty()) {
        DIR = dir;
    } else {
        INFO += "EKLM::CORE::SETDIR::EMPTY_STRING\n";
        return -1;
    }

    INIT_DIR = true;

    return 0;
}

int  EKLM::CORE::Run() 
{
    if (INITIALIZED && INIT_DIR && INIT_KEY && INIT_DATA) {
        if (CMD.CreateDir()) {
            // success
            if (LD.Download() == 0) {
                FILE_DIR = std::filesystem::path(DIR) / LD.GetFileName();

                if (UZIP.Unzip(FILE_DIR.string(), DIR.string()) == 0) {
                    // build and path codes here

                    return 0;
                } else {
                    INFO += "EKLM::CORE::RUN::COULD_NOT_UNZIP\n";
                    return -1;
                }

            } else {
                INFO += "EKLM::CORE::RUN::COULD_NOT_DOWNLOAD\n";
                return -1;
            }
        } else {
            INFO += "EKLM::CORE::RUN::COULD_NOT_CREATE_DIR\n";
            return -1;
        }
    } else {
        INFO += "EKLM::CORE::RUN::PLEASE_INITIALIZE_SETTINGS_FIRST\n";
        return -1;
    }
}

void EKLM::CORE::PrintInfo() 
{
    std::cerr << INFO;
}

void EKLM::CORE::PrintAllInfo() 
{
    std::cerr << INFO;
    DATA.PrintInfo();
    CMD.PrintInfo();
    UZIP.PrintInfo();
    LD.PrintInfo();
}

void EKLM::CORE::Delete() 
{
    LD.Delete();
    DATA.Delete();
}
