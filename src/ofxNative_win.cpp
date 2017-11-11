#include "ofxNative.h"

#ifdef _WIN32

#include <winuser.h>
#include <commdlg.h>
#define _WIN32_DCOM
#include <windows.h>
#include <shlobj.h>

using namespace ofxNative;

// utf-16 to utf-8
static std::string convertWideToNarrow(const wchar_t *s, char dfault = '?',
	const std::locale& loc = std::locale())
{
	std::ostringstream stm;

	while (*s != L'\0') {
		stm << std::use_facet< std::ctype<wchar_t> >(loc).narrow(*s++, dfault);
	}
	return stm.str();
}


// utf-8 to utf-16
static std::wstring convertNarrowToWide(const std::string& as) {
	// deal with trivial case of empty string
	if (as.empty())    return std::wstring();

	// determine required length of new string
	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);

	// construct new string of required length
	std::wstring ret(reqLength, L'\0');

	// convert old string to new string
	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());

	// return new string ( compiler should optimize this away )
	return ret;
}


void ofxNative::showFile(string filename) {
	wstring w = convertNarrowToWide(filename); 
	PIDLIST_ABSOLUTE pidl = ILCreateFromPath(w.c_str());
	if (pidl) {
		SHOpenFolderAndSelectItems(pidl, 0, 0, 0);
		ILFree(pidl);
	}
}


void ofxNative::openFile( string filename ){
	wstring r = convertNarrowToWide(filename); 
	ShellExecute(0, 0, r.c_str(), 0, 0, SW_SHOW);
}


void ofxNative::maximizeWindow( ofAppGLFWWindow & window ){
	HWND w32Window = window.getWin32Window();
	ShowWindow(w32Window, SW_MAXIMIZE);
}


void ofxNative::setMinimumWindowSize( ofAppGLFWWindow & window, int minWidth, int minHeight ){
	// not implemented
	cerr << "ofxNative::setMinimumSize() not implemented for Windows" << endl;
}


void ofxNative::setWindowAlwaysOnTop(ofAppBaseWindow & window, bool onTop){
		HWND w32Window = window.getWin32Window();
		RECT rect;
		GetWindowRect(w32Window, &rect);
		SetWindowPos(w32Window, HWND_TOPMOST, rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top, SWP_SHOWWINDOW);
}


void ofxNative::setMousePositionRelativeToWindow( ofVec2f pos ){
	// not implemented
	cerr << "ofxNative::setMousePositionRelativeToWindow() not implemented for Windows" << endl;
}

// Thread naming found on SO https://stackoverflow.com/a/23899379/347508

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)


void ofxNative::setThreadName( const string & name){
	DWORD dwThreadID = GetCurrentThreadId();
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = name.c_str();
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;
	
	const DWORD MS_VC_EXCEPTION = 0x406D1388;
	__try{
		RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
	}
	__except(EXCEPTION_EXECUTE_HANDLER){
	}
}

#endif