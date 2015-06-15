#pragma once

#include "../../src/ofxMSA_MCTS.h"

using namespace msa::mcts;

class MyState : public State {
public:
	// performs a deep clone of the given state
	void clone_from(const State &state) override {

	}

	// whether or not this state is terminal (reached end)
	bool is_terminal() const override {
		return false;
	}

	// apply action to state
	void apply_action(const Action& action) override {

	}


	// return possible actions from this state
	void get_actions(std::vector<Action> & actions) const override {
	}


	// return number of actions
	int get_num_actions() const override {
		return 0;
	}

	/*
	// would this work?
	virtual void get_random_action(Action & action) const = 0;
	*/

	// evaluate this state and return a 'value' or 'score'
	float get_value() const override {
		return 0;
	}


	// return state as string (for debug purposes)
	std::string to_string() const override {
		return "";
	}

};