#pragma once
#include <fstream>
#include <iostream>
#include <cstdlib>

void ReadFile(const char* path, int* buffer, size_t kNumVals);
void WriteFile(const char* path, int* input_data, size_t kNumVals);
