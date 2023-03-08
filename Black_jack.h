/*#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include "Textbox.h"
using namespace std;

int balance = 500;
bool betPlaced = false, betBarEnable = true, first = true, gameFinish = false;
int playerNrOfCards, dealerNrOfCards;
int playerCards, dealerCards;
textBox bet;

struct card
{
    int rank;
    int value;
};

card player[6], dealer[6];

int randomGenerator()
{
    int v = rand() % 14 + 1;
    return v;
}

int randomRank()
{
    int r = rand() % 4 + 1;
    return r;
}

void Place()
{
    betBarEnable = false;
    betPlaced = true;
    balance -= bet.betValue;
}

void Hit()
{
    if (betPlaced == true && playerCards < 21 && playerNrOfCards < 5)
    {
        playerNrOfCards++;
        int card = randomGenerator();
        if (card > 9)
        {
            playerCards++;
        }
        else
        {
            playerCards += card;
        }
        player[playerNrOfCards].value = card;
        card = randomRank();
        player[playerNrOfCards].rank = card;
    }
}

void Stand()
{
    while (dealerCards < 17)
    {
        dealerNrOfCards++;
        int card = randomGenerator();
        if (card > 9)
        {
            dealerCards += 10;
        }
        else
        {
            dealerCards += card;
        }
        dealer[dealerNrOfCards].value = card;
        card = randomRank();
        dealer[dealerNrOfCards].rank = card;

    }

    if (playerCards > 21 || dealerCards > playerCards && dealerCards <= 21)
    {
        cout << "Lose\n";
        cout << "Player card=" << playerCards << " Dealer cards=" << dealerCards << "\n";
        gameFinish = true;
    }
    else if (playerCards > dealerCards && playerCards <= 21 || dealerCards > 21)
    {
        cout << "Win\n";
        cout << "Player card=" << playerCards << " Dealer cards=" << dealerCards << "\n";
        balance += 2 * bet.betValue;
        gameFinish = true;
    }
    else
    {
        cout << "Tie\n";
        cout << "Player card=" << playerCards << " Dealer cards=" << dealerCards << "\n";
        balance += bet.betValue;
        gameFinish = true;

    }
}

void Blackjack()
{
	if (first == true && betPlaced == true)
	{
		playerNrOfCards++;
		int card = randomGenerator();
		if (card > 9)
		{
			playerCards += 10;
		}
		else
		{
			playerCards += card;
		}
		player[playerNrOfCards].value = card;
		card = randomRank();
		player[playerNrOfCards].rank = card;
		playerNrOfCards++;
		card = randomGenerator();
		if (card > 9)
		{
			playerCards += 10;
		}
		else
		{
			playerCards += card;
		}
		player[playerNrOfCards].value = card;
		card = randomRank();
		player[playerNrOfCards].rank = card;
		dealerNrOfCards++;
		card = randomGenerator();
		if (card > 9)
		{
			dealerCards += 10;
		}
		else
		{
			dealerCards += card;
		}
		dealer[dealerNrOfCards].value = card;
		card = randomRank();
		dealer[dealerNrOfCards].rank = card;
		dealerNrOfCards++;
		card = randomGenerator();
		if (card > 9)
		{
			dealerCards += 10;
		}
		else
		{
			dealerCards += card;
		}
		dealer[dealerNrOfCards].value = card;
		card = randomRank();
		dealer[dealerNrOfCards].rank = card;
		first = false;
	}


	
}
void Gamefinish()
{
if (gameFinish == true)
	{
		sleep(seconds(3));
		betBarEnable = true;
		betPlaced = false;
		playerCards = 0;
		playerNrOfCards = 0;
		dealerCards = 0;
		dealerNrOfCards = 0;
		first = true;
		gameFinish = false;
	}
}
*/