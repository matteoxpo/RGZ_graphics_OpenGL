#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

void init();
void resize(int width, int height);
void display();
void drawPoint(GLdouble x, GLdouble y, GLdouble r, GLdouble g, GLdouble b);
void drawLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);

void Draw(double x, double y, double r, double a) {
  int i;
  double xx[6], yy[6];

  for (i = 0; i < 6; i++) {
    xx[i] = r * cos(a + i * M_PI * 2 / 5);
    yy[i] = r * sin(a + i * M_PI * 2 / 5);
  }
  for (i = 0; i < 5; i++)
    drawLine(x + xx[i], y + yy[i], x + xx[i + 1], y + yy[i + 1]);
}

void ProvRis(double x, double y, double r, double a, int d) {
  int i;
  double h;

  h = 2 * r * cos(M_PI / 5);

  for (i = 0; i < 5; i++) {
    Draw(x - h * cos(a + i * M_PI * 2 / 5), y - h * sin(a + i * M_PI * 2 / 5),
         r, a + M_PI);
    if (d > 0)
      ProvRis(x - h * cos(a + i * M_PI * 2 / 5),
              y - h * sin(a + i * M_PI * 2 / 5), r / (2 * cos(M_PI / 5) + 1), a,
              d - 1);
  }
  if (d > 0) ProvRis(x, y, r / (2 * cos(M_PI / 5) + 1), a + M_PI, d - 1);
}

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("RGZ");
  glutReshapeFunc(resize);
  init();
  glColor3d(1, 1, 0);

  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}

void init() {
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2,
          WINDOW_HEIGHT / 2, 0, 2);
  gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
}

void resize(int width, int height) {}

void display() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glColor3d(1, 1, 0);
  drawLine(0, 0, 200, 0);
  // ProvRis(320, 260, 95, M_PI / 2, 3);

  char c;
  scanf("%c", &c);

  glFlush();
}

void drawPoint(GLdouble x, GLdouble y, GLdouble r, GLdouble g, GLdouble b) {
  glBegin(GL_POINTS);
  {
    glColor3d(r, g, b);
    glVertex2d(x, y);
  }
  glEnd();
}

void drawLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
  glBegin(GL_LINES);
  {
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  }
  glEnd();
}