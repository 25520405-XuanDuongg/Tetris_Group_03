#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define H 20
#define W 15

// Khai báo biến toàn cục
char board[H][W] = {};

// Khai báo chuẩn 7 khối Tetris
char blocks[7][4][4] = {
    {{' ',' ',' ',' '}, {'I','I','I','I'}, {' ',' ',' ',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ','T',' ',' '}, {'T','T','T',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ','S','S',' '}, {'S','S',' ',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {'Z','Z',' ',' '}, {' ','Z','Z',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {'J',' ',' ',' '}, {'J','J','J',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',' ','L',' '}, {'L','L','L',' '}, {' ',' ',' ',' '}}
};

int x = 4, y = 0, b = 1;
int speed = 200;         // SV5: Biến tốc độ khởi tạo
int lineCount = 0;       // SV5: Đếm số hàng đã ăn
char currentBlock[4][4]; // SV4: Biến chứa khối đang rơi

// Hàm đổi màu chữ trong Console (Cần cho UI của SV3)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD c = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1))
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}

// Xóa vết của currentBlock trên board
void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentBlock[i][j] != ' ' && y + i < H)
                board[y + i][x + j] = ' ';
}

// Lưu currentBlock vào board
void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentBlock[i][j] != ' ')
                board[y + i][x + j] = currentBlock[i][j];
}

// Kiểm tra va chạm (Dùng currentBlock)
bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentBlock[i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

// Hàm kiểm tra xem ma trận temp sau khi xoay có hợp lệ không
bool canRotate(char temp[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (temp[i][j] != ' ') {
                int tx = x + j;
                int ty = y + i;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
        }
    }
    return true;
}

// Hàm xoay khối (Dùng currentBlock theo logic SV4)
void rotateBlock() {
    char temp[4][4];
    // xoay 90 độ
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[j][3 - i] = currentBlock[i][j];

    // kiểm tra có xoay được không
    if (canRotate(temp)) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                currentBlock[i][j] = temp[i][j];
    }
}

// Hàm xóa hàng của SV2 (Đổi thành kiểu int để đếm số hàng)
int removeLine() {
    int cleared = 0;
    for (int i = H - 2; i > 0; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            cleared++;
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < W - 1; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 1; j < W - 1; j++) {
                board[0][j] = ' ';
            }
            i++; // SV2 logic
        }
    }
    return cleared;
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char c = board[i][j];
            if (c == '#') {
                setColor(8);
                cout << "##";
            }
            else if (c == ' ') {
                cout << "  ";
            }
            else {
                switch (c) {
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
            setColor(7); // Trả lại màu xám mặc định
        }
        cout << endl;
    }

    // In thông tin bên cạnh màn hình
    gotoxy(W * 2 + 5, 2);
    setColor(15);
    cout << "TETRIS GROUP 03";
    gotoxy(W * 2 + 5, 4);
    cout << "Lines: " << lineCount;
    gotoxy(W * 2 + 5, 5);
    cout << "Speed: " << speed << "ms";
}

// Copy blueprint sang currentBlock
void spawnBlock() {
    b = rand() % 7;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            currentBlock[i][j] = blocks[b][i][j];
}

int main() {
    srand((unsigned int)time(0));
    system("cls");

    // Tắt con trỏ nhấp nháy trên console cho đẹp
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    initBoard();
    spawnBlock();

    while (1) {
        boardDelBlock();
        if (_kbhit()) {
            char c = _getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'x' && canMove(0, 1))  y++;
            if (c == 'w') rotateBlock();
            if (c == 'q') break;
        }

        if (canMove(0, 1)) {
            y++;
        }
        else {
            // Lưu khối đã chạm đáy vào board
            block2Board();

            // Xóa hàng & Cập nhật điểm, tốc độ
            int linesCleared = removeLine();
            if (linesCleared > 0) {
                lineCount += linesCleared;
                speed = speed - (linesCleared * 10);
                if (speed < 50) speed = 50;
            }

            // Sinh khối mới về đầu màn hình
            x = 5;
            y = 0;
            spawnBlock();

            // KIỂM TRA GAME OVER
            if (!canMove(0, 0)) {
                gotoxy(0, H + 2);
                setColor(12); // Màu đỏ
                cout << "==== GAME OVER! ====" << endl;
                setColor(7);
                break;
            }
        }

        block2Board();
        draw();
        Sleep(speed); // Dùng Sleep của Windows.h chuẩn hơn _sleep
    }
    return 0;
}