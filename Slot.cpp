#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

enum {
    Nrow=3,Ncol=5
};
#define S_row for(int row=0;row<Nrow;row++) 
#define S_col for(int col=0;col<Ncol;col++) 
#define Run_sym for(int sym=0;sym<8;sym++) //ไล่ sym ที่มี ใช่ในcheckwin
//S==Slot
//P == Player
string S_machine[Nrow][Ncol],key;
string S_symbol[]={"\6","\3","\4","A","K","Q","J","10"}; // \3=heart \4=diamond \6=spade

double P_chips = 500,Cost=10,C_multi=-99999; //multi=ตัวคูณ Cost=ราคา/1spin

double checkwin();
void Show_PL(); //PL = playline
void randslot(int N);
void P_input(string &);
void mutiplier(int);
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
    cout << "S  = 1_spin \nMS = multiple spin \nC  = set amount of chips per 1 spin(Base = 10) \nE  = Exit \nH  = help \n: ";
    cin >> command;
}

void randslot(int N){
    for (int k = 0; k < N; k++)//random N times
    {
        P_chips-=Cost;
        cout << endl << "Round :" << k+1 << endl ;
        S_row{
            cout <<"|";
            S_col{
                S_machine[row][col] = S_symbol[(rand()%8)];
                cout << setw(3) << S_machine[row][col] << " ";
            }
        cout <<" |" << endl;
        }
        cout << setw(23)<< "-----------------------" << endl;
        P_chips += checkwin();
    }
}


void Show_PL(){

}

double checkwin(){
    double cal=0; 
    int count=0;
    //check same 3-5 in a row case
    Run_sym{
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    count++;//find amount of same symbol in row
                }
            }
            //หาตัวคูณต่อ
        count=0; //new row set 0
        //cout << key << "count = "<< count <<"::";
        }
    }

    //check V case
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(row==col || row+col==4){
                    if (key==S_machine[row][col]){
                        count++;
                    }    
                }
            }
       
        }
        //หาตัวคูณต่อ            
        //cout << key << "count = "<< count <<"::";
    }
    //check ^ case
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(row+col==Ncol/2 || row+2==col){
                    if (key==S_machine[row][col]){
                        count++;
                    }    
                }
            }
       
        }
        //cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }

    //check m case0=ครึ่งบน case1=ครึ่งล่าง
    for(int cases=0;cases<2;cases++){
        Run_sym{
            count=0;
            key=S_symbol[sym];
                S_row{
                    S_col{
                        if(row+col==1+cases || row+col==1+(Ncol/2)+cases || row+col==Ncol+cases){
                            if (cases==0 &&row!=Nrow-1 && key==S_machine[row][col]){
                                count++;                            
                            }else if( row!=0 && key==S_machine[row][col]){
                                if(cases ==1)count++;
                            }
                        }
                    }
       
                }
            //หาตัวคูณต่อ
           // cout << key << "count = "<< count <<"::";
            count=0;
        }
    }

    //check M เว้นกลาง
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    if (row==Nrow-1 && (row+col)%2==0){
                        count++;
                    }else if(row==0 && (row+col)%2==1){
                        count++;
                    }    
                }
            }
       
        }
       // cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }

    //check w บนล่าง
    for(int cases=0;cases<2;cases++){ //0=w บน, 1=wล่าง
        Run_sym{
            count=0;
            key=S_symbol[sym];
                S_row{
                    S_col{
                        if(key==S_machine[row][col]){
                            if (cases==0&& row !=Nrow-1 && (row+col)%2==0 ){
                                count++;
                            }else if(row!=0 && (row+col)%2==1){
                                if(cases==1)count++;
                            }     
                        }
                    }
                }
            //หาตัวคูณต่อ
          //  cout << key << "count = "<< count <<"::";
        }
    }

    //check W เว้นแถวกลาง
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    if (row==Nrow-1 && (row+col)%2==1){
                        count++;
                    }else if(row==0 && (row+col)%2==0){
                        count++;
                    }    
                }
            }
       
        }
       //cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }
    //check /.\ .
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    if ((row==Nrow-1 && col==Ncol/2)/*ตัวกลางล่าง*/|| ((row+col)%2==1 && row!=Nrow-1 && col!=Ncol/2)){
                        count++;
                    }
                }
            }
       
        }
      // cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }

    //check case \*/
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    if ((row == 0 && col==Ncol/2)/*ตัวกลางบน*/|| ((row+col)%2==1 && row!=0 && col!=Ncol/2)){
                        count++;
                    }
                }
            }
       
        }
     //  cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }

    //check case *...*
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    if ((row==0 && (col==0||col==Ncol-1)) || (row==Nrow-1 && (col!=0 &&col!=Ncol-1))){
                        count++;
                    }
                }
            }
       
        }
      // cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }

    //check case .***.
    Run_sym{
        count=0;
        key=S_symbol[sym];
        S_row{
            S_col{
                if(key==S_machine[row][col]){
                    if ((row==Nrow-1 && (col==0||col==Ncol-1)) || (row==0 && (col!=0 &&col!=Ncol-1))){
                        count++;
                    }
                }
            }
       
        }
      // cout << key << "count = "<< count <<"::";
        //หาตัวคูณต่อ
    }
    return cal;
}