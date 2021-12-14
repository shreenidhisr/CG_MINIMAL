#include<glut.h>
#include<stdio.h>

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;
int x1, y1, x2, y2;


int cliptest(double p, double q, double* u1, double* u2)
{
	double r;
	if (p) r = q / p;  // to check whether p
	if (p < 0.0)    // potentially entry point, update te 
	{
		if (r > *u1) *u1 = r;
		if (r > *u2) return(false); // line portion is outside
	}
	else
		if (p > 0.0)    //  Potentially leaving point, update tl
		{
			if (r < *u2) *u2 = r;
			if (r < *u1) return(false); // line portion is outside
		}
		else
			if (p == 0.0)
			{
				if (q < 0.0) return(false); // line parallel to edge but outside
			}
	return(true);
}


void clip_line(double x1, double y1,double x2, double y2) {
	double dx, dy;
	dx = x2 - x1;
	dy = y2 - y1;
	double u1 = 0.0;
	double u2 = 1.0;

	if (cliptest(-dx, x1 - xmin, &u1, &u2)) 
	if (cliptest(dx, xmax - x1, &u1, &u2)) 
	if (cliptest(-dy, y1 - ymin, &u1, &u2)) 
	if (cliptest(dy, ymax - y1, &u1, &u2))
	{
		if (u2 < 1.0) {
			x2 = x1 + u2 * dx;
			y2 = y1 + u2 * dy;
		}

		if (u1 > 0.0)
		{
			x1 = x1 + u1 * dx;
			y1 = y1 + u1 * dy;
		}

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
	glutCreateWindow("program 9 - line clipping");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();

}