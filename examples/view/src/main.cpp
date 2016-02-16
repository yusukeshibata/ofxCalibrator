#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofAppGLFWWindow win;
    ofSetupOpenGL(&win, 640,480, OF_WINDOW);
    ofRunApp( new ofApp());
}
