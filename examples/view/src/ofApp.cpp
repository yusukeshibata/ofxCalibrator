#include "ofApp.h"
#include "ofxJSONElement.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxJSONElement setting;
	setting.open("setup.json");
	//ofSetFullscreen(TRUE);
	calib.load("config");
	width = setting["width"].asInt();
	height = setting["height"].asInt();

	ofImage image;
	image.load(setting["guide"].asString());
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
	ofBackgroundHex(0xffffff);
	int fw = calib.getWidth();
	int fh = calib.getHeight();
	int ww = ofGetWidth();
	int wh = ofGetHeight();
	float per = min((float)ww/(float)fw,(float)wh/(float)fh);
	int w = fw*per;
	int h = fh*per;
	ofPushMatrix();
	ofTranslate((ww-w)/2,(wh-h)/2);
	ofScale(per,per);
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
