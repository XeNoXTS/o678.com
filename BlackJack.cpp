#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

string Cardsuit[4] = {"\3","\4","\5","\6"};
string Cardface[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
string deck[4][13];
int playerscore = 0;
int botonescore = 0;

void BuildDeck(string deck[][13], string Cardsuit[],string Cardface[]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            deck[i][j] = Cardsuit[i] + Cardface[j];
        }
    }
}

string drawcard(string deck[][13]){
    int row, col;
    string card;
    do{
    row = rand()%4;
    col =  rand()%13;
    }while(deck[row][col] == "0");
    card = deck[row][col];
    deck[row][col] = "0";
    return card;
}

void shuffledeck(string deck[][13]){
	
	for(int i = 0 ; i < 100; i++){
		int p1 = rand()%4;int p3 = rand()%4;
		int p2 = rand()%13;int p4 = rand()%13;
		string temp = deck[p1][p2];
		deck[p1][p2] = deck[p3][p4];
		deck[p3][p4] = temp;
	}
	
}

void CheckAce(vector<string> Card,int N,int &score){
    if(score > 21){
                for(int i = 0; i < N; i++){
                    if(Card[i] == Cardsuit[0] + Cardface[0]){score -= 10;break;} // ACE value = 1 point
                    else if(Card[i] == Cardsuit[1] + Cardface[0]) {score -= 10;break;}
                    else if(Card[i] == Cardsuit[2] + Cardface[0]) {score -= 10;break;}
                    else if(Card[i] == Cardsuit[3] + Cardface[0]) {score -= 10;break;}
                }
            }
}

void Check2_10(vector<string> Card,int &score, int n){
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= 9; j++){
            if(Card[i] == Cardsuit[0] + Cardface[j]) score += j+1;
            else if(Card[i] == Cardsuit[1] + Cardface[j]) score += j+1;
            else if(Card[i] == Cardsuit[2] + Cardface[j]) score += j+1;
            else if(Card[i] == Cardsuit[3] + Cardface[j]) score += j+1;
            }
    }
}

void CheckJQK(vector<string> Card,int &score, int n){
    char k = 'K', q = 'Q', j = 'J';
    for(int i = 0; i < n; i++){
        if(Card[i][1] == k || Card[i][1] == q || Card[i][1] == j){
            score += 10;
        }
    }
}


int CheckScore(vector<string> Cards){
    int score = 0;
    Check2_10(Cards, score, Cards.size());
    CheckJQK(Cards, score, Cards.size());
    //Check Ace
     for(int i = 0; i < Cards.size(); i++)
     {
        if(Cards[i] == Cardsuit[0] + Cardface[0]) score += 11; 
        else if(Cards[i] == Cardsuit[1] + Cardface[0]) score += 11;
        else if(Cards[i] == Cardsuit[2] + Cardface[0]) score += 11;
        else if(Cards[i] == Cardsuit[3] + Cardface[0]) score += 11;
     }
    return score;
}

void ShowCard(vector<string> Cards){
    for(unsigned int i = 0; i < Cards.size(); i++) cout << Cards[i] << " ";
    cout << endl;
}

void PlayerAction(){
    
    //draw two cards
    vector<string>playerCard;
    playerCard.push_back(deck[1][11]); 
    playerCard.push_back(deck[3][10]);

    //show playercards
    cout << "You get ";
    ShowCard(playerCard);

    //Calulate Score
    int playerscore = CheckScore(playerCard);

     // In case AA
    CheckAce(playerCard,playerCard.size(),playerscore);

    //show playerscore
    cout << "Your score = " << playerscore << endl;

    //case playerscore (only two card) = 21
    if(playerscore == 21) cout << "BlackJack";

    //hit || stand
    string playerhit_stand;

    if(playerscore < 21){
        do{
            do{
                cout << "hit or stand" << endl;
                getline(cin,playerhit_stand);

            }while(playerhit_stand != "hit" && playerhit_stand != "stand");

            //hit
            if(playerhit_stand == "hit"){
                //draw 
                string newCard = drawcard(deck);
                
                //in case get ace
                if(newCard == Cardsuit[0] + Cardface[0] ||newCard == Cardsuit[1] + Cardface[0] || newCard == Cardsuit[2] + Cardface[0] || newCard == Cardsuit[3] + Cardface[0]){
                    if(playerscore > 10) playerscore++;
                    else if(playerscore <= 10) playerscore += 11;
                    playerCard.push_back(newCard);
                }else {
                    playerCard.push_back(newCard);
                    playerscore = CheckScore(playerCard);
                    CheckAce(playerCard,playerCard.size(),playerscore);
                }

                //show new cards 
                ShowCard(playerCard);

                //show new score
                if(playerscore <= 21) cout << "Your new score = " << playerscore << endl;

                // when hit แล้ว playerscores > 21 
                else if(playerscore > 21)
                {
                    cout << "Your new score = " << playerscore << endl; 
                    cout << "bust" << endl;
                }

            }else if(playerhit_stand == "stand"){ // stand ไม่จั่วต่อ
                break;
            }
        }while(playerscore < 21);
    }
}
void botoneAction(){
    for (int i = 0; i < 21; i++)
    {
       //draw two cards
    vector<string>botoneCard;
    botoneCard.push_back(drawcard(deck)); 
    botoneCard.push_back(drawcard(deck));

    //show botonecards
    cout << "botone got ";
    for(unsigned int i = 0; i < botoneCard.size(); i++) cout << botoneCard[i] << " ";
    cout << endl;

    //Calulate Score
    int botonescore = CheckScore(botoneCard);

     // In case AA
            if(botonescore > 21){
                for(int i = 0; i < botoneCard.size(); i++){
                    if(botoneCard[i] == Cardsuit[0] + Cardface[0]){playerscore -= 10;break;} // ACE value = 1 point
                    else if(botoneCard[i] == Cardsuit[1] + Cardface[0]) {playerscore -= 10;break;}
                    else if(botoneCard[i] == Cardsuit[2] + Cardface[0]) {playerscore -= 10;break;}
                    else if(botoneCard[i] == Cardsuit[3] + Cardface[0]) {playerscore -= 10;break;}
                }
            }

    //show botonescore
    cout << "botone score = " << botonescore << endl;

    //case botonescore (only two card) = 21
    if(botonescore == 21) cout << "BlackJack You so noob pair bot";

    //hit || stand for botone
    if (botonescore < 15)
    {
        cout << "hit";
        string newCard = drawcard(deck);
        //in case get ace
                if(newCard == Cardsuit[0] + Cardface[0] ||newCard == Cardsuit[1] + Cardface[0] || newCard == Cardsuit[2] + Cardface[0] || newCard == Cardsuit[3] + Cardface[0]){
                    if(botonescore > 10) botonescore++;
                    else if(botonescore <= 10) botonescore += 11;
                    botoneCard.push_back(newCard);
                }else {
                    botoneCard.push_back(newCard);
                    botonescore = CheckScore(botoneCard);

                    if(botonescore > 21){
                        for(int i = 0; i < botoneCard.size(); i++){
                            if(botoneCard[i] == Cardsuit[0] + Cardface[0]){botonescore -= 10;break;} // ACE value = 1 point
                            else if(botoneCard[i] == Cardsuit[1] + Cardface[0]) {botonescore -= 10;break;}
                            else if(botoneCard[i] == Cardsuit[2] + Cardface[0]) {botonescore -= 10;break;}
                            else if(botoneCard[i] == Cardsuit[3] + Cardface[0]) {botonescore -= 10;break;}
                        }
                    }
                }
                //show new botonecards 
                for(unsigned int i = 0; i < botoneCard.size(); i++) cout << botoneCard[i] << " ";

                //show new botonescore
                if(botonescore <= 21) cout << "\n bot one score = " << botonescore << endl;

                // lock hit give he botonescores > 21 
                else if(botonescore > 21){
                    cout << "\n bot one score = " << botonescore << endl; 
                    cout << "gg";
                    }

            }else if(botonescore >= 15 ){ // stand botone
                cout << "stand";
                break;
            }
        }
    }

void checkWinner(int playerscore, int botonescore){
	cout << "\n---------------------------------\n";
	//(begingameline) simplecheck
    for (int i = 0; i < 21; i++)
    {   int psum,bsum;
            psum = 21 - playerscore;
            bsum = 21 - botonescore;
        if (playerscore <= 21 && botonescore <= 21)
        {
            if (psum < bsum)
            {
                cout << "player win!!! yahu";
            }else if (playerscore > 21 && botonescore <=21)
            {
                cout << "player defeat!!! noob";
            }else if(botonescore > 21 && playerscore <=21)
            {
                cout << "player win!!! yahu";
            }else if (botonescore == playerscore)
            {
                cout << "Draw!!!";
            }
    }
    // endgameline simeplecheck
    cout << "\n---------------------------------\n";
}
}
int sum = rand()%4+1;
switch (sum)
{
case 1:
    botoneAction();
    break;
case 2:
    bottwoAction();
    break;
case 3:
    botthreeAction();
    break;
case 4:
    botfourAction();
    break;

default:
    break;
}
int main(){
    
    srand(time(0));
    BuildDeck(deck,Cardsuit,Cardface);
    shuffledeck(deck);

    
    PlayerAction();
}