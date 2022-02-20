# CG LAB PROGRAMS OVERVIEW (RVCE)

## boiler plate code
<pre>
#include "glut.h"
#include "stdio.h"

void display() {
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(10, 10);
	glVertex2f(100, 100);
	glEnd();
	glFlush();
}

void mouse(int state,int button,int x,int y){}

void keyboard(unsigned char key,int x,int y){}

void myInit() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("1st program ");
	glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
	myInit();
	glutMainLoop();
}
</pre>

## program 1 ( Bresanhmas line drawing algo)

<h3> Logic </h3>
<ol>
<li>read x1,y1 and x2,y2 (either through stdin or mouse)</li>
<li>dx = x2 - x1; dy = y2 - y1;</li>
<li> if dx==0 draw a line parallel to y axis {for every in dy : draw_pixel(x1, y1+i);}</li>
<li>if dy==0 draw a line parallel to y axis {for every in dx : draw_pixel(x1+i, y1);}</li>
<li>if dx<0 change it to -dx and dy<0 change it to -dy and also change incx and incy to -1 if dx<0 or dy<0 respectively</li>
<li> take 2 points x=x1 and y=1 </li>
<pre>
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
</pre>
<li>In case of dy>dx (slope > 1) : swap dy and dx in above code</li>
</ol>

## program 2 (Circle drawing algo )
<h3> logic </h3>
<ol>
<li> read x1 ,y1 and r(radius) </li>
<li> draw point in every octant</li>
<pre>
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
</pre>
<li>draw circle algo--></li>
<pre>
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
</pre>


## program 3(spin rectangles single and double buffers)

1. just create 2 windows 
2. In One window display square or rect 
3. For other window use doubleBuffer
4. and Add <pre> glutIdleFunc(..) </pre> to it,which basically has callback function which rotates the sqaure by some degree and calls <pre> glutPostRedisplay</pre>

## program 4 (Cylinder and Parallelo pipped)

1. Just write logic to create circle and rectangle 
2. Then draw constant radius circle(by iterating over radius) and constant width and height ractangle (iterate over values of height and width)
