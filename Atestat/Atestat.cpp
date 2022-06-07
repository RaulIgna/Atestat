#include "framework.h"
#include "Atestat.h"
#include "Frontend/Directx9.h"
#include "Frontend/Renderer.h"
#include <memory>
#include <thread>
#include "Backend/Algoritm.h"
#include "Backend/Internet.h"
#pragma warning (disable : 4996 )

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    GLOBAL::render = new Directx9();
    GLOBAL::sortare = new Algoritm();
    GLOBAL::internet = new Internet();
    GLOBAL::internet->DownloadFonts();
    std::thread thgrafica(&Renderer::CreareFereastra, GLOBAL::render); // pentru grafica
    std::thread thalgoritm(&Algoritm::sorteaza,GLOBAL::sortare); // pentru algoritmi
    thalgoritm.join();
    thgrafica.join();
    delete GLOBAL::render;
    delete GLOBAL::sortare;
    delete GLOBAL::internet;
}

