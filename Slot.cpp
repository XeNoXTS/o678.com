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
-help --- > show playline
*/


//S==Slot
//P == Player
string S_machine[3][5];
string S_symbol[]={"\3","\4","10","\6","A","J","Q","K"};

int P_chips = 500;

void checkwin(){

}

void Show_PL(){//PL = playline

} 

string makeUpper(string x){
    string y=x;
    for(unsigned int i=0;i<y.size();i++){
        y[i] = toupper(x[i]);
    }
    return y;
}
void randslot(int N);
void P_input();

int main(){
    srand(time(0));

    P_input();

    return 0;
}

void P_input(){ 
    int round;
    string command;
    cout <<"Current chips = " << P_chips << endl;
    while(P_chips>=0){
        cout << "Input command (S = 1_spin,MS = multiple spin,P = playline,H = help,E=Exit): ";
        cin >> command;
         command = makeUpper(command);
         if(command == "E") break;
         else if(command == "MS"){
             cout << "Input rounds to spin: ";
            cin >> round; 
             randslot(round);
        }else if(command == "S"){
             round =1;
             randslot(round);
        }else if(command == "H"){
          Show_PL();
        }else{
            cout << "Invalid Command";
        }
    }
}

void randslot(int N){
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
        checkwin();
    }
}