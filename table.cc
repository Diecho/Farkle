#include "table.h"

using namespace std;


Table::Table() {
    turn_score = 0;
    current_dice = nullptr; 
}

void Table::set_dice(vector<Die>* player_dice) {
    current_dice = player_dice;
	for (int i = 0; i < 6; i++) {
		held_dice.push_back(false);
	}
	//Create vector<bool> held_dice full of true 
}

void Table::roll_dices() {
	for (int i = 0; i < 6; i++) {
		if(!(held_dice[i])) {
			(*current_dice)[i].roll();
		}
	}

}

vector<ScoringOption> Table::possible_moves_calculation() {
	//TODO
	vector<int> num(6, 0);
	for (int i = 0; i < 6; i++) {
        if(!(held_dice[i])) {
            int val = (*current_dice)[i].get_roll();
			num[val-1] = num[val-1] + 1;
        }
    }
	int count = 0;
	for (int i = 0; i < 6; i++) {
		count++;
		if (num[i] > 3) {}

	}

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

int Table::get_held_count() const {
    int count = 0;
    for(bool b : held_dice) {
        if(b) {
            count++;
        }
    }
    return count;
}

void Table::reset_held_dice() {
    for(unsigned int i = 0; i < held_dice.size(); i++) {
        held_dice[i] = false;
    }
}

