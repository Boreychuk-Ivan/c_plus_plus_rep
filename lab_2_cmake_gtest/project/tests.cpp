#include <windows.h>	//read dll
#include <iostream>
#include <cstdlib>		//rand
#include <gtest/gtest.h>
#include "../src/file_lib/file_lib.h"
#include "../src/sort_lib/sort_lib.h"

const size_t kNumVals = 2000;

void Mergesort(int* left_edge, int* right_edge);

//Unsorted data - array of random numbers
TEST(TestSortSuite, TestSortRandomNumbers) {
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

	Mergesort(sorted_data, (sorted_data + kNumVals));

	for (int it = 0; it < kNumVals; ++it) {
		ASSERT_EQ(expected_data[it], sorted_data[it]) << "Error: actual and expected data not equal in: " << it << " position;\n";
	}

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;
}

//Unsorted data - array of sorted numbers
TEST(TestSortSuite, TestSortSortedNumbers) {
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

    Mergesort(sorted_data, (sorted_data + kNumVals));

	for (int it = 0; it < kNumVals; ++it) {
		ASSERT_EQ(expected_data[it], sorted_data[it]) << "Error: actual and expected data not equal in: " << it << " position;\n";
	}

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;
}

//Unsorted data - array of (-1,1,-1,1,...)
TEST(TestSortSuite, TestSortGrandeRow){
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

	Mergesort(sorted_data, (sorted_data + kNumVals));

	for (int it = 0; it < kNumVals; ++it) {
		ASSERT_EQ(expected_data[it], sorted_data[it]) << "Error: actual and expected data not equal in: " << it << " position;\n";
	}

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;
}

//Unsorted data - array of sorted numbers in reverse order
TEST(TestSortSuite, TestSortReverseOrder){
	int* unsorted_data = new int[kNumVals];
	int* expected_data = new int[kNumVals];

    for (int it = 0; it < kNumVals; ++it) {
		unsorted_data[it] = kNumVals - 1 - it;
		expected_data[it] = it;
	}

    int* sorted_data = new int[kNumVals];
	std::copy(unsorted_data, (unsorted_data + kNumVals), sorted_data);

	Mergesort(sorted_data, (sorted_data + kNumVals));

	for (int it = 0; it < kNumVals; ++it) {
		ASSERT_EQ(expected_data[it], sorted_data[it]) << "Error: actual and expected data not equal in: " << it << " position;\n";
	}

	delete[] unsorted_data;
	delete[] expected_data;
	delete[] sorted_data;

}

//Unsorted data - empty_pointer
TEST(TestSortSuite, TestSortEmptyPointer) {
	int *empty_pointer = nullptr;

    Mergesort(empty_pointer, empty_pointer);

    ASSERT_EQ(empty_pointer, nullptr) << "Error: empty_pointer was chanched!";
}

//Unsorted data - single number
TEST(TestSortSuite, TestSortSignleNum) {
	int actual_data = 1;
	int expected_data = actual_data;

	Mergesort(&actual_data, &actual_data);

    ASSERT_EQ(actual_data, expected_data) << "Error: actual and expected data not equal";
}


int main(int argc, char *argv[])
{
	const size_t kFileSize = 40;
	int* input_data = new int[kFileSize];

    const char* input_path = "../../files/input_data.txt";
	ReadFile(input_path, input_data, kFileSize);

	try {
		Mergesort(input_data, input_data + kFileSize);
	}
	catch (const char* exception)
	{
		std::cerr << exception;
	}

	const char* output_path = "../../files/output_data.txt";
	WriteFile(output_path, input_data, kFileSize);

    delete[] input_data;

	try{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
	catch(const char* exception)
	{
		std::cerr << exception;
	}
}



void Mergesort(int* left_edge, int* right_edge) {
	#ifdef DEBUG_FLAG
		const char* path_lib = "../src/sort_lib/Debug/sort_lib.dll";
	#else
		const char* path_lib = "../src/sort_lib/Release/sort_lib.dll";
	#endif

	HINSTANCE hinst_lib = LoadLibrary(path_lib);

	if (!hinst_lib){
		throw "Error: can't find sort_lib.dll\n";
	}

	static _Mergesort DllFunc =
		(_Mergesort)GetProcAddress(hinst_lib, "Mergesort");

	if (!DllFunc){
		throw "Error: can't find function\n";
	}
	else{
		DllFunc(left_edge, right_edge);
	}

	FreeLibrary(hinst_lib);
}
