#include "../include/EKLM.h"

EKLM::CORE::CORE() 
{
}

EKLM::CORE::~CORE() 
{
}

int  EKLM::CORE::Init() 
{
    std::ios_base::sync_with_stdio(false);

    // Internal

    DIR = std::filesystem::path(DIR) / KEY;

    INFO += "EKLM::CORE::INIT::INITIALIZING\n";
    if (DATA.Init(DATA_NAME.string()) != 0) {
        std::cerr << "Couldn't found data.ek at \"C:/EKLMD/DATA/data.ek\", please create one or get\n";
        std::cerr << "from github.com/ekfx/EKLibraryManager. This is a\n";
        std::cerr << "important file that contains link source.";
        return -1;
    }
    
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
                    /*
                        plans to not use path, but create a .bat or automatize the cmd line
                        to compile, due to overcharge of the path, I will just create the 
                        cmd line and put it on a archive, adding the directory lib and include
                        for each library that the user wants. I will need two files:
                        1. the cmd line
                        2. the installed libraries and their respective directories

                        I will read the 2 and put it all on a map, in the program I will automatize
                        the -I and -L flags using the directories in the file; prevening errors,
                        I will check if the directory exists, else I will return -1 and exit.

                        by the way, I want to create a friendly environment and create buttons like:
                        <debug compile> -> this help you, developer, to find errors and create a better application.

                        when I finish this logic part, I want to get started in QT and  create this
                        helper to beginners. I don't know HOW I will find the compiler or if the user
                        doesn't have a compiler, but its the 4th day of this project, and I have 2,5 years,
                        so I have time.
                    */

                    std::string _DIR = (std::filesystem::path(DIR.string()) / UZIP.GetRootName()).make_preferred().string();
                    std::string _I = "-I" + _DIR + "include ";
                    std::string _L = "-L" + _DIR + "lib";
                    std::string _l = "-l";
                    EKW.RegisterInFile(std::filesystem::path("C:\\EKLMD\\DATA\\" + KEY + ".ek").string(), "name", KEY);
                    EKW.RegisterInFile(std::filesystem::path("C:\\EKLMD\\DATA\\" + KEY + ".ek").string(), "directory", _DIR);
                    EKW.RegisterInFile(std::filesystem::path("C:\\EKLMD\\DATA\\" + KEY + ".ek").string(), "include", _I);
                    EKW.RegisterInFile(std::filesystem::path("C:\\EKLMD\\DATA\\" + KEY + ".ek").string(), "lib", _L);
                    EKW.RegisterInFile(std::filesystem::path("C:\\EKLMD\\DATA\\" + KEY + ".ek").string(), "flags", _l);

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

std::string EKLM::CORE::GetCompileLine(const std::vector<std::string>& KEY, EKLM::EKR& SETTINGS) {
    EKLM::EKR LIBS;

    std::string name = "";
    std::string compiler = SETTINGS.GetValue("compiler");
    std::string version = SETTINGS.GetValue("version");
    std::string file_tgt = SETTINGS.GetValue("main_file_name");
    std::string exit_file_name = SETTINGS.GetValue("exit_file_name");
    std::string root_lib = "";
    std::string _I = "";    // include
    std::string _L = "";    // libs
    std::string _l = "";    // flags
    std::string _m = "";    // modifiers

    std::cout << "\n\n";

    for (auto& i : KEY) {
        name = "C:\\EKLMD\\DATA\\";
        name += i; 
        name += ".ek";
        LIBS.Init(std::filesystem::path(name));
        //root_lib = LIBS.GetValue("directory");
        _I += LIBS.GetValue("include") + " ";
        //_L += LIBS.GetValue("lib") + " ";
        _l += LIBS.GetValue("flags") + " ";
        _m += SETTINGS.GetValue("modifiers") + " ";
    }
    
    std::string cmd = compiler + " " + version + " " + file_tgt + " " + root_lib + " " + _I + " " + _L + " " + _l + " " + _m + " " + exit_file_name;

    return cmd;
    // x86_64-w64-mingw32-g++ -Iinclude -MMD -MP -O0 -g0 -pipe -ID:/vcpkg/packages/curl_x64-windows/include -c src/EKLM.cpp -o build/EKLM.o
    // <compilador> <versão c++> <arquivo alvo> <raiz biblioteca> <include -I> <libs -L> <flags -l> <modificador> <arquivo final>
}

void EKLM::CORE::Delete() 
{
    LD.Delete();
    DATA.Delete();
}
