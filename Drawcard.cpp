#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;
/*
string Drawcards(){
    char suit[] = {'S', 'H', 'D', 'C'};
    string rank[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    int nS = sizeof(suit)/sizeof(suit[0]);
    int nR = sizeof(rank)/sizeof(rank[0]);

    string card;

    card = rank[rand()%nR] + ' ' + suit[rand()%nS];
    return card;
}
*/
int main(){
    srand(time(0));
    char suit[] = {'S', 'H', 'D', 'C'};
    string rank[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    int nS = sizeof(suit)/sizeof(suit[0]);
    int nR = sizeof(rank)/sizeof(rank[0]);

    string card;

    card = rank[rand()%nR] + ' ' + suit[rand()%nS];

    cout << '[' << card << ']';
}