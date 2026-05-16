#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

#define H 20
#define W 15

char board[H][W] = {};
char blocks[][4][4] = {
        {{' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}},
        {{' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}, {' ','I',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {'I','I','I','I'}, {' ',' ',' ',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','O','O',' '}, {' ','O','O',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','T',' ',' '}, {'T','T','T',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ','S','S',' '}, {'S','S',' ',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {'Z','Z',' ',' '}, {' ','Z','Z',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {'J',' ',' ',' '}, {'J','J','J',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',' ','L',' '}, {'L','L','L',' '}, {' ',' ',' ',' '}}
};

int x = 4, y = 0, b = 1;

void gotoxy(int x, int y) {
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ' && y + j < H)
                board[y + i][x + j] = ' ';
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++)
            cout << board[i][j];
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

// --- THUẬT TOÁN XÓA HÀNG CỦA SV2 ---
void removeLine() {
    // Chạy từ H-2 vì H-1 là viền đáy '#'
    for (int i = H - 2; i > 0; i--) {
        bool full = true;

        // Bỏ qua cột 0 và W-1 vì nó là viền '#'
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') { // Nếu có khoảng trắng là chưa đầy
                full = false;
                break;
            }
        }

        if (full) {
            // Kéo các hàng từ trên xuống
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < W - 1; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }

            // Dòng trên cùng (dòng 0) gán lại khoảng trắng
            for (int j = 1; j < W - 1; j++) {
                board[0][j] = ' ';
            }

            // Giữ lại hiệu ứng vẽ để thấy hàng biến mất
            draw();
            _sleep(100);

            // SV2 logic: Kiểm tra lại chính dòng này (phòng trường hợp ăn 2-3 hàng)
            i++;
        }
    }
}
// Logic mẫu khi bấm phím Xoay (Mũi tên LÊN)
void handleRotation(Piece* currentPiece) {
    // 1. Cứ cho xoay trước
    currentPiece->rotate();

    // 2. Viết 1 hàm check xem vị trí mới có bị đâm vào tường (Wall) 
    // hoặc đâm vào khối cũ dưới đáy không.
    if (!isValidPosition(currentPiece)) {
        // 3. Nếu đụng, phải xoay ngược lại 3 lần (tương đương 270 độ) 
        // để đưa nó về vị trí cũ (Undo rotation).
        currentPiece->rotate();
        currentPiece->rotate();
        currentPiece->rotate();
    }
}
int main()
{
    srand(time(0));
    b = rand() % 7;
    system("cls");
    initBoard();

    while (1) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'x' && canMove(0, 1))  y++;
            if (c == 'q') break;
        }

        if (canMove(0, 1)) y++;
        else {
            block2Board();
            removeLine(); // Chạy hàm của SV2
            x = 5; y = 0; b = rand() % 7;
        }

        block2Board();
        draw();

        // Tốc độ được giữ nguyên ở mức 200ms ban đầu (chưa có code SV5)
        _sleep(200);
    }
    return 0;
}
