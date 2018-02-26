#include <GL/glut.h>

#include <stdlib.h>
#include <fstream>


#include "vars.hpp"
#include "game.hpp"



fruct fru;
game snake;

static int window;

static int gameOver=0;

void gameOverMouseFunc(int, int, int, int);
void backSpaceFunc(int, int, int);
void mouseFunc(int, int, int, int);
void homeMouseFunc(int, int, int, int);
void displayStartWindow();

void display() {
	glClear(GL_COLOR_BUFFER_BIT);


	snake.drawField();

	snake.drawSnake();

	snake.drawCounter();

	fru.draw();

	//snake.drawText("PlayerName");
	//snake.strokeTextTimes("Score :", -0.5,0.55);



	glutSwapBuffers();
}

void firstRecordSetup() {
	std::ifstream RI("save.snk");
	RI >> MX;
	myMX = MX;
}

void firstGameSetup() {
	for(int i = 0; i < sh; i++) {
		s[i].x = VM_N / 2;
		s[i].y = (VM_M + sh) / 2 - i;
	}
    srand(time(0));
	fru.gen();
}

void firstSetup() {
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
}

void drawTextTimes(char* string,float x, float y)
{
	glColor3f(1,1,1);
	glPushMatrix();
	int len, i;
	//glTranslatef(x,y,0);
	//glScalef(0.0015f, 0.0015f, 1);
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for(i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
		//glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);

	}
	glPopMatrix();

}

void strokeTextTimes(char* string,float x, float y)
{
	//glRasterPos2d(17*VM_Scale, VD_H+25);
	glColor3f(1,1,1);
	glPushMatrix();
	int len, i;
	glTranslatef(x,y,0);
	glScalef(0.0010f, 0.0010f, 1);
	//glRasterPos2f(x,y);
	len=(int) strlen(string);
	for(i = 0; i < len; i++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);

	}
	glPopMatrix();
}

void gameOverScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	//glTranslatef(0.0, 0.0, -2.0);
	glColor3f(1,1,1);
	//float bo = -0.1*(maximum/2.0f);
	//borderexit(bo - 0.01, -bo - 0.01,0.0, bo);
	drawTextTimes("GAME OVER",-0.2,0.3);
	char score[10];
	sprintf(score, "%d", sh-5);
	char str[30] = "Your Score is: ";
	strcat(str, score);
	drawTextTimes(str,-0.22,0.07);

	drawTextTimes("Home", -0.09, -0.3);

	drawTextTimes("Exit", -0.06, -0.44);

	glutSwapBuffers();
}

int gameOverWindow()
{
    std::ofstream RO("save.snk");
    RO << myMX;
    RO.close();

    gameOver=1;
	glutDestroyWindow(window);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (VD_W, VD_H+100);
	glutInitWindowPosition (100, 100);
	window=glutCreateWindow("Game Over");

	glutDisplayFunc(gameOverScreen);
	glutIdleFunc(gameOverScreen);
	//glutReshapeFunc(Reshape);
	glutMouseFunc(gameOverMouseFunc);
	glutSpecialFunc(backSpaceFunc);
	glutMainLoop();
	return 0;
}

void highScoreScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	//glTranslatef(0.0, 0.0, -2.0);
	glColor3f(1,1,1);
	drawTextTimes("HIGH SCORE ",-0.2,0.3);
	firstRecordSetup();
	char hscore[10];
	itoa(MX, hscore, 10);
	char str[30] = "High Score is: ";
	strcat(str, hscore);
	drawTextTimes(str,-0.22,0.1);
	drawTextTimes("Home", -0.07, -0.9);
	glutMouseFunc(homeMouseFunc);
	glutSwapBuffers();
}


void stroke() {
	for(int i = sh; i > 0; i--) {
		s[i].x = s[i-1].x;
		s[i].y = s[i-1].y;
	}

	if(dir == 1)
		s[0].y += 1;
	if(dir == 2)
		s[0].x += 1;
	if(dir == 3)
		s[0].y -= 1;
	if(dir == 4)
		s[0].x -= 1;


	if(fru.x == s[0].x && fru.y == s[0].y) {
		sh++;
		fru.gen();
		score++;
		if(sh > MX)
			myMX = score;

		if(step > 1)
			step -= step / 20;
	}

	if(s[0].x < 0 || s[0].x >= VM_N || s[0].y < 0 || s[0].y >= VM_M)
		gameOverWindow();

	for(int i = 1; i < sh; i++)
		if(s[0].x == s[i].x && s[0].y == s[i].y)
			gameOverWindow();
}

void timer(int = 0) {
	display();
	stroke();
	glutTimerFunc(step, timer, 0);
}

void displayStartScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity ();
	//glTranslatef(0.0, 0.0, -2.0);

    glLineWidth(5);
    strokeTextTimes("SNAKE 2D",-0.36,0.55);
    //glLineWidth(2);
   	//glScalef(0.0005f, 0.0005f, 1);
    drawTextTimes("START GAME", -0.2,0.1);
    drawTextTimes("SCORES", -0.11,-0.05);
    drawTextTimes("QUIT", -0.07,-0.2);
    glutSwapBuffers();
}

int highScoreWindow() {
	glutDestroyWindow(window);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (VD_W, VD_H+100);
	glutInitWindowPosition (100, 100);
	window=glutCreateWindow("High Score");

	glutDisplayFunc(highScoreScreen);
	glutIdleFunc(highScoreScreen);
	//glutReshapeFunc(Reshape);
	glutSpecialFunc(backSpaceFunc);
	glutMainLoop();
	return 0;
}

int gameWindow() {
    glutDestroyWindow(window);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (VD_W, VD_H+100);
	glutInitWindowPosition (100, 100);
	window=glutCreateWindow("GAME");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, VD_W, 0, VD_H+100);


	firstSetup();
	firstGameSetup();
	firstRecordSetup();

	glutSpecialFunc(game::keyboard);

	glutTimerFunc(step, timer, 0);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
    return 0;
}
void gameOverMouseFunc(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if( gameOver==1 && x >= 341 && x<= 404 &&  y >= 385 && y <= 410){
            glutDestroyWindow(window);
            displayStartWindow();
        }
        if (gameOver==1 && x >= 350 && x <= 395 && y >= 429 && y <= 453) {
            exit(0);
    	}
    }


}
void homeMouseFunc(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if( gameOver==0 && x >= 348 && x <= 410 && y >= 575 && y <=595) {
            glutDestroyWindow(window);
            displayStartWindow();
        }
    }
}
void mouseFunc(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(x >= 300 && x <= 455 && y >= 260 && y<= 285){
			gameWindow();
		}
    	if (x >= 333 && x <= 425 && y >= 308 && y <= 330) {
    		highScoreWindow();
    	}
    	if (gameOver==0 && x >= 350 && x <=415 && y >=354 && y <=379) {
    		exit(0);
    	}

    }
}


void displayStartWindow() {
    gameOver = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(VD_W, VD_H+100);
	glutInitWindowPosition(100, 100);
	window = glutCreateWindow("XSnake 2D");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutMouseFunc(mouseFunc);
	glutDisplayFunc(displayStartScreen);
	glutIdleFunc(displayStartScreen);
	glutSpecialFunc(backSpaceFunc);
	glutMainLoop();
}

void backSpaceFunc(int key, int x, int y) {
	if (key == GLUT_KEY_HOME) {
		glutDestroyWindow(window);
		displayStartWindow();
	}
	if (key == GLUT_KEY_END) {
        exit(0);
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	displayStartWindow();
	/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(VD_W, VD_H+100);
	glutInitWindowPosition(100, 100);
	window = glutCreateWindow("XSnake 2D");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, VD_W, 0, VD_H+100);


	//firstSetup();
	//firstGameSetup();
	//firstRecordSetup();


	//glutSpecialFunc(game::keyboard);

	glutMouseFunc(mouseFunc);
	glutDisplayFunc(displayStart);
	glutIdleFunc(displayStart);
	//glutTimerFunc(step, timer, 0);


	glutMainLoop();*/

	return 0;
}
