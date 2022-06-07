#pragma once
#include <iostream>
#include <vector>


class Algoritm {
public:
	void sorteaza();
	void TrebeSaIes() { iesire = true; }
	std::vector<int> valori;
	int current = 0;
	int next = 0;
	bool wait;
	bool sortare;
	int sortmode = 1;
	int viteza = 50;
private:
	bool iesire = false;
	void bubblesort();
	void quicksort(int stanga, int dreapta);
	void InsertionSort();
	void HeapSort();
	void MergeSort(int stanga, int dreapta);
	
};

