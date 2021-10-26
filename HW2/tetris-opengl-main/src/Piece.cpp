// piece.cpp

#include "Piece.h"

Piece::Piece() {
	Piece(0);
}

// 設定新的寶石並修改顏色，並將rotation設定為0，目的為產生與投影片要求的一樣的原始沒有轉動過的圖片
Piece::Piece(int numType) {
	type = numType;
	switch (type) {
		case 0:
			redVal = 1.0;
			greenVal = 0.0;
			blueVal = 0.0;
			break;
		case 1: 
			redVal = 0.0;
			greenVal = 0.0;
			blueVal = 1.0;
			break;
		case 2: 
			redVal = 0.0;
			greenVal = 1.0;
			blueVal = 0.0;
			break;
		case 3: 
			redVal = 1.0;
			greenVal = 0.0;
			blueVal = 1.0;
			break;
		case 4: 
			redVal = 0.5;
			greenVal = 1.0;
			blueVal = 0.9;
			break;
		case 5: 
			redVal = 1.0;
			greenVal = 0.0;
			blueVal = 0.5;
			break;
		case 6: 
			redVal = 1.0;
			greenVal = 1.0;
			blueVal = 0.0;
			break;
	}
	rotation = 0;
}

// 返回一個寶石
const int* Piece::rotations() {
	return gamePieces[type][rotation];
}

// 改變寶石狀態，相當於旋轉
void Piece::rotatePiece(int dir) {
	if(dir > 0) {
		if (rotation == 3)
			rotation = 0;
		else
			rotation += dir;
	}
	else {
		if (rotation == 0)
			rotation = 3;
		else
			rotation += dir;
	}
}
