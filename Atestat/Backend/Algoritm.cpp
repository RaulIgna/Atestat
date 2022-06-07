#include "Algoritm.h"
#include "../Frontend/Renderer.h"
#include <vector>
#include <assert.h>
#include <thread>
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std::chrono_literals;

void Algoritm::sorteaza() {
	while (!iesire) {
		if (!sortare) continue;
		if (wait) continue;
		if (std::is_sorted(valori.begin(), valori.end())) {
			sortare = false;
			// TODO: adauga logging pentru detalii.
			continue;
		}
		if (!valori.empty()) {
			switch (sortmode) {
			case 0:	bubblesort(); break;
			case 1: quicksort(0,valori.size() - 1); break;
			case 2: MergeSort(0, valori.size() - 1); break;
			case 3: InsertionSort(); break;
			case 4: HeapSort(); break;
			}
		}
	}
}

void merge(std::vector<int>&valori,int left, int mid, int right) {
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne];
	int *rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = valori[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = valori[mid + 1 + j];
	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
			valori[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			GLOBAL::sortare->current = indexOfSubArrayOne;
			GLOBAL::sortare->next = indexOfMergedArray;
			indexOfSubArrayOne++;
		}
		else {
			valori[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			GLOBAL::sortare->current = indexOfSubArrayTwo;
			GLOBAL::sortare->next = indexOfMergedArray;
			std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
		valori[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		GLOBAL::sortare->current = indexOfSubArrayOne;
		GLOBAL::sortare->next = indexOfMergedArray;
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		GLOBAL::sortare->current = indexOfMergedArray;
		GLOBAL::sortare->next = indexOfSubArrayTwo;
		std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
		valori[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void Algoritm::MergeSort(int stanga, int dreapta) {
	if (stanga >= dreapta)
		return; // Returns recursively

	auto mid = stanga + (dreapta - stanga) / 2;
	MergeSort(stanga, mid);
	MergeSort(mid + 1, dreapta);
	merge(valori, stanga, mid, dreapta);
}


void heap(std::vector<int>& valori, int n, int i) {
	int mare = i;
	int stanga = i * 2 + 1;
	int dreapta = i * 2 + 2;

	if (stanga < n && valori[stanga] > valori[mare]) {
		mare = stanga;
	}
	if (dreapta < n && valori[dreapta] > valori[mare]) {
		mare = dreapta;
	}

	if (mare != i) {
		GLOBAL::sortare->current = i;
		GLOBAL::sortare->next = mare;
		std::swap(valori[i], valori[mare]);
		std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
		heap(valori, n, mare);
	}
}

void Algoritm::HeapSort() {
	for (int i = valori.size() / 2 - 1; i >= 0; i--)
		heap(valori, valori.size(), i);
	for (unsigned int i = valori.size() - 1; i > 0; i--) {
		std::swap(valori[0], valori[i]);
		std::this_thread::sleep_for(std::chrono::milliseconds(viteza));
		heap(valori, i, 0);
	}
}

int partitie(std::vector<int>&arr, int stanga, int dreapta)
{
	int i = stanga;
	int pivot_value = arr[dreapta];
	for (int j = stanga; j < dreapta; j++)
	{
		if (arr[j] <= pivot_value)
		{
			std::swap(arr[i], arr[j]);
			GLOBAL::sortare->current = i;
			GLOBAL::sortare->next = j;
			std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
			i++;
		}
	}
	std::swap(arr[i], arr[dreapta]);
	std::this_thread::sleep_for(std::chrono::milliseconds(GLOBAL::sortare->viteza));
	return i;
}

void Algoritm::quicksort(int stanga, int dreapta) {
	if (stanga < dreapta)
	{
		int pivot = partitie(valori, stanga, dreapta);
		quicksort(stanga, pivot - 1);
		quicksort(pivot + 1, dreapta);
	}
}

void Algoritm::bubblesort() {
	for (unsigned int i = 0; i < valori.size() - 1; i++) {
		for (unsigned int j = 0; j < valori.size() - 1 - i; j++) {
			current = j;
			next = j + 1;
			if (valori[j] > valori[j + 1]) {
				std::swap(valori[j], valori[j + 1]);
				std::this_thread::sleep_for(std::chrono::milliseconds(viteza));
			}
		}
	}
}

void Algoritm::InsertionSort() {
	int n, j;
	for (unsigned int i = 1; i < valori.size(); i++) {
		n = valori[i];
		j = i - 1;
		while (j >= 0 && valori[j] > n) {
			std::this_thread::sleep_for(std::chrono::milliseconds(viteza));
			valori[j + 1] = valori[j];
			next = j + 1;
			current = j;
			j--;
		}
		valori[j + 1] = n;
		std::this_thread::sleep_for(std::chrono::milliseconds(viteza));
	}
}