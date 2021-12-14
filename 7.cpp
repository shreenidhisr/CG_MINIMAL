#include<glut.h>
#include<iostream>
#include<algorithm>
#include<Windows.h>


using namespace std;

int xmin, ymin, xmax, ymax;
int x[100], y[100];
int intx[10] = { 0 };
int n;
int m;



void draw_line(float x1, float y1, float x2, float y2)
{
	Sleep(100);
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void edgeDetect(int x1, int y1, int x2, int y2, int scanline) {
	int temp;
	if (y2 < y1) {
		temp = x1;
		x1 = x2;
		x2 = temp;

		temp = y1;
		y1 = y2;
		y2 = temp;

	}
	if (scanline > y1 && scanline < y2) {
		intx[m++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
	}
}

void scanfill(int x[], int y[]) {
	int s1,i;
	for (s1 = 0;s1 < 500;s1++) {
		m = 0;
		for (i = 0;i < n;i++) {
			edgeDetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], s1);
		}
		std::sort(intx, intx + m);

		for (i = 0;i < m;i++) {
			draw_line(intx[i], s1, intx[(i + 1)%m], s1);
		}
	}
}

void display() {
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0;i < n;i++) {
		glVertex2i(x[i], y[i]);
	}
	glEnd();
	scanfill(x, y);
	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(1, 0, 0);
}


int main(int argc, char* argv[]) {
	
	cout << "Enter no of edges:";
	cin >> n;

	int i;
	for (i = 0;i < n;i++) {
		cout << "Enter coordinates:";
		cin >> x[i] >> y[i];

	}
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Scanline");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();

}