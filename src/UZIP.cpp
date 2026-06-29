#include "../include/UZIP.h"

EKLM::UZIP::UZIP() 
{
}

EKLM::UZIP::~UZIP()
{
}

int EKLM::UZIP::Unzip(const char* path_source, const char* dest_path) {
	mz_zip_archive zip;	// ponteiro para a struct
	mz_zip_archive_file_stat archive_status;	// struct de dados do zip

	if (!std::filesystem::exists(path_source)) {
		INFO += "EKLM::UZIP::UNZIP::THIS_PATH_DOESNT_EXISTS\n";
		return -1;
	} 

	INFO += path_source; INFO += "\n";

	mz_bool status = mz_zip_reader_init_file(&zip, path_source, 0);	// inicializa leitor
	// retorna MZ_FALSE se der errado
	if (!status) { 
		INFO += "EKLM::UZIP::UNZIP::INIT_ERROR\n";
		return -1; 
	}

	unsigned int qty_arc = mz_zip_reader_get_num_files(&zip);
	// get numbers of archives inside the zip
	INFO += "EKLM::UZIP::UNZIP::" + std::to_string(qty_arc) + "_ARCHIVES\n";

	for (unsigned int i = 0; i < qty_arc; i++) {
		status = mz_zip_reader_file_stat(&zip, i, &archive_status);
		//archive_status is a pointer to a struct that contains data about a file in the zip archive
		if (!status) { 
			INFO += "EKLM::UZIP::UNZIP::ERROR_READING_ARCHIVE_STATUS\n";
			return -1; 
		}

		std::string filename = "";
		for (int j = 0; j < MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE; j++) {
			filename += archive_status.m_filename[j];
		}

		INFO += filename + "\n";
		filename = dest_path + '/' + filename;
		std::filesystem::create_directory(filename);
		mz_zip_reader_extract_to_file(&zip, i, filename.c_str(), 0);
	}

	mz_zip_reader_end(&zip);	// desaloca memoria

	INFO += "EKLM::UZIP::UNZIP::SUCCESS\n";
	return 0;
}

void EKLM::UZIP::GetInfo() {
	std::cerr << INFO;
}
