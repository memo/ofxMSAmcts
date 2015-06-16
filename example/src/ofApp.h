#pragma once

#include "State.h"
#include "Action.h"

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

class ofApp : public ofBaseApp{
public:

	State current_state;
	Action current_action;
	UCT<State, Action> uct;


	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		

	ofImage img;
	ofxCvHaarFinder finder;
};
