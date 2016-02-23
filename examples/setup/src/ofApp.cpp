#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetFullscreen(TRUE);
	calib.load("config");
}

//--------------------------------------------------------------
void ofApp::update(){
	calib.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	int i,j;
	ofBackgroundHex(0xffffff);
	ofFbo *fbo = calib.getFbo();
	int fw = fbo->getWidth();
	int fh = fbo->getHeight();
	int ww = ofGetWidth();
	int wh = ofGetHeight();
	float per = min((float)ww/(float)fw,(float)wh/(float)fh);
	int w = fw*per;
	int h = fh*per;
	fbo->draw((ww-w)/2,(wh-h)/2,w,h);
	//if(mousepos.length() > 0) {
	//    ofSetHexColor(0x00fff00);
	//    ofDrawLine(mousepos.x-10,mousepos.y,mousepos.x+10,mousepos.y);
	//    ofDrawLine(mousepos.x,mousepos.y-10,mousepos.x,mousepos.y+10);
	//}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int index;
	if(key == 'f') {
		ofToggleFullscreen();
	} else if(49 <= key  && key <= 57) {
		index = key - 49;
		calib.setCurrentScreen(index);
	} else if(key == 358) { // ->
		calib.push_col();
	} else if(key == 356) { // <-
		calib.pop_col();
	} else if(key == 357) { // up
		calib.push_row();
	} else if(key == 359) { // down
		calib.pop_row();
	} else if(key == 's') {
		ofLog() << "save";
		calib.save();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	mousepos.x = x;
	mousepos.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	calib.mouseDragged(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	calib.mousePressed(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	
}
