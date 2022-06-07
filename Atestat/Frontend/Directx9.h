#pragma once
#include <d3d9.h>
#include "Renderer.h" // Clasa de baza

class Directx9 : public Renderer{
public:
	void Afisare();

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void ResetDevice();
	void CreareFereastra();
};