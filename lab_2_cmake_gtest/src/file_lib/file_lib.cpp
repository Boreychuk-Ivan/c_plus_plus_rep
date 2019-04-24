#include "file_lib.h"

void ReadFile(const char* path, int* buffer, const size_t kNumVals)
{
	std::ifstream rd_file(path);

	if (!rd_file.is_open()) {
		std::cout << "Error! File was not opened.\n";
		exit(1);
	}

	rd_file.seekg(0, std::ios::beg);

	for (int it = 0; it < kNumVals; ++it) {
		if (!rd_file.eof()) {
			rd_file >> buffer[it];
		}
	}

	std::cout << "Successful read from file.\n";
	rd_file.close();
}

void WriteFile(const char* path, int* input_data, const size_t kNumVals){

	std::ofstream wr_file(path);

	if (!wr_file.is_open()) {
		std::cout << "Error! File was not opened.\n";
		exit(1);
	}

	for (int it = 0; it < kNumVals; ++it) {
		wr_file << input_data[it] << std::endl;
	}
	std::cout << "Successful write to file. \n";
	wr_file.close();
};