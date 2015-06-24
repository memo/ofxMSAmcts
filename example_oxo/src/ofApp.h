#pragma once

#include "OXOState.h"
#include "ofMain.h"

using namespace oxo;

class ofApp : public ofBaseApp{
public:
	State state;
	Action action;
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
};
