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

    for (int i = HEIGHT - 1; i >= 0; i--) {

        bool full = true;

        // kiểm tra dòng đầy
        for (int j = 0; j < WIDTH; j++) {

            if (board[i][j] == 0) {
                full = false;
                break;
            }
        }

        // nếu đầy
        if (full) {

            // kéo xuống
            for (int k = i; k > 0; k--) {

                for (int j = 0; j < WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }

            // dòng đầu = rỗng
            for (int j = 0; j < WIDTH; j++) {
                board[0][j] = 0;
            }

            score += 100;

            // kiểm tra lại dòng hiện tại
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