
#include<iostream>
#include<glut.h>

using namespace std;

int house[11][2] = { {100,100},{150,200},{200,100},{100,100},{100,50},{125,50},{125,75},{150,75},{150,50},{200,50},{200,100} };
double angle;
float m, c;
void draw_house() {
	int i;
	glColor3f(1, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (i = 0;i < 10;i++) {
		glVertex2i(house[i][0], house[i][1]);
		glVertex2i(house[i+1][0], house[i+1][1]);
	}
	glEnd();

}

void reflect(){
	glClear(GL_COLOR_BUFFER_BIT);

	draw_house();

	//reflection line
	float x1 = 0, x2 = 500;
	float y1, y2;

	y1 = m * x1 + c;
	y2 = m * x2 + c;
	printf("%f %f\n", y1, m * x2 + c);
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();


	//reflect it
	glPushMatrix();
	glTranslatef(0, c, 0);
	double theta = atan(m);
	theta = theta * 180 / 3.14;
	glRotatef(theta, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, -c, 0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 11; i++)
			glVertex2iv(house[i]);
		glEnd();
	glPopMatrix();
	

	glFlush();
}

void rotate(){
	glClear(GL_COLOR_BUFFER_BIT);
	draw_house();
	glFlush();


	
	glPushMatrix();
	glTranslatef(100, 50, 0);
	glRotatef(40, 0, 0, 1);
	glTranslatef(-100, -50, 0);
	draw_house();
	glPopMatrix();
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rotate();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		reflect();
	}
	
}

void display() {}
void init() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-400, 500, -400, 500);
}
int main(int argc, char* argv[])
{
	printf("enter angle:");
	scanf_s("%f", &angle);

	printf("Enter m & c values of y=mx+c:");
	scanf_s("%f%f", &m,&c);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Polygon Clipping!");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}