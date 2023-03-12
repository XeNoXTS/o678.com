#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <string>
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

//ประกาศ Global เพื่อให้ function เอาไปใช้ได้โดยไม่ต้อง input
vector<Card> player_hand;
vector<Card> dealer_hand;

//ฟังก์ชั่นโชว์การ์ด
void Show_Community_Card(string R, vector<Card>& deck) {
    int n = deck.size();
    cout << "------------------------------------------------------------\n";
    cout << "Community Card " ;
    if (R == "flop") {
        for (int i = 0; i < 3; i++) {
            cout << deck[n - i - 1].rank << deck[n - i - 1].suit << " ";
        }
    }
    else if (R == "turn") {
        for (int i = 0; i < 4; i++) {
            cout << deck[n - i - 1].rank << deck[n - i - 1].suit << " ";
        }
    }
    else {
        for (int i = 0; i < 5; i++) {
            cout<< deck[n - i - 1].rank << deck[n - i - 1].suit << " ";
        }
    }
    cout << "\n------------------------------------------------------------\n";
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
            cout << "------------------------------------------------------------\n";
            cout << "Dealer Card :: " << dealer_hand[0].rank << dealer_hand[0].suit << " " << dealer_hand[1].rank << dealer_hand[1].suit << endl;
            cout << "------------------------------------------------------------\n";
            cout << "Game over." << endl;
            cout << "------------------------------------------------------------\n";
            exit(0);
        }
        else if (choose == 'C') {//ลงเดิมพันต่อ
            Bet(chip, all_bet);
            cout << "------------------------------------------------------------\n";
        }
        else if (choose == 'A') {//หมดหน้าตัก
            all_bet += 2 * chip;
            chip = 0;
            cout << "You are all in." << endl;
            cout << "------------------------------------------------------------\n";
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

bool compareCards(const Card& card1, const Card& card2) {
    // Convert rank strings to integer values for comparison
    int rankValue1 = 0, rankValue2 = 0;
    if (card1.rank == "A") {
        rankValue1 = 14;
    } else if (card1.rank == "K") {
        rankValue1 = 13;
    } else if (card1.rank == "Q") {
        rankValue1 = 12;
    } else if (card1.rank == "J") {
        rankValue1 = 11;
    } else {
        rankValue1 = std::stoi(card1.rank);
    }
    if (card2.rank == "A") {
        rankValue2 = 14;
    } else if (card2.rank == "K") {
        rankValue2 = 13;
    } else if (card2.rank == "Q") {
        rankValue2 = 12;
    } else if (card2.rank == "J") {
        rankValue2 = 11;
    } else {
        rankValue2 = std::stoi(card2.rank);
    }

    // Group together cards with the same rank
    if (rankValue1 == rankValue2) {
        // Sort cards by suit in descending order
        if (card1.suit == "\6" && card2.suit != "\6") {
            return false;
        } else if (card1.suit == "\5" && (card2.suit != "\6" && card2.suit != "\5")) {
            return false;
        } else if (card1.suit == "\4" && (card2.suit == "\3" || (card2.rank == "A" && card2.suit == "\4"))) {
            return false;
        } else if (card1.suit == "\3" && (card2.rank == "A" && card2.suit == "\3")) {
            return false;
        }
        return true;
    }

    // Compare rank values in descending order
    return rankValue1 > rankValue2;
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

bool CheckFlush(vector<int> suit){
    for(int i = 0;i < 3;i++){
        if(suit[i] == suit[i+1] && suit[i+1] == suit[i+2] && suit[i+2] == suit[i+3] && suit[i+3] == suit[i+4]) return 1;
    }
    return 0;
}

bool sortByFrequency(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

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
    sort(result.begin(), result.end(), sortByFrequency);
    return result;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

vector<int> rankconverterstoi(vector<Card> hand){
    vector<int> rank;
    for(int i = 0;i < 7;i++){
        if(hand[i].rank == "A") hand[i].rank = "14";
        if(hand[i].rank == "K") hand[i].rank = "13";
        if(hand[i].rank == "Q") hand[i].rank = "12";
        if(hand[i].rank == "J") hand[i].rank = "11";
    }

    for(int i = 0;i < 7;i++){
        rank.push_back(stoi(hand[i].rank));
    }
    return rank;
}

vector<int> suitconverterstoi(vector<Card> hand){
    vector<int> suit;
    for(int i = 0;i < 7;i++){
        if(hand[i].suit == "\3") hand[i].suit = "4";
        if(hand[i].suit == "\4") hand[i].suit = "3";
        if(hand[i].suit == "\5") hand[i].suit = "2";
        if(hand[i].suit == "\6") hand[i].suit = "1";
    }

    for(int i = 0;i < 7;i++){
        suit.push_back(stoi(hand[i].suit));
    }
    return suit;
}

int findLargest(vector<int> v) {
    int largest = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] > largest) {
            largest = v[i];
        }
    }
    return largest;
}

void findElementLoc(vector<Card> hand,vector<int> &Loc, int key){
    for(int i = 0;i < hand.size();i++){
        if(hand[i].rank == "A") hand[i].rank = "14";
        if(hand[i].rank == "K") hand[i].rank = "13";
        if(hand[i].rank == "Q") hand[i].rank = "12";
        if(hand[i].rank == "J") hand[i].rank = "11";
    }
    for(int i = 0;i < hand.size();i++){
        int ref = stoi(hand[i].rank);
        if(key == ref){
            Loc.push_back(i);
        }
    }
}

//ฟังก์ชั่นตรวจสอบรูปแบบของcard
string CheckCard(vector<Card> hand){
    string result;
    bool flush = 0, straight = 0;
    int samecount = 0,samecountii = 0;
    vector<int> rank = rankconverterstoi(hand), suit = suitconverterstoi(hand);

    CardSort(rank,suit);

    straight = CheckStraight(rank);
    flush = CheckFlush(suit);

    vector<pair<int, int>> dup = findDuplicateElements(rank,rank.size());
    if(dup.size() >= 1){
        if(dup.size() > 1){
            samecount = dup[0].second;
            samecountii = dup[1].second;
        }else{
            samecount = dup[0].second;
        }
    }    
    for(int i = 0;i < 3;i++){
        if(suit[i] == suit[i+1] && suit[i+1] == suit[i+2] && suit[i+2] == suit[i+3] && suit[i+3] == suit[i+4]) flush = 1;
    }
    if(flush && straight){
        for(int i = 0; i < 3;i++){
            if(rank[i] == 10 && rank[i+1] == 11 && rank[i+2] == 12 && rank[i+3] == 13 && rank[i+4] == 14) return "Royal Flush";
        }
        return "Straight Flush";
    }
    if(samecount == 4) return "Four of a kind";
    if(samecount == 3 && samecountii == 2) return "Full House";
    if(flush) return "Flush";
    if(straight) return "Straight";
    if(samecount == 3) return "Three of a kind";
    if(samecount == 2 && samecountii == 2) return "Two Pair";
    if(samecount == 2) return "One Pair";
    if(flush == 0 && straight == 0 && samecount == 0 && samecountii == 0) return "High Card";
    return "Error Occured";
}


string CheckEqual(string outcome){
    sort(player_hand.begin(),player_hand.end(),compareCards);
    for(int i = 0;i < player_hand.size();i++){
        cout << player_hand[i].rank << player_hand[i].suit << ' ';
    }
    cout << endl;
    sort(dealer_hand.begin(),dealer_hand.end(),compareCards);
    for(int i = 0;i < dealer_hand.size();i++){
        cout << dealer_hand[i].rank << dealer_hand[i].suit << ' ';
    }
    cout << endl;
    vector<int> player_rank = rankconverterstoi(player_hand);
    vector<int> dealer_rank = rankconverterstoi(dealer_hand);

    vector<pair<int,int>> player_dup = findDuplicateElements(player_rank,player_rank.size());
    vector<pair<int,int>> dealer_dup = findDuplicateElements(dealer_rank,dealer_rank.size());
    //ไว้ดูค่า dup ของ
    /*cout << player_dup.size() << endl;
    for (int i = 0; i < player_dup.size(); i++) {
        cout << "Element " << player_dup[i].first << " has frequency " << player_dup[i].second << endl;
    }
    cout << dealer_dup.size() << endl;
    for (int i = 0; i < dealer_dup.size(); i++) {
        cout << "Element " << dealer_dup[i].first << " has frequency " << dealer_dup[i].second << endl;
    }*/
    vector<int> player_Loc;
    vector<int> dealer_Loc;

    //เอาค่าของตัวที่มีตัวซ้ำไปหาตำแหน่งของค่านั้นทั้งหมดที่อยู่ใน vector
    for(int i = 0;i < player_dup.size();i++){
        findElementLoc(player_hand,player_Loc,player_dup[i].first);
    }
    for(int i = 0;i < dealer_dup.size();i++){
        findElementLoc(dealer_hand,dealer_Loc,dealer_dup[i].first);
    }
    //เอาไว้ cout ดูค่า Loc 
    sort(player_Loc.begin(),player_Loc.end());
    sort(dealer_Loc.begin(),dealer_Loc.end());
    cout << "Player stored Loc\n"; //ตรวจค่าใน Vector Loc
    for(int i = 0;i < player_Loc.size();i++){
        cout << player_Loc[i] << ' ';
    }
    cout << endl;
    cout << "Dealer stored Loc\n";
    for(int i = 0;i < dealer_Loc.size();i++){
        cout << dealer_Loc[i] << ' ';
    }
    cout << endl;
    //erase element ที่อยู่ใน dup แล้ว
    for(int i = 0;i < player_Loc.size();i++){
        int idx = player_Loc[i] - i;
        player_hand.erase(player_hand.begin() + idx);
    }
    for(int i = 0;i < dealer_Loc.size();i++){
        int idx = dealer_Loc[i] - i;
        dealer_hand.erase(dealer_hand.begin() + idx);
    }
    cout << "Player erased hand :: ";
    for(int i = 0;i < player_hand.size();i++){
        cout << player_hand[i].rank << player_hand[i].suit << ' ';
    }
    cout << endl;
    cout << "Dealer erased hand :: ";
    for(int i = 0;i < dealer_hand.size();i++){
        cout << dealer_hand[i].rank << dealer_hand[i].suit << ' ';
    }
    cout << endl;
    
    Card player_kicker, dealer_kicker;
    int j = 0;
    do{
        player_kicker = player_hand[j];
        dealer_kicker = dealer_hand[j];
        j++;
    }while(player_kicker.rank == dealer_kicker.rank && player_kicker.suit == dealer_kicker.suit);
    //Show Kicker card
    cout << "Player Kicker :: " << player_kicker.rank << player_kicker.suit << endl;
    cout << "Dealer Kicker :: " << dealer_kicker.rank << dealer_kicker.suit << endl;
    
    if(outcome == "Royal Flush") return "Unfinished Code"; 
    if(outcome == "Straight Flush") return "Unfinished Code"; 
    if(outcome == "Four of a kind") return "Unfinished Code"; 
    if(outcome == "Full House") return "Unfinished Code"; 
    if(outcome == "Flush") return "Unfinished Code"; 
    if(outcome == "Straight") return "Unfinished Code"; 
    if(outcome == "Three of a kind"){
        if(player_dup[0].first > dealer_dup[0].first) return "Player Win!!";
        else if(player_dup[0].first == dealer_dup[0].first){
            if(player_kicker.rank > dealer_kicker.rank) return "Player Win!!";
        else return "Player Lose!!";
        } else return "Player Lose!!";
    }
    if(outcome == "Two Pair"){
        if(player_dup[0].first > dealer_dup[0].first) return "Player Win!!";
        else if(player_dup[0].first < dealer_dup[0].first) return "Player Lose!!";
        else if(player_dup[0].first == dealer_dup[0].first){
            if(player_dup[1].first > dealer_dup[1].first) return "Player Win!!";
            else if(player_dup[1].first < dealer_dup[1].first) return "Player Lose!!";
            else if(player_dup[1].first == dealer_dup[1].first){
                if(player_kicker.rank > dealer_kicker.rank) return "Player Win!!";
                else return "Player Lose!!";
            }
        }
    }
    if(outcome == "One Pair"){
        if(player_dup[0].first > dealer_dup[0].first) return "Player Win!!";
        else if(player_dup[0].first == dealer_dup[0].first){
            if(player_kicker.rank > dealer_kicker.rank) return "Player Win!!";
        else return "Player Lose!!";
        } else return "Player Lose!!";
    }
    if(outcome == "High Card"){
        if(player_kicker.rank > dealer_kicker.rank) return "Player Win!!";
        else return "Player Lose!!";
    }
}

void CheckWinner(string PlayerResult, string DealerResult){
    int PlayerScore = 0, DealerScore = 0;
    string result;
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
    if(PlayerScore > DealerScore) result = "Player Win!!";
    else if(PlayerScore < DealerScore) result = "Player Lose!!";
    else if(PlayerScore == DealerScore){
        result = CheckEqual(PlayerResult);
    }
    else result = "Error";
    cout << "------------------------------------------------------------\n";
    cout << "\t\t\t" << result << endl;
    cout << "------------------------------------------------------------\n";
}

int main(){

    int Chip=500,All_Bet=0;
    vector<Card> deck = create_deck();
    shuffle_deck(deck);

    //จั่วการ์ด
    for(int i=0;i<2;i++){
        player_hand.push_back(deck.back());
        deck.pop_back();
        dealer_hand.push_back(deck.back());
        deck.pop_back();
    }

    //preflop_เหมือนรอบ0นั้นแหละ
    cout << "------------------------------------------------------------\n";
    cout<<"Your Chip :: " << Chip << endl;
    cout<<"Your Card :: " << player_hand[0].rank<<player_hand[0].suit << " " << player_hand[1].rank<<player_hand[1].suit << endl;
    cout << "------------------------------------------------------------\n";

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

    cout << "Player actual card :: ";
    for(int i = 0;i < 7;i++){
        cout << player_hand[i].rank << player_hand[i].suit << ' ';
    }
    cout << endl;
    cout << "Deal actual card :: ";
    for(int i = 0;i < 7;i++){
        cout << dealer_hand[i].rank << dealer_hand[i].suit << ' ';
    }
    cout << endl;
    cout << "------------------------------------------------------------\n";
    cout << "Player got " << CheckCard(player_hand) << endl;
    cout << "------------------------------------------------------------\n";
    cout << "Dealer got " << CheckCard(dealer_hand) << endl;
    cout << "------------------------------------------------------------\n";

    CheckWinner(CheckCard(player_hand), CheckCard(dealer_hand));

    return 0;
}