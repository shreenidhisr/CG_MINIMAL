#include<stdio.h>
#include<glut.h>
#include<math.h>

GLfloat x=1, y=1;
int window1, window2;
GLfloat spin = 0;

void draw_sqaure() {
	
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.25, -0.25, 0.25);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.25, -0.25, 0.25);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.25, 0.25, 0.25);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-0.25, 0.25, 0.25);
	
}

void spinFunc() {
	spin += 0.025;
	if (spin > 360) {
		spin = 0;
	}
	
	glutSetWindow(window2);
	glutPostRedisplay();
	

}


void display1() {
	glBegin(GL_QUADS);
	draw_sqaure();
	glEnd();
	glFlush();
}

void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(spin,0,0,1);
	glBegin(GL_QUADS);
	draw_sqaure();
	glEnd();
	
	glPopMatrix();
	glutSwapBuffers();
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	gluOrtho2D(-2,2,-2,2);
	glColor3f(1, 0, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	window1=glutCreateWindow("program 3 - single buffer");
	glutDisplayFunc(display1);
	myInit();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	window2=glutCreateWindow("program 3 - double buffer");
	glutDisplayFunc(display2);
	glutIdleFunc(spinFunc);
	glutMainLoop();
}