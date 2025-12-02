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
	int temp = 0;
	vector<ScoringOption> sov;
	for (int i = 0; i < 6; i++) {
		count++;
		if (num[i] > 3) {
			if (count == 1) {
				temp = count * 1000 * 2 *(num[i]-2);
			} else {
				temp = count * 100 * 2 *(num[i]-2);
			}
			ScoringOption a;
			a.description = "You got " + std::to_string(num[i]) + "s " + std::to_string(count);
			a.score = temp;
			vector<bool> vec(6, false);
			for (int i = 0; i < 6; i++) {
		    	if(!(held_dice[i])) {
        	    	int val = (*current_dice)[i].get_roll();
					if (val == count) vec[i] = true;
				}
			 }
			a.die_indices = vec;
			sov.push_back(a);
		} else if (num[i] > 2) {
			if (count == 1) {
                temp = count * 1000;
            } else {
                temp = count * 100;
            }
			ScoringOption a;
			a.description = "You got " + std::to_string(num[i]) + "s " + std::to_string(count);
            a.score = temp;
            vector<bool> vec(6, false);
            for (int i = 0; i < 6; i++) {
                if(!(held_dice[i])) {
                    int val = (*current_dice)[i].get_roll();
                    if (val == count) vec[i] = true;
                }
             }
            a.die_indices = vec;
			sov.push_back(a);
		}
	}
	count = 0;
	for (int x : num) {
		if (x > 0) count++;
	}
	if (count > 4) {
		if (num[0] == 0) {
			ScoringOption a;
			a.description = "You got a partial straight (2, 3, 4, 5, 6)";
			a.score = 750;
			vector<bool> bb(6, false);
			for (int i = 0; i < 6; i++) {
				if(!(held_dice[i])) {
					int val = (*current_dice)[i].get_roll();
					if (val != 1 && !(bb[val-1])) {
						bb[val-1] = true;
					}
				}
			}
			a.die_indices = bb;
			sov.push_back(a);

		} else if (num[0] == 0) {
			ScoringOption a;
			a.description = "You got a partial straight (1, 2, 3, 4, 5)";
			a.score = 500;
			vector<bool> bb(6, false);
			for (int i = 0; i < 6; i++) {
				if(!(held_dice[i])) {
					int val = (*current_dice)[i].get_roll();
					if (val != 6 && !(bb[val-1])) {
						bb[val-1] = true;
					}
				}
			}
			a.die_indices = bb;
			sov.push_back(a);
		}
	}
	if (count > 5) {
		ScoringOption a;
        a.description = "You got a full straight (1, 2, 3, 4, 5, 6)";
		vector<bool> sixty_seven(6, true);
		a.die_indices = sixty_seven;
		a.score = 1500;
		sov.push_back(a);

	}
	vector<bool> ddd(6,false);
	for (int i = 0; i < 6; i++) {
		if(!(held_dice[i])) {
			int val = (*current_dice)[i].get_roll();
			if(val == 1 || val == 5){
				ddd[val-1] = true;
			}
		}
	}
	if (ddd[0]) {
		count = 0;
		ScoringOption al;
		vector<bool> asd(6, false);
		for (int i = 0; i < 6; i++) {
			if(!(held_dice[i]) && count < 3) {
				int val = (*current_dice)[i].get_roll();
				if (val == 1 && !(asd[i])) {
					asd[i] = true;
					count++;
				}
			}
		}
		al.description = "You got " + std::to_string(count) + "s 1";
		al.score = 100 * count;
		al.die_indices = asd;
		sov.push_back(al);
	}
	if (ddd[4]) {
		count = 0;
		ScoringOption al;
		vector<bool> asd(6, false);
		for (int i = 0; i < 6; i++) {
			if(!(held_dice[i]) && count < 3) {
				int val = (*current_dice)[i].get_roll();
				if (val == 5 && !(asd[i])) {
					asd[i] = true;
					count++;
				}
			}
		}
		al.description = "You got " + std::to_string(count) + "s 5";
		al.score = 50 * count;
		al.die_indices = asd;
		sov.push_back(al);
	}
	if (sov.empty()) return {};
    return sov; 
}

void Table::perform_move(const ScoringOption& option) {
	turn_score += option.score;
	for (int i = 0; i < 6; i++) {
		if (held_dice[i] != option.die_indices[i]) {
			held_dice[i] = true;
		}
	}
}

const vector<Die>& Table::get_dice() const {
    return *current_dice; 
}

int Table::get_turn_score() const {
    return turn_score;
}

void Table::reset() {
	turn_score = 0;
	for (int i = 0; i < 6; i++) {
		held_dice[i] = false;
	}
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

const vector<bool>& Table::get_held() const {
    return held_dice; 
}
