#include<stdio.h>
#include<glut.h>
#include<math.h>

int x1, x2, y11, y2, flag = 0;
int r;

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

void draw_circle() {
	int p = 3 - 2 * r;
	int x, y;
	x = 0;
	y = r;
	while (x <= y) {
		draw_pixel(x1, y11, x, y);
		x++;
		if (p > 0) {
			y--;
			p += 4 * (x - y) + 10;
		}
		else {
			p += 4 * x + 6;
		}
		draw_pixel(x1, y11, x, y);
	}
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !flag) {
		x1 = x-250;
		y11 = 250-y;
		flag = 1;
		printf("(%d,%d)--\n", x1, y11);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag==1) {
		x2 = x-250;
		y2 = 250-y;
		r = (int)sqrt((x2 - x1) * (x2 - x1) + (y2 - y11) * (y2 - y11));
		printf("(%d,%d)--\n", x2, y2);
		draw_circle();
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
	glutCreateWindow("program 2");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	myInit();
	glutMainLoop();
}