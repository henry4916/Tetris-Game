// piece.cpp

#include "Piece.h"

Piece::Piece() {
	Piece(0);
}

// �]�w�s���_�ۨíק��C��A�ñNrotation�]�w��0�A�ت������ͻP��v���n�D���@�˪���l�S����ʹL���Ϥ�
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

// ��^�@���_��
const int* Piece::rotations() {
	return gamePieces[type][rotation];
}

// �����_�۪��A�A�۷�����
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
