#include<stdio.h>
#include<glut.h>
#include<iostream>

using namespace std;

int m;

GLfloat tetra[4][3] = { {0,250,-250},{0,0,250},{250,-250,-250},{-250,-250,-250} };;

void draw_faces(GLfloat p1[], GLfloat p2[], GLfloat p3[]) {
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
}

void drawTetraHedron(GLfloat p1[], GLfloat p2[], GLfloat p3[], GLfloat p4[]) {
	glColor3f(1, 1, 0);
	draw_faces(p1, p2, p3);
	glColor3f(1, 0, 0);
	draw_faces(p1, p3, p4);
	glColor3f(1, 1, 0.1);
	draw_faces(p1, p4, p2);
	glColor3f(0, 1, 1);
	draw_faces(p2, p3, p4);
}

void divide_tetra(GLfloat p1[], GLfloat p2[], GLfloat p3[], GLfloat p4[], int m) {
	GLfloat mid[6][3];
	int i;
	if (m > 0) {
		for (i = 0;i < 3;i++) mid[0][i] = (p1[i] + p2[i]) / 2;
		for (i = 0;i < 3;i++) mid[1][i] = (p1[i] + p3[i]) / 2;
		for (i = 0;i < 3;i++) mid[2][i] = (p1[i] + p4[i]) / 2;
		for (i = 0;i < 3;i++) mid[3][i] = (p2[i] + p3[i]) / 2;
		for (i = 0;i < 3;i++) mid[4][i] = (p3[i] + p4[i]) / 2;
		for (i = 0;i < 3;i++) mid[5][i] = (p4[i] + p2[i]) / 2;

		divide_tetra(p1, mid[0], mid[1], mid[2], m - 1);
		divide_tetra(mid[0], p2, mid[3], mid[5], m - 1);
		divide_tetra(mid[1], mid[3], p3, mid[4], m - 1);
		divide_tetra(mid[2], mid[4], p4, mid[5], m - 1);

	}
	else {
		drawTetraHedron(p1, p2, p3, p4);
	}
}

void draw_tetra() {
	glBegin(GL_TRIANGLES);
	divide_tetra(tetra[0], tetra[1], tetra[2], tetra[3],m);
	glEnd();
	glFlush();
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1, 1);
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
	glColor3f(1, 0, 0);
}

int main(int argc, char* argv[]) {
	cout << "enter no of subdivisions:";
	cin >> m;
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("program 5- Serpinski");
	glutDisplayFunc(draw_tetra);
	glEnable(GL_DEPTH_TEST);
	myInit();
	glutMainLoop();
}