#include "declarations.h"

player::player(): player_ID(no_of_players_static), in_game(true), played_first_move_in_round(false) , bet_in_round(0)
{
    players_in_game.push_back(this);
    all_players.push_back(this);
    no_of_players_static++;
}

player::~player()
{
  no_of_players_static--;
  player_hand.submit();
}

bool player::collect_bet(int amount) //returns false if player doesnt have enough balance to raise by amount, else returns true, deducts the amount from players balance and adds it to pot
{   
    if (money_in_hand<amount){
        cout<<"Error, not enough balance in acc of "<<player_name<<" to pay "<<amount<<endl;
        return false;
    }
    money_in_hand-=amount;
    bet_in_round+=amount;
    pot_amount+=amount;
    cout<<"Collecting bet of "<<amount<<" from "<<player_name<<", money left in account of "<<player_name<<" is "<<money_in_hand<<endl;
    cout<<"The pot now is "<<pot_amount<<endl;

    return true;
}

void player::check() //allowed only if current bet is zero
{
    cout<<player_name<<" chose to check, passing turn to next player\n";
}

bool player::raise(int raise_amount) //returns false if player doesnt have enough balance to raise by amount, else returns true, and collects the raise and any leftover sum
{
    bool raise_possible= (this->collect_bet(current_bet+raise_amount- bet_in_round));
    if (raise_possible) {
      current_bet+=raise_amount;
      no_of_raises++;
      cout<<"Successfully raised by "<<raise_amount<<", the current bet now is "<<current_bet<<endl;
    }
    else cout<<"Cannot raise by "<<raise_amount<<" ,try again\n";
    return raise_possible;
}

void player::fold() //changes in_game to false and removes player from list players_in_game
{
    cout<<"Player "<<player_name<<" has folded and is now out of game\n";
    in_game=false;

    int index;                        
    for (int i=0; i<players_in_game.size(); i++) if (players_in_game[i]==this) index=i; 
    players_in_game.erase(players_in_game.begin()+index);
}