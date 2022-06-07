#include "Internet.h"
#include <Windows.h>
#include <string>
#include <wininet.h>
#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

Internet* internet = new Internet();

void Internet::DownloadFonts() {
	URLDownloadToFile(NULL, "https://github.com/RaulIgna/RaulIgna.github.io/blob/master/CascadiaCode-Bold.ttf?raw=true", "nice.ttf", NULL,NULL);
	URLDownloadToFile(NULL, "https://github.com/RaulIgna/RaulIgna.github.io/blob/master/fontawesome-webfont.ttf?raw=true", "icons.ttf", NULL, NULL);
}