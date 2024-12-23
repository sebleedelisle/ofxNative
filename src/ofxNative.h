/**
 * Native utils for openFramworks
 *
 */

#pragma once
#include "ofMain.h"

namespace ofxNative{
	
	// shows a file in finder/explorer
	void showFile( string path );
	
	// opens a file with the default application
	void openFile( string path );
	
	// opens a url in the browser
	void openUrl( string url ); 
	
	// maximizes a GLFWWindow on the current screen
	void maximizeWindow( ofAppGLFWWindow & window );
	
	// sets the minimum size for a GLFWWindow
	void setMinimumWindowSize( ofAppGLFWWindow & window, int minWidth, int minHeight );
	
	// this makes a window float on top of everything else
	void setWindowAlwaysOnTop(ofAppBaseWindow & window, bool onTop);
	
	// sets the window document + title
	void setWindowRepresentedFilename(ofAppBaseWindow & window, const string & title, const string & filename );

	// moves the mouse to a location relative the window coordinates
	// eg setMousePositionRelativeToWindow({10+ofGetMouseX(),ofGetMouseY()}) moves it 10px to the right.
	// funny issues might arise with retina screens.
	void setMousePositionRelativeToWindow( ofVec2f pos );
	
	// sets the name of the current thread
	void setThreadName( const string & name );

	// checks if a system console (where cout goes) is visible or not
	// for now, this is only visible in windows 
	bool canShowConsole(); 

	// checks if the console window is visible
	bool getConsoleVisible(); 

	// shows/hides the system console (for now only windows) 
	void setConsoleVisible(bool show); 

	// returns a path where the application can safely write data (usually) outside of the OF application
	// this is great for settings files and the like.
	// for osx this is ~/Library/Application Support directory/<bundle-identifier>
	//                 or ~/Library/Containers/<bundle-identifier>/
	// for windows this is %APPDATA%/<app-name>
	// on linux, or in case something goes wrong, this returns just the default data folder (this behavior might change!)
	std::string getSystemDataFolder();
	
	// Returns the path to some kind of documents folder
	std::string getSystemDocumentsFolder();

	// Returns the path to a temporary folder
	std::string getTempFolder();
	
	ofFileDialogResult systemLoadDialog(std::string windowTitle="", bool bFolderSelection = false, std::string defaultPath="", std::vector<std::string> extensions = {});

	ofFileDialogResult systemSaveDialog(string defaultName = "", string messageName = "", std::vector<std::string> extensions = {});

}
