#include<glut.h>
#include<stdio.h>

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;
int x1, y1, x2, y2;

#define LEFT 8
#define RIGHT 4
#define TOP 2
#define BOTTOM 1

int computecode(int x, int y) {
	int code = 0;
	if (y > ymax) {
		code |= TOP;
	}
	if (y < ymin) {
		code |= BOTTOM;
	}
	if (x > xmax) {
		code |= RIGHT;
	}
	if (x < xmin) {
		code |= LEFT;
	}
	return code;
}

void clip_line(int x1, int y1, int x2, int y2) {
	int outcode0, outcode1, outcodeout;
	outcode0 = computecode(x1, y1);
	outcode1 = computecode(x2, y2);
	bool accept = false, done = false;
	double x, y;
	do {
		if (!(outcode0 | outcode1)) {
			accept = true;
			done = true;
		}
		else if (outcode0 & outcode1) {
			done = true;
		}
		else {
			outcodeout = outcode0 ? outcode0 : outcode1;

			if (outcodeout & TOP) {
				x= x1 + (ymax - y1) * (x2 - x1) / (y2 - y1);
				y = ymax;
			}else if(outcodeout & BOTTOM){
				x = x1 + (ymin - y1) * (x2 - x1) / (y2 - y1);
				y = ymin;
			}
			else if (outcodeout & LEFT) {
				x = xmin;
				y = y1 + (xmin - x1) * (y2 - y1) / (x2 - x1);
			}
			else {
				x = xmax;
				y = y1 + (xmax - x1) * (y2 - y1) / (x2 - x1);
			}

			if (outcodeout == outcode0) {
				x1 = x;
				y1 = y;
				outcode0 = computecode(x1, y1);
			}
			else {
				x2 = x;
				y2 = y;
				outcode1 = computecode(x2, y2);
			}
		}
		

	} while (!done);

	if (accept) {
		double sx = (xvmax - xvmin) / (xmax - xmin);
		double sy = (yvmax - yvmin) / (ymax - ymin);

		double vx0 = xvmin + (x1 - xmin) * sx;
		double vy0 = yvmin + (y1 - ymin) * sy;
		double vx1 = xvmin + (x2 - xmin) * sx;
		double vy1 = yvmin + (y2 - ymin) * sy;

		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex2d(vx0, vy0);
		glVertex2d(vx1, vy1);
		printf("%d %d %d %d\n", vx0, vy0, vx1, vy1);
		glEnd();

		glFlush();
	}

}

void display() {
	//draw window 
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin, ymin);
	glVertex2i(xmax, ymin);
	glVertex2i(xmax, ymax);
	glVertex2i(xmin, ymax);
	glEnd();

	//draw line
	x1 = 120, y1 = 10, x2 = 40, y2 = 130;
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);

	glVertex2i(25, 25);
	glVertex2i(125, 125);

	glVertex2i(25, 25);
	glVertex2i(75, 25);

	glEnd();
	glFlush();
	

	clip_line(x1, y1, x2, y2);
	clip_line(25, 25, 125, 125);
	clip_line(25, 25, 75, 25);
	glFlush();
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
	
}


int main(int argc, char* argv[]) {
	
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("program 8 - line clipping");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();

}