#include "pch.h"
#include "lab1_lib.h"


int main()
{

	const int kNumVals = 40;
	TestSortRandomNumbers(Mergesort, kNumVals);
	TestSortSortedNumbers(Mergesort, kNumVals);
	TestSortGrandeRow(Mergesort, kNumVals);
	TestSortReverseOrder(Mergesort, kNumVals);
	TestSortEmptyPointer(Mergesort);
	TestSortSignleNum(Mergesort);


	const char* rd_path = "input_data.txt";
	int* rd_data = new int[kNumVals];
	
	ReadFile(rd_path, rd_data, kNumVals);

	for (int it = 0; it < kNumVals; ++it) {
		std::cout << rd_data[it] << "\n";
	}
	std::cout << "\n\n";

	const char* wr_path = "output_data.txt";
	WriteFile(wr_path, rd_data, kNumVals);

	Mergesort(rd_data, (rd_data + kNumVals));
	for (int it = 0; it < kNumVals; ++it) {
		std::cout << rd_data[it] << "\n";
	}

	std::cout << "\n\n";

	return 0;
}



