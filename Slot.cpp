#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>


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

void Costset(){
    int current;
    cout << "Chips per round(min 1,max 1000) :";
    cin >> current;
    if(current>1000 || current<1){
        cout << "You can't do that Bro! Try again.\n";
    }else if(current >P_chips){
        printf("You have %d chips.Try again.\n",P_chips);
    }else{
        Cost = current;
    }
}

int main(){
    srand(time(0));
    string command;
    int round;
    do{
        P_input(command);
        command = makeUpper(command);
    //check command
        if(command == "E" || command =="EXIT") 
            break;
        else if(command == "MS"){
            cout << "Input rounds to spin: ";
            cin >> round; 
            //check current chips;
            if(P_chips-(Cost*round)>=0){
                randslot(round);
            }else{
                cout <<"-----------------------\n"<< "You don't have enough chips.Try again.\n"<<"-----------------------\n";
            }
        }else if(command == "S"){
            randslot(1);
        }else if(command == "H" || command == "HELP"){
            Show_PL();
        }else if(command == "C"){
            Costset();
        }else{
            cout <<"-----------------------\n"<< "Invalid Command\n"<<"-----------------------\n";
        }

    }while(1);

    return 0;
}
void P_input(string &command){ 
    cout <<"\n-----------------------\n"<<"Current chips = " << P_chips << endl;
    cout << "Input command \n"<<"-----------------------\n";
    cout << "S  = 1_spin \nMS = multiple spin \nC  = set amount of chips per 1 spin \nE  = Exit \nH  = help \n: ";
    cin >> command;
}

void randslot(int N){
    for (int k = 0; k < N; k++)
    {
        cout << endl << "Round :" << k+1 << endl ;
        for(int i=0;i<3;i++){
            cout <<"|";
            for(int j=0;j<5;j++){
                S_machine[i][j] = S_symbol[(rand()%8)];
                cout << setw(3) << S_machine[i][j] << " ";
            }
        cout <<" |" << endl;
        }
        cout << setw(23)<< "_______________________" << endl;
        checkwin();
    }
}