#include "scoreboard.h"
using namespace std; 

Scoreboard::Scoreboard() {
    // if needed 
}

void Scoreboard::clear_screen() {
	for (int i=0; i<50; ++i) { //idk if this works, Instead of clearing it just pushes it off the screen, if doesnt work ill come back and fix
		cout << '\n'; 
	}
}

void Scoreboard::print_title() {
	cout << "========================================\n";
    cout << "               FARKLE                  \n";
    cout << "========================================\n";
}

void Scoreboard::print_turn(const Player& current_player, const Table& table) {
	cout << "========================================\n";
	cout << "Player:        " << current_player.get_name() << '\n'; 
	cout << "Total score:   " << current_player.get_score()<< '\n';
	cout << "Turn score:    " << table.get_turn_score() << '\n';
	cout << "========================================\n";

	const vector<Die>& src = table.get_dice(); 

	vector<Die> dice; 
	dice.assign(src.begin(), src.end()); 

	cout <<"Dice:" <<endl; 
	for (size_t i = 0; i < dice.size(); ++i) { 
		cout << " Die " << i << ": " << dice[i].get_roll() << endl;
	}
	/*const vector<Die>& dice = table.get_dice(); 
	cout << "Dice:" << endl; 
	
	for (size_t i = 0; i < dice.size(); ++i){ 
		cout << " Die " << i << ": " << dice[i].get_roll() << endl; 
	}*/
}

void Scoreboard::print_options(const vector<ScoringOption>& options) {
	if (options.empty()) {
		cout << "No scoring options available." << endl; 
		return;
	}
	cout << "Scoring Options:" << endl; 

	for (size_t i = 0; i < options.size(); ++i) {
		cout << i << ") " << options[i].description << "  (+" << options[i].score<< " points"; 

		if (!options[i].die_indices.empty()) {
			cout << ", dice: ";
		
		for (size_t d = 0; d < options[i].die_indices.size(); d++) {
			cout << options[i].die_indices[d];
			if (d+1 < options[i].die_indices.size()) {
				cout << ",";
			}
		}
	}
		cout << ")" << endl; 
	}
}

void Scoreboard::print_winner(const Player& winner) {
	cout << "Winner: " << winner.get_name() << " with " << winner.get_score() << " points!" << endl; 
}
