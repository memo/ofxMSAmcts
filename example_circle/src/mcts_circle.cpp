#include "CircleState.h"
#include "ofMain.h"

using namespace circle;

class ofApp : public ofBaseApp{
public:
    State state;
    Action action;
    UCT<State, Action> uct;

    //--------------------------------------------------------------
    void setup() {
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
    void update(){
        // run uct mcts on current state and get best action
        action = uct.run(state);

        // apply the action to the current state
        state.apply_action(action);
    }

    //--------------------------------------------------------------
    void draw() {
        state.draw();

        // black bg for text
        ofSetColor(0);
        ofDrawRectangle(0, 0, 220, 80);

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
    void keyPressed(int key){
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
};

//========================================================================
int main( ){

    ofSetupOpenGL(1280, 1024, OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new ofApp());
}
