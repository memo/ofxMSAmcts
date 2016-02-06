#pragma once

#include "ofxMSAmcts.h"

#include "ofMain.h"


using namespace msa::mcts;

namespace circle {
//--------------------------------------------------------------
//--------------------------------------------------------------
struct Action {
    float turn;
};


#define kNumActions		10
#define kTurnRangeMin	-30
#define kTurnRangeMax	30

//--------------------------------------------------------------
//--------------------------------------------------------------
class State {
public:

    //--------------------------------------------------------------
    // MUST HAVE METHODS (INTERFACE)

    State() {
        data.do_discrete_random = true;
        reset();
    }

    // default constructors will do
    // copy and assignment operators should perform a DEEP clone of the given state
    //    State(const State& other);
    //    State& operator = (const State& other);


    // whether or not this state is terminal (reached end)
    bool is_terminal() const  {
        return false;
    }

    //  agent id (zero-based) for agent who is about to make a decision
    int agent_id() const {
        return 0;
    }

    // apply action to state
    void apply_action(const Action& action)  {
        data.vel.rotate(action.turn);
        data.pos += data.vel;

        // update avg_pos
        data.avg_pos = (data.avg_pos * data.frame_num + data.pos) / (data.frame_num + 1);
        data.frame_num++;
    }


    // return possible actions from this state
    void get_actions(std::vector<Action>& actions) const  {
        actions.resize(kNumActions);
        for(int i=0; i<kNumActions; i++) {
            if(data.do_discrete_random) actions[i].turn = ofMap(i, 0, kNumActions-1, kTurnRangeMin, kTurnRangeMax);
            else get_random_action(actions[i]);
        }
    }


    // get a random action, return false if no actions found
    bool get_random_action(Action& action) const {
        if(data.do_discrete_random) action.turn = ofMap(floor(ofRandom(kNumActions)), 0, kNumActions-1, kTurnRangeMin, kTurnRangeMax);
        else action.turn = ofRandom(kTurnRangeMin, kTurnRangeMax);
        return true;
    }


    // evaluate this state and return a vector of rewards (for each agent)
    const vector<float> evaluate() const  {
        vector<float> rewards(1);

        // try to be a circle with diameter desired_distance
        float desired_distance = min(min(ofGetMouseX(), ofGetMouseY()), min(ofGetWidth() - ofGetMouseX(), ofGetHeight() - ofGetMouseY()));
        if(desired_distance < 1) desired_distance = 1;
        ofVec2f center(ofGetMouseX(), ofGetMouseY());

        // score based on distance to center being close to desired_distance
        float distance_score = 1.0f - fabs(data.pos.distance(center) / desired_distance - 1.0f);

        // score based on avg_pos being in center
        float avg_pos_score = 1.0f - data.avg_pos.distance(center) / desired_distance;

        rewards[0] = distance_score + avg_pos_score * 0.5;
        return rewards;
    }


    // return state as string (for debug purposes)
    std::string to_string() const  {
        stringstream str;
        str << "do_discrete_random : " << (data.do_discrete_random ? "YES" : "NO" ) << endl;
        return str.str();
    }


    //--------------------------------------------------------------
    // IMPLEMENTATION SPECIFIC

    struct {
        ofVec2f pos;		// current position
        ofVec2f vel;		// current velocity
        int frame_num = 0;		// current tick
        ofVec2f avg_pos;	// average position
        bool do_discrete_random = true;	// discretize turn vs sample random turns
    } data;

    void reset() {
        data.pos.set(ofGetWidth()/2, ofGetHeight()/2);
        data.vel.set(0, 10);
        data.frame_num = 0;
        data.avg_pos.set(data.pos);
    }

    void draw() {
        // fade bg
        ofSetColor(0, 10);
        ofDrawCircle(data.pos, 50);

        ofSetColor(255, 255);
        ofDrawLine(data.pos, data.pos - data.vel);
    }

};

}
