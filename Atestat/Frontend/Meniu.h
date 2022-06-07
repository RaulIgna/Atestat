#pragma once
#include <Windows.h>
#include "Renderer.h"
#include <vector>
class Meniu {
public:
	void Afisare(Renderer*);
	int IaStare(); // TODO: nume mai bun?
	void SetareStare(const int&); // TODO: nume mai bun?
	void Sortare(Renderer*);
	void GasireLocatie(Renderer*);
	float timpi = 0, timpf = 0, durata = 0;
private:
	int stare = 0; // TODO: nume mai bun?
	std::vector<int> distributie;
}; extern Meniu* meniu;