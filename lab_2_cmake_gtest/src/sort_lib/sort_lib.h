#pragma once

#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>
#include <cstdlib>

extern "C" {
	__declspec(dllexport) void Mergesort(int* left_edge, int* right_edge);
}

using _Mergesort = void(*)(int*, int*);