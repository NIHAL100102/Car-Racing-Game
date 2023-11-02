

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glut.h>

const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_9_BY_15;

time_t t;

//track level
int level = 0;

//Track Score
int score = 0;

//Game Speed
int speed = 50;
int start = 0;
int show = 0;
int day = 1;

//move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//For the car to move left or right
int lrIndex = 0;

int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;


char s[30];

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}




void tree(int x, int y)
{
	float x1 = x;
	float y1 = y;

	//Bark of tree
	glColor3f(0.36, 0.25, 0.20);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1 + 11, y1 + 55);
	glVertex2f(x1 + 12, y1 + 45);
	glVertex2f(x1 + 10, y1 + 45);
	glEnd();

	//tree branch
	glColor3f(0.5, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1 + 11, y1 + 58);
	glVertex2f(x1 + 15, y1 + 52);
	glVertex2f(x1 + 7, y1 + 52);
	glEnd();
}



void startGame()
{

	tree(85, 30);
	tree(2, 15);
	tree(665, 5);

	//Road
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	// Left Border
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(23, 100);
	glVertex2f(23, 0);
	glEnd();

	// Right Border
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(77, 0);
	glVertex2f(77, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivTop + 80);
	glVertex2f(48, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 80);
	glEnd();

	roadDivTop--;

	//Middle
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivMdl + 40);
	glVertex2f(48, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 40);
	glEnd();



	roadDivMdl--;

	//Bottom
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivBtm + 0);
	glVertex2f(48, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 0);
	glEnd();
	roadDivBtm--;


	if (roadDivBtm < -20) {
		roadDivBtm = 100;
		score++;
	}

	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(80, 97);
	glVertex2f(100, 97);
	glVertex2f(100, 98 - 8);
	glVertex2f(80, 98 - 8);
	glEnd();

	//Print Score
	char buffer[50];

	sprintf(buffer,"SCORE:%d", score);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(102.5, 95, GLUT_BITMAP_TIMES_ROMAN_24, buffer);


	//Speed Print
	char buffer1[50];
	sprintf(buffer1, "SPEED:%dKm/h", speed);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(.5, 95 - 2, GLUT_BITMAP_TIMES_ROMAN_24, buffer1);

	//level Print
	if (score % 20 == 0) {
		int last = score / 20;
		if (last != level) {
			level = score / 20;
			speed = speed + 2;
		}
	}

	char level_buffer[50];
	sprintf(level_buffer, "LEVEL: %d", level);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(80.5, 95 - 4, (void*)font3, level_buffer);


	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 5);
	glVertex2f(lrIndex + 26 - 2, 7);
	glVertex2f(lrIndex + 30 + 2, 7);
	glVertex2f(lrIndex + 30 + 2, 5);
	glEnd();
	//Back Tire
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 1);
	glVertex2f(lrIndex + 26 - 2, 3);
	glVertex2f(lrIndex + 30 + 2, 3);
	glVertex2f(lrIndex + 30 + 2, 1);
	glEnd();

	//Car Body
	glColor3f(0.9, 0.1, 0.3);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26, 1);
	glVertex2f(lrIndex + 26, 8);
	glColor3f(0.000, 0.545, 0.545);

	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 30, 8);
	glVertex2f(lrIndex + 30, 1);
	glEnd();


	//COmputer operated car 1
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 4);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 6);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 6);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 4);
	glEnd();

	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 2);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 2);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100);
	glEnd();

	glColor3f(1.000, 0.000, 0.350);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26, car1 + 100);
	glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
	glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
	glColor3f(0.500, 0.545, 0.545);
	glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
	glVertex2f(lrIndex1 + 30, car1 + 100);
	glEnd();

	car1--;
	if (car1 < -100) {
		car1 = 0;
		lrIndex1 = lrIndex;
	}

	if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10)) {
		start = 0;
		show = 1;

	}

	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 4);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 6);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 6);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 4);
	glEnd();

	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 2);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 2);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100);
	glEnd();

	glColor3f(1.294, 0.000, 1.510);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26, car2 + 100);
	glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
	glVertex2f(lrIndex2 + 28, car2 + 100 - 9);
	glColor3f(0.500, 0.545, 0.545);
	glVertex2f(lrIndex2 + 30, car2 + 100 - 7);
	glVertex2f(lrIndex2 + 30, car2 + 100);
	glEnd();

	car2--;
	if (car2 < -100) {
		car2 = 0;
		lrIndex2 = lrIndex;
	}
	//check car2 for collision
	if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10)) {
		start = 0;
		show = 1;
	}


	//Computer operated car 3
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
	glEnd();

	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
	glEnd();

	glColor3f(1.000, 1.271, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26, car3 + 100);
	glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
	glColor3f(0.500, 0.545, 0.545);
	glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
	glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
	glVertex2f(lrIndex3 + 30, car3 + 100);
	glEnd();

	car3--;
	if (car3 < -100) {
		car3 = 0;
		lrIndex3 = lrIndex;
	}
	// check car3 for collision
	if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10)) {
		start = 0;
		show = 1;
	}
}

//home page  -- Scene2
void home()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Sky
	glColor3f(0.000, 0.8, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glColor3f(0.686, 0.933, 0.933);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glEnd();


	//Hills
	//back side hills
	glColor3f(0.50, 0.30, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(20, 55 + 10);
	glVertex2f(20 + 7, 55);
	glVertex2f(0, 55);
	glEnd();

	glColor3f(0.50, 0.30, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(87, 55 + 10);
	glVertex2f(100, 55);
	glVertex2f(60, 55);
	glEnd();



	glColor3f(0.36, 0.25, 0.20);
	glBegin(GL_TRIANGLES);
	glVertex2f(35, 67);
	glVertex2f(51, 55);
	glVertex2f(10, 55);
	glEnd();

	glColor3f(0.36, 0.25, 0.20);
	glBegin(GL_TRIANGLES);
	glVertex2f(70, 70);
	glVertex2f(90, 55);
	glVertex2f(51, 55);
	glEnd();

	//sun
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(43, 61);
	glVertex2f(59, 61);
	glVertex2f(51, 55);
	glEnd();

	// sun rays
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(44, 61);
	glVertex2f(42, 66);
	glVertex2f(46, 61);
	glVertex2f(44, 66);
	glVertex2f(48, 61);
	glVertex2f(46, 66);
	glVertex2f(48, 66);
	glVertex2f(50, 61);
	glVertex2f(52, 61);
	glVertex2f(54, 66);
	glVertex2f(54, 61);
	glVertex2f(56, 66);
	glVertex2f(56, 61);
	glVertex2f(58, 66);
	glEnd();





	tree(-5, 1);
	tree(15, -15);



	//roof

	glColor3f(0.1, 0.1, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(50, 50);
	glVertex2i(90, 50);
	glVertex2i(100, 35);
	glVertex2i(60, 35);
	glEnd();


	// Top wall
	glColor3f(0.52, 0.39, 0.39);
	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(40, 35);
	glVertex2i(60, 35);
	glEnd();


	// Front Wall
	glColor3f(0.7, 0.2, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(40, 35);
	glVertex2i(60, 35);
	glVertex2i(60, 10);
	glVertex2i(40, 10);
	glEnd();

	//  Door
	glColor3f(0.7, 0.2, 0.9);
	glBegin(GL_POLYGON);
	glVertex2i(45, 25);
	glVertex2i(50, 25);
	glVertex2i(50, 10);
	glVertex2i(45, 10);
	glEnd();


	// Door Lock
	glColor3f(0.3, 0.7, 0.9);
	glPointSize(15);
	glBegin(GL_POINTS);
	glVertex2i(45, 20);
	glEnd();


	//side Wall

	glColor3f(0.1, 0.2, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(60, 35);
	glVertex2i(100, 35);
	glVertex2i(100, 10);
	glVertex2i(60, 10);
	glEnd();

	// window

	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(61, 30);
	glVertex2i(71, 30);
	glVertex2i(71, 25);
	glVertex2i(61, 25);
	glEnd();


	glColor3f(0.1, 0.7, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(68, 30);
	glVertex2i(68, 25);
	glVertex2i(64, 30);
	glVertex2i(64, 25);
	glEnd();

	// window two

	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(81, 30);
	glVertex2i(91, 30);
	glVertex2i(91, 25);
	glVertex2i(81, 25);
	glEnd();


	glColor3f(0.1, 0.7, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(84, 30);
	glVertex2i(88, 30);
	glVertex2i(88, 25);
	glVertex2i(84, 25);
	glEnd();


	// Path
	glColor3f(0.3, 0.5, 0.7);
	glLineWidth(3);
	glBegin(GL_POLYGON);
	glVertex2i(45, 10);
	glVertex2i(55, 10);
	glVertex2i(50, 0);
	glVertex2i(35, 0);
	glEnd();


	//car
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2i(7, 18);
	glVertex2i(7, 20);
	glVertex2i(18, 18);
	glVertex2i(18, 20);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2i(7, 11);
	glVertex2i(7, 13);
	glVertex2i(18, 13);
	glVertex2i(18, 11);
	glEnd();

	//body
	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(8, 12);
	glVertex2i(17, 12);
	glVertex2i(15, 10);
	glVertex2i(10, 10);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(8, 12);
	glVertex2i(8, 19);
	glVertex2i(17, 19);
	glVertex2i(17, 12);
	glEnd();

	glColor3f(0.2, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2i(8, 19);
	glVertex2i(10, 21);
	glVertex2i(15, 21);
	glVertex2i(17, 19);
	glEnd();

	glColor3f(1, 0, 1);
	renderBitmapString(45, 85, (void*)font1, "Adding Fun to your Life.");

	glColor3f(0, 0, 1);
	renderBitmapString(45, 80, (void*)font3, "Coz you are a gamer.");



	glColor3f(1.0, 1.0, 0.6);
	renderBitmapString(70, 15, (void*)font1, "PRESS Y TO CONTINUE");

	glutPostRedisplay();
	glutSwapBuffers();

}

//Instructions page -- Scene 3
void initialDesign()
{
	//Side track
	glColor3f(0, 0.305, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glColor3f(0.7, 0.804, 0.3);
	glVertex2f(100, 50 - 50);
	glVertex2f(0, 50 - 50);
	glEnd();


	//Road
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(51, 55);
	glVertex2f(90, 0);
	glVertex2f(10, 0);
	glEnd();

	//divider
	glColor3f(0.658824, 0.658824, 0.658824);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(50 + 2, 50 - 50);
	glVertex2f(50 - 2, 50 - 50);
	glEnd();

	if (day == 1) {
		// Sky -- Sunny day
		glColor3f(0.000, 0.8, 1.000);
		glBegin(GL_POLYGON);
		glVertex2f(100, 100);
		glVertex2f(0, 100);
		//glColor3f(0.686, 0.933, 0.933);
		glVertex2f(0, 55);
		glVertex2f(100, 55);
		glEnd();
	}
	else if (day == 2) {
		// Sky -- Cloudy day
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(100, 100);
		glVertex2f(0, 100);
		glColor3f(0.686, 0.933, 0.933);
		glVertex2f(0, 55);
		glVertex2f(100, 55);
		glEnd();

	}
	else {
		// Sky -- Night
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(100, 100);
		glVertex2f(0, 100);
		//glColor3f(0.686, 0.933, 0.933);
		glVertex2f(0, 55);
		glVertex2f(100, 55);
		glEnd();
	}


	glColor3f(0.235, 0.702, 0.443);
	glBegin(GL_TRIANGLES);
	glVertex2f(20, 55 + 10);
	glVertex2f(20 + 7, 55);
	glVertex2f(0, 55);
	glEnd();

	//hill4
	glColor3f(0.235, 0.702, 0.443);
	glBegin(GL_TRIANGLES);
	glVertex2f(87, 55 + 10);
	glVertex2f(100, 55);
	glVertex2f(60, 55);
	glEnd();


	//front side hills-2
	glColor3f(0.000, 0.502, 0.000);
	glBegin(GL_TRIANGLES);
	glVertex2f(35, 67);
	glVertex2f(51, 55);
	glVertex2f(10, 55);
	glEnd();

	glColor3f(0.000, 0.502, 0.000);
	glBegin(GL_TRIANGLES);
	glVertex2f(70, 70);
	glVertex2f(90, 55);
	glVertex2f(51, 55);
	glEnd();


	tree(15, -15);
	tree(70, 5);
	//tree(75, -15);
	//tree(10, -5);
	tree(665, 5);
	tree(65, -15);




	//menuholder
	glColor3f(0.255, 0.160, 0.122);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	glColor3f(00, 0, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 4 + 10);
	glVertex2f(32 - 4, 50 + 4 + 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(32 + 45, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 + 45, 50 - 15 + 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	if (show == 1) {


		glColor3f(1.000, 0.000, 1.000);

		renderBitmapString(45, 85, (void*)font1, "GAME OVER!!!!");
		glColor3f(1.000, 0.000, 0.000);
		char buffer2[50];
		sprintf(buffer2, "Your Score is : %d", score);
		renderBitmapString(45, 70, (void*)font1, buffer2);
	}
	else {
		glColor3f(0.435294, 0.258824, 0.258824);
		renderBitmapString(45, 85, (void*)font1, "Bored? How about playing?");
	}

	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(40, 50 + 10, (void*)font2, "Press SPACE to START");
	renderBitmapString(40, 50 - 3 + 10, (void*)font2, "Press ESC to EXIT");



	glColor3f(1.000, 1.000, 1.000);
	renderBitmapString(40, 50 - 6 + 10, (void*)font3, "Press UP to increase Speed");
	renderBitmapString(40, 50 - 8 + 10, (void*)font3, "Press DOWN to decrease Speed");
	renderBitmapString(40, 50 - 10 + 10, (void*)font3, "Press RIGHT to turn Right");
	renderBitmapString(40, 50 - 12 + 10, (void*)font3, "Press LEFT to turn Left");
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (start == 1)
	{
		startGame();

	}
	else
		initialDesign();

	glFlush();
	glutSwapBuffers();
}


void welcomeDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tree(-6, -15);
	//tree(15, -15);
	tree(85, 30);
	//tree(2, 15);
	tree(65, 5);

	glColor3f(0.53, 0.12, 0.47);

	renderBitmapString(35, 80, (void*)font1, "2D CAR RACING GAME");

	glColor3f(0.1, 0.2, 0.3);
	renderBitmapString(10, 60, (void*)font2, "Submitted By:");

	glColor3f(0.1, 0.2, 0.1);
	renderBitmapString(20, 50, (void*)font2, "Name:");

	glColor3f(0.55, 0.09, 0.09);
	renderBitmapString(25, 50, (void*)font3, "Pinto Priya   Nihal");

	glColor3f(0.1, 0.2, 0.1);
	renderBitmapString(20, 44, (void*)font2, "USN:");

	glColor3f(0.55, 0.09, 0.09);
	renderBitmapString(30, 44, (void*)font3, "4SO20CS101    4SO20CS097");

	glColor3f(0.4, 0.2, 0.4);
	renderBitmapString(30, 30, (void*)font2, "ENJOY GAMING!!!");

	glColor3f(0.8, 0.196078, 0.6);
	renderBitmapString(60, 10, (void*)font1, "PRESS X TO CONTINUE");


	glutSwapBuffers();
}


void spe_key(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_DOWN:   // to decrease speed
		speed = speed - 2;
		break;

	case GLUT_KEY_UP:   //to increase speed
		speed = speed + 2;
		break;

	case GLUT_KEY_LEFT:   // move car to left
		if (lrIndex >= 0) {
			lrIndex = lrIndex - (speed / 10);
			if (lrIndex < 0) {
				lrIndex = -1;
			}
		}
		break;


	case GLUT_KEY_RIGHT:  //move car to right
		if (lrIndex <= 44) {
			lrIndex = lrIndex + (speed / 10);
			if (lrIndex > 44) {
				lrIndex = 45;
			}
		}
		break;

	default:
		break;
	}

}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':glutDisplayFunc(home);
		glutPostRedisplay();
		break;

	case 'y':glutDisplayFunc(display);
		break;
	case ' ':
		if (start == 0) {
			start = 1;
			show = 0;
			speed = 50;
			roadDivTopMost = 0;
			roadDivTop = 0;
			roadDivMdl = 0;
			roadDivBtm = 0;
			lrIndex = 0;
			car1 = 0;
			lrIndex1 = 0;
			car2 = +35;
			lrIndex2 = 0;
			car3 = +70;
			lrIndex3 = 0;
		}
		break;

	case 'd':    //day mode
	case 'D':
		day = 1;
		break;

	case 'n':    //night mode
	case 'N':
		day = 0;
		break;

	case 'c':  //cloudy mode
	case 'C':
		day = 2;
		break;



	case 27:   //exit
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();

}

//For movement of the car
void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / speed, timer, 0);
}

int main(int argc, char* argv[])
{
	srand(1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1200, 1200);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D Car Game");
	glutDisplayFunc(welcomeDisplay);
	glutSpecialFunc(spe_key);
	glutKeyboardFunc(keys);
	glOrtho(0, 100, 0, 100, -1, 1);
	glClearColor(1.0, 1.0, 0.6, 1);
	glutTimerFunc(1000, timer, 0);
	glutMainLoop();
	return 0;

}
