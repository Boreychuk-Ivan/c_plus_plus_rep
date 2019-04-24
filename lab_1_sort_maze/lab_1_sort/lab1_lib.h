#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <cmath>	
#include <cstdlib>

void ReadFile(const char* path, int* buffer, size_t kNumVals);
void WriteFile(const char* path, int* input_data, size_t kNumVals);
void Mergesort(int* l, int* r);
void MergesortRecursion(int* l, int* r, int* temp);
void Merge(int* l, int* m, int* r, int* temp);
void TestSortRandomNumbers(void(*sortFunc)(int*, int*), const size_t kNumVals);
void TestSortSortedNumbers(void(*sortFunc)(int*, int*), const size_t kNumVals);
void TestSortGrandeRow(void(*sortFunc)(int*, int*), const size_t kNumVals);
void TestSortReverseOrder(void(*sortFunc)(int*, int*), const size_t kNumVals);
void TestSortEmptyPointer(void(*sortFunc)(int*, int*));
void TestSortSignleNum(void(*sortFunc)(int*, int*));

void CompareArray(int* arr1, int* arr2, size_t kNumVals);
void DisplayArrays(int* unsorted_data, int* expected_data, int* sorted_data, size_t kNumVals);