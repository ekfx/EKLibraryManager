#ifndef LD_PORTABLE_H
#define LD_PORTABLE_H

#include <cstdio>   // FILE
#include <iostream>
#include <string>
#include <filesystem>
#include <curl/curl.h>

namespace EKLM {
    class LDP {
    private:
        CURL*       curl;
        FILE*       source;
        CURLcode    succode;
        
        std::string INFO;
        std::string URL_TARGET;
        std::string OUTFILE;
        
        std::string DIR_TARGET;
        std::string FILENAME;
        
    public:
        LDP();
        ~LDP();
        
        // callback para o curl gravar toda vez que receber parte do download
        static size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream);
        static int ShowBar(void* clientp, curl_off_t dltotal, curl_off_t dlnow,
                           curl_off_t ultotal, curl_off_t ulnow);

        int Init();
        int SetURL(const std::string& url_target, const std::string& dir_out);
        int Download();
        void Delete();
        void PrintInfo();
        std::string& GetFileName();

    };
};

#endif // LD_PORTABLE_H