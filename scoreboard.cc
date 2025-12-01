#include "scoreboard.h"
using namespace std; 

Scoreboard::Scoreboard() {
    // if needed 
}

void Scoreboard::clear_screen() {
	//TODO
}

void Scoreboard::print_title() {
    cout << "--- FARKLE TITLE ---" << endl; // upgrade this later
}

void Scoreboard::print_turn(const Player& current_player, const Table& table) {
	//TODO
}

void Scoreboard::print_options(const vector<ScoringOption>& options) {
	//TODO
}

void Scoreboard::print_winner(const Player& winner) {
	//TODO
}
