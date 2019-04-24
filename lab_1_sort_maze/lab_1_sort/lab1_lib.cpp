#include "pch.h"
#include "lab1_lib.h"

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

void Mergesort(int* left_edge, int* right_edge) {
	int* temp = new int[right_edge - left_edge];
	MergesortRecursion(left_edge, right_edge, temp);
	delete temp;
}

void MergesortRecursion(int* left_edge, int* right_edge, int* temp) {
	if (right_edge - left_edge <= 1) return;
	int *mid = left_edge + (right_edge - left_edge) / 2;
	MergesortRecursion(left_edge, mid, temp);
	MergesortRecursion(mid, right_edge, temp);
	Merge(left_edge, mid, right_edge, temp);
}
void Merge(int* left_edge, int* m, int* right_edge, int* temp) {
	int *current_left_edge = left_edge, *current_right_edge = m, cur = 0;
	while (current_left_edge < m && current_right_edge < right_edge) {
		if (*current_left_edge < *current_right_edge) temp[cur++] = *current_left_edge, current_left_edge++;
		else temp[cur++] = *current_right_edge, current_right_edge++;
	}
	while (current_left_edge < m) temp[cur++] = *current_left_edge, current_left_edge++;
	while (current_right_edge < right_edge) temp[cur++] = *current_right_edge, current_right_edge++;
	cur = 0;
	for (int* i = left_edge; i < right_edge; i++)
		 *i = temp[cur++];
}


//Test for sort function.
//Unsorted data - array of random numbers.
void TestSortRandomNumbers(void(*sortFunc)(int*, int*), const size_t kNumVals)
{
	std::cout << "TestSortRandomNumbers\n\n";
	int rand_seed = 1;
	srand(rand_seed);

	int* unsorted_data = new int[kNumVals];
	int* expected_data = new int[kNumVals];
	for (int it = 0; it < kNumVals; ++it) {
		unsorted_data[it] = pow(-1, it)*(rand() % 256);
	}
	std::copy(unsorted_data, (unsorted_data + kNumVals), expected_data);
	std::sort(expected_data, (expected_data + kNumVals));
	
	int* sorted_data = new int[kNumVals];
	std::copy(unsorted_data, (unsorted_data + kNumVals), sorted_data);

	sortFunc(sorted_data, (sorted_data + kNumVals));


	DisplayArrays(unsorted_data, expected_data, sorted_data, kNumVals);
	CompareArray(sorted_data, expected_data, kNumVals);

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;
}


//Test for sort function.
//Unsorted data - array of sorted numbers.
void TestSortSortedNumbers(void(*sortFunc)(int*, int*), const size_t kNumVals)
{
	std::cout << "TestSortSortedNumbers\n\n";
	int rand_seed = 1;
	srand(rand_seed);

	int* unsorted_data = new int[kNumVals];
	int* expected_data = new int[kNumVals];

	for (int it = 0; it < kNumVals; ++it) {
		unsorted_data[it] = it;
		expected_data[it] = it;
	}

	int* sorted_data = new int[kNumVals];
	std::copy(unsorted_data, (unsorted_data + kNumVals), sorted_data);
	sortFunc(sorted_data, (sorted_data + kNumVals));

	DisplayArrays(unsorted_data, expected_data, sorted_data, kNumVals);
	CompareArray(unsorted_data, sorted_data, kNumVals);
	
	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;

}

//Test for sort function.
//Unsorted data - array of (-1,1,-1,1,...).
void TestSortGrandeRow(void(*sortFunc)(int*, int*), const size_t kNumVals)
{
	std::cout << "TestSortGrandeRow\n\n";
	int rand_seed = 1;
	srand(rand_seed);

	int* unsorted_data = new int[kNumVals];
	int* expected_data = new int[kNumVals];

	for (int it = 0; it < kNumVals; ++it) {
		unsorted_data[it] = pow(-1, it);
	}
	std::copy(unsorted_data, (unsorted_data + kNumVals), expected_data);
	std::sort(expected_data, (expected_data + kNumVals));

	int* sorted_data = new int[kNumVals];
	std::copy(unsorted_data, (unsorted_data + kNumVals), sorted_data);
	sortFunc(sorted_data, (sorted_data + kNumVals));
	
	DisplayArrays(unsorted_data, expected_data, sorted_data, kNumVals);
	CompareArray(unsorted_data, sorted_data, kNumVals);

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;
}

//Test for sort function.
//Unsorted data - array of sorted numbers in reverse order.
void TestSortReverseOrder(void(*sortFunc)(int*, int*), const size_t kNumVals) {
	std::cout << "TestSortReverseOrder\n\n";
	int* unsorted_data = new int[kNumVals];
	int* expected_data = new int[kNumVals];
	for (int it = 0; it < kNumVals; ++it) {
		unsorted_data[it] = kNumVals-1 - it;
		expected_data[it] = it;
	}
	int* sorted_data = new int[kNumVals];
	std::copy(unsorted_data, (unsorted_data + kNumVals), sorted_data);
	sortFunc(sorted_data, (sorted_data + kNumVals));

	DisplayArrays(unsorted_data, expected_data, sorted_data, kNumVals);
	CompareArray(unsorted_data, sorted_data, kNumVals);

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;
}

//Test for sort function.
//Unsorted data - empty_pointer.
void TestSortEmptyPointer(void(*sortFunc)(int*, int*)) {
	std::cout << "TestSortEmptyPointer\n\n";
	int *empty_pointer = nullptr;
	std::cout << "Empty pointer before sort: " << empty_pointer << "\n";
	sortFunc(empty_pointer, empty_pointer);
	std::cout << "Empty pointer after sort: " << empty_pointer << "\n\n";
}


//Test for sort function.
//Unsorted data - single number.
void TestSortSignleNum(void(*sortFunc)(int*, int*)) {
	std::cout << "TestSortSignleNum\n\n";
	int single_number = 1;
	std::cout << "Input number before sort: " << single_number << "\n";
	sortFunc(&single_number, &single_number);
	std::cout << "Input number after sort: " << single_number << "\n\n";
}


void CompareArray(int* arr1, int* arr2, const size_t kNumVals) {
	for (int it = 0; it < kNumVals; ++it) {
		if (arr1[it] != arr1[it]) {
			std::cout << "Sorted and expected arrays are not equal.\n";
			return;
		}
	}
	std::cout << "Sorted and expected arrays are equal.\n";
	std::cout << "\n\n";
}


void DisplayArrays(int* unsorted_data, int* expected_data, int* sorted_data, const size_t kNumVals) 
{
	std::cout << "Unsorted array: \n";
	for (int it = 0; it < kNumVals; ++it) {
		std::cout << unsorted_data[it] << ",";
	}
	std::cout << "\n\n";

	std::cout << "Expected array: \n";
	for (int it = 0; it < kNumVals; ++it) {
		std::cout << expected_data[it] << ",";
	}
	std::cout << "\n\n";

	std::cout << "Sorted array: \n";
	for (int it = 0; it < kNumVals; ++it) {
		std::cout << sorted_data[it] << ",";
	}
	std::cout << "\n\n";
}