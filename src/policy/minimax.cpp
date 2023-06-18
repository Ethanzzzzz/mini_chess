#include <cstdlib>
#include <iostream>
#include <cmath>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief get a legal action according to state value
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move MiniMax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;

    Move next_move;

    if(state->player == 0){
        int max = -100000;
        for(Move next: actions){
            if(minimax(state->next_state(next), depth-1, false) > max){
                next_move = next;
                max = minimax(state->next_state(next), depth-1, false);
            }
        }
    }
    else{
        int min = 100000;
        for(Move next: actions){
            if(minimax(state->next_state(next), depth-1, true) < min){
                next_move = next;
                min = minimax(state->next_state(next), depth-1, true);
            }
        }
    }
    return next_move;
}


// 按照psuedo code寫
int MiniMax::minimax(State* state, int depth, bool maximizing_player){

    if(!state->legal_actions.size())
        state->get_legal_actions();

    std::vector<Move> actions = state->legal_actions;

    if(depth == 0){
        return state->evaluate();
    }
    if(maximizing_player){
        int value = -100000;
        for(auto n: actions){
            State* next = state->next_state(n);
            value = std::max(value, minimax(next, depth-1, false));
        }
        return value;
    }
    else{   
        int value = 100000;
        for(auto n: actions){
            State* next = state->next_state(n);
            value = std::min(value, minimax(next, depth-1, true));
        }
        return value;
    }
}