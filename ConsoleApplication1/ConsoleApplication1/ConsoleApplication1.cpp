#include <iostream>
using namespace std;

const int HEIGHT = 20;
const int WIDTH = 10;

int board[HEIGHT][WIDTH];
int score = 0;

void initBoard() {

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard() {

    for (int i = 0; i < HEIGHT; i++) {

        for (int j = 0; j < WIDTH; j++) {

            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << "# ";
        }

        cout << endl;
    }

    cout << "\nScore: " << score << endl;
}

void removeLine() {
    // Chỉ chạy từ H-2 vì H-1 là viền đáy '#'
    for (int i = H - 2; i >= 0; i--) {
        bool full = true;

        // Bỏ qua cột 0 và W-1 vì nó là viền '#'
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') { // Nếu có khoảng trắng là chưa đầy
                full = false;
                break;
            }
        }

        // Nếu hàng đầy (không có khoảng trắng)
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
            
            // TODO: Kết hợp với biến lineCount của SV5 ở đây
            // lineCount++;

            // Kiểm tra lại dòng hiện tại (i) sau khi đã kéo xuống
            i++; 
        }
    }
}
void createTestData() {

    // dòng đầy
    for (int j = 0; j < WIDTH; j++) {
        board[19][j] = 1;
    }

    // block khác
    board[18][2] = 1;
    board[18][3] = 1;
    board[17][5] = 1;
}

int main() {

    initBoard();

    createTestData();

    cout << "Before removeLine:\n\n";
    printBoard();

    removeLine();

    cout << "\nAfter removeLine:\n\n";
    printBoard();

    return 0;
}
