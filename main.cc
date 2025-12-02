//Write your last name and your partner's name here
// Hidalgo
// Kuang
// Ngo
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

#include "die.h"
#include "table.h"
#include "player.h"
#include "scoreboard.h"

using namespace std;

struct DieWeights{ // get this from the data base
    string name;
    vector<double> weights;
};

vector<DieWeights> load_dice_database(){
    vector<DieWeights> diceData;
    ifstream file("dice_database.txt");
    
    if (!file.is_open()){
        cout << "Error: Could not open dice_database.txt" << endl;
        return diceData;
    }

    string name;
    //  Dice_name w1 w2 w3 w4 w5 w6
    while (file >> name){
        DieWeights die;
        die.name = name;
        double total = 0;
        vector<double> weights;

        for(int i = 0; i < 6; i++){
            double w;
            file >> w;
            weights.push_back(w);
            total += w;
        }

        for(double &w : weights){
			w = w / total;
        }
        
		die.weights = weights;
        diceData.push_back(die);
    }
    file.close();
    return diceData;
}
void chooseDie(Player& p, const vector<DieWeights>& diceData){
    vector<Die> chosen_dice;
    
    cout << "\n--- " << p.get_name() << ", choose your dice! ---\n";
    
    for(size_t i = 0; i < diceData.size(); i++){
        cout << "["  << i << "]: " << diceData[i].name << endl;
    }

    for(int i = 0; i < 6; i++){
        int selection;
        while(true){
			cout << "Pick die #" << (i+1) << " (0-" << diceData.size() - 1 << "): ";
            cin >> selection;
            
			if (cin.fail()) {
				cout << "Invalid input! Please enter a number.\n";
				cin.clear(); 
				cin.ignore(10000, '\n'); 
				continue; 
			}
			if (selection >= 0 && selection < diceData.size()){
				Die d(diceData[selection].weights, 6);
				chosen_dice.push_back(d);
                break;
            } else {
                cout << "Invalid. Try again.\n";
            }
        }
    }
    p.set_dice(chosen_dice);
}


int main() {
	srand(time(0));

	Scoreboard view;
	Table table;

	vector<DieWeights> all_dice = load_dice_database();
    if(all_dice.empty()){
        cout << "Database empty :c" << endl;
    }

	string name1;
	string name2;
	
	cout << "Type player 1 name:  \n";
	cin >> name1;

	cout << "Type player 2 name:  \n";

	cin >> name2;

    Player p1(name1);
    Player p2(name2);

	chooseDie(p1, all_dice);
	chooseDie(p2, all_dice);

	bool game_running = true;
    Player* current_player = &p1; 

	while (game_running){

		table.reset(); //important resets vector of true values
		table.set_dice(&current_player->get_dice());
		bool turn_active = true;
			while(turn_active){
				view.clear_screen(); //this should work as a clear
				view.print_title();
				
				cout << "Rolling dice...\n";
				table.roll_dices();
				view.print_turn(*current_player, table);

				vector<ScoringOption> options = table.possible_moves_calculation(); // this uses a struct that is in table.h

				if (options.empty()) {
					cout << "\nFARKLE!! Turn over :c\n";
					cout << "Press Enter to continue...";
					cin.ignore(); cin.get(); 
					turn_active = false;
					break;
				}
				view.print_options(options); //important to undertand how the struck in table.h works to do this :D try to do something similar of what i did in the choose dice part you can run a.out to see how it looks

				int choice;
				cout << "\nSelect a move (0-" << options.size()-1 << "): ";
				cin >> choice;
				if (cin.fail() || choice < 0 || choice >= options.size()) {
					cout << "Invalid choice. Picking first option by default\n";
					cin.clear(); cin.ignore(10000, '\n');
					choice = 0;
				}

				table.perform_move(options[choice]);

				if (table.get_held_count() == 6) {
					cout << "\nHOT DICE!!\n";

					table.reset_held_dice(); 

					cout << "Press Enter to roll again...";
					cin.ignore(); cin.get();
					continue;
				}
				
				char decision;
				cout << "\nCurrent Turn Score: " << table.get_turn_score() << endl;
				cout << "[R]oll remaining dice or [B]ank points? ";
				cin >> decision;

				if (decision == 'B' || decision == 'b') {
					current_player->add_score(table.get_turn_score());
					cout << "New Total: " << current_player->get_score() << endl;
					cout << "Press Enter to switch players...";
					cin.ignore(); cin.get();
					turn_active = false;
				}
			}
			if (current_player->get_score() >= 4000) { // 4000 points to win
				view.print_winner(*current_player);
				game_running = false;
			}
			if (current_player == &p1) current_player = &p2;
			else current_player = &p1;
	}
	return 0;
}
