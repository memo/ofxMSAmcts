#pragma once

#include "ofxMSAmcts.h"

#include "ofMain.h"


using namespace msa::mcts;

namespace oxo {

//--------------------------------------------------------------
//--------------------------------------------------------------
struct Action {
public:
    Action(int t=0):tile(t) {}

    int tile;	// tile to place move in, 0..8, 0: top left, 8: bottom right
};


#define kNone		-1
#define kPlayer1	0
#define kPlayer2	1

//--------------------------------------------------------------
//--------------------------------------------------------------
class State {
public:

    //--------------------------------------------------------------
    // MUST HAVE METHODS

    State() {
        reset();
    }

    // default constructors will do
    // copy and assignment operators should perform a DEEP clone of the given state
    //    State(const State& other);
    //    State& operator = (const State& other);


    // whether or not this state is terminal (reached end)
    bool is_terminal() const  {
        return data.is_terminal;
    }

    //  agent id (zero-based) for agent who is about to make a decision
    int agent_id() const {
        return data.player_turn;
    }

    // apply action to state
    void apply_action(const Action& action)  {
        // sanity check
        if(action.tile < 0 || action.tile > 8) return;

        // place tile on board
        data.board[action.tile] = data.player_turn;

        // swap player turn
        data.player_turn = 1 - data.player_turn;

        // update game state
        static int win_combo[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

        for(int i=0; i<8; i++) {
            // if winning combo found,
            if(data.board[ win_combo[i][0] ] > kNone && data.board[ win_combo[i][0] ] == data.board[ win_combo[i][1] ] && data.board[ win_combo[i][1] ] == data.board[ win_combo[i][2] ]) {
                data.winner = data.board[ win_combo[i][0] ];
                data.is_terminal = true;
                return;
            }
        }

        // if no winning combo found
        // find number of empty tiles
        int num_empty = 0;
        for(int i=0; i<9; i++) if(data.board[i] == kNone) num_empty++;
        if(num_empty == 0) {
            data.winner = kNone;
            data.is_terminal = true;
        }
    }


    // return possible actions from this state
    void get_actions(std::vector<Action>& actions) const  {
        actions.clear();

        // any tile which is empty is a valid action
        for(int i=0; i<9; i++) if(data.board[i] == kNone) actions.push_back(Action(i));
    }


    // get a random action, return false if no actions found
    bool get_random_action(Action& action) const {
        std::vector<Action> actions;
        get_actions(actions);

        // sanity check
        if(actions.empty()) return false;

        action = actions[floor(ofRandom(actions.size()))];
        return true;
    }


    // evaluate this state and return a vector of rewards (for each agent)
    const vector<float> evaluate() const  {
        vector<float> rewards(2);

        if(data.is_terminal) {
            // could be written more compact, but this is more readable
            switch(data.winner) {

            case kNone: // draw
                rewards[kPlayer1] = rewards[kPlayer2] = 0.5;
                break;

            case kPlayer1: // player 1 wins
                rewards[kPlayer1] = 1;
                rewards[kPlayer2] = 0;
                break;

            case kPlayer2: // player 2 wins
                rewards[kPlayer1] = 0;
                rewards[kPlayer2] = 1;
                break;
            default:
                //assert(0);
                break;
            }
        } else {
            // game still going
            rewards[kPlayer1] = rewards[kPlayer2] = 0.0;
        }
        return rewards;
    }


    // return state as string (for debug purposes)
    std::string to_string() const  {
        stringstream str;
        str << "player_turn:" << player_to_string(data.player_turn) << "(" << data.player_turn << "), ";
        str << "is_terminal:" << data.is_terminal << ", ";
        str << "winner:" << player_to_string(data.winner) << "(" << data.winner << "), ";
        return str.str();
    }


    //--------------------------------------------------------------
    // IMPLEMENTATION SPECIFIC

    struct {
        int player_turn;	// which players turn it is, kPlayer1 or kPlayer2
        bool is_terminal;	// whether state is terminal or not
        int winner;			// who won: kNone (draw), kPlayer1 or kPlayer2
        int board[9];		// who is on each tile: kNone, kPlayer1 or kPlayer2
    } data;

    string player_to_string(int player_id) const {
        switch(player_id) {
        case kNone: return "None";
        case kPlayer1: return "Player 1";
        case kPlayer2: return "Player 2";
        }
    }

    void reset() {
        data.player_turn = kPlayer1;
        data.is_terminal = false;
        data.winner = kNone;
        for(int i=0; i<9; i++) data.board[i] = kNone;
    }

    void draw() {
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(20);
        ofBackground(150);
        float w = ofGetWidth();
        float h = ofGetHeight();
        float tile_w = w / 3;
        float tile_h = h / 3;

        // draw grid
        ofSetColor(0);
        ofDrawLine(0, tile_h, w, tile_h);
        ofDrawLine(0, 2 * tile_h, w, 2 * tile_h);
        ofDrawLine(tile_w, 0, tile_w, h);
        ofDrawLine(2 * tile_w, 0, 2 * tile_w, h);

        for(int c=0; c<9; c++) {
            int i = c % 3;
            int j = c / 3;
            ofRectangle tile_rect(i*tile_w, j*tile_h, tile_w, tile_h);
            float size = 0.7;
            if(data.board[c]==kPlayer1) draw_o(tile_rect, size);
            else if(data.board[c]==kPlayer2) draw_x(tile_rect, size);
        }
        ofPopStyle();
    }

    static void draw_x(ofRectangle rect, float scale) {
        rect.scaleFromCenter(scale);
        ofDrawLine(rect.getTopLeft(), rect.getBottomRight());
        ofDrawLine(rect.getTopRight(), rect.getBottomLeft());
    }

    static void draw_o(ofRectangle rect, float scale) {
        ofDrawEllipse(rect.x + rect.width/2, rect.y + rect.height/2, rect.width * scale, rect.height * scale);
    }

};

}
