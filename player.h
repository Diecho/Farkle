#pragma once
#include <string>
#include <vector>
#include "die.h"
// diego's comments ask me if you dont undertand something :D
class Player {

	private:
		std::string name;
		int score;
		std::vector<Die> dice; // store the 6 dice, player should chose the different weights at the start of the game/round

	public:
		Player();
		Player(std::string name); //chose game for the player, we should have two players (maybe we can implement more)

		std::string get_name() const;
        int get_score() const; // this is the total score, not the score of of one turn

		void add_score(int points); // this only adds to the total
		void set_dice(const std::vector<Die>& new_dice); //I think this is once at the begining and thats it 

		std::vector<Die>& get_dice(); // returns the vector of dice of the player. We should use pointers table class :D 
};
