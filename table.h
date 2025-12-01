#pragma once
#include <vector>
#include "die.h"
#include "player.h"

//Diego's comments; ask me


struct ScoringOption {
    std::string description;
    int score;
    std::vector<int> die_indices; 
}; // this is going to be what the calculations of possible plays is going to return so then we can print all the options to the player


class Table { 

	private:
		std::vector<Die>* current_dice;

		std::vector<bool> held_dice; // to know what dice can be used

		int turn_score; // this should add to the total score if player wins the turn

	public:
		Table();

		void set_dice(std::vector<Die>* player_dice);

		void roll_dices(); // do a functions that rolls all the remaing dice 


		std::vector<ScoringOption> possible_moves_calculation(); // calculate all possible moves, return an empty vector if is not possible. This will be a lot of if staments :c detect single 5s, single 1s, three 2s, four 2s, straghts, etc....


		void perform_move(const ScoringOption& option); // this is when depending on the user input we change the held_dice bool vector index from [0-5]

		const std::vector<Die>& get_dice() const; // idk the use for this. maybe we dont need it 
        int get_turn_score() const; // used at the end when user ends turn
        void reset(); // reset table, turn_score set to 0, vector bool all positive, etc
};
