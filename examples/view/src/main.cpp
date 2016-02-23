#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofAppGLFWWindow win;
	win.setMultiDisplayFullscreen(TRUE);
	ofSetupOpenGL(&win, 800,600, OF_WINDOW);
	ofRunApp( new ofApp());
}
