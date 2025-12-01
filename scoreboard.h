#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "player.h" 
#include "table.h" 

class Scoreboard {
    public:
        Scoreboard();
        
        void clear_screen(); 

        void print_title(); //maybe add like a cool logo or something

        // should print
		// player name and total score
		// the dice in the table
		// player turn score
        void print_turn(const Player& current_player, const Table& table);

        void print_options(const std::vector<ScoringOption>& options);// prints all options of the vector ScoringOptions that is in table

        void print_winner(const Player& winner); // when someone gets to 4000 total points 
};
