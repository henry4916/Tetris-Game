// main.cpp

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <time.h>

#include "glew.h"
#include "glut.h"
#include "Game.h"

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>

using namespace std;

// 正方形大小為 20 x 20 像素
const int BLOCKSIZE = 20;
const int VPWIDTH = COLS * BLOCKSIZE;
const int VPHEIGHT = ROWS * BLOCKSIZE;


Game game;
GLvoid* font_style = GLUT_BITMAP_TIMES_ROMAN_24;

// Displaying text on the screen
void BitmapText(char *str, int wcx, int wcy)
{
	glRasterPos2i(wcx, wcy);
	for (int i=0; str[i] != '\0'; i++) {
		//字形設定
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
	}
}

// 獲取區間 [0, 1] 中的隨機數
double random()
{ 
	int r = rand();
	return double(r) / RAND_MAX;
}

// Callback function, timer
void timer(int id)
{
	// 如果gameover
	if (game.killed) {

		game.paused = true;
		//glutTimerFunc(200, timer, id);
		game.clearMainGrid();
		game.clearNextPieceGrid();
		glutPostRedisplay();

	// 如果遊戲繼續並且沒有暫停
	} else if (!game.paused) {	
		game.update();		
		if (game.killed) {
			glutTimerFunc(10, timer, 1);
		} else {
			glutPostRedisplay();
			glutTimerFunc(game.timer, timer, 0);
		}
	}
}

// entet(重新開始), p & Esc(遊戲暫停) 與 鍵盤下鍵(寶石加速） 的功能設定
void keyboard(unsigned char key, int x, int y)
{
	// 如果gameover按 enter 可以重新開始
	if (game.paused && game.killed) 
	{
		// 13 == ENTER
		if (key == 13) { 
			game.killed = false;
			game.restart();
			glutTimerFunc(game.timer, timer, 0);
		}
	}
	else 
	{
		// 按 p 可以使遊戲暫停
		// 27 == Esc
		if (key == 'p' || key == 27)
		{ 
			game.paused = !game.paused;
			if (!game.paused)
				glutTimerFunc(game.timer, timer, 0);
		}
		// 按鍵 z 順時針旋轉
		else if (!game.paused && !game.killed && key == 'Z' || key == 'z')
		{
			game.rotateShape(-1);
			glutPostRedisplay();
		}
		// 按鍵 x 逆時針旋轉
		else if (!game.paused && !game.killed && key == 'x' || key == 'X')
		{
			game.rotateShape(1);
			glutPostRedisplay();
		}
	}
	// 使用glutPostRedisplay繪圖功能會使寶石掉落速度變慢
	glutPostRedisplay();
}

//設定按鍵左右下的移動功能
int temp_start = 0;
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		
		if (temp_start == 0)
		{
			game.restart();
			temp_start = 1;
		}
		game.start_flag = 1;
		
	}
	// 如果遊戲沒有gameover
	if (!game.paused && !game.killed) 
	{
		// 按鍵左讓寶石向左邊移動
		if (key == GLUT_KEY_LEFT) 
		{
			game.move(-1);
			glutPostRedisplay();
		} 
		// 按鍵右讓寶石向右邊移動
		else if (key == GLUT_KEY_RIGHT) 
		{
			game.move(1);
			glutPostRedisplay();
		} 
		// 按鍵下鍵讓寶石加速往下
		else if (key == GLUT_KEY_DOWN)
		{
			game.update();
		} 
	}
	// 使用glutPostRedisplay繪圖功能會使寶石掉落速度變慢
	glutPostRedisplay();
}

// 回調函數，顯示遊戲窗口
void display(void)
{
	const int N = 100;
	char msg[N + 1];

	// 設定底色
	glClearColor(0.5f, 0.5f, 0.5f, 0.72);
	
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Grid
	glViewport(1, 1, VPWIDTH, VPHEIGHT);
	glMatrixMode(GL_PROJECTION);

	

	//如果遊戲處於活動狀態，則進行棋子的移動
	if (!game.paused && game.start_flag) {

		glLoadIdentity();
		gluOrtho2D(0, COLS, ROWS, 0);
		
		//r c控制左圖坐標
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				Square& square = game.mainGrid[r][c];
				if (square.isFilled) {
					glColor3f(square.red, square.green, square.blue);
					glRectd(c + .1, r + .1, c + .9, r + .9);
				}
				else {
					glColor3f(0.9, 0.9, 0.9);
					glRectd(c, r, c + 1, r + 1);
				}
			}
		}
	}
	else {

		glLoadIdentity();
		gluOrtho2D(0, VPWIDTH, 0, VPHEIGHT);


		if (game.start_flag == 0)
		{
			glColor3f(0.1, 0.1, 0.1);
			sprintf_s(msg, N, "Press the button UP to start the game");
			BitmapText(msg, 60, VPHEIGHT / 2+100);
		}

		if (game.paused && !game.killed) {		
			glColor3f(0.1, 0.1, 0.1);
			sprintf_s(msg, N, "GAME PAUSED");
			BitmapText(msg, 140, VPHEIGHT/2);
		}
		if (game.paused && game.killed) {		
			glColor3f(0.1, 0.1, 0.1);
			sprintf_s(msg, N, "GAME OVER");
			BitmapText(msg,  155, VPHEIGHT/2 + 50);
			sprintf_s(msg, N, "YOUR SCORE: %d", game.linesCleared);
			BitmapText(msg,  140, VPHEIGHT/2-50);
			sprintf_s(msg, N, "Press [ENTER] to restart ...");
			BitmapText(msg, 75, VPHEIGHT/2+30 - 100);
		}
	}

	// 垂直分隔條
	glViewport(VPWIDTH, 0, VPWIDTH, VPHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, VPWIDTH, 0, VPHEIGHT);

	glBegin(GL_LINES);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2d(1, 0);
	glVertex2d(1, glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();

	// 視窗右側的消息
	glLoadIdentity();
	gluOrtho2D(0, VPWIDTH, 0, VPHEIGHT);

	glColor3f(0.1, 0.1, 0.1);
	sprintf_s(msg, N, "Level: %d", game.level);
	BitmapText(msg, 20, 100);
	sprintf_s(msg, N, "Score: %d", game.linesCleared);
	BitmapText(msg, 20, 50);
	//sprintf_s(msg, N, "Next Shape:");
	//BitmapText(msg, 50, VPHEIGHT - 50);

	// 垂直分隔條
	/*
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2d(1,0);
		glVertex2d(1, glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();
	*/

	// 網格顯示下一塊
	glViewport(VPWIDTH + 70, -100, VPWIDTH, VPHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, COLS, ROWS, 0);
	
	for (int r = 1; r < 5; r++) 
	{
		for (int c = 0; c < 3; c++) 
		{
			Square& square = game.nextPieceGrid[r][c];
			if (square.isFilled) 
			{
				glColor3f(square.red, square.green, square.blue);
				glRectd(c + .1, r + .1, c + .9, r + .9);
			}
			else 
			{
				glColor3f(0.9, 0.9, 0.9);

				glRectd(c, r, c + 1, r + 1);
			}
		}
	}

	glutSwapBuffers();
}

void main(int argc, char *argv[])
{
	//初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowPosition(100, 100);

	// 設定WindowSize  column與row在Game.h可以調整
	glutInitWindowSize(VPWIDTH*2, VPHEIGHT);

	//設定視窗顯示名稱
	glutCreateWindow("Tetris");

	glutDisplayFunc(display);

	//設定鍵盤功能
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	//更新畫面讓寶石往下掉
	glutTimerFunc(game.timer, timer, 0);

	//讓所有與事件有關的函式調用無限循環
	glutMainLoop();
}
