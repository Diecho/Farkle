#include "player.h"
// nothing to do here (I think is good to go)

using namespace std;

Player::Player() {
    score = 0;
    name = "Unknown";
}

Player::Player(string new_name) {
    score = 0;
    name = new_name;
}

string Player::get_name() const {
    return name;
}

int Player::get_score() const {
    return score;
}

void Player::add_score(int points) {
    score += points;
}

void Player::set_dice(const vector<Die>& new_dice) {
    dice = new_dice;
}

vector<Die>& Player::get_dice() {
    return dice; 
}
