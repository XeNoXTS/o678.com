#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include "Black_jack.h"
#include "Poker.h"
#include "slot.h"
#include "Textbox.h"

using namespace std;
using namespace sf;


int balance = 500;
bool betPlaced = false, betBarEnable = true, first = true, gameFinish = false;
bool betPlacedforP = false;
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


void Hit()
{
	if (betPlaced == true && playerCards < 21 && playerNrOfCards < 5)
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

void showslot(RenderWindow& window, slotmac& mac) {//https://en.sfml-dev.org/forums/index.php?topic=9453.0 ได้วิธีมาจากนี่

	Texture s10, sj, sq, sk, sa, scat, sbruh, sdog;
	s10.loadFromFile("slot_im/10.png");
	sj.loadFromFile("slot_im/j.png");
	sq.loadFromFile("slot_im/q.png");
	sk.loadFromFile("slot_im/k.png");
	sa.loadFromFile("slot_im/a.png");
	scat.loadFromFile("slot_im/cat.png");
	sdog.loadFromFile("slot_im/dog.png");
	sbruh.loadFromFile("slot_im/bruh.png");

	Sprite sym10(s10), symj(sj), symq(sq), symk(sk), syma(sa), symcat(scat), symdog(sdog), symbruh(sbruh);
	sym10.scale(0.8, 0.8);
	symj.scale(0.8, 0.8);
	symq.scale(0.8, 0.8);
	symk.scale(0.8, 0.8);
	syma.scale(0.8, 0.8);
	symcat.scale(0.8, 0.8);
	symdog.scale(0.8, 0.8);
	symbruh.scale(0.8, 0.8);
	int xpos = 0, ypos = 50;
	S_row{
		xpos = 350;
		S_col{
			switch (mac.sym[row][col]) {
			case 1:
				sym10.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(sym10);
				break;
			case 2:
				symj.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(symj);
				break;
			case 3:
				symq.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(symq);
				break;
			case 4:
				symk.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(symk);
				break;
			case 5:
				syma.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(syma);
				break;
			case 6:
				symbruh.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(symbruh);
				break;
			case 7:
				symcat.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(symcat);
				break;
			case 8:
				symdog.setPosition(xpos, ypos);
				xpos += 240;
				window.draw(symdog);
				break;
			default:

				break;

			}
		}
		ypos += 270;
	}

}

int main() {
	srand(time(0));
	RenderWindow window(VideoMode(1600, 900), "O678.COM", Style::Titlebar | Style::Close);

	textBox bet;
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t18, t19, t20, t21, t22, t23, t24, t25, t17;
	Texture t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47;
	Texture t48, t49, t50, t51, t52;
	Texture t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71;

	t1.loadFromFile("images/2_of_clubs.png");
	t2.loadFromFile("images/2_of_diamonds.png");
	t3.loadFromFile("images/2_of_hearts.png");
	t4.loadFromFile("images/2_of_spades.png");

	t5.loadFromFile("images/3_of_clubs.png");
	t6.loadFromFile("images/3_of_diamonds.png");
	t7.loadFromFile("images/3_of_hearts.png");
	t8.loadFromFile("images/3_of_spades.png");

	t9.loadFromFile("images/4_of_clubs.png");
	t10.loadFromFile("images/4_of_diamonds.png");
	t11.loadFromFile("images/4_of_hearts.png");
	t12.loadFromFile("images/4_of_spades.png");

	t13.loadFromFile("images/5_of_clubs.png");
	t14.loadFromFile("images/5_of_diamonds.png");
	t15.loadFromFile("images/5_of_hearts.png");
	t16.loadFromFile("images/5_of_spades.png");

	t17.loadFromFile("images/6_of_clubs.png");
	t18.loadFromFile("images/6_of_diamonds.png");
	t19.loadFromFile("images/6_of_hearts.png");
	t20.loadFromFile("images/6_of_spades.png");

	t21.loadFromFile("images/7_of_clubs.png");
	t22.loadFromFile("images/7_of_diamonds.png");
	t23.loadFromFile("images/7_of_hearts.png");
	t24.loadFromFile("images/7_of_spades.png");

	t25.loadFromFile("images/8_of_clubs.png");
	t26.loadFromFile("images/8_of_diamonds.png");
	t27.loadFromFile("images/8_of_hearts.png");
	t28.loadFromFile("images/8_of_spades.png");

	t29.loadFromFile("images/9_of_clubs.png");
	t30.loadFromFile("images/9_of_diamonds.png");
	t31.loadFromFile("images/9_of_hearts.png");
	t32.loadFromFile("images/9_of_spades.png");

	t33.loadFromFile("images/10_of_clubs.png");
	t34.loadFromFile("images/10_of_diamonds.png");
	t35.loadFromFile("images/10_of_hearts.png");
	t36.loadFromFile("images/10_of_spades.png");

	t37.loadFromFile("images/ace_of_clubs.png");
	t38.loadFromFile("images/ace_of_diamonds.png");
	t39.loadFromFile("images/ace_of_hearts.png");
	t40.loadFromFile("images/ace_of_spades.png");

	t41.loadFromFile("images/jack_of_clubs.png");
	t42.loadFromFile("images/jack_of_diamonds.png");
	t43.loadFromFile("images/jack_of_hearts.png");
	t44.loadFromFile("images/jack_of_spades.png");

	t45.loadFromFile("images/king_of_clubs.png");
	t46.loadFromFile("images/king_of_diamonds.png");
	t47.loadFromFile("images/king_of_hearts.png");
	t48.loadFromFile("images/king_of_spades.png");

	t49.loadFromFile("images/queen_of_clubs.png");
	t50.loadFromFile("images/queen_of_diamonds.png");
	t51.loadFromFile("images/queen_of_hearts.png");
	t52.loadFromFile("images/queen_of_spades.png");

	t53.loadFromFile("images/BG_MN.png");
	t54.loadFromFile("images/PBJ.png");
	t55.loadFromFile("images/PPK.png");
	t56.loadFromFile("images/PSL.png");
	t57.loadFromFile("images/Exit.png");

	t58.loadFromFile("images/hit.png");
	t59.loadFromFile("images/stand.png");
	t60.loadFromFile("images/place.png");
	t71.loadFromFile("images/place2.png");
	t66.loadFromFile("images/Call.png");
	t67.loadFromFile("images/Fold.png");
	t68.loadFromFile("images/Allin.png");

	t61.loadFromFile("images/10.png");
	t69.loadFromFile("images/50.png");
	t62.loadFromFile("images/100.png");
	t70.loadFromFile("images/500.png");
	t63.loadFromFile("images/1000.png");

	t64.loadFromFile("images/background1.png");


	Sprite cardd;

	Sprite two_of_clubs(t1);
	Sprite two_of_diamonds(t2);
	Sprite two_of_hearts(t3);
	Sprite two_of_spades(t4);

	Sprite three_of_clubs(t5);
	Sprite three_of_diamonds(t6);
	Sprite three_of_hearts(t7);
	Sprite three_of_spades(t8);

	Sprite four_of_clubs(t9);
	Sprite four_of_diamonds(t10);
	Sprite four_of_hearts(t11);
	Sprite four_of_spades(t12);

	Sprite five_of_clubs(t13);
	Sprite five_of_diamonds(t14);
	Sprite five_of_hearts(t15);
	Sprite five_of_spades(t16);

	Sprite six_of_clubs(t17);
	Sprite six_of_diamonds(t18);
	Sprite six_of_hearts(t19);
	Sprite six_of_spades(t20);

	Sprite seven_of_clubs(t21);
	Sprite seven_of_diamonds(t22);
	Sprite seven_of_hearts(t23);
	Sprite seven_of_spades(t24);

	Sprite eight_of_clubs(t25);
	Sprite eight_of_diamonds(t26);
	Sprite eight_of_hearts(t27);
	Sprite eight_of_spades(t28);

	Sprite nine_of_clubs(t29);
	Sprite nine_of_diamonds(t30);
	Sprite nine_of_hearts(t31);
	Sprite nine_of_spades(t32);

	Sprite ten_of_clubs(t33);
	Sprite ten_of_diamonds(t34);
	Sprite ten_of_hearts(t35);
	Sprite ten_of_spades(t36);

	Sprite ace_of_clubs(t37);
	Sprite ace_of_diamonds(t38);
	Sprite ace_of_hearts(t39);
	Sprite ace_of_spades(t40);

	Sprite jack_of_clubs(t41);
	Sprite jack_of_diamonds(t42);
	Sprite jack_of_hearts(t43);
	Sprite jack_of_spades(t44);

	Sprite king_of_clubs(t45);
	Sprite king_of_diamonds(t46);
	Sprite king_of_hearts(t47);
	Sprite king_of_spades(t48);

	Sprite queen_of_clubs(t49);
	Sprite queen_of_diamonds(t50);
	Sprite queen_of_hearts(t51);
	Sprite queen_of_spades(t52);

	Sprite BG_menu(t53);

	Sprite PBJ(t54);
	PBJ.setPosition(550, 350);
	Sprite PPK(t55);
	PPK.setPosition(550, 500);
	Sprite PSL(t56);
	PSL.setPosition(550, 650);
	Sprite ExitButton(t57);
	ExitButton.setPosition(1400, 820);

	Sprite HitButton(t58);
	HitButton.setPosition(700, 400);
	Sprite StandButton(t59);
	StandButton.setPosition(400, 400);
	Sprite placeButton(t60);
	placeButton.setPosition(800, 400);
	Sprite placeButton2(t71);
	placeButton2.setPosition(800, 400);

	//Chip for PK
	
	Sprite bet50(t69);
	bet50.setPosition(200, 600);
	
	Sprite bet500(t70);
	bet500.setPosition(200, 700);
	

	//Chip for BJ
	Sprite bet10(t61);
	bet10.setPosition(100, 600);
	Sprite bet100(t62);
	bet100.setPosition(100, 700);
	Sprite bet1000(t63);
	bet1000.setPosition(100, 800);

	Sprite back(t64);

	/*
	Sprite HitButton(t60);
	Sprite StandButton(t62);*/
	Sprite CallButton(t66);
	CallButton.setPosition(700, 400);
	Sprite FoldButton(t67);
	FoldButton.setPosition(400, 400);
	Sprite AllinButton(t68);
	AllinButton.setPosition(1000,400);
	//Sprite ExitButton(t65);
	
	//Slot texture/sprite
	Texture spin_but;
	spin_but.loadFromFile("slot_im/spin.png");
	Sprite spin(spin_but);
	spin.scale(0.35f, 0.35f);
	spin.setPosition(25, 30);
	slotmac slot;
	bool checkran = 0;

	Event e;
	int gamestate = 0;;
	window.clear();
	window.draw(BG_menu);
	window.draw(PBJ);
	window.draw(PPK);
	window.draw(PSL);
	window.display();

	while (window.isOpen())
	{

		while (window.pollEvent(e))
		{

			if (e.type == Event::Closed)
			{
				window.close();
			}
			if (e.type == Event::TextEntered)
			{
				bet.input(e, betBarEnable);
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == Mouse::Left)
				{
					if (gamestate == 0)
					{
						if (PBJ.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
						{
							gamestate = 1;
						}
						if (PPK.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
						{
							gamestate = 2;
						}
						if (PSL.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
						{
							gamestate = 3;

						}
					}
					if (gamestate == 1 || gamestate == 2 || gamestate == 3)
					{
						if (ExitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
						{
							gamestate = 0;
							bet.betValue = 0;
							betBarEnable = true;

						}
						if (bet10.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == true)
						{
							bet.addButton(10);
						}
						if (bet50.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == true)
						{
							bet.addButton(50);
						}
						if (bet100.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == true)
						{
							bet.addButton(100);
						}
						if (bet500.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == true)
						{
							bet.addButton(500);
						}
						if (bet1000.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == true)
						{
							bet.addButton(1000);
						}
					}
					if (gamestate == 1)
					{
						if (placeButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && bet.betValue > 0 && bet.betValue <= balance && betPlaced == false)
						{

							betBarEnable = false;
							betPlaced = true;
							balance -= bet.betValue;

						}
						if (HitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == false)
						{
							Hit();
						}
						if (StandButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == false)
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
					}
					if (gamestate == 2)
					{
						if (placeButton2.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && bet.betValue > 0 && bet.betValue <= balance && betPlacedforP == false)
						{

							betBarEnable = false;
							betPlacedforP = true;
							balance -= bet.betValue;

						}
						if (FoldButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && betBarEnable == false)
						{
							
						}
					}
					if (gamestate == 3)
					{
						if (spin.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && bet.betValue > 0)
						{

							if (balance - bet.betValue >= 0) {
								betBarEnable = 0;
								balance -= bet.betValue;
								slot.randslot();
								checkran = 1;
							}
							else bet.betValue = 0;
						}
					}


				}

			}
			window.clear(Color::Green);

			if (gamestate == 0)
			{
				window.clear();
				window.draw(BG_menu);
				//window.draw(Money);
				window.draw(PBJ);
				window.draw(PPK);
				window.draw(PSL);
				window.display();


			}
			if (gamestate == 1)
			{
				window.clear();
				window.draw(placeButton);
				
				if (betPlaced == false)
				{
					window.draw(back);
					window.draw(placeButton);
				}
				else
				{
					window.draw(back);
					window.draw(HitButton);
					window.draw(StandButton);

				}
				window.draw(ExitButton);
				window.draw(bet10);
				window.draw(bet100);
				window.draw(bet1000);
				bet.drawBetBar(window);

				Blackjack();

				string b;
				b = "Balance: " + to_string(balance);
				Text balanceText;
				Font font;
				font.loadFromFile("fonts/Arial.ttf");
				balanceText.setFont(font);
				balanceText.setOutlineColor(Color::Black);
				balanceText.setOutlineThickness(2);
				balanceText.setString(b);
				balanceText.setPosition(30, 300);
				balanceText.setCharacterSize(45);
				window.draw(balanceText);
				int position = 260;
				for (int i = 1; i <= playerNrOfCards; i++)
				{
					if (player[i].value == 1 || player[i].value == 11)
					{
						if (player[i].rank == 1)
						{
							cardd = ace_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = ace_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = ace_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = ace_of_spades;
						}
					}
					if (player[i].value == 2)
					{
						if (player[i].rank == 1)
						{
							cardd = two_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = two_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = two_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = two_of_spades;
						}
					}
					if (player[i].value == 3)
					{
						if (player[i].rank == 1)
						{
							cardd = three_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = three_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = three_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = three_of_spades;
						}
					}
					if (player[i].value == 4)
					{
						if (player[i].rank == 1)
						{
							cardd = four_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = four_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = four_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = four_of_spades;
						}
					}
					if (player[i].value == 5)
					{
						if (player[i].rank == 1)
						{
							cardd = five_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = five_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = five_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = five_of_spades;
						}
					}
					if (player[i].value == 6)
					{
						if (player[i].rank == 1)
						{
							cardd = six_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = six_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = six_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = six_of_spades;
						}
					}
					if (player[i].value == 7)
					{
						if (player[i].rank == 1)
						{
							cardd = seven_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = seven_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = seven_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = seven_of_spades;
						}
					}
					if (player[i].value == 8)
					{
						if (player[i].rank == 1)
						{
							cardd = eight_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = eight_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = eight_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = eight_of_spades;
						}
					}
					if (player[i].value == 9)
					{
						if (player[i].rank == 1)
						{
							cardd = nine_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = nine_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = nine_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = nine_of_spades;
						}
					}
					if (player[i].value == 10)
					{
						if (player[i].rank == 1)
						{
							cardd = ten_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = ten_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = ten_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = ten_of_spades;
						}
					}
					if (player[i].value == 12)
					{
						if (player[i].rank == 1)
						{
							cardd = jack_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = jack_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = jack_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = jack_of_spades;
						}
					}
					if (player[i].value == 13)
					{
						if (player[i].rank == 1)
						{
							cardd = queen_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = queen_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = queen_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = queen_of_spades;
						}
					}
					if (player[i].value == 14)
					{
						if (player[i].rank == 1)
						{
							cardd = king_of_clubs;
						}
						if (player[i].rank == 2)
						{
							cardd = king_of_diamonds;
						}
						if (player[i].rank == 3)
						{
							cardd = king_of_hearts;
						}
						if (player[i].rank == 4)
						{
							cardd = king_of_spades;
						}
					}
					cardd.setPosition(position, 630);
					position += 260;
					window.draw(cardd);
				}
				position = 260;
				for (int i = 1; i <= dealerNrOfCards; i++)
				{
					if (i != 2 || gameFinish == true)
					{
						if (dealer[i].value == 1 || dealer[i].value == 11)
						{
							if (dealer[i].rank == 1)
							{
								cardd = ace_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = ace_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = ace_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = ace_of_spades;
							}
						}
						if (dealer[i].value == 2)
						{
							if (dealer[i].rank == 1)
							{
								cardd = two_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = two_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = two_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = two_of_spades;
							}
						}
						if (dealer[i].value == 3)
						{
							if (dealer[i].rank == 1)
							{
								cardd = three_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = three_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = three_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = three_of_spades;
							}
						}
						if (dealer[i].value == 4)
						{
							if (dealer[i].rank == 1)
							{
								cardd = four_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = four_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = four_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = four_of_spades;
							}
						}
						if (dealer[i].value == 5)
						{
							if (dealer[i].rank == 1)
							{
								cardd = five_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = five_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = five_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = five_of_spades;
							}
						}
						if (dealer[i].value == 6)
						{
							if (dealer[i].rank == 1)
							{
								cardd = six_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = six_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = six_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = six_of_spades;
							}
						}
						if (dealer[i].value == 7)
						{
							if (dealer[i].rank == 1)
							{
								cardd = seven_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = seven_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = seven_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = seven_of_spades;
							}
						}
						if (dealer[i].value == 8)
						{
							if (dealer[i].rank == 1)
							{
								cardd = eight_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = eight_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = eight_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = eight_of_spades;
							}
						}
						if (dealer[i].value == 9)
						{
							if (dealer[i].rank == 1)
							{
								cardd = nine_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = nine_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = nine_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = nine_of_spades;
							}
						}
						if (dealer[i].value == 10)
						{
							if (dealer[i].rank == 1)
							{
								cardd = ten_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = ten_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = ten_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = ten_of_spades;
							}
						}
						if (dealer[i].value == 12)
						{
							if (dealer[i].rank == 1)
							{
								cardd = jack_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = jack_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = jack_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = jack_of_spades;
							}
						}
						if (dealer[i].value == 13)
						{
							if (dealer[i].rank == 1)
							{
								cardd = queen_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = queen_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = queen_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = queen_of_spades;
							}
						}
						if (dealer[i].value == 14)
						{
							if (dealer[i].rank == 1)
							{
								cardd = king_of_clubs;
							}
							if (dealer[i].rank == 2)
							{
								cardd = king_of_diamonds;
							}
							if (dealer[i].rank == 3)
							{
								cardd = king_of_hearts;
							}
							if (dealer[i].rank == 4)
							{
								cardd = king_of_spades;
							}
						}
					}
					cardd.setPosition(position, 30);
					position += 260;
					window.draw(cardd);
				}
				bet.drawBetBar(window);
				window.display();

				Gamefinish();
			}


			if (gamestate == 2)
			{
				window.clear(Color::Green);
				if (betPlacedforP == false)
				{
					window.draw(placeButton2);
				}
				else
				{
					window.draw(CallButton);
					window.draw(FoldButton);
					window.draw(AllinButton);
				}

				string bforP;
				bforP = "Balance: " + to_string(balance);
				Text balanceText;
				Font font;
				font.loadFromFile("fonts/Arial.ttf");
				balanceText.setFont(font);
				balanceText.setOutlineColor(Color::Black);
				balanceText.setOutlineThickness(2);
				balanceText.setString(bforP);
				balanceText.setPosition(30, 300);
				balanceText.setCharacterSize(45);
				window.draw(balanceText);

				bet.drawBetBar(window);

				//window.draw(PK_BJ);
				window.draw(bet10);
				window.draw(bet50);
				window.draw(bet100);
				window.draw(bet500);
				window.draw(bet1000);
				//window.draw(BetButton);
				window.draw(ExitButton);
				window.display();


				

			}
			if (gamestate == 3)
			{
				window.clear(Color::Cyan);
				window.draw(ExitButton);
				window.draw(spin);
				window.draw(bet10);
				window.draw(bet50);
				window.draw(bet100);
				window.draw(bet500);
				window.draw(bet1000);

				string bforS;

				Text balanceText;
				Font font;
				bforS = "Balance: " + to_string(balance);
				font.loadFromFile("fonts/Arial.ttf");
				balanceText.setFont(font);
				balanceText.setOutlineColor(Color::Black);
				balanceText.setOutlineThickness(2);
				balanceText.setString(bforS);
				balanceText.setPosition(30, 300);
				balanceText.setCharacterSize(45);

				window.draw(balanceText);
				bet.drawBetBar(window);
				window.display();

				if (checkran) {
					window.clear(Color::Cyan);
					window.draw(ExitButton);
					window.draw(spin);
					window.draw(bet10);
					window.draw(bet50);
					window.draw(bet100);
					window.draw(bet500);
					window.draw(bet1000);
					bforS = "Balance: " + to_string(balance);
					balanceText.setString(bforS);
					window.draw(balanceText);
					bet.drawBetBar(window);

					checkran = 0;
					showslot(window, slot);

					window.display();
					slot.checkwin();
					balance += bet.betValue * slot.C_multi;
					//cout << balance;
					//cout << slot.C_multi;
					sleep(seconds(2));

					window.clear(Color::Cyan);
					window.draw(ExitButton);
					window.draw(spin);
					window.draw(bet10);
					window.draw(bet50);
					window.draw(bet100);
					window.draw(bet500);
					window.draw(bet1000);
					bforS = "Balance: " + to_string(balance);
					balanceText.setString(bforS);
					window.draw(balanceText);
					bet.drawBetBar(window);
					slot.C_multi = 0;
					bet.betValue = 0;
					betBarEnable = 1;

				}
			}


		}

	}

	return 0;
}