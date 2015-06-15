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

#include <random>

#include "Node.h"
#include "Action.h"
#include "State.h"
#include "MSALoopTimer.h"


namespace msa {
	namespace mcts {

		template <class State, class Action>
		class UCT {
			typedef NodeT <State, Action> Node;
		public:
			float uct_k;			// k value in UCT function. default = sqrt(2)
			unsigned int max_iterations;		// do a maximum of this many iterations (0 to run till end)
			unsigned int max_millis;			// run for a maximum of this many milliseconds (0 to run till end)
			unsigned int rollout_depth;

			UCT() {
				uct_k = sqrt(2);
				max_iterations = 100;
				max_millis = 0;
				rollout_depth = 10;
			}

/*
			Node* select(Node* node) {
		
				//Node *c = node;
				//float uct_score = c.wins / c.visits + sqrt(2 * log(self.visits)/c.visits)

			}
		*/
			

			// get best (immediate) child for given node based on uct score
			Node * get_best_child_uct(Node* node, float uct_k) const {
				int num_children = node->get_num_children();

				if(num_children == 0) return NULL;

				float best_utc_score = -std::numeric_limits<float>::max();
				Node *best_node = NULL;
				
				// iterate all immediate children and find best UTC score
				for(int i=0; i< num_children; i++) {
					/* 
					QUESTIONS:
						- some implementations divide child->value by child->num_visits, others don't. why?
						- some implementations add FLT_EPSILON to the divisor, others don't. why?
						- some implementations add 1 to this->num_visits inside log, others don't. why?
					*/
					Node *child = node->get_child(i).get();
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




			Action run(const State& current_state, unsigned int seed = 1) {
				// initialize timer
				LoopTimer timer;
				timer.init();

				// initialize random generator
				std::mt19937 rand_gen(seed);

				// initialize root node with current state
				Node root_node(current_state);

				// iterate
				int i=0;
				while(true) {
					// indicate start of loop
					timer.loop_start();

					// search tree with mcts uct


					// start at root
					Node *node = &root_node;

					// 1. select a leaf node
					/* 
					QUESTIONS:
						- does this loop until a node 
					*/
					while(!node->get_state().is_terminal() && node->get_depth() < rollout_depth && node->is_expanded()) {
						node = get_best_child_uct(node, uct_k);
					}

					// 2. expand

					// 3. rollout
					//double delta = selected.rollOut(playerID);

					// 4. back propagation
					//


					// indicate end of loop for timer
					timer.loop_end();

					// exit loop if current total run duration (since init) exceeds max_millis
					if(max_millis > 0 && timer.check_duration(max_millis)) break;

					// exit loop if current iterations exceeds max_iterations
					if(max_iterations > 0 && i++ > max_iterations) break;
				}


				// return most visited action
				return Action();
			}


		};
	}
}
