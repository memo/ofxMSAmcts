// Abstract base class (Interface) for an Action that can be applied to a State

#pragma once

#include <string>
#include <memory>

namespace msa {
	namespace mcts {

		//class Action;
		//typedef std::shared_ptr<Action> ActionPtr;

		class Action {
		public:

			// return as string (for debug purposes)
			virtual std::string to_string() const { return ""; }
		};

	}
}
