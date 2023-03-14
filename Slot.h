#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include <random>

using namespace sf;
using namespace std;

enum {
    Nrow = 3, Ncol = 5
};

#define S_row for(int row=0;row<Nrow;row++) 
#define S_col for(int col=0;col<Ncol;col++)
#define Run_sym for(int symbol=0;symbol<8;symbol++)

class slotmac {

    int key;

public:
    double C_multi = 0;
    int sym[Nrow][Ncol];
    void randslot() {
        S_row{
            S_col{
                sym[row][col] = (rand() % 8) + 1; //1=10 2=j 3=q 4=k 5=a 6=bruh 7=cat 8=dog
            }
        }

    }

    void checkwin() {
        int count = 0;
        //check same 3-5 in a row case
        Run_sym{
            key = symbol + 1;
            S_row{
                S_col{
                    if (key == sym[row][col]) {
                        count++;//find amount of same symbol in row
                    }
                }
                //หาตัวคูณต่อ
                if (count > 2) mutiplier(count);
            count = 0; //new row set 0
            //cout << key << "count = "<< count <<"::";
            }
        }
            //check V case
                Run_sym{
                            count = 0;
                            key = symbol + 1;
                            S_row{
                                S_col{
                                    if (row == col || row + col == 4) {
                                        if (key == sym[row][col]) {
                                            count++;
                                        }
                                    }
                                }

                            }
                                //หาตัวคูณต่อ  
                                if (count > 2) mutiplier(count);
                                //cout << key << "count = "<< count <<"::";
            }
                //check ^ case
                Run_sym{
                            count = 0;
                            key = symbol + 1;
                            S_row{
                                S_col{
                                    if (row + col == Ncol / 2 || row + 2 == col) {
                                        if (key == sym[row][col]) {
                                            count++;
                                        }
                                    }
                                }

                            }
                                //cout << key << "count = "<< count <<"::";
                                //หาตัวคูณต่อ
                                if (count > 2) mutiplier(count);
            }
                //check m case0=ครึ่งบน case1=ครึ่งล่าง
            for (int cases = 0; cases < 2; cases++) {
                Run_sym{
                    count = 0;
                    key = symbol + 1;
                        S_row{
                            S_col{
                                if (row + col == 1 + cases || row + col == 1 + (Ncol / 2) + cases || row + col == Ncol + cases) {
                                    if (cases == 0 && row != Nrow - 1 && key == sym[row][col]) {
                                        count++;
                                    }
        else if (row != 0 && key == sym[row][col]) {
           if (cases == 1)count++;
       }
   }
}

}
//หาตัวคูณต่อ
if (count > 2) mutiplier(count);
// cout << key << "count = "<< count <<"::";
 count = 0;
                }
            }
            //check M เว้นกลาง
            Run_sym{
                    count = 0;
                    key = symbol + 1;
                    S_row{
                        S_col{
                            if (key == sym[row][col]) {
                                if (row == Nrow - 1 && (row + col) % 2 == 0) {
                                    count++;
                                }
            else if (row == 0 && (row + col) % 2 == 1) {
               count++;
           }
       }
    }

    }
                        // cout << key << "count = "<< count <<"::";
                         //หาตัวคูณต่อ
                         if (count > 2) mutiplier(count);
            }
                //check w บนล่าง
            for (int cases = 0; cases < 2; cases++) { //0=w บน, 1=wล่าง
                Run_sym{
                    count = 0;
                    key = symbol + 1;
                        S_row{
                            S_col{
                                if (key == sym[row][col]) {
                                    if (cases == 0 && row != Nrow - 1 && (row + col) % 2 == 0) {
                                        count++;
                                    }
        else if (row != 0 && (row + col) % 2 == 1) {
           if (cases == 1)count++;
       }
   }
}
}
//หาตัวคูณต่อ
if (count > 2) mutiplier(count);
//  cout << key << "count = "<< count <<"::";
                }
            }
            //check W เว้นแถวกลาง
            Run_sym{
                    count = 0;
                    key = symbol + 1;
                    S_row{
                        S_col{
                            if (key == sym[row][col]) {
                                if (row == Nrow - 1 && (row + col) % 2 == 1) {
                                    count++;
                                }
            else if (row == 0 && (row + col) % 2 == 0) {
               count++;
           }
       }
    }

    }
                        //cout << key << "count = "<< count <<"::";
                         //หาตัวคูณต่อ
                         if (count > 2) mutiplier(count);
            }
                //check /.\ .
                Run_sym{
                            count = 0;
                            key = symbol + 1;
                            S_row{
                                S_col{
                                    if (key == sym[row][col]) {
                                        if ((row == Nrow - 1 && col == Ncol / 2)/*ตัวกลางล่าง*/ || ((row + col) % 2 == 1 && row != Nrow - 1 && col != Ncol / 2)) {
                                            count++;
                                        }
                                    }
                                }

                            }
                                // cout << key << "count = "<< count <<"::";
                                  //หาตัวคูณต่อ
                                  if (count > 2) mutiplier(count);
            }
                //check case \*/
                Run_sym{
                            count = 0;
                            key = symbol + 1;
                            S_row{
                                S_col{
                                    if (key == sym[row][col]) {
                                        if ((row == 0 && col == Ncol / 2)/*ตัวกลางบน*/ || ((row + col) % 2 == 1 && row != 0 && col != Ncol / 2)) {
                                            count++;
                                        }
                                    }
                                }

                            }
                                //  cout << key << "count = "<< count <<"::";
                                   //หาตัวคูณต่อ
                                   if (count > 2) mutiplier(count);
            }
                //check case *...*
                Run_sym{
                            count = 0;
                            key = symbol + 1;
                            S_row{
                                S_col{
                                    if (key == sym[row][col]) {
                                        if ((row == 0 && (col == 0 || col == Ncol - 1)) || (row == Nrow - 1 && (col != 0 && col != Ncol - 1))) {
                                            count++;
                                        }
                                    }
                                }

                            }
                                // cout << key << "count = "<< count <<"::";
                                  //หาตัวคูณต่อ
                                  if (count > 2) mutiplier(count);
            }
                //check case .***.
                Run_sym{
                            count = 0;
                            key = symbol + 1;
                            S_row{
                                S_col{
                                    if (key == sym[row][col]) {
                                        if ((row == Nrow - 1 && (col == 0 || col == Ncol - 1)) || (row == 0 && (col != 0 && col != Ncol - 1))) {
                                            count++;
                                        }
                                    }
                                }

                            }
                                // cout << key << "count = "<< count <<"::";
                                  //หาตัวคูณต่อ
                                  if (count > 2) mutiplier(count);
            }

                //      double cal = Cost * C_multi;
                      // printf("C_multi: %.2f Cost: %d ",C_multi,Cost);
            cout << "You got *" << C_multi << endl;
            //   if (cal)cout << "Win: " << cal << " chips.";
         //      else cout << "Loss";
               //return cal;
    }

    void  mutiplier(int N) {//หาค่าตัวคูณหลังจากเช็คว่าชนะไหมเสร็จ
        switch (N) {
        case 3:
            if (key == 8 /* && C_multi < 1.5*/) C_multi += 1.5; //spade
            if (key == 7 /* && C_multi < 1.25*/) C_multi += 1.25; //heart
            if (key == 6 /* && C_multi < 0.75*/) C_multi += 0.75; //diamond
            if ((key == 5 || key == 4) /* && C_multi < 0.15*/) C_multi += 0.15; //A,K
            if ((key == 3 || key == 2 || key == 1) /* && C_multi < 0.1*/) C_multi += 0.1; //Q,J,10
            break;
        case 4:
            if (key == 8 /* && C_multi < 5*/) C_multi += 5;
            if (key == 7 /* && C_multi < 3.75*/) C_multi += 3.75;
            if (key == 6 /* && C_multi < 2*/) C_multi += 2;
            if ((key == 5 || key == 4) /* && C_multi < 0.3*/) C_multi += 0.3;
            if ((key == 3 || key == 2 || key == 1) /* && C_multi < 0.25*/) C_multi += 0.25;
            break;
        case 5:
            if (key == 8 /* && C_multi < 20*/) C_multi += 20;
            if (key == 7 /* && C_multi < 12.5 */ ) C_multi += 12.5;
            if (key == 6 /* && C_multi < 7.5*/) C_multi += 7.5;
            if ((key == 5 || key == 4) /* && C_multi < 1.5 */ ) C_multi += 1.5;
            if ((key == 3 || key == 2 || key == 1) /* && C_multi < 1*/) C_multi += 1;
            break;
        default:
            break;
        }

    }

    slotmac() {
        cout << "-----------------------------------Slot Rules-----------------------------------\n\n";
        cout << "----------------Pay line(X)------------------\n\n";

        cout << "(1) X X X X X\t" << "(2) O O O O O\t" << "(3) O O O O O\n";
        cout << "    O O O O O" << "\t    X X X X X" << "\t    O O O O O\n";
        cout << "    O O O O O" << "\t    O O O O O" << "\t    X X X X X\n\n";

        cout << "(4) X O O O X\t" << "(5) O O X O O\t" << "(6) O X O X O\n";
        cout << "    O X O X O" << "\t    O X O X O" << "\t    X O O O X\n";
        cout << "    O O X O O" << "\t    X O O O X" << "\t    O O X O O\n\n";

        cout << "(7) O O X O O\t" << "(8) X O O O X\t" << "(9) O X X X O\n";
        cout << "    X O O O X" << "\t    O O O O O" << "\t    O O O O O\n";
        cout << "    O X O X O" << "\t    O X X X O" << "\t    X O O O X\n\n";

        cout << "(10)O X O X O\t" << "(11)O O O O O\t" << "(12)O X O X O\n";
        cout << "    X O X O X" << "\t    O X O X O" << "\t    O O O O O\n";
        cout << "    O O O O O" << "\t    X O X O X" << "\t    X O X O X\n\n";

        cout << "(13)X O X O X\t" << "(14)O O O O O\t" << "(15)X O X O X\n";
        cout << "    O X O X O" << "\t    X O X O X" << "\t    O O O O O\n";
        cout << "    O O O O O" << "\t    O X O X O" << "\t    O X O X O\n\n";

        cout << "--------------------Rate---------------------\n\n";
        cout << "-\6-\t\t\t" << "-\3-\t\t\t" << "-\4-\n";
        cout << "5 - *20.00\t\t" << "5 - *12.50\t\t" << "5 - *7.50\n";
        cout << "4 - *5.00\t\t" << "4 - *3.75\t\t" << "4 - *2.00\n";
        cout << "3 - *1.50\t\t" << "3 - *1.25\t\t" << "3 - *0.75\n\n";

        cout << "-A-\t\t\t" << "-K-\t\t\t" << "-Q-\t\t\t" << "-J-\t\t\t" << "-10-\n";
        cout << "5 - *1.50\t\t" << "5 - *1.50\t\t" << "5 - *1.00\t\t" << "5 - *1.00\t\t" << "5 - *1.00\n";
        cout << "4 - *0.30\t\t" << "4 - *0.30\t\t" << "4 - *0.25\t\t" << "4 - *0.25\t\t" << "4 - *0.25\n";
        cout << "3 - *0.15\t\t" << "3 - *0.15\t\t" << "3 - *0.10\t\t" << "3 - *0.10\t\t" << "3 - *0.10\n\n";

        cout << "--------------------Rule---------------------\n";
        cout << "1.You will win if 3 or more similar symbol laying\nsame with the patern of payline.\n";
        cout << "2.The different symbol give the different price.\nThe price are showing in Rate topic.\n";
        cout << "---------------------------------------------\n";

        //แสดง playline ทั้งหมด 
        //แสดงเรทของแต่ละตัว
        //อธิบายนิดหน่อยว่าแบบไหนชนะ
    }
};