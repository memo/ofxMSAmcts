#include "OXOState.h"
#include "ofMain.h"

using namespace oxo;

class ofApp : public ofBaseApp{
public:
    State state;
    Action action;
    UCT<State, Action> uct;

    //--------------------------------------------------------------
    void setup() {
        ofSetBackgroundAuto(true);
        ofBackground(0);
        ofSetVerticalSync(true);


        // OPTIONAL init uct params
        uct.uct_k = sqrt(2);
        uct.max_millis = 0;
        uct.max_iterations = 1000;
        uct.simulation_depth = 1000;

        //msa::LoopTimer::test(10000);
    }

    //--------------------------------------------------------------
    void update(){
        // if game is not over, and player 2 is about to play
        if(!state.data.is_terminal) {
            if(state.agent_id() == kPlayer2) {
                // run uct mcts on current state and get best action
                action = uct.run(state);

                // apply the action to the current state
                state.apply_action(action);
            }
        }

    }

    //--------------------------------------------------------------
    void draw() {
        state.draw();

        // stats
        stringstream str;
        str << ofGetFrameRate() << " fps" << endl;
        str << "total time : " << uct.get_timer().run_duration_micros() << " us" << endl;
        str << "avg time : " << uct.get_timer().avg_loop_duration_micros() << " us" << endl;
        str << "iterations : " << uct.get_iterations() << endl;
        str << "--------------------------------------------" << endl;
        str << state.to_string();

        if (state.is_terminal()) {
            str << endl << endl;
            str << "Game Over. Press SPACE to restart." << endl;
        }

        ofSetColor(255);
        ofDrawBitmapString(str.str(), 10, 15);
    }

    //--------------------------------------------------------------
    void keyPressed(int key){
        switch(key) {
        case 'f':
            ofToggleFullscreen();
            break;

        case ' ':
            state.reset();
            break;
        }
    }

    //--------------------------------------------------------------
    void mousePressed(int x, int y, int button){
        // if game is not over, and player 1 is about to play
        if(!state.data.is_terminal) {
            if(state.agent_id() == kPlayer1) {
                int tile_size_x = ofGetWidth()/3;
                int tile_size_y = ofGetHeight()/3;
                int tile = floor(x/tile_size_x) + floor(y/tile_size_y) * 3;

                // if that tile is empty, apply it
                if(state.data.board[tile] == kNone) state.apply_action(Action(tile));
            }
        }
    }

};

//========================================================================
int main( ){

    ofSetupOpenGL(800, 800, OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new ofApp());
}
