#include "Piece.h"

// Logic xoay mặc định của đa số các khối (Thuật toán quay ma trận 90 độ)
void Piece::rotate() {
    char temp[PIECE_SIZE][PIECE_SIZE];

    // Thuật toán quay 90 độ theo chiều kim đồng hồ: Transpose + Reverse rows
    for (int i = 0; i < PIECE_SIZE; ++i) {
        for (int j = 0; j < PIECE_SIZE; ++j) {
            temp[j][PIECE_SIZE - 1 - i] = shape[i][j];
        }
    }

    // Cập nhật lại shape
    for (int i = 0; i < PIECE_SIZE; ++i) {
        for (int j = 0; j < PIECE_SIZE; ++j) {
            shape[i][j] = temp[i][j];
        }
    }
}

// Cài đặt cho khối O
OPiece::OPiece(int startX, int startY) : Piece(startX, startY) {
    // Vẽ khối hình vuông 2x2
    shape[1][1] = 'O'; shape[1][2] = 'O';
    shape[2][1] = 'O'; shape[2][2] = 'O';
}

void OPiece::rotate() {}

// Cài đặt cho khối T 
TPiece::TPiece(int startX, int startY) : Piece(startX, startY) {
    shape[1][1] = 'T'; shape[1][2] = 'T'; shape[1][3] = 'T';
    shape[2][2] = 'T';
}

void TPiece::rotate() {
    // Gọi hàm xoay mặc định của class cha
    Piece::rotate();
}