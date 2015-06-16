#pragma once

#include "../../src/ofxMSA_MCTS.h"

#include "Action.h"

using namespace msa::mcts;

class State /*: public StateT<Action> */{
	typedef std::shared_ptr< Action > ActionPtr;
public:
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

	// whether or not this state is terminal (reached end)
	bool is_terminal() const  {
		return false;
	}

	// apply action to state
	void apply_action(const Action& action)  {

	}


	// return possible actions from this state
	void get_actions(std::vector<Action>& actions) const  {
	}


	// return number of actions
	int get_num_actions() const  {
		return 0;
	}

	
	// get a random action
	void get_random_action(Action& action) const {
	}
	

	// evaluate this state and return a 'value' or 'score'
	float get_value() const  {
		return 0;
	}


	// return state as string (for debug purposes)
	std::string to_string() const  {
		return "";
	}

};