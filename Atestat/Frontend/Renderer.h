#pragma once
#include <Windows.h> // HWND
#include <memory>
#include <d3d9.h>
#include "../ImGui/imgui.h"
typedef unsigned int ui;

class Renderer {
public:
	virtual void Afisare() = 0;
	virtual void CreareFereastra() = 0;
	virtual void ResetDevice() = 0;
	void IaMarimi() {
		if (GetWindowRect(hwnd, &patratfereastra)) {
			inaltime = patratfereastra.bottom - patratfereastra.top;
			lungime = patratfereastra.right - patratfereastra.left;
		}
		else {
			MessageBox(hwnd, "Nu am putut lua mariema ferestrei", "Eroare!", MB_OK);
		}
	}
public:

	HWND hwnd = NULL; // Fereastra principala
	WNDCLASSEX wc;
	bool sfarsit = false;
	RECT patratfereastra;
	ui inaltime;
	ui lungime;
	LPDIRECT3D9              g_pD3D = 0;
	LPDIRECT3DDEVICE9        g_pd3dDevice = 0;
	D3DPRESENT_PARAMETERS    g_d3dpp = {};
	ImFont* fontnormal;
};

class Algoritm;
class Internet;

namespace GLOBAL {
	extern Renderer* render;
	extern Algoritm* sortare;
	extern Internet* internet;
}