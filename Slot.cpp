#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/* 
-Slot size 3*5 
-rand symbols
-check win cond
*/



int machine[3][5];
int P_chips = 500;

string P_input(){ //P == Player

    cout << "Current chips = " << P_chips << endl;
    cout << "";
    cin >> input; 

}

void randSlot(){
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            machine[i][j] = rand()%6;
            cout << machine[i][j] << " ";
        }
        cout << endl;
    }

}


int main(){
    srand(time(0));

    P_input();

    return 0;
}