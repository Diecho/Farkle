#include "table.h"

using namespace std;


Table::Table() {
    turn_score = 0;
    current_dice = nullptr; 
}

void Table::set_dice(vector<Die>* player_dice) {
    current_dice = player_dice;
	//Create vector<bool> held_dice full of true 
}

void Table::roll_dices() {
	//TODO
}

vector<ScoringOption> Table::possible_moves_calculation() {
	//TODO
    return {}; 
}

void Table::perform_move(const ScoringOption& option) {
	//TODO
}

const vector<Die>& Table::get_dice() const {
    return *current_dice; 
}

int Table::get_turn_score() const {
    return turn_score;
}

void Table::reset() {
	//TODO
}
