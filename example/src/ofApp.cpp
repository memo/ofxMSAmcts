#include "ofApp.h"



using namespace msa::mcts;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundAuto(false);
	ofBackground(0);
	ofSetVerticalSync(false);
	ofSetCircleResolution(10);

	uct.max_millis = 0;
	uct.max_iterations = 100;
	uct.simulation_depth = 5;

	//msa::LoopTimer::test(10000);

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
	// black bg for text
	ofSetColor(0);
	ofRect(0, 0, 220, 80);

	// fade bg
	ofSetColor(0, 5);
	//ofRect(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(0, 5);
	ofCircle(current_state.pos, 50);

	// current pos
	ofColor c;
	c.setHsb(int(ofGetElapsedTimef() * 10) % 255, 170, 255, 200);
	//ofSetColor(255, 150, 0, 200);
	ofSetColor(c);
	ofCircle(current_state.pos, 7);

	ofSetColor(255, 255);
	ofCircle(current_state.pos, 5);

	/*	ofNoFill();
	ofSetColor(255);
	ofCircle(current_state.pos, 4);
	ofFill();
	*/
	//	img.draw(0, 0);
	//	ofNoFill();
	//	for(unsigned int i = 0; i < finder.blobs.size(); i++) {
	//		ofRectangle cur = finder.blobs[i].boundingRect;
	//		ofRect(cur.x, cur.y, cur.width, cur.height);
	//	}

	ofSetColor(255);

	stringstream str;
	str << ofGetFrameRate() << " fps" << endl;
	str << "total time : " << uct.timer.run_duration_micros() << " us" << endl;
	str << "avg time : " << uct.timer.avg_loop_duration_micros() << " us" << endl;
	str << "iterations : " << uct.iterations << endl;
	str << "do_discrete_random : " << (current_state.do_discrete_random ? "YES" : "NO" )<< endl;

	ofDrawBitmapString(str.str(), 10, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
	case 'f':
		ofToggleFullscreen();
		break;
	case 'c':
		ofBackground(0);
		break;
	case 'r':
		current_state.reset();
		break;
	case 'd':
		current_state.do_discrete_random ^= true;
		break;
	case 'v':
		ofSetVerticalSync(false);
		break;

	case 'V':
		ofSetVerticalSync(true);
		break;

	case 'a':
		ofSetBackgroundAuto(false);
		break;

	case 'A':
		ofSetBackgroundAuto(true);
		break;


	}
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
