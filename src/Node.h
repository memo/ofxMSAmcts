/*
A node in the decision tree.
I tried to keep this independent of UCT/MCTS.
Only contains information / methods related to State, Action, Parent, Children etc. 

*/

#pragma once

#include <memory>
#include <math.h>
#include <vector>

#include "State.h"

namespace msa {
	namespace mcts {

		template <class State, class Action>
		class NodeT {

			typedef std::shared_ptr<NodeT<State, Action> > NodePtr;


		public:
			NodeT(const State& state, const NodeT* parent = NULL) {
				this->state.clone_from(state);
				this->parent = parent;

				//				is_expanded = false;
				num_visits = 0;
				value = 0;
				depth = parent ? 0 : parent->depth + 1;

				children.clear();
			}


			void expand() {
				int bestAction = 0;
				float best_value = -std::numeric_limits<float>::max();

				for (int i = 0; i < children.length; i++) {
					double x = m_rnd.nextDouble();
					if (x > bestValue && children[i] == null) {
						bestAction = i;
						bestValue = x;
					}
				}

				SimpleBattle nextState = state.clone();
				if(playerId == 0) {
					nextState.update(MMMCTS.actions.get(bestAction).buildAction(), DEFAULTACTION);
				} else {
					nextState.update(DEFAULTACTION, MMMCTS.actions.get(bestAction).buildAction());
				}

				SingleTreeNode tn = new SingleTreeNode(nextState, this, this.m_rnd);
				children[bestAction] = tn;
				return tn;

			}

			// getters
			const State & get_state() const { return state; }
			const Action & get_action() const { return action; }
			bool is_expanded() const { return children.empty() == false; }
			int get_num_visits() const { return num_visits; }
			float get_value() const { return value; }
			int get_depth() const { return depth; }
			int get_num_children() const { return children.size(); }
			NodePtr get_child(int i) const { return children[i]; }

		private:
			State state;			// the state of this node
			Action action;			// the action which led to the state of this node
			const NodeT* parent;		// parent of this node

			//			bool is_expanded;		// whether node is fully expanded or not
			int num_visits;			// number of times node has been visited
			float value;			// value of this node
			int depth;

			std::vector< NodePtr > children;	// all current children


			// create a clone of the current state, apply action, and add as child
			void add_child_with_action(const Action &new_action) {
				NodeT *child_node = new NodeT(state, this);
				child_node->action = new_action;
				child_node->state.apply_action(action);
				children.push_back( NodePtr(child_node) );	// add to children
			}

			void update_value(float value) {
				this->value += value;
				num_visits++;
			}




		};

	}
}