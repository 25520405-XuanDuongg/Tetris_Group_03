#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#define H 21
#define W 12
char board[H][W] = {} ;
char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

int x=4,y=0,b=1;
void gotoxy(int x, int y) {
    COORD c;

    c.X = (SHORT)x;
    c.Y = (SHORT)y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        c
    );
}
void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' && y+i < H)
                board[y+i][x+j] = ' ';
}
void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' )
                board[y+i][x+j] = blocks[b][i][j];
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if ((i==H-1) || (j==0) || (j == W-1))
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}
void setColor(int color){
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
}
void draw() {

    gotoxy(0,0);

    for (int i = 0 ; i < H ; i++) {

        for (int j = 0 ; j < W ; j++) {

            char c = board[i][j];

            if (c == '#') {
                setColor(8);
                cout << "##";
            }

            else if (c == ' ') {
                cout << "  ";
            }

            else {

                switch(c){

                    case 'I': setColor(11); break;
                    case 'O': setColor(14); break;
                    case 'T': setColor(13); break;
                    case 'S': setColor(10); break;
                    case 'Z': setColor(12); break;
                    case 'J': setColor(9);  break;
                    case 'L': setColor(6);  break;

                    default: setColor(7);
                }

                cout << "[]";
            }

            setColor(7);
        }

        cout << endl;
    }
}
bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;
                if ( tx<1 || tx >= W-1 || ty >= H-1) return false;
                if ( board[ty][tx] != ' ') return false;
            }
    return true;
}
bool canRotate(char temp[4][4]){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (temp[i][j] != ' '){

                int tx = x + j;
                int ty = y + i;

                if (tx < 1 || tx >= W-1 || ty >= H-1)
                    return false;

                if (board[ty][tx] != ' ')
                    return false;
            }

    return true;
}

void rotateBlock(){

    char temp[4][4];

    // xoay 90 độ
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            temp[j][3 - i] = blocks[b][i][j];

    // kiểm tra có xoay được không
    if (canRotate(temp)){

        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                blocks[b][i][j] = temp[i][j];
    }
}
int main()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_CURSOR_INFO cursor;

cursor.bVisible = FALSE;
cursor.dwSize = 1;

SetConsoleCursorInfo(hOut, &cursor);

    srand(time(0));
    b = rand() % 7;
    system("cls");
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c=='a' && canMove(-1,0)) x--;
            if (c=='d' && canMove(1,0) ) x++;
            if (c=='x' && canMove(0,1))  y++;
            if (c=='q') break;
            if (c=='w'){
                boardDelBlock();
                rotateBlock();
            }
        }
        if (canMove(0,1)) y++;
        else {
            block2Board();
            x = 5; y = 0; b = rand() % 7;
        }
        block2Board();
        draw();
        Sleep(200);;
    }
    return 0;
}
