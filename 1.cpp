#include<stdio.h>
#include<glut.h>


int x1, y1, x2, y2,flag=0;

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void draw_line() {
	
	int dx, dy, incx = 1, incy = 1, inc1, inc2, p,i;
	dx = x2 - x1;
	dy = y2 - y1;
	if (dx == 0) {
		for (i = 0;i <= dy;i++) {
			draw_pixel(x1, y1+i);
			return;
		}	
	}
	if (dy == 0) {
		for (i = 0;i <=dx;i++) {
			draw_pixel(x1+i, y1);
			return;
		}
	}
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	if (x2 < x1) {
		incx = -1;
	}
	if (y2 < y1) {
		incy = -1;
	}
	int x, y;
	x = x1;
	y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		p = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0;i < dx;i++) {
			if (p > 0) {
				y=y+incy;
				p = p + inc1;
			}
			else {
				p = p + inc2;
			}
			x=x+incx;
			draw_pixel(x, y);
		}
	}
	else {
		draw_pixel(x, y);
		p = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0;i < dy;i++) {
			if (p > 0) {
				x+=incx;
				p = p + inc1;
			}
			else {
				p = p + inc2;
			}
			y+=incy;
			draw_pixel(x, y);
		}
	}
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !flag) {
		x1 = x-250;
		y1 = 250-y;
		flag = 1;
		printf("(%d,%d)--\n", x1, y1);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag==1) {
		x2 = x-250;
		y2 = 250-y;
		printf("(%d,%d)--\n", x2, y2);
		draw_line();
		flag = 0;
	}
}

void display() {

}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	gluOrtho2D(-250, 250, -250, 250);
	glColor3f(1, 0, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("program 1");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	myInit();
	glutMainLoop();
}