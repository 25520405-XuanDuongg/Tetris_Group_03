#pragma once
#include <iostream>
using namespace std;
const int PIECE_SIZE = 4;

class Piece {
protected:
    char shape[PIECE_SIZE][PIECE_SIZE];
    int posX, posY; 

public:
    Piece(int startX, int startY) : posX(startX), posY(startY) {
        for (int i = 0; i < PIECE_SIZE; ++i) {
            for (int j = 0; j < PIECE_SIZE; ++j) {
                shape[i][j] = '.';
            }
        }
    }

    virtual ~Piece() {}

    // Class con nào có cách xoay đặc biệt (như khối O, khối I) sẽ tự ghi đè (override) lại logic này.
    virtual void rotate();

    // Hàm phụ trợ cho Thành viên 2 dễ làm việc
    char getCell(int r, int c) const { return shape[r][c]; }
    void setCell(int r, int c, char val) { shape[r][c] = val; }
};

// --- ĐỊNH NGHĨA CÁC CLASS CON ---

// Khối O (Hình vuông)
class OPiece : public Piece {
public:
    OPiece(int startX, int startY);
    void rotate() override; // Ghi đè vì khối vuông xoay kiểu gì cũng không đổi
};

// Khối T
class TPiece : public Piece {
public:
    TPiece(int startX, int startY);
    // Khối T có thể dùng logic rotate() mặc định của class cha, hoặc override nếu muốn xoay theo hệ toạ độ riêng
    void rotate() override;
};

// (Khai báo tương tự cho IPiece, JPiece, LPiece, SPiece, ZPiece...)
// Khối I (Đường thẳng)
class IPiece : public Piece {
private:
    bool isVertical; // Trạng thái để xử lý xoay riêng cho khối I
public:
    IPiece(int startX, int startY);
    void rotate() override; // Ghi đè để xoay khối I mượt hơn, không bị lệch tâm
};

// Khối J
class JPiece : public Piece {
public:
    JPiece(int startX, int startY);
    void rotate() override { Piece::rotate(); }
};

// Khối L
class LPiece : public Piece {
public:
    LPiece(int startX, int startY);
    void rotate() override { Piece::rotate(); }
};

// Khối S
class SPiece : public Piece {
public:
    SPiece(int startX, int startY);
    void rotate() override { Piece::rotate(); }
};

// Khối Z
class ZPiece : public Piece {
public:
    ZPiece(int startX, int startY);
    void rotate() override { Piece::rotate(); }
};