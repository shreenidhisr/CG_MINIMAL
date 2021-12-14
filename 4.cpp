#include<stdio.h>
#include<glut.h>
#include<math.h>

GLfloat window1, window2;

void draw_pixel(int xc, int yc, int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(xc+x, yc+y);
	glVertex2i(xc-x, yc+y);
	glVertex2i(xc+x, yc-y);
	glVertex2i(xc-x, yc-y);
	glVertex2i(xc+y, yc+x);
	glVertex2i(xc-y, yc+x);
	glVertex2i(xc+y, yc-x);
	glVertex2i(xc-y, yc-x);
	glEnd();
}

void draw_circle(int xc, int yc, int r) {
	int p = 1 - r;
	int x = 0;
	int y = r;
	while (x < y) {
		draw_pixel(xc, yc, x, y);
		x++;
		if (p > 0) {
			y--;
			p += 2 * (x - y) + 5;
		}
		else {
			p += 2 * x + 3;
		}
		draw_pixel(xc, yc, x, y);
	}
	glFlush();
}

void display1(){
	int i;
	int xc = 100, yc = 100;
	for (i = 0;i < 30;i+=2) {
		draw_circle(xc+i, yc, 50);
	}
	
	glFlush();
}


void draw_rect(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}
void display2() {
	int i;
	for (i = 0;i < 20;i++) {
		draw_rect(50+i, 50+i, 150+i, 150+i);
	}
	

	glFlush();
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	gluOrtho2D(0,200,0,200);
	glColor3f(1, 0, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	window1=glutCreateWindow("program 4- cylinder");
	glutDisplayFunc(display1);
	myInit();

	
	window2=glutCreateWindow("program 4 - parallelo pipped");
	glutDisplayFunc(display2);
	myInit();

	glutMainLoop();
}