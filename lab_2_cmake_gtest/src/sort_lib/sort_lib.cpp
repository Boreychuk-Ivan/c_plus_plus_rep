#include "sort_lib.h"

void MergesortRecursion(int* left_edge, int* right_edge, int* temp);
void Merge(int* left_edge, int* m, int* right_edge, int* temp);


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
	int *current_left_edge = left_edge;
    int *current_right_edge = m;
    int cur = 0;

    while (current_left_edge < m && current_right_edge < right_edge) {
		if (*current_left_edge < *current_right_edge){
            temp[cur++] = *current_left_edge, current_left_edge++;
        }
		else{
            temp[cur++] = *current_right_edge, current_right_edge++;
        }
	}

	while (current_left_edge < m){
        temp[cur++] = *current_left_edge, current_left_edge++;
    }

	while (current_right_edge < right_edge){
     temp[cur++] = *current_right_edge, current_right_edge++;
    }

	cur = 0;
	for (int* i = left_edge; i < right_edge; i++){
		 *i = temp[cur++];
    }
}