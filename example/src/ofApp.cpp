#include "ofApp.h"



using namespace msa::mcts;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundAuto(false);
	ofBackground(0);
	ofSetVerticalSync(true);
//	ofSetCircleResolution(2);

	uct.max_millis = 16;
	uct.max_iterations = 0;
	uct.simulation_depth = 10;

	//msa::LoopTimer::test();

//	img.loadImage("test.jpg");
//	finder.setup("haarcascade_frontalface_default.xml");
//	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void ofApp::update(){
	// run uct mcts on current state and get best action
	current_action = uct.run(current_state);

	// apply the action to the current state
	current_state.apply_action(current_action);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(0, 1);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(255);
	ofCircle(current_state.pos, 2);
//	img.draw(0, 0);
//	ofNoFill();
//	for(unsigned int i = 0; i < finder.blobs.size(); i++) {
//		ofRectangle cur = finder.blobs[i].boundingRect;
//		ofRect(cur.x, cur.y, cur.width, cur.height);
//	}
	
	ofSetColor(255);
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 2) , 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
