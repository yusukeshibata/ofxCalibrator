#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	calib.load();
	fbo.allocate(640,480);
	fbo.begin();
	ofClear(0x000000);
	ofSetLineWidth(2);
	ofSetHexColor(0xffffff);
	for(float y=0;y<480;y+=20) {
		ofDrawLine(0,y,640,y);
		for(float x=0;x<640;x+=20) {
			ofDrawLine(x,0,x,480);
		}
	}
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(0x000000);
	ofSetHexColor(0xffffff);
	calib.draw(&fbo);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
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
