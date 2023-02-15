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

void BuileDeck(string deck[][13], string Cardsuit[],string Cardface[]){
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

void CheckScore(vector<string> Cards){
    int n = Cards.size();
    
    for(int i = 0; i < n ; i++){
        for(int j = 2; j <= 10; j++){
        if(Cards[i] == Cardsuit[0] + Cardface[j]) playerscore += j;
        else if(Cards[i] == Cardsuit[1] + Cardface[j]) playerscore += j;
        else if(Cards[i] == Cardsuit[2] + Cardface[j]) playerscore += j;
        else if(Cards[i] == Cardsuit[3] + Cardface[j]) playerscore += j;
        }
    }
    
}

int main(){
    
    srand(time(0));
    BuileDeck(deck,Cardsuit,Cardface);
    shuffledeck(deck);
    /*for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            cout << deck[i][j] << " ";
        }
        cout << endl;
    }
    cout << drawcard(deck) << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            cout << deck[i][j] << " ";
        }
        cout << endl;
    }*/

    vector<string>playerCard;
    playerCard[0] = drawcard(deck); playerCard[1] = drawcard(deck);

}