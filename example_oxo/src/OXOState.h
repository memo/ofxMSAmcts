#pragma once

#include "../../src/ofxMSAmcts.h"

#include "ofMain.h"


using namespace msa::mcts;

namespace oxo {

	//--------------------------------------------------------------
	//--------------------------------------------------------------
	struct Action /*: public ActionBase */{
	public:
		Action(int t=0):tile(t) {}

		int tile;	// tile to place move in, 0..8, 0: top left, 8: bottom right
	};

	//--------------------------------------------------------------
	//--------------------------------------------------------------
	class State /*: public StateT<Action> */{
		//typedef std::shared_ptr< Action > ActionPtr;
	public:

		//--------------------------------------------------------------
		// MUST HAVE METHODS

		State() {
			reset();
		}

		// perform a deep clone of the given state
		State(const State& other)  {
			clone_from(other);
		}

		// perform a deep clone of the given state
		State& operator = (const State& other ) {
			clone_from(other);
			return *this;
		}

		// perform a deep clone of the given state
		void clone_from(const State& other)  {
			memcpy(&data, &other.data, sizeof(data));
		}

		// whether or not this state is terminal (reached end)
		bool is_terminal() const  {
			return data.is_terminal;
		}

		// apply action to state
		void apply_action(const Action& action)  {
			// sanity check
			if(action.tile < 0 || action.tile > 8) return;

			// place tile on board
			data.board[action.tile] = data.player_turn;

			// swap player turn
			data.player_turn = 3 - data.player_turn;

			// update game state
			static int win_combo[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

			for(int i=0; i<8; i++) {
				// if winning combo found,
				if(data.board[ win_combo[i][0] ] > 0 && data.board[ win_combo[i][0] ] == data.board[ win_combo[i][1] ] && data.board[ win_combo[i][1] ] == data.board[ win_combo[i][2] ]) {
					data.winner = data.board[ win_combo[i][0] ];
					data.is_terminal = true;
					return;
				}
			}

			// if no winning combo found
			// find number of empty tiles
			int num_empty = 0;
			for(int i=0; i<9; i++) if(data.board[i] == 0) num_empty++;
			if(num_empty == 0) {
				data.winner = 0;
				data.is_terminal = true;
			}
		}


		// return possible actions from this state
		void get_actions(std::vector<Action>& actions) const  {
			actions.clear();

			// any tile which is empty is a valid action
			for(int i=0; i<9; i++) if(data.board[i] == 0) actions.push_back(Action(i));
		}


		// get a random action, return false if no actions found
		bool get_random_action(Action& action) const {
			std::vector<Action> actions;
			get_actions(actions);
			//if(actions.empty()) return false;

			action = actions[floor(ofRandom(actions.size()))];
			return true;
		}


		// evaluate this state and return a 'value' based on rewards and penalties
		float evaluate() const  {
			// game still going
			if(!data.is_terminal) return 0;

			// draw
			if(data.winner == 0) return 0.5;

			// won (evaluation is done after the move, so need to check against other player)
			if(data.winner == 3 - data.player_turn) return 1;

			// lost
			return 0;
		}


		// return state as string (for debug purposes)
		std::string to_string() const  {
			stringstream str;
			str << "player_turn:" << data.player_turn << ", ";
			str << "is_terminal:" << data.is_terminal << ", ";
			str << "winner:" << data.winner << ", ";
			return str.str();
		}


		//--------------------------------------------------------------
		// IMPLEMENTATION SPECIFIC

		// POD containing data about state that's safe to memcpy
		struct {
			int player_turn;	// which players turn it is, 1 or 2
			bool is_terminal;	// whether state is terminal or not
			int winner;			// who won
			int board[9];		// 0: empty, 1: player 1, 2: player2
		} data;

		void reset() {
			data.player_turn = 1;
			data.is_terminal = false;
			data.winner = 0;
			for(int i=0; i<9; i++) data.board[i] = 0;
		}

		void draw() {
			ofPushStyle();
			ofNoFill();
			ofBackground(150);
			float w = ofGetWidth();
			float h = ofGetHeight();
			float tile_w = w / 3;
			float tile_h = h / 3;
			
			// draw grid
			ofSetColor(0);
			ofLine(0, tile_h, w, tile_h);
			ofLine(0, 2 * tile_h, w, 2 * tile_h);
			ofLine(tile_w, 0, tile_w, h);
			ofLine(2 * tile_w, 0, 2 * tile_w, h);

			for(int c=0; c<9; c++) {
				int i = c % 3;
				int j = c / 3;
				ofRectangle tile_rect(i*tile_w, j*tile_h, tile_w, tile_h);
				float size = 0.7;
				if(data.board[c]==1) draw_o(tile_rect, size);
				else if(data.board[c]==2) draw_x(tile_rect, size);
			}
			ofPopStyle();
		}

		static void draw_x(ofRectangle rect, float scale) {
			rect.scaleFromCenter(scale);
			ofLine(rect.getTopLeft(), rect.getBottomRight());
			ofLine(rect.getTopRight(), rect.getBottomLeft());
		}

		static void draw_o(ofRectangle rect, float scale) {
			ofEllipse(rect.x + rect.width/2, rect.y + rect.height/2, rect.width * scale, rect.height * scale);
		}

	};

}