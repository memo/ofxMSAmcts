#pragma once

#include "../../src/ofxMSA_MCTS.h"

#include "ofMain.h"


using namespace msa::mcts;

class Action /*: public ActionBase */{
public:
	float turn;
};


#define kNumActions		10
#define kTurnRangeMin	-30
#define kTurnRangeMax	30

class State /*: public StateT<Action> */{
	typedef std::shared_ptr< Action > ActionPtr;
public:

	//--------------------------------------------------------------
	// MUST HAVE METHODS
	State():
		pos(ofGetWidth()/2, ofGetHeight()/2),
		vel(0, 3),
		frame_num(0),
		avg_pos(pos)
	{

	}
	/*
	// perform a deep clone of the given state
	State(const State& other)  {
	clone_from(other);
	}

	// perform a deep clone of the given state
	State& operator = (const State& rhs ) {
	clone_from(rhs);
	}

	// perform a deep clone of the given state
	void clone_from(const State& state)  {
	}
	*/
	// whether or not this state is terminal (reached end)
	bool is_terminal() const  {
		return false;
	}

	// apply action to state
	void apply_action(const Action& action)  {
		vel.rotate(action.turn);
		pos += vel;
		
		// update avg_pos
		avg_pos = (avg_pos * frame_num + pos) / (frame_num + 1);
		frame_num++;
	}


	// return possible actions from this state
	void get_actions(std::vector<Action>& actions) const  {
		actions.resize(kNumActions);
		for(int i=0; i<kNumActions; i++) {
			actions[i].turn = ofMap(i, 0, kNumActions-1, kTurnRangeMin, kTurnRangeMax);
		}
	}

	/*
	// return number of actions
	int get_num_actions() const  {
		return kNumActions;
	}
	*/

	// get a random action
	void get_random_action(Action& action) const {
		action.turn = ofMap(ofRandom(kNumActions), 0, kNumActions-1, kTurnRangeMin, kTurnRangeMax);
	}


	// evaluate this state and return a 'value' or 'score'
	float get_value() const  {
		// try to be a circle with diameter desired_distance
		float desired_distance = ofGetHeight()/2;
		ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);

		// score based on distance to center being close to desired_distance
		float distance_score = ofClamp(1.0f - fabs(pos.distance(center) / desired_distance - 1.0f), 0, 1);

		// score based on avg_pos being in center
		float avg_pos_score = ofClamp(1.0f - avg_pos.distance(center) / desired_distance, 0, 1);

		return distance_score + avg_pos_score;
	}


	// return state as string (for debug purposes)
	std::string to_string() const  {
		return "";
	}


	//--------------------------------------------------------------
	// IMPLEMENTATION SPECIFIC
	ofVec2f pos;		// current position
	ofVec2f vel;		// current velocity
	int frame_num;		// current tick
	ofVec2f avg_pos;	// average position

};