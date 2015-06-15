#include "ofApp.h"



using namespace msa::mcts;

//--------------------------------------------------------------
void ofApp::setup(){
	msa::LoopTimer::test();

	img.load("test.jpg");
	finder.setup("haarcascade_frontalface_default.xml");
	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void ofApp::update(){
	// create a Node from current state
	current_action = uct.run(current_state);

	// get the best action
	//current_action = uct.get_best_action();

	// apply the action to the current state
	current_state.apply_action(current_action);
}

//--------------------------------------------------------------
void ofApp::draw(){
	img.draw(0, 0);
	ofNoFill();
	for(unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);
	}
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
