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

    int min = std::numeric_limits<int>::max(), max = std::numeric_limits<int>::min();
    Move next_move;

    if(depth % 2 == 0){
        for(Move next: actions){
            if(minimax(state->next_state(next), depth, false) <= min){
                next_move = next;
                min = minimax(state->next_state(next), depth, true);
            }
        }
    }
    else{
        for(Move next: actions){
            if(minimax(state->next_state(next), depth, false) >= max){
                next_move = next;
                max = minimax(state->next_state(next), depth, false);
            }
        }
    }
    return next_move;
}


// 按照psuedo code寫
int MiniMax::minimax(State* state, int depth, bool player){

    if(!state->legal_actions.size())
        state->get_legal_actions();

    std::vector<Move> actions = state->legal_actions;

    if(depth == 0 || state->game_state == WIN){
        return state->evaluate();
    }
    if(player){
        int value = std::numeric_limits<int>::min();
        for(auto n: actions){
            State* next = state->next_state(n);
            value = std::max(value, minimax(next, depth-1, false));
        }
        return value;
    }
    else{
        int value = std::numeric_limits<int>::max();
        for(auto n: actions){
            State* next = state->next_state(n);
            value = std::min(value, minimax(next, depth-1, true));
        }
        return value;
    }
}