/*
 Interface that the State class needs to comply with.
 (it doesn't need to extend this class, this is just here for reference)
 'Action' is your custom class containing your action information
 See examples for usage

class State {

	// perform a deep clone of the given state
	State(const State& other) {
		clone_from(other);
	}

	// perform a deep clone of the given state
	State& operator = (const State& other) {
		clone_from(other);
		return *this;
	}

	// perform a deep clone of the given state
	void clone_from(const State& other);

	// whether or not this state is terminal (reached end)
	bool is_terminal() const;

	//  agent id (zero-based) for agent who is about to make a decision
	int agent_id() const;

	// apply action to state
	void apply_action(const Action& action);

	// return possible actions from this state
	void get_actions(std::vector<Action>& actions) const;

	// get a random action, return false if no actions found
	bool get_random_action(Action& action) const;

	// evaluate this state and return a vector of rewards (for each agent)
	const vector<float> evaluate() const;

	// return state as string (for debug purposes)
	std::string to_string() const;

};

*/
