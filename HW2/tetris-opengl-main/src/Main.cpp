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

// ����Τj�p�� 20 x 20 ����
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
		//�r�γ]�w
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
	}
}

// ����϶� [0, 1] �����H����
double random()
{ 
	int r = rand();
	return double(r) / RAND_MAX;
}

// Callback function, timer
void timer(int id)
{
	// �p�Ggameover
	if (game.killed) {

		game.paused = true;
		//glutTimerFunc(200, timer, id);
		game.clearMainGrid();
		game.clearNextPieceGrid();
		glutPostRedisplay();

	// �p�G�C���~��åB�S���Ȱ�
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

// entet(���s�}�l), p & Esc(�C���Ȱ�) �P ��L�U��(�_�ۥ[�t�^ ���\��]�w
void keyboard(unsigned char key, int x, int y)
{
	// �p�Ggameover�� enter �i�H���s�}�l
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
		// �� p �i�H�ϹC���Ȱ�
		// 27 == Esc
		if (key == 'p' || key == 27)
		{ 
			game.paused = !game.paused;
			if (!game.paused)
				glutTimerFunc(game.timer, timer, 0);
		}
		// ���� z ���ɰw����
		else if (!game.paused && !game.killed && key == 'Z' || key == 'z')
		{
			game.rotateShape(-1);
			glutPostRedisplay();
		}
		// ���� x �f�ɰw����
		else if (!game.paused && !game.killed && key == 'x' || key == 'X')
		{
			game.rotateShape(1);
			glutPostRedisplay();
		}
	}
	// �ϥ�glutPostRedisplayø�ϥ\��|���_�۱����t���ܺC
	glutPostRedisplay();
}

//�]�w���䥪�k�U�����ʥ\��
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
	// �p�G�C���S��gameover
	if (!game.paused && !game.killed) 
	{
		// ���䥪���_�ۦV���䲾��
		if (key == GLUT_KEY_LEFT) 
		{
			game.move(-1);
			glutPostRedisplay();
		} 
		// ����k���_�ۦV�k�䲾��
		else if (key == GLUT_KEY_RIGHT) 
		{
			game.move(1);
			glutPostRedisplay();
		} 
		// ����U�����_�ۥ[�t���U
		else if (key == GLUT_KEY_DOWN)
		{
			game.update();
		} 
	}
	// �ϥ�glutPostRedisplayø�ϥ\��|���_�۱����t���ܺC
	glutPostRedisplay();
}

// �^�ը�ơA��ܹC�����f
void display(void)
{
	const int N = 100;
	char msg[N + 1];

	// �]�w����
	glClearColor(0.5f, 0.5f, 0.5f, 0.72);
	
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Grid
	glViewport(1, 1, VPWIDTH, VPHEIGHT);
	glMatrixMode(GL_PROJECTION);

	

	//�p�G�C���B�󬡰ʪ��A�A�h�i��Ѥl������
	if (!game.paused && game.start_flag) {

		glLoadIdentity();
		gluOrtho2D(0, COLS, ROWS, 0);
		
		//r c����ϧ���
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

	// �������j��
	glViewport(VPWIDTH, 0, VPWIDTH, VPHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, VPWIDTH, 0, VPHEIGHT);

	glBegin(GL_LINES);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2d(1, 0);
	glVertex2d(1, glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();

	// �����k��������
	glLoadIdentity();
	gluOrtho2D(0, VPWIDTH, 0, VPHEIGHT);

	glColor3f(0.1, 0.1, 0.1);
	sprintf_s(msg, N, "Level: %d", game.level);
	BitmapText(msg, 20, 100);
	sprintf_s(msg, N, "Score: %d", game.linesCleared);
	BitmapText(msg, 20, 50);
	//sprintf_s(msg, N, "Next Shape:");
	//BitmapText(msg, 50, VPHEIGHT - 50);

	// �������j��
	/*
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2d(1,0);
		glVertex2d(1, glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();
	*/

	// ������ܤU�@��
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
	//��l��
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowPosition(100, 100);

	// �]�wWindowSize  column�Prow�bGame.h�i�H�վ�
	glutInitWindowSize(VPWIDTH*2, VPHEIGHT);

	//�]�w������ܦW��
	glutCreateWindow("Tetris");

	glutDisplayFunc(display);

	//�]�w��L�\��
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	//��s�e�����_�۩��U��
	glutTimerFunc(game.timer, timer, 0);

	//���Ҧ��P�ƥ������禡�եεL���`��
	glutMainLoop();
}
