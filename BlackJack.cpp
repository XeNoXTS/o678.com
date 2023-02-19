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
int Dealerscore = 0;

int PlayerChip = 500;
int DealerChip = 500;
int all_bet = 0;

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
        int countace = 0;
        for(int i = 0; i < N ; i++){
            char ace = 'A';
            if(Card[i][1] == ace) countace++;  
        }
        if(countace > 1) score -= 10*(countace - 1);
        else if(countace == 1){
            if(score > 21) score -= 10;
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

void Bet(int& chip,int& bchip, int& all_bet) {
    int bet;
    while (true) {
        cout << "Bet: ";
        cin >> bet;
        if (chip - bet >= 0) {
            chip -= bet; bchip -= bet;
            all_bet += 2 * bet;
            break;
        }
        else {
            cout << "Not enough chips." << endl;
        }
    }
}

void HitAce(string newCard,int& score,vector<string>&Card){
    if(newCard == Cardsuit[0] + Cardface[0] ||newCard == Cardsuit[1] + Cardface[0] || newCard == Cardsuit[2] + Cardface[0] || newCard == Cardsuit[3] + Cardface[0]){
                    if(score > 10) score++;
                    else if(score <= 10) score += 11;
                    Card.push_back(newCard);
                }else {
                    Card.push_back(newCard);
                    score = CheckScore(Card);
                    CheckAce(Card,Card.size(),score);
                }
}

void PlayerAction(){
    cout << "\n---------------------------------\n";
    cout << "PlayerChip: " << PlayerChip << endl;
    //draw two cards
    vector<string>playerCard;
    playerCard.push_back(drawcard(deck)); 
    playerCard.push_back(drawcard(deck));

    //Player Bet
    Bet(PlayerChip,DealerChip,all_bet);

    //show playercards
    cout << "You get "; ShowCard(playerCard);

    //Calulate Score
    playerscore = CheckScore(playerCard);

     // In case AA
    CheckAce(playerCard,playerCard.size(),playerscore);

    //show playerscore
    cout << "Your score = " << playerscore << endl;

    //case playerscore (only two card) = 21
    if(playerscore == 21) cout << "BlackJack!!!" << endl;

    //hit || stand
    string playerhit_stand;

    if(playerscore < 21){ cin.ignore();
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
                HitAce(newCard,playerscore,playerCard);
                //show new cards 
                ShowCard(playerCard);
                //show new score
                if(playerscore <= 21) cout << "Your new score = " << playerscore << endl;
                // when hit แล้ว playerscores > 21 
                else if(playerscore > 21)
                {
                    cout << "Your new score = " << playerscore << endl; 
                    cout << "Player bust" << endl;
                }
            }else if(playerhit_stand == "stand"){ // stand ไม่จั่วต่อ
                break;
            }
        }while(playerscore < 21);
    }
    cout << "---------------------------------\n";
}

void DealerAction(){
    bool Dealerhit_stand = 1;
    cout << "\n---------------------------------\n";
    cout << "DealerChip: " << DealerChip << endl;
    //draw two cards
    vector<string>DealerCard;
    DealerCard.push_back(drawcard(deck)); 
    DealerCard.push_back(drawcard(deck));

    //show Dealercards
    ShowCard(DealerCard);
    //cout << "Dealer get " << DealerCard[0] << " " << "[]" << endl;

    //Calulate Score
    Dealerscore = CheckScore(DealerCard);

     // In case AA
    CheckAce(DealerCard,DealerCard.size(),Dealerscore);

    //Dealerhit_stand
    int Perhit = rand()%100;
    if(Dealerscore <= 17){    
        if(Perhit >= 30) Dealerhit_stand = 1;
        else Dealerhit_stand = 0;
    }else if(Dealerscore == 20) Dealerhit_stand = 0;
    else if(Dealerscore > 17){
        if(Perhit >= 90) Dealerhit_stand = 1;
        else Dealerhit_stand = 0;
    } 

    //hit || stand for Dealer
    if(Dealerhit_stand == 1){
        do {cout << "Dealer hit " << endl;
        string newCard = drawcard(deck);
        //in case get ace
        HitAce(newCard,Dealerscore,DealerCard);

        cout << "hit " << DealerCard[2] << endl;
        cout << "Dealer score = " << Dealerscore << endl;
        }while(Dealerscore < 21);
    }else if(Dealerhit_stand == 0){ 
        cout << "Dealer stand" << endl;
        cout << "Dealer score = " << Dealerscore << endl;
    }
        cout << "\n---------------------------------\n";
}
    

void checkWinner(int pscore, int Dscore){
	cout << "\n---------------------------------\n";
        if(pscore < 21 && Dscore < 21){
            int difPlayer = 21 - pscore; int difDealer = 21 - Dscore;
            if(difDealer > difPlayer) {cout << "Player Win"; PlayerChip += all_bet;} 
            else if(difDealer < difPlayer) {cout << "Dealer Win"; DealerChip += all_bet;}
        }
        else if(pscore <= 21 && Dscore > 21) {cout << "Player win"; PlayerChip += all_bet;}
        else if(pscore > 21 && Dscore <= 21) {cout << "Dealer win"; DealerChip += all_bet;}
        else if((pscore > 21 && Dscore > 21) || (pscore == Dscore)) {cout << "Draw"; PlayerChip += all_bet/2; DealerChip += all_bet/2;}

        cout << "\n" << "PlayerChip left " << PlayerChip << endl << "DealerChip left " << DealerChip; 

    cout << "\n---------------------------------\n";
}


int main(){
    srand(time(0));
    BuildDeck(deck,Cardsuit,Cardface);
    shuffledeck(deck);
    PlayerAction();
    DealerAction();
    checkWinner(playerscore,Dealerscore);
    }
