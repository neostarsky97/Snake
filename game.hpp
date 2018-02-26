#include<time.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<iostream>

using namespace std;

class fruct{
	public:
		int x, y;





		void gen() {
			srand(time(NULL));
			x = rand() % VM_N;
			y = rand() % VM_M;

			for(int i = 0; i < sh; i++)
				if(s[i].x == x && s[i].y == y)
					gen();
		}



		void draw() {
			glColor3f(1, 0, 0);
			glRecti(x * VM_Scale - 1, y * VM_Scale, (x + 1) * VM_Scale, (y + 1) * VM_Scale + 1);
		}
};











class game {
	public:
		void over() {
			std::ofstream RO("save.snk");

			RO << myMX;

			RO.close();


			exit(0);
		}



		void drawField() {

			glColor3f(1,1,1);
			glBegin(GL_LINES);
				glVertex2i(0, VD_H+2);
				glVertex2i(VD_W,VD_H+2);
			glEnd();

			/*glColor3f(0, 0, 0);

			glBegin(GL_LINES);
				for(int i = 0; i < VM_N; i++) {
					glVertex2i(i * VM_Scale, 0);	glVertex2i(i * VM_Scale, VD_H);
				}
				for(int i = 0; i < VM_M-3; i++) {
					glVertex2i(0, i * VM_Scale);	glVertex2i(VD_W, i * VM_Scale);
				}
			glEnd();*/

		}

		/*void drawText(char *string1) {
			char *c;
			glRasterPos2d(12, (VD_H+25));
			for (c = string1; *c; c++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			}

		}*/




		void drawSnake() {
			glColor3f(1, 1, 0);
			glRecti(s[0].x * VM_Scale - 1, s[0].y * VM_Scale, (s[0].x + 1) * VM_Scale, (s[0].y + 1) * VM_Scale + 1);

			glColor3f(1, 0, 1);
			for(int i = 1; i < sh; i++)
				glRecti(s[i].x * VM_Scale - 1, s[i].y * VM_Scale, (s[i].x + 1) * VM_Scale, (s[i].y + 1) * VM_Scale + 1);
		}

		void drawCounter() {
			//glColor3f(1,1,1);
			//glRasterPos2d(13*VM_Scale, VD_H+25);
			char str[10] = "Score: ";
			//for(char *c = str; *c; c++) {
			//	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			//}
			char number[10];
			sprintf(number, "%d", score);
            strcat(str, number );
            glColor3f(1,1,1);
            glPushMatrix();
            int len, i;
            //glTranslatef(x,y,0);
            //glScalef(0.0015f, 0.0015f, 1);
            glRasterPos2f(13*VM_Scale,VD_H+28);
            len=(int) strlen(str);
            for(i = 0; i < len; i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
                //glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);

            }
            glPopMatrix();
			//itoa(score, number, 10);
			//for(char *c = str; *c; c++) {
				//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);

		}

		static void keyboard(int key, int a, int b) {
			switch(key) {
				case 101:
					if(dir != 3)
						dir = 1;
				break;

				case 102:
					if(dir != 4)
						dir = 2;
				break;

				case 103:
					if(dir != 1)
						dir = 3;
				break;

				case 100:
					if(dir != 2)
						dir = 4;
				break;
			}
		}
};
