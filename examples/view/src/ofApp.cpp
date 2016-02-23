#include "ofApp.h"
#include "ofxJSONElement.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxJSONElement setting;
	setting.open("config.json");
	//ofSetFullscreen(TRUE);
	ofDisableArbTex();
	calib.load("config");
	width = setting["width"].asInt();
	height = setting["height"].asInt();

	ofImage image;
	image.load("test.jpg");
	fbo.allocate(width,height);
	fbo.begin();
	ofClear(0x000000);
	image.draw(0,0,width,height);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(0x000000);
	ofSetHexColor(0xffffff);
	float ww = ofGetWidth();
	float wh = ofGetHeight();
	float cw = calib.getWidth();
	float ch = calib.getHeight();
	float pw = ww/cw;
	float ph = wh/ch;
	float p = min(pw,ph);
	ofPushMatrix();
	ofScale(p,p);
	calib.draw(&fbo);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='f') {
		ofToggleFullscreen();
	}
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
