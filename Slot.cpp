#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/* 
-Slot size 3*5 
-rand symbols
-check win cond
-P_input
*/


//S==Slot
string S_machine[3][5];
string S_symbol[]={"\3","\4","10","\6","A","J","Q","K"};
int P_chips = 500;


void randSlot(int N){
    for (int k = 0; k < N; k++)
    {
        cout << endl << "Round :" << k+1 << endl;
        for(int i=0;i<3;i++){
            for(int j=0;j<5;j++){
                S_machine[i][j] = S_symbol[(rand()%8)];
                cout << S_machine[i][j] << " ";
            }
        cout << endl;
        }
        cout << "______________________" << endl;
    }
}

void P_input(){ //P == Player
    int round;
    cout <<"Current chips = " << P_chips << endl;
    cout << "Input amount of round to spins: ";
    
    cin >> round; 
    randSlot(round);
}

int main(){
    srand(time(0));

    P_input();

    return 0;
}