#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif

#if defined(HX_WINDOWS)
#include <windows.h>
#include <dwmapi.h>

#pragma comment(lib, "Dwmapi")
#endif

//#include <hxcpp.h>
#include <iostream>
#include <string>
#include <hx/CFFI.h>
#include <hx/CFFIPrime.h>

#if defined(HX_WINDOWS)

using namespace std;

// returns true when successful, an error message otherwise.
static value set_window_icon(value hpath, bool mods, value hmodsFolder) {
	if (!val_is_string(hpath) || !val_is_string(hmodsFolder)) {
		cerr << "Bad arguments!" << endl;
		return alloc_bool(false);
	}

	string path = string(val_string(hpath));
	string iconPath = ".\\" + path;

	if (mods) {
		string modsFolder = string(val_string(hmodsFolder));
		iconPath = ".\\mods\\" + modsFolder + "\\" + path;
	}

	HWND hWnd = GetActiveWindow();
	HICON hIconSmall = (HICON) LoadImage(NULL, iconPath.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	HICON hIconLarge = (HICON) LoadImage(NULL, iconPath.c_str(), IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

	if (!hIconLarge || !hIconSmall) {
    	cerr << "Failed to load icons. Error code: " << GetLastError() << endl;
		cerr << "Icon path: " << iconPath << endl;
		return alloc_bool(false);
	} else {
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIconSmall);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM) hIconLarge);
	}

	return alloc_bool(true);
}
DEFINE_PRIME3(set_window_icon);

#else

// doesnt work on non-windows platforms
static value set_window_icon(value modsFolder) {
	return alloc_bool(false);
}
DEFINE_PRIME1(set_window_icon);

#endif

// if someone can tell me how to get a variable from a haxe class i will be forever grateful
/*static value test() {
	hx::Class folder = hx::Class_obj::Resolve(HX_CSTRING("funkin.backend.assets.ModsFolder"));
	hx::Val val = folder->__Field(HX_CSTRING("currentModFolder"), false);
	char const * modsFolder = val->toString().__CStr();
	return alloc_string(modsFolder);
}
DEFINE_PRIME0(test);*/

extern "C" void ndll_main() {
	val_int(0); // Fix Neko init
}
DEFINE_ENTRY_POINT(ndll_main);