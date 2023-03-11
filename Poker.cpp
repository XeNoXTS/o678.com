#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <string>
#include <set>
#include <map>

using namespace std;

//ทำstruct เก็บ ชนิดกับค่าของไฟ่
struct Card{
    string rank;
    string suit;    
};

//ฟังก์ชั่นสร้างdeckและกำหนดค่าต่างๆในvector
vector<Card> create_deck(){
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
/*void shuffle_deck(vector<Card>& deck) {
    random_device rd;
    mt19937 g(rd()); //ลองไปศึกษาดู ส่วนตัวอย่างนี้สะดวกกว่า
    shuffle(deck.begin(), deck.end(), g);
}*/

// กันไว้เผื่ออยากใช้ตัวนี้แทน มันใช่ได้จริงแต่มีสิทธิ์ที่จะสุ่ม i=j เสมออยู่
void shuffle_deck(vector<Card>& deck) {
    srand(time(nullptr));
    int n = deck.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(deck[i], deck[j]);
    }
}


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

//ตามชื่อฟังก์ขั่น need implementation
void Show_Winer(int& chip, int& all_bet, int winner) {
    if (winner == 1) {
        chip += all_bet;
        cout << "You won " << all_bet << " chips." << endl;
    }
    else {
        cout << "You loss "<<endl;
    }
}

//เรียงการ์ด
void CardSort(vector<int>& rank, vector<int>& suit) {
    for (int i = 0; i < 6; i++) {
        int min_idx = i;
        for (int j = i + 1; j < 7; j++) {
            if (rank[j] < rank[min_idx] || (rank[j] == rank[min_idx] && suit[j] < suit[min_idx])) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(rank[i], rank[min_idx]);
            swap(suit[i], suit[min_idx]);
        }
    }
}

//เอาไว้เช็คว่าการ์ดในมือมีตัวที่มีค่าเรียงกันมั้ย BUG หนักมาก
bool CheckStraight(vector<int> card) {
    sort(card.begin(), card.end());
    for (int i = 0; i <= 2; i++) {
        int highest = card[i];
        int count = 1;
        for (int j = i+1; j < 7; j++) {
            if (card[j] == highest + 1) {
                highest = card[j];
                count++;
                if (count == 5) {
                    return true;
                }
            }
            else if (card[j] != highest) {
                highest = card[j];
                count = 1;
            }
        }
    }
    return false;
}

//code frome Chatgpt เอาไว้ใช้หาตัวซ้ำ
vector<pair<int, int>> findDuplicateElements(vector<int> arr, int n) {
    map<int, int> freqMap;
    for (int i = 0; i < n; i++) {
        freqMap[arr[i]]++;
    }
    vector<pair<int, int>> result;
    for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
        if (it->second > 1) {
            result.push_back(make_pair(it->first, it->second));
        }
    }
    return result;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

//ฟังก์ชั่นตรวจสอบรูปแบบของcard ตอนนี้พังๆอยู่
string CheckCard(vector<Card> hand){
    string result;
    bool flush = 0, straight = 0;
    int samecount = 0,samecountii = 0;
    vector<int> rank, suit;
    vector<pair<int, int>> dup;

    for(int i = 0;i < 7;i++){
        if(hand[i].rank == "A") hand[i].rank = "14";
        if(hand[i].rank == "K") hand[i].rank = "13";
        if(hand[i].rank == "Q") hand[i].rank = "12";
        if(hand[i].rank == "J") hand[i].rank = "11";
        if(hand[i].suit == "\3") hand[i].suit = "4";
        if(hand[i].suit == "\4") hand[i].suit = "3";
        if(hand[i].suit == "\5") hand[i].suit = "2";
        if(hand[i].suit == "\6") hand[i].suit = "1";
    }

    for(int i = 0;i < 7;i++){
        rank.push_back(stoi(hand[i].rank));
        suit.push_back(stoi(hand[i].suit));
    }

    CardSort(rank,suit);

    if(CheckStraight(rank)) straight = 1;

    int n = sizeof(rank) / sizeof(rank[0]);
    dup = findDuplicateElements(rank,n);
    if(dup.size() != 0){
        for(int i = dup.size();i > 1;i--){
            for(int j = 0;j < dup.size() - 1;j++){
                if(dup[i].second < dup[i+1].second) swap(dup[i],dup[i+1]);
            }
        }        
    }
    samecount = dup[0].second;
    samecountii = dup[1].second;

    for(int i = 0;i < 3;i++){
        if(suit[i] == suit[i+1] && suit[i+1] == suit[i+2] && suit[i+2] == suit[i+3] && suit[i+3] == suit[i+4]) flush = 1;
    }
    
    if(flush){
        for(int i = 0; i < 3;i++){
            if(rank[i] == 10 && rank[i+1] == 11 && rank[i+2] == 12 && rank[i+3] == 13 && rank[i+4] == 14) return "Royal Flush";
        }
    }
    if(straight && flush){
        return "Straight Flush";
    }
    if(samecount == 3){
        return "Four of a kind";
    }
    if(samecount == 2 && samecountii == 1){
        return "Full House";
    }
    if(flush){
        return "Flush";
    }
    if(straight){
        return "Straight";
    }
    if(samecount == 2){
        return "Three of a kind";
    }
    if(samecount == 1 && samecountii == 1){
        return "Two Pair";
    }
    if(samecount == 1){
        return "One Pair";
    }
    else{
        return "High Card"; 
    }
}

void CheckWinner(string PlayerResult, string DealerResult){
    int PlayerScore = 0, DealerScore = 0;
    if(PlayerResult == "Royal Flush") PlayerScore = 10;
    if(PlayerResult == "Straight Flush") PlayerScore = 9;
    if(PlayerResult == "Four of a kind") PlayerScore = 8;
    if(PlayerResult == "Full House") PlayerScore = 7;
    if(PlayerResult == "Flush") PlayerScore = 6;
    if(PlayerResult == "Straight") PlayerScore = 5;
    if(PlayerResult == "Three of a kind") PlayerScore = 4;
    if(PlayerResult == "Two Pair") PlayerScore = 3;
    if(PlayerResult == "One Pair") PlayerScore = 2;
    if(PlayerResult == "High Card") PlayerScore = 1;
    if(DealerResult == "Royal Flush") DealerScore = 10;
    if(DealerResult == "Straight Flush") DealerScore = 9;
    if(DealerResult == "Four of a kind") DealerScore = 8;
    if(DealerResult == "Full House") DealerScore = 7;
    if(DealerResult == "Flush") DealerScore = 6;
    if(DealerResult == "Straight") DealerScore = 5;
    if(DealerResult == "Three of a kind") DealerScore = 4;
    if(DealerResult == "Two Pair") DealerScore = 3;
    if(DealerResult == "One Pair") DealerScore = 2;
    if(DealerResult == "High Card") DealerScore = 1;
    if(PlayerScore > DealerScore) cout << "Player Win!!" << endl;
    else if(DealerScore > PlayerScore) cout << "Player Lose!!" << endl;
    else cout << "Draw" << endl;
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
    cout<<"Your Chip ::" << Chip << endl;
    cout<<"Your Card :: " << player_hand[0].rank<<player_hand[0].suit << " " << player_hand[1].rank<<player_hand[1].suit << endl;
    Bet(Chip,All_Bet);

    //flop_เหมือนรอบแรกนั้นแหละจะลงเท่าไหร่หรือหมอบ
    Show_Community_Card("flop",deck);
    Choose(Chip,All_Bet,dealer_hand);

    //ตามข้างบนรอบ2
    Show_Community_Card("turn",deck);
    Choose(Chip,All_Bet,dealer_hand);

    //ตามข้างบนรอบจบ_เปิดการ์ดทุกคนแล้วนับแต้ม
    cout << "Dealer Card :: " <<  dealer_hand[0].rank << dealer_hand[0].suit << " " << dealer_hand[1].rank << dealer_hand[1].suit << endl;
    Show_Community_Card("river",deck);
    cout << "Your Card :: " <<  player_hand[0].rank << player_hand[0].suit << " " << player_hand[1].rank << player_hand[1].suit << endl;

    //ตามที่เราคุยกันไว้คือจะเอาเข้ามาในมือให้เรียบร้อย_เหมือนทั้ง2คนมี7ใบ_แล้วทำเงื่อนไขว่าใครชนะ
    for(int i=0;i<5;i++){
        player_hand.push_back(deck.back());
        dealer_hand.push_back(deck.back());
        deck.pop_back();
    }

    cout << "Dealer got " << CheckCard(dealer_hand) << endl;
    cout << "Player got " << CheckCard(player_hand) << endl;


    //ฉะนั้น_ฟังค์ชั่นเงื่อนไขกับจบ_เพื่อน_ฝากที_ราตรีสวัสดิ์!!!

    return 0;
}