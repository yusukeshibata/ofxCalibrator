#include "ofApp.h"
#include "ofxJSONElement.h"

//--------------------------------------------------------------
void ofApp::setup(){
	snap = FALSE;
	focus_currentscreen = FALSE;
	//ofSetFullscreen(TRUE);
	calib.load("config");
	ofxJSONElement json;
	if(json.open("setup.json")) {
		if(json["guide"].empty() == FALSE) {
			ofImage guideImage;
			guideImage.load(json["guide"].asString());
			int width = json["width"].asInt();
			int height = json["height"].asInt();;
			guideFbo.allocate(width,height);
			guideFbo.begin();
			guideImage.draw(0,0,width,height);
			guideFbo.end();

		}
	}
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
	ofPushMatrix();
	ofTranslate((ww-w)/2,(wh-h)/2);
	ofScale(per,per);
	if(guideFbo.isAllocated()) {
		calib.draw(&guideFbo);
	}
	fbo->draw(0,0,fw,fh);
	ofPopMatrix();
	// if(mousepos.length() > 0) {
	//     ofSetHexColor(0x00fff00);
	//     ofDrawLine(mousepos.x-10,mousepos.y,mousepos.x+10,mousepos.y);
	//     ofDrawLine(mousepos.x,mousepos.y-10,mousepos.x,mousepos.y+10);
	// }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int index;
	if(key == 'f') {
		ofToggleFullscreen();
	} else if(key == OF_KEY_SHIFT) {
		snap = TRUE;
		calib.mouseDragged(mousepos.x,mousepos.y,snap);
	} else if(key == ' ') {
		focus_currentscreen = !focus_currentscreen;
		calib.setFocusCurrentScreen(focus_currentscreen);
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
	if(key == OF_KEY_SHIFT) {
		snap = FALSE;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	mousepos.x = x;
	mousepos.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	mousepos.x = x;
	mousepos.y = y;
	calib.mouseDragged(x,y,snap);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mousepos.x = x;
	mousepos.y = y;
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
