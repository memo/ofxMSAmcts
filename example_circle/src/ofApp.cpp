#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundAuto(false);
	ofBackground(0);
	ofSetVerticalSync(false);
	ofSetCircleResolution(10);

	// OPTIONAL init uct params
	uct.uct_k = sqrt(2);
	uct.max_millis = 0;
	uct.max_iterations = 100;
	uct.simulation_depth = 5;

	//msa::LoopTimer::test(10000);
}

//--------------------------------------------------------------
void ofApp::update(){
	// run uct mcts on current state and get best action
	action = uct.run(state);

	// apply the action to the current state
	state.apply_action(action);
}

//--------------------------------------------------------------
void ofApp::draw() {
	state.draw();

	// black bg for text
	ofSetColor(0);
	ofRect(0, 0, 220, 80);

	// stats
	stringstream str;
	str << ofGetFrameRate() << " fps" << endl;
	str << "total time : " << uct.get_timer().run_duration_micros() << " us" << endl;
	str << "avg time : " << uct.get_timer().avg_loop_duration_micros() << " us" << endl;
	str << "iterations : " << uct.get_iterations() << endl;
	str << "--------------------------------------------" << endl;
	str << state.to_string();

	ofSetColor(255);
	ofDrawBitmapString(str.str(), 10, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		uct.max_iterations = 100 + (key-'0') * 1000;
		break;

	case 'f':
		ofToggleFullscreen();
		break;

	case 'c':
		ofBackground(0);
		break;

	case 'r':
		state.reset();
		break;

	case 'd':
		state.data.do_discrete_random ^= true;
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
