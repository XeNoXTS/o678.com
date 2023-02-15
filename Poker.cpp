#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

char suit[] = {'\3', '\4', '\5', '\6'};
string rank[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

vector<string> BuildDeck(){
    vector<string> Deck;
    string temp;
    for(int i = 0; i < 52;i++){
        temp = ::rank[rand()%13]+::suit[rand()%4];
        for()
    }
}

int main(){
    srand(time(0));
}