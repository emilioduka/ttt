#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <vector>

using namespace std;

void BoardInit(char board[9]);
void PrintBoard(char board[9]);
void UserPlay(char board[9], bool& xo, int& round);
bool Win(char board[9]);
void AIPlay(char board[9], bool& xo, int& round);

int main(int argc, char** argv) {

    //Initialisation
    char board[9];
    BoardInit(board);
    srand(time(0));
    bool xo = rand() % 2; //0 for O, 1 for X
    bool win = 0;
    int round = 1;
    
    //Game Loop
    while (!win && round<10){
        AIPlay(board, xo, round);
        win = Win(board);
        if (!win && round<10) {
            UserPlay(board, xo, round);
            win = Win(board);
        }
    }
    
    cout<<"\n\n\n";
    PrintBoard(board);
    cout<<(win?"Game over.":"It's a tie.");
    
    return 0;
}

void PrintBoard(char board[9]){
    
    char boardVisual[] = " %c | %c | %c\n"
            "-----------\n"
            " %c | %c | %c\n"
            "-----------\n"
            " %c | %c | %c\n\n";
    printf(boardVisual, board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);
}

void BoardInit(char board[9]){
    
    for (int i=0; i<9; i++){
        board[i] = (to_string(i+1))[0];
    }
    
}

void UserPlay(char board[9], bool& xo, int& round){
    
    char pos;
    printf("Round %d\n%c plays, enter position (1-9).\n\n\n", round, (xo?'X':'O'));
    PrintBoard(board);
    do {
        cin>>pos;
        pos = atoi(&pos);
        if (pos<1 || pos>9){
            cout<<"Position must be 1-9\n";
        }
        if (board[pos-1] == 'X' || board[pos-1] == 'O'){
            cout<<"Select empty space\n";
            pos=0;
        }
    }
    while (pos<1 || pos>9);
    
    board[pos-1] = xo?'X':'O';
    xo = !xo;
    round++;
}

bool Win(char board[9]){
       
    //Horizontal Check
    for (int i=0; i<7; i+=3){
       if ((board[i]==board[i+1])&&(board[i]==board[i+2])&&(board[i+1]==board[i+2])) return 1;
    }
    
    //Vertical Check
    for (int i=0; i<3; i++){
       if ((board[i]==board[i+3])&&(board[i]==board[i+6])&&(board[i+3]==board[i+6])) return 1;
    }
    
    //Diagonal Check
    if ((board[0]==board[4])&&(board[0]==board[8])&&(board[4]==board[8])) return 1;
    if ((board[2]==board[4])&&(board[2]==board[6])&&(board[4]==board[6])) return 1;
    
    return 0;
}

void AIPlay(char board[9], bool& xo, int& round) {
    
    printf("Round %d\n%c plays.\n\n\n", round, (xo?'X':'O'));
    PrintBoard(board);
    cout.flush();
    Sleep(1500);
    char ai = xo?'X':'O',op = xo?'O':'X'; //AI and Opponent's Characters
    int i, pos=9, counter = 9, win = 9; //pos: Non-Counter Move, counter: Counter Move, win: Winning Move
    
    
    
    if (round == 1) pos = rand() % 9;
    else if (round == 2) {
        do
            pos = rand() % 9;
        while (board[pos] == op);
    }
    
    //Check for Possible Moves/Winning Move
    
    //Horizontal Check
    for (i=0; i<7; i+=3){
        if (win!=9) break;
        //-X-       
        if ((board[i]!=op)&&(board[i+1]==ai)&&(board[i+2]!=op)) {
            if (board[i]==ai) {
                win = i+2;
            }
            else if (board[i+2]==ai) {
                win = i;
            }
            else {
                pos = (rand()%2)?i:i+2;
            }
        }
        //X--
        else if ((board[i]==ai)&&(board[i+1]!=op)&&(board[i+2]!=op)) {
            if (board[i+1]==ai) {
                win = i+2;
            }
            else if (board[i+2]==ai) {
                win = i+1;
            }
            else {
                pos = (rand()%2)?i+2:i+1;
            }
        }
        //--X
        else if ((board[i]!=op)&&(board[i+1]!=op)&&(board[i+2]==ai)) {
            if (board[i]==ai) {
                win = i+1;
            }
            else if (board[i+1]==ai) {
                win = i;
            }
            else {
                pos = (rand()%2)?i+1:i;
            }
        }
    }
    
    //Vertical Check
    for (i=0; i<3; i++){
        if (win!=9) break;
        //-X-       
        if ((board[i]!=op)&&(board[i+3]==ai)&&(board[i+6]!=op)) {
            if (board[i]==ai) {
                win = i+6;
                break;
            }
            else if (board[i+6]==ai) {
                win = i;
                break;
            }
            else {
                pos = (rand()%2)?i+6:i;
            }
        }
        //X--
        else if ((board[i]==ai)&&(board[i+3]!=op)&&(board[i+6]!=op)) {
            if (board[i+3]==ai) {
                win = i+6;
                break;
            }
            else if (board[i+6]==ai) {
                win = i+3;
                break;
            }
            else {
                pos = (rand()%2)?i+6:i+3;
            }
        }
        //--X
        else if ((board[i]!=op)&&(board[i+3]!=op)&&(board[i+6]==ai)) {
            if (board[i]==ai) {
                win = i+3;
                break;
            }
            else if (board[i+3]==ai) {
                win = i;
                break;
            }
            else {
                pos = (rand()%2)?i+3:i;
            }
        }
    }
    
    //Diagonal Check
    for (i=2; i<=4; i+=2){
        if (win!=9) break;
        //-X-       
        if ((board[4+i]!=op)&&(board[4-i]==ai)&&(board[4]!=op)) {
            if (board[4]==ai) {
                win = 4+i;
                break;
            }
            else if (board[4+i]==ai) {
                win = 4;
                break;
            }
            else {
                pos = (rand()%2)?4+i:4;
            }
        }
        //X--
        else if ((board[4]==ai)&&(board[4-i]!=op)&&(board[4+i]!=op)) {
            if (board[4-i]==ai) {
                win = 4+i;
                break;
            }
            else if (board[4+i]==ai) {
                win = 4-i;
                break;
            }
            else {
                pos = (rand()%2)?4+i:4-i;
            }
        }
        //--X
        else if ((board[4]!=op)&&(board[4-i]!=op)&&(board[4+i]==ai)) {
            if (board[4]==ai) {
                win = 4-i;
                break;
            }
            else if (board[4-i]==ai) {
                win = 4;
                break;
            }
            else {
                pos = (rand()%2)?4-i:4;
            }
        }
    }
    
    
    
    //Check For Possible Counter Moves
    //Horizontal
    for (i=0; i<7; i+=3){
        //X-X        
        if ((board[i]==op)&&(board[i+2]==op)&&(board[i+1]!=op)&&(board[i+1]!=ai)) {
           counter = i+1;
        }
        //XX-
        else if ((board[i]==op)&&(board[i+1]==op)&&(board[i+2]!=op)&&(board[i+2]!=ai)) {
            counter = i+2;
        }
        //-XX
        else if ((board[i+1]==op)&&(board[i+2]==op)&&(board[i]!=op)&&(board[i]!=ai)) {
            counter = i;
        }
    }
    
    //Vertical
    for (i=0; i<3; i++) {
        //X-X        
        if ((board[i]==op)&&(board[i+6]==op)&&(board[i+3]!=op)&&(board[i+3]!=ai)) {
           counter = i+3;
        }
        //XX-
        else if ((board[i]==op)&&(board[i+3]==op)&&(board[i+6]!=op)&&(board[i+6]!=ai)) {
            counter = i+6;
        }
        //-XX
        else if ((board[i+3]==op)&&(board[i+6]==op)&&(board[i]!=op)&&(board[i]!=ai)) {
            counter = i;
        }
    }
    
    //Diagonal
    for (i=2; i<=4; i+=2) {
        //X-X        
        if ((board[4-i]==op)&&(board[4+i]==op)&&(board[4]!=op)&&(board[4]!=ai)) {
           counter = 4;
        }
        //XX-
        else if ((board[4-i]==op)&&(board[4]==op)&&(board[4+i]!=op)&&(board[4+i]!=ai)) {
            counter = 4+i;
        }
        //-XX
        else if ((board[4]==op)&&(board[4+i]==op)&&(board[4-i]!=op)&&(board[4-i]!=ai)) {
            counter = 4-i;
        }
    }
    
    if (win != 9) pos = win;
    else if (counter != 9) pos = counter;
    else if (pos == 9) {
        do
            pos = rand() % 9;
        while ((board[pos] == op) || (board[pos] == ai));
    }
    
    board[pos] = xo?'X':'O';
    xo = !xo;
    round++;
    
}