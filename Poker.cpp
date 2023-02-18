#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

//ทำstruct เก็บ ชนิดกับค่าของไฟ่
struct Card {
    string rank;
    string suit;    
};

//ฟังก์ชั่นสร้างdeckและกำหนดค่าต่างๆในvector
vector<Card> create_deck() {
    vector<Card> deck;
    string suits[] = {"\3", "\4", "\5", "\6"};
    string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for (string suit : suits) {
        for (string rank : ranks) {
            deck.push_back({rank, suit});
        }
    }
    return deck;
}

//shuffle deck ทั้งกอง
void shuffle_deck(vector<Card>& deck) {
    random_device rd;
    mt19937 g(rd()); //ลองไปศึกษาดู ส่วนตัวอย่างนี้สะดวกกว่า
    shuffle(deck.begin(), deck.end(), g);
}

/* กันไว้เผื่ออยากใช้ตัวนี้แทน มันใช่ได้จริงแต่มีสิทธิ์ที่จะสุ่ม i=j เสมออยู่
void shuffle_deck(vector<Card>& deck) {
    srand(time(nullptr));
    int n = deck.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(deck[i], deck[j]);
    }
}
*/

//ฟังก์ชั่นโชว์การ์ด
void Show_Community_Card(string R, vector<Card>& deck) {
    int n = deck.size();
    cout << "Community Card " ;
    if (R == "flop") {
        for (int i = 0; i < 3; i++) {
            cout<< deck[n - i - 1].rank << deck[n - i - 1].suit << " ";
        }
    }
    else if (R == "turn") {
        for (int i = 0; i < 4; i++) {
            cout<< deck[n - i - 1].rank << deck[n - i - 1].suit << " ";
        }
    }
    else {
        for (int i = 0; i < 5; i++) {
            cout<< deck[n - i - 1].rank << deck[n - i - 1].suit << " ";
        }
    }
    cout << endl;
}

//ฟังก์ชั่นคำนวณchipที่ลงเดิมพัน
void Bet(int& chip, int& all_bet) {
    int bet;
    while (true) {
        cout << "Bet: ";
        cin >> bet;
        if (chip - bet >= 0) {
            chip -= bet;
            all_bet += 2 * bet;
            break;
        }
        else {
            cout << "Not enough chips." << endl;
        }
    }
}

//ฟังก์ชั่นตัวเลือกต่างๆ
void Choose(int& chip, int& all_bet,vector<Card> dealer_hand) {
    char choose;
    cout << "Fold/Call/All in -->(F/C/A): ";
    do {
        cin >> choose;
        if (choose == 'F') {//หมอบ_แต่เล่น2คนก็เหมือนจบเกม
            cout << "You folded." << endl;
            cout << "Dealer Card :: " << dealer_hand[0].rank << dealer_hand[0].suit << " " << dealer_hand[1].rank << dealer_hand[1].suit << endl;
            cout << "Game over." << endl;
            exit(0);
        }
        else if (choose == 'C') {//ลงเดิมพันต่อ
            Bet(chip, all_bet);
        }
        else if (choose == 'A') {//หมดหน้าตัก
            all_bet += 2 * chip;
            chip = 0;
            cout << "You are all in." << endl;
        }
    } while (choose != 'F' && choose != 'C' && choose != 'A');
}

//ตามชื่อฟังก์ขั่น
void Check_Winer(int& chip, int& all_bet, int winner) {
    if (winner == 1) {
        chip += all_bet;
        cout << "You won " << all_bet << " chips." << endl;
    }
    else {
        cout << "You loss "<<endl;
    }
}

//ฟังก์ชั่นตรวจสอบรูปแบบของcard ตอนนี้พังๆอยู่
string CheckCard(vector<Card> hand){
    string result;
    bool flush = 0;
    bool insequence = 0;
    int samecount = 0;
    int samecountii = 0;
    int remb;
    //หาวิธีเรียงค่าของการ์ดในมืออยู่ กับวิธีตรวจการ์ดในมือ
    /*for(int i = 0; i < hand.size(); i++){
        if(hand[i].suit == hand[i+1].suit && hand[i+1].suit == hand[i+2].suit && hand[i+2].suit == hand[i+3].suit && hand[i+3].suit == hand[i+4].suit) flush = 1;
    }*/
    /*for(int i = 0;i<hand.size();i++){
        string key = hand[i].rank;
        for(int j = 0; j < hand.size();i++){
            if(key == hand[j].rank && i != j && i != remb){
                samecount++;
            }
        }
    }*/

    if(flush){
        bool A = 0,K = 0, Q = 0, J = 0, T = 0;
        for(int i = 0; i < hand.size(); i++){
            if(hand[i].rank == "A") A = 1;
            if(hand[i].rank == "K") K = 1;
            if(hand[i].rank == "Q") Q = 1;
            if(hand[i].rank == "J") J = 1;
            if(hand[i].rank == "10") T = 1;
        }
        if(A && K && Q && J && T) result = "Royal Flush";
        return result;
    }
    if(insequence && flush){
        result = "Straight Flush";
        return result;
    }
    if(samecount == 3){
        result = "Four of a kind";
        return result;
    }
    if(samecount == 2 && samecountii == 1){
        result = "Full House";
        return result;
    }
    if(flush){
        result = "Flush";
        return result;
    }
    if(insequence){
        result = "Straight";
        return result;
    }
    if(samecount == 2){
        result = "Three of a kind";
        return result;
    }
    if(samecount == 1 && samecountii == 1){
        result = "Two Pair";
        return result;
    }
    if(samecount == 1){
        result = "One Pair";
        return result;
    }
    else{
        result = "High Card";
        return result;
    }
}

int main(){

    int Chip=500,All_Bet=0;
    vector<Card> deck = create_deck();
    shuffle_deck(deck);

    vector<Card> player_hand;
    vector<Card> dealer_hand;

    //จั่วการ์ด
    for(int i=0;i<2;i++){
        player_hand.push_back(deck.back());
        deck.pop_back();
        dealer_hand.push_back(deck.back());
        deck.pop_back();
    }

    //preflop_เหมือนรอบ0นั้นแหละ
    cout<<"Your Chip ::"<<Chip<<endl;
    cout<<"Your Card :: "<<player_hand[0].rank<<player_hand[0].suit<<" "<<player_hand[1].rank<<player_hand[1].suit<<endl;
    Bet(Chip,All_Bet);

    //flop_เหมือนรอบแรกนั้นแหละจะลงเท่าไหร่หรือหมอบ
    Show_Community_Card("flop",deck);
    Choose(Chip,All_Bet,dealer_hand);

    //ตามข้างบนรอบ2
    Show_Community_Card("turn",deck);
    Choose(Chip,All_Bet,dealer_hand);

    //ตามข้างบนรอบจบ_เปิดการ์ดทุกคนแล้วนับแต้ม
    cout<<"Dealer Card :: "<<dealer_hand[0].rank<<dealer_hand[0].suit<<" "<<dealer_hand[1].rank<<dealer_hand[1].suit<<endl;
    Show_Community_Card("river",deck);
    cout<<"Your Card :: "<<player_hand[0].rank<<player_hand[0].suit<<" "<<player_hand[1].rank<<player_hand[1].suit<<endl;

    //ตามที่เราคุยกันไว้คือจะเอาเข้ามาในมือให้เรียบร้อย_เหมือนทั้ง2คนมี7ใบ_แล้วทำเงื่อนไขว่าใครชนะ
    for(int i=0;i<5;i++){
        player_hand.push_back(deck.back());
        dealer_hand.push_back(deck.back());
        deck.pop_back();
    }


    //ฉะนั้น_ฟังค์ชั่นเงื่อนไขกับจบ_เพื่อน_ฝากที_ราตรีสวัสดิ์!!!

    return 0;
}