#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

#define H 20
#define W 15

char board[H][W] = {} ;
char blocks[7][4][4] = {
    {{' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}},
    {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ','T',' ',' '}, {'T','T','T',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ','S','S',' '}, {'S','S',' ',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {'Z','Z',' ',' '}, {' ','Z','Z',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {'J',' ',' ',' '}, {'J','J','J',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',' ','L',' '}, {'L','L','L',' '}, {' ',' ',' ',' '}}
};

int x = 4, y = 0, b = 1;

// --- BIẾN TOÀN CỤC CỦA SV5 ---
int speed = 200;
int lineCount = 0;

void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
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
            if ((i==H-1) || (j==0) || (j == W-1)) board[i][j] = '#';
            else board[i][j] = ' ';
}

void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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
    // Giao diện hiển thị điểm (SV5)
    cout << "\n Lines Cleared: " << lineCount << "  ";
    cout << "\n Speed: " << speed << " ms  \n";
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

// --- THUẬT TOÁN XOAY GẠCH (SV4 - Đã tối ưu) ---
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
    char temp[4][4] = {
        {' ',' ',' ',' '}, {' ',' ',' ',' '}, 
        {' ',' ',' ',' '}, {' ',' ',' ',' '}
    };
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            temp[j][3 - i] = blocks[b][i][j];

    if (canRotate(temp)){
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                blocks[b][i][j] = temp[i][j];
    }
}

// --- THUẬT TOÁN XÓA HÀNG VÀ TÍNH ĐIỂM (SV2 + SV5) ---
void removeLine() {
    for (int i = H - 2; i > 0; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') { 
                full = false;
                break;
            }
        }
            
        if (full) {
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < W - 1; j++) {
                    board[k][j] = board[k-1][j];
                }
            }
            for (int j = 1; j < W - 1; j++) {
                board[0][j] = ' ';
            }
            
            // Logic tính điểm và tăng tốc độ (SV5)
            lineCount++;
            if (speed > 50) speed -= 10;
            
            draw();
            Sleep(100); 
            i++; 
        }
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
        if (_kbhit()){
            char c = _getch();
            if (c=='a' && canMove(-1,0)) x--;
            if (c=='d' && canMove(1,0) ) x++;
            if (c=='x' && canMove(0,1))  y++;
            if (c=='w') rotateBlock(); // Gọi hàm xoay khối gạch
            if (c=='q') break;
        }
        
        if (canMove(0,1)) y++;
        else {
            block2Board();
            removeLine(); // Gọi hàm xóa hàng
            x = 5; y = 0; b = rand() % 7;
        }
        
        block2Board();
        draw();
        Sleep(speed); // Thời gian chờ động theo cấp độ
    }
    return 0;
}
