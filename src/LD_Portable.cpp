#include <curl/curl.h>

#include "../include/LD.h"

EKLM::LDP::LDP() 
{
}

EKLM::LDP::~LDP() 
{
}

size_t EKLM::LDP::WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int EKLM::LDP::Init() 
{
    INFO += "EKLM::LDP::INIT::INITIALIZING_DOWNLOADER\n";

    curl = curl_easy_init();
    // inicializa curl
    if (!curl) {
        INFO += "EKLM::LDP::INIT::FAIL_TO_INITIALIZE\n";
        return -1;
    } else {
        return 0;
    }
}

int EKLM::LDP::SetURL(const std::string& url_target, const std::string& dir_out) 
{
    if (!url_target.empty()) {
        URL_TARGET = url_target;
    } else {
        INFO += "EKLM::LDP::SETURL::EMPTY_STRING::URL_TARGET\n";
        return -1;
    }

    if (!dir_out.empty()) {
        DIR_TARGET = dir_out;
    } else {
        INFO += "EKLM::LDP::SETDIR::EMPTY_STRING::DIR\n";
        return -1;
    }

    size_t start = URL_TARGET.rfind('/');
	for (size_t i = start + 1; i < URL_TARGET.length(); i++) {
		FILENAME += URL_TARGET[i];
	}

    return 0;
}

int EKLM::LDP::Download() 
{
    std::string OUTFILE = DIR_TARGET + "\\" + FILENAME;
    // INICIALIZANDO ARQUIVO DE SAIDA
    source = fopen(OUTFILE.c_str(), "wb"); // -> wb é um tipo de escrita binaria
    // é como se fosse abrir um arquivo e enfiar as coisas dentro
    
    if (source == nullptr) {
        INFO += "EKLM::LDP::DOWNLOAD::FAILED_TO_OPEN_OUTFILE\n";
        curl_easy_cleanup(curl);
        return -1;
    } else {
        INFO += "EKLM::LDP::DOWNLOAD::SUCCESS_TO_INITIALIZE\n";
    }

    // curl_easy_setopt -> set option/setar opcao

    // verificacoes ssl
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    // seta o url alvo
    curl_easy_setopt(curl, CURLOPT_URL, URL_TARGET.c_str());
    // diz qual funcao vai salvar os dados: WRITEFUNCTION
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, EKLM::LDP::WriteData);
    
    // é a funcao que seta qual é o arquivo que vai receber o download
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, source);
    
    // diz para seguir os redirecionamentos, é caso a página exija
    // mudança pra um https, por exemplo, e o curl poder prosseguir
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    // issue: add existing file verification
    if (std::filesystem::exists(DIR_TARGET + "\\" + FILENAME)) {
        succode = curl_easy_perform(curl);  // download de fato
        fclose(source);     // pega do buffer da ram e coloca em disco
        
		INFO += "EKLM::LDP::DOWNLOAD::DOWNLOADING\n";
	} else {
		INFO += "EKLM::LDP::DOWNLOAD::FILE_ALREADY_EXISTS\n";

		return -1;
	}

    if (succode == CURLE_OK) {
        INFO += "EKLM::LDP::DOWNLOAD::DOWNLOADED_SUCCEFULLY\n";
    } else {
        INFO += "EKLM::LDP::DOWNLOAD::FAIL_TO_DOWNLOAD\n";
        INFO += "EKLM::LDP::DOWNLOAD::STATUS";
        INFO += curl_easy_strerror(succode);
        INFO += "\n";
        return -1;
    }
    
    return 0;
}

void EKLM::LDP::Delete() 
{
    curl_easy_cleanup(curl);
    fclose(source);
}

void EKLM::LDP::PrintInfo() 
{
    INFO += "EKLM::LDP::FILENAME::" + FILENAME + "\n";
    INFO += "EKLM::LDP::URL_TARGET::" + URL_TARGET + "\n";
    INFO += "EKLM::LDP::OUTFILE::" + OUTFILE + "\n";
    INFO += "EKLM::LDP::DIR_TARGET::" + DIR_TARGET + "\n";

    std::cerr << INFO;
}

std::string EKLM::LDP::GetFileName() {
    return FILENAME;
}
