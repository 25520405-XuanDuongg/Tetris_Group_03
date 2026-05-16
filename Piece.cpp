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
// --- KHỐI I ---
IPiece::IPiece(int startX, int startY) : Piece(startX, startY), isVertical(true) {
    // Khởi tạo khối I nằm dọc
    shape[0][1] = 'I'; 
    shape[1][1] = 'I'; 
    shape[2][1] = 'I'; 
    shape[3][1] = 'I';
}

// Xoay khối I (Đảo qua lại giữa dọc và ngang để không bị lệch khỏi ma trận)
void IPiece::rotate() {
    // Xóa hình dáng cũ
    for(int i = 0; i < PIECE_SIZE; ++i) {
        for(int j = 0; j < PIECE_SIZE; ++j) {
            shape[i][j] = '.';
        }
    }

    if (isVertical) {
        // Chuyển sang nằm ngang
        shape[1][0] = 'I'; shape[1][1] = 'I'; shape[1][2] = 'I'; shape[1][3] = 'I';
    } else {
        // Chuyển về nằm dọc
        shape[0][1] = 'I'; shape[1][1] = 'I'; shape[2][1] = 'I'; shape[3][1] = 'I';
    }
    isVertical = !isVertical; // Đổi trạng thái
}

// --- KHỐI J ---
JPiece::JPiece(int startX, int startY) : Piece(startX, startY) {
    shape[0][1] = 'J';
    shape[1][1] = 'J';
    shape[2][1] = 'J';
    shape[2][0] = 'J'; // Móc của chữ J
}

// --- KHỐI L ---
LPiece::LPiece(int startX, int startY) : Piece(startX, startY) {
    shape[0][1] = 'L';
    shape[1][1] = 'L';
    shape[2][1] = 'L';
    shape[2][2] = 'L'; // Móc của chữ L
}

// --- KHỐI S ---
SPiece::SPiece(int startX, int startY) : Piece(startX, startY) {
    shape[1][1] = 'S'; shape[1][2] = 'S';
    shape[2][0] = 'S'; shape[2][1] = 'S';
}

// --- KHỐI Z ---
ZPiece::ZPiece(int startX, int startY) : Piece(startX, startY) {
    shape[1][0] = 'Z'; shape[1][1] = 'Z';
    shape[2][1] = 'Z'; shape[2][2] = 'Z';
}