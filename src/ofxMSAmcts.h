/*

MCTS Code Based on the Java (Simon Lucas - University of Essex) and Python (Peter Cowling, Ed Powley, Daniel Whitehouse - University of York) impelementations by at http://mcts.ai/code/index.html

Usage:
'State' contains the current state
'Action' contains an action that can be applied to a state to bring it to a new state

1. Extend class 'msa::mcts::State' to contain the state of your system

2. Extend class 'msa::mcts::Action' to contain actions that can apply to your system state

3. init:
StatePtr current_state = StatePtr(new State());
Action current_action;

4. update loop:
// create a Node from current state
Node current_node( current_state, current_action );

// get the best action
current_action = current_node->get_best_action();

// apply the action to the current state
current_state->apply_action(current_action);


Some points in no particular order
- it's not tailored for any specific use case. i.e. quite generic (but perhaps not generic enough)
- it's not optimized (priority on readability and flexibility)
- it supports variable number of actions per step



*/

#pragma once

//#include <random>

//#include "StateT.h"
#include "TreeNodeT.h"
//#include "Action.h"
//#include "State.h"
#include "MSALoopTimer.h"


namespace msa {
	namespace mcts {

		template <class State, typename Action>
		class UCT {
			typedef TreeNodeT<State, Action> TreeNode;
		public:
			float uct_k;					// k value in UCT function. default = sqrt(2)
			unsigned int max_iterations;	// do a maximum of this many iterations (0 to run till end)
			unsigned int max_millis;		// run for a maximum of this many milliseconds (0 to run till end)
			unsigned int simulation_depth;	// how many ticks (frames) to run simulation for
			LoopTimer timer;
			int iterations;

			// QUESTION: Macro actions. run MCTS in a separate thread to have L*times longer?

			//--------------------------------------------------------------
			UCT() :
				uct_k( sqrt(2) ), 
				max_iterations( 100 ),
				max_millis( 0 ),
				simulation_depth( 10 )
			{}


			//--------------------------------------------------------------
			// get best (immediate) child for given TreeNode based on uct score
			TreeNode* get_best_uct_child(TreeNode* node, float uct_k) const {
				// sanity check
				if(!node->is_fully_expanded()) return NULL;

				float best_utc_score = -std::numeric_limits<float>::max();
				TreeNode* best_node = NULL;

				// iterate all immediate children and find best UTC score
				int num_children = node->get_num_children();
				for(int i=0; i< num_children; i++) {
					/* 
					QUESTIONS:
					- some implementations divide child->value by child->num_visits, others don't. why?
					- some implementations add FLT_EPSILON to the divisor, others don't. why?
					- some implementations add 1 to this->num_visits inside log, others don't. why?
					*/
					TreeNode* child = node->get_child(i);
					float uct_exploitation = (float)child->get_value() / (child->get_num_visits() + FLT_EPSILON);
					float uct_exploration = sqrt( log((float)node->get_num_visits() + 1) / (child->get_num_visits() + FLT_EPSILON) );
					float uct_score = uct_exploitation + uct_k * uct_exploration;

					if(uct_score > best_utc_score) {
						best_utc_score = uct_score;
						best_node = child;
					}
				}

				return best_node;
			}


			//--------------------------------------------------------------
			TreeNode* get_most_visited_child(TreeNode* node) const {
				int most_visits = 0;
				TreeNode* best_node = NULL;

				// iterate all immediate children and find best UTC score
				int num_children = node->get_num_children();
				for(int i=0; i< num_children; i++) {
					TreeNode* child = node->get_child(i);
					if(child->get_num_visits() > most_visits) {
						most_visits = child->get_num_visits();
						best_node = child;
					}
				}

				return best_node;
			}



			//--------------------------------------------------------------
			Action run(const State& current_state, unsigned int seed = 1) {
				// initialize timer
				timer.init();

				// initialize root TreeNode with current state
				TreeNode root_node(current_state);

				TreeNode* best_node = NULL;

				// iterate
				iterations = 0;
				while(true) {
					// indicate start of loop
					timer.loop_start();

					// 1. SELECT. Start at root, dig down into tree using UCT on all fully expanded nodes
					TreeNode* selected_node = &root_node;
					while(!selected_node->is_terminal() && selected_node->is_fully_expanded()) {
						selected_node = get_best_uct_child(selected_node, uct_k);
//						assert(selected_node);	// sanity check
					}

					// 2. EXPAND by adding a single child
					TreeNode* expanded_node = selected_node->expand();

					// 3. SIMULATE
					State simulated_state(expanded_node->get_state());
					Action action;
					for(int t = 0; t < simulation_depth; t++) {
						if(simulated_state.is_terminal()) break;
						simulated_state.get_random_action(action);
						simulated_state.apply_action(action);
					}

					float value = simulated_state.evaluate();

					// 4. BACK PROPAGATION
					while(expanded_node) {
						expanded_node->update(value);
						expanded_node = expanded_node->get_parent();
					}

					// find most visited child
					best_node = get_most_visited_child(&root_node);

					// indicate end of loop for timer
					timer.loop_end();

					// exit loop if current total run duration (since init) exceeds max_millis
					if(max_millis > 0 && timer.check_duration(max_millis)) break;

					// exit loop if current iterations exceeds max_iterations
					if(max_iterations > 0 && iterations > max_iterations) break;
					iterations++;
				}

				// return best node's action
				if(best_node) return best_node->get_action();

				// we shouldn't be here
				return Action();
			}


		};
	}
}
