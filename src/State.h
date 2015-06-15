// Abstract base class (Interface) for the current 'State'

#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Action.h"

namespace msa {
	namespace mcts {

		//class State;
		//typedef std::shared_ptr<State> StatePtr;

		class State {
		public:
			virtual ~State() {}

			// performs a deep copy of the given state
			//virtual State* clone() const = 0;
			virtual void clone_from(const State &state) = 0;

			// whether or not this state is terminal (reached end)
			virtual bool is_terminal() const = 0;

			// apply action to state
			virtual void apply_action(const Action& action) = 0;

			// return possible actions from this state
			virtual void get_actions(std::vector<Action> & actions) const = 0;

			// return number of actions
			virtual int get_num_actions() const = 0;

			/*
			// would this work?
			virtual void get_random_action(Action & action) const = 0;
			*/

			// evaluate this state and return a 'value' or 'score'
			virtual float get_value() const = 0;


			// return state as string (for debug purposes)
			virtual std::string to_string() const { return ""; }
			
		};
	}
}