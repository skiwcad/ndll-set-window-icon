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

#include <hx/CFFI.h>
#include <hx/CFFIPrime.h>

#include <string>
#include <iostream>

using namespace std;

#if defined(HX_WINDOWS)

static value set_window_icon(value hpath, value hmodsFolder) {
	if (!val_is_string(hpath)) {
		cerr << "\x1b[31m[ERROR] Icon path must be a string\x1b[0m" << endl;
		return alloc_bool(false);
	}

	const string path = string(val_string(hpath));

	string iconPath;
	if (val_is_string(hmodsFolder)) {
		string modsFolder = string(val_string(hmodsFolder));
		iconPath = "./mods/" + modsFolder + "/" + path;
	} else {
		iconPath = "./" + path;
	}

	const HWND windowHandle = GetActiveWindow();
	const HICON iconSmall = (HICON) LoadImage(NULL, iconPath.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	const HICON iconBig = (HICON) LoadImage(NULL, iconPath.c_str(), IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

	if (!iconBig || !iconSmall) {
    	cerr << "\x1b[31m[ERROR] Failed to load icons from: " << iconPath <<
			" (Error code: " << GetLastError() << ")\x1b[0m" << endl;
		return alloc_bool(false);
	}

	SendMessage(windowHandle, WM_SETICON, ICON_SMALL, (LPARAM) iconSmall);
	SendMessage(windowHandle, WM_SETICON, ICON_BIG, (LPARAM) iconBig);

	return alloc_bool(true);
}
DEFINE_PRIME2(set_window_icon);

#else

// doesnt work on non-windows platforms
static value set_window_icon(value hpath, value hmodsFolder) {
	cerr << "\x1b[31m[ERROR] set_window_icon is only available for Windows\x1b[0m" << endl;
	return alloc_bool(false);
}
DEFINE_PRIME2(set_window_icon);

#endif

extern "C" void ndll_main() {
	val_int(0); // fix neko init
}
DEFINE_ENTRY_POINT(ndll_main);