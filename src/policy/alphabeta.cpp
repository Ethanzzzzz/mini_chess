#include <cstdlib>
#include <iostream>
#include <cmath>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief get a legal action according to state value
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;

    Move next_move;

    if(state->player == 0){
        int max = -1e6;
        for(Move next: actions){
            if(alphabeta(state->next_state(next), depth-1, -1e6, 1e6, false) > max){
                next_move = next;
                max = alphabeta(state->next_state(next), depth-1, -1e6, 1e6, false);
            }
        }
    }
    else{
        int min = 1e6;
        for(Move next: actions){
            if(alphabeta(state->next_state(next), depth-1, -1e6, 1e6, true) < min){
                next_move = next;
                min = alphabeta(state->next_state(next), depth-1, -1e6, 1e6, true);
            }
        }
    }
    return next_move;
}


// 按照psuedo code寫
int AlphaBeta::alphabeta(State* state, int depth, int alpha, int beta, bool maximizing_player){

    if(!state->legal_actions.size())
        state->get_legal_actions();

    std::vector<Move> actions = state->legal_actions;

    if(depth == 0){
        return state->evaluate();
    }
    if(maximizing_player){
        int value = -1e6;
        for(auto n: actions){
            State* next = state->next_state(n);
            value = std::max(value, alphabeta(next, depth-1, alpha, beta, false));
            alpha = std::max(alpha, value);
            if(alpha >= beta) break;
        }
        return value;
    }
    else{
        int value = 1e6;
        for(auto n: actions){
            State* next = state->next_state(n);
            value = std::min(value, alphabeta(next, depth-1, alpha, beta, true));
            beta = std::min(beta, value);
            if(beta <= alpha) break;
        }
        return value;
    }
}