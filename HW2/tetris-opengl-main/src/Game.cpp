// game.cpp  

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "glut.h"
#include "Game.h"

using namespace std;

/*
�C��p�ɾ�����ɽեΡA���C���S�������μȰ�
*/
void Game::update() {
	// Check pieces collision
	if (moveCollision(0)) {					// �p�G�o�͸I��
		if (activePiece.y <= 2) {			// �ˬd���O�_�����C��
			killed = true;
		}
		else {								// �p�G�C�����M���D
			updateActiveAfterCollision();	// �H���T�w�N���I��
			linesCleared_score = linesCleared;
			checkLine();					// �ˬd��R����

			/* 
				���ƭp�� 
				���� mark = 10 * Combo * Combo
				Combo = number of rows disappeared for a single block
			*/
			if (linesCleared - linesCleared_score >=1 )
			{
				// temp�Ψӭp��������ƶq
				int temp_linesCleared = linesCleared - linesCleared_score;
				// ����
				linesCleared += (linesCleared - linesCleared_score) * (linesCleared - linesCleared_score) * 10;
				// �ű�checkLine�|�h�[
				linesCleared -= temp_linesCleared;
			}
				
			/*
			�p�G���ƴ��ɫh���Ŵ��ɳt���ܧ�
			����  the falling speed equals to [1000msec �V(level �V 1) * 100] per grid-square
			*/
			if(linesCleared / 30 >= 1)
				level = linesCleared / 30;
			
			//timer = 1000 - (level - 1) * 100;
			switch (level)
			{
				case 1:
					timer = 900;
					break;
				case 2:
					timer = 750;
					break;
				case 3:
					timer = 600;
					break;
				case 4:
					timer = 400;
					break;
				case 5:
					timer = 200;
					break;
				case 6:
					timer = 100;
					break;
				case 7:
					timer = 80;
					break;
				case 8:
					timer = 50;
					break;
				case 9:
					timer = 20;
					break;
				case 10:
					timer = 10;
					break;
				default:
					break;
			}
				

			// level�̤j��10�A�����h����
			if (level == 10)
				restart();

				
			if (deleteLines)				// �p�G�o�{��Q�R���A
				clearLine();				// ��R���u�Q�R��
			genNextPiece();					// ���ͷspiece

			clearNextPieceGrid();
			updateNextPieceGrid();

			updateActivePiece();			// ���b�C�����椤����s
		}
	}
	else {									// �p�G�S���I���A�o���|����U��
		fixActivePiece();
		activePiece.y++;
		updateActivePiece();
	}
}

/*
�}�l�@�ӷs�C���ê�l�Ʃһݪ�����
*/
void Game::restart()
{
	clearMainGrid();		// Cleaning the main grid
	clearNextPieceGrid();	// Clearing the grid with the next figure
	linesCleared = 0;		// The player's score is zero
	linesCleared_score = 0;
	level = 1;
	shapesCount = 1;		// The counter of pieces per game is equal to one �C�����ɪ��Ѥl�Ƶ���@
	killed = false;
	paused = false;
	deleteLines = false;

	// Generating the current random piece �ͦ���e���H�����q
	activePiece = Piece(rand() % numPieces);
	/*
	�@�~�n�D 
		The starting position of a block is at the middle of the third top row.
		Suppose the width of a row is A, the x coordinate of the center of the new block is either floor[A / 2] or ceiling[A / 2].
	*/
	activePiece.x = COLS/2;
	activePiece.y = 0;
	updateActivePiece();

	// Generating the next piece �ͦ��U�@��
	nextPiece = Piece(rand() % numPieces);
	nextPiece.x = COLS/2;
	nextPiece.y = 0;
	updateNextPieceGrid();
}

/*
Updating the game grid and the correct display of the active figure when falling ��s�C������M�����ɬ��ʤH�������T���
*/
void Game::fixActivePiece() {
	// Determining the data of the current piece by its type and position �q�L�������M��m�T�w��e���_���ƾ�
	const int* trans = activePiece.rotations();
	for(int i = 0; i < 8; i += 2){
		Square &square = mainGrid[activePiece.y + trans[i + 1]][activePiece.x + trans[i]];
		// Setting active and inactive cells �]�m���ʩM�D���ʳ椸��
		square.isFilled = false;
		square.isActive = false;
	}
}

// �Ыطs���_��
void Game::genNextPiece() {
	activePiece = nextPiece;
	nextPiece = Piece(rand() % numPieces);
	nextPiece.x = COLS/2;
	nextPiece.y = 0;
	// Increase the piece counter per game
	shapesCount++;
}

/*
Move the active piece left and right ���k���ʬ��ʶ�
*/
void Game::move(int dir)
{
	if(moveCollision(dir))	// If there is a collision with one of the borders, �p�G�P�䤤�@����ɵo�͸I���A
		return;				// nothing happens �S�o�ͤ����
	fixActivePiece();
	activePiece.x += dir;
	updateActivePiece();
}

/*
Cleaning the main grid 
�M��D�q��
*/
void Game::clearMainGrid()
{
	for (int r=0; r<ROWS; r++) {
		for (int c=0; c<COLS; c++) {
			mainGrid[r][c].isFilled = false;
			mainGrid[r][c].isActive = false;
		}
	}
}

/*
Clearing the grid with the next piece 
�ΤU�@���M������
*/
void Game::clearNextPieceGrid()
{
	for (int r = 0; r < 5; r++) {	
		for (int c = 0; c < 5; c++) {
			nextPieceGrid[r][c].isFilled = false;
			nextPieceGrid[r][c].isActive = false;
		}
	}
}

/*
Updating the position of the active piece with rotation �q�L�����s���ʶ�����m
*/
void Game::updateActivePiece() {
	// Pointer to an array that stores all conversions ���V�s�x�Ҧ��ഫ���Ʋժ����w
	const int* trans = activePiece.rotations();
	for(int i = 0; i < 8; i += 2){
		// Find the active piece in the game grid �b�C�����椤��쬡�ʪ��Ѥl
		Square &square = mainGrid[activePiece.y + trans[i + 1]][activePiece.x + trans[i]];
		// Convert the active piece to filled grid cells �N���ʶ��ഫ����R������椸
		square.isFilled = true;
		square.isActive = true;
		square.red = activePiece.redVal;
		square.green = activePiece.blueVal;
		square.blue = activePiece.greenVal;
	}	
}

/*
Updating the grid with the next piece

�ΤU�@����s����
*/
void Game::updateNextPieceGrid() {
	// Pointer to an array that stores all conversions  ���V�s�x�Ҧ��ഫ���Ʋժ����w
	const int* transNext = nextPiece.rotations();
	for (int i = 0; i < 8; i += 2) {
		// Find the active piece in the game grid �b�C�����椤��쬡�ʪ��Ѥl
		Square& squareNext = nextPieceGrid[nextPiece.y + transNext[i + 1]][nextPiece.x + transNext[i]];
		// Convert the active piece to filled grid cells �N���ʶ��ഫ����R������椸
		squareNext.isFilled = true;
		squareNext.isActive = true;
		squareNext.red = nextPiece.redVal;
		squareNext.green = nextPiece.blueVal;
		squareNext.blue = nextPiece.greenVal;
	}
}

/*
Constructor
*/
Game::Game()
{
	restart();
	timer = 1000;
	level = 1;
	start_flag = 0;
}

/*
Rotate the current piece and check if it can be rotated
�����e�����ˬd���O�_�i�H����
*/
void Game::rotateShape(int dir) {
	// �H�����ͤ@�ӳ]�w���_��
	activePieceCopy = Piece(rand() % numPieces);
	activePieceCopy.x = activePiece.x;
	activePieceCopy.y = activePiece.y;
	activePieceCopy.rotation = activePiece.rotation;
	activePieceCopy.type = activePiece.type;
	activePieceCopy.rotatePiece(dir);
	
	// If the active piece can be rotated, it is rotated and displayed �p�G���ʶ��i�H����A�h��������
	if(canRotate(activePieceCopy)) {
		fixActivePiece();
		activePiece.rotatePiece(dir);
		updateActivePiece();
	}
}

/*
Checking whether a piece can be rotated
�ˬd�u��O�_�i�H����
*/
bool Game::canRotate(Piece activeP) {
	if(rotationCollision()) {
		return false;
	}
	else
		return true;
}

/*
Checking for collisions when rotating a piece
����u����ˬd�I��
*/
bool Game::rotationCollision() {
	int x, y;
	const int* trans = activePieceCopy.rotations();
	for (int i = 0; i < 8; i += 2) {
		x = activePieceCopy.x + trans[i];
		y = activePieceCopy.y + trans[i + 1];

		if (x >= COLS || y >= ROWS || x < 0 || (mainGrid[y][x].isFilled && !mainGrid[y][x].isActive))
			return true;
	}
	return false;
}

/*
Checking for collisions when the piece is moving
��u�󲾰ʮ��ˬd�I��
*/
bool Game::moveCollision(int dir) {
	int x, y;
	const int* trans = activePiece.rotations();
	for (int i = 0; i < 8; i += 2) {
		x = activePiece.x + trans[i];
		y = activePiece.y + trans[i + 1];
		if (dir == 0)
			y += 1;
		else
			x += dir;
		if (x >= COLS || y >= ROWS || x < 0 || (mainGrid[y][x].isFilled && !mainGrid[y][x].isActive))
			return true;
	}
	return false;
}

/*
Updating the location of the active piece after a collision
�I�����s���ʥ󪺦�m
*/
void Game::updateActiveAfterCollision() {
	const int* trans = activePiece.rotations();
	for(int i = 0; i < 8; i += 2){
		Square &square = mainGrid[activePiece.y + trans[i + 1]][activePiece.x + trans[i]];
		square.isActive = false;
	}
}

/*
Checking lines for filling and setting filled lines for deleting 
�ˬd��R��M�]�m�R����R��
*/
void Game::checkLine() {
	int fullRows = 0;
	for (int r=0; r<ROWS; r++) {
		bool fullRow = false;
			for (int c=0; c<COLS; c++) {
				Square &square = mainGrid[r][c];
				if (square.isFilled){
					fullRow = true;
					
				}
				else {
					fullRow = false;
					break;
				}
			}
		if(fullRow) {
			for ( int c =0; c < COLS; c++){
				mainGrid[r][c].toBeDeleted = true;
				//linesCleared_score++;
				
			}
			deleteLines = true;
			linesCleared++;
		}
	}
}

/*
Remove a filled row and move all pieces up one cell down
�R����R����ñN�Ҧ������V�W���ʤ@�ӳ椸��
*/
void Game::clearLine() {
	for (int r = ROWS-1; r > 0; r--){ // Checking each line
		int linesDeleted = 0;
		if (mainGrid[r][0].toBeDeleted){
			for (int r2 = r; r2>0; r2--){ // Move all rows down one cell
				for (int c = 0; c < COLS; c++){
					mainGrid[r2][c].isFilled=mainGrid[r2-1][c].isFilled;
					mainGrid[r2][c].isActive=mainGrid[r2-1][c].isActive;
					mainGrid[r2][c].toBeDeleted=mainGrid[r2-1][c].toBeDeleted;
					mainGrid[r2][c].red=mainGrid[r2-1][c].red;
					mainGrid[r2][c].green=mainGrid[r2-1][c].green;
					mainGrid[r2][c].blue=mainGrid[r2-1][c].blue;
				}
			}
			r++;
		}
	}
	deleteLines = false;

}