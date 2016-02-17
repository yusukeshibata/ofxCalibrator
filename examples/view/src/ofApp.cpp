#include "ofApp.h"
#include "ofxJSONElement.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxJSONElement setting;
	setting.open("config.json");
	ofSetFullscreen(TRUE);
	ofDisableArbTex();
	calib.load();
	width = setting["width"].asInt();
	height = setting["height"].asInt();
	fbo.allocate(width,height);
	fbo.begin();
	ofClear(0x000000);
	ofSetLineWidth(2);
	ofSetHexColor(0xffffff);
	for(float y=0;y<height;y+=20) {
		ofDrawLine(0,y,width,y);
		for(float x=0;x<width;x+=20) {
			ofDrawLine(x,0,x,height);
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
