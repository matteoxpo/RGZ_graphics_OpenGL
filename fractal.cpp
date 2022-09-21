#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>

void init();
void resize(int width, int height);
void display();
void drawGraphMinkovskogo(GLdouble x, GLdouble y);
void drawHorizontalLines(GLdouble x, GLdouble y);
void drawVerticalLines(GLdouble x, GLdouble y);
void drawLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(800, 800);
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

GLdouble k;
void display() {
  glViewport(0, 0, 800, 800);
  k = 70;
  GLdouble x = -20, y = 20;
  drawGraphMinkovskogo(x, y);

  glFlush();
}

void drawGraphMinkovskogo(GLdouble x, GLdouble y) {
  // for (int i = 0; i < 5; i++)
  glColor3d(1, 1, 1);

  // glColor3d(1, 0.5, 0);
  drawHorizontalLines(x, y);
  drawVerticalLines(x + k, y);

  glColor3d(0.3, 0.77, 0.32);
  k *= -1;
  drawHorizontalLines(x, y);
  k *= -1;
  drawVerticalLines(x - k, y);

  glColor3d(0.35, 0.17, 0.48);
  drawHorizontalLines(x, y);
  // drawVerticalLines(x - k, y);

  glColor3d(1, 1, 0);
  // drawHorizontalLines(x, y);
  // drawVerticalLines(x + k, y);

  // drawHorizontalLines(x, y);
  // drawVerticalLines(x + k, y);

  for (int i = 0; i < 2; i++) {
    k *= pow(-1, i);
    y *= pow(-1, i);
    /*
    drawHorizontalLines(x, y);

    drawVerticalLines(x + k, y);
    */
    // разделение нахуй
    // drawHorizontalLines(x + k, y + k);

    // drawVerticalLines(x + 2 * k, y - k);
    // drawVerticalLines(x + 2 * k, y);

    /*
        drawVerticalLines(x + k, y);
        drawHorizontalLines(x + k, y + k);

        drawVerticalLines(x + 2 * k, y - k);
        drawVerticalLines(x + 2 * k, y);

      */

    // drawHorizontalLines(x + 2 * k, y - k);

    // drawVerticalLines(x + 3 * k, y - k);

    // drawHorizontalLines(x + 3 * k, y);

    // drawHorizontalLines(x + 4 * k, y);
  }
}

void drawHorizontalLines(GLdouble x, GLdouble y) {
  drawLine(x, y, x + k / 4, y);
  drawLine(x + k / 4, y + k / 4, x + k / 4 + k / 4, y + k / 4);
  drawLine(x + k / 4 + k / 4, y - k / 4, x + k - k / 4, y - k / 4);
  drawLine(x + k - k / 4, y, x + k, y);
  drawLine(x + k / 4, y, x + k / 4, y + k / 4);
  drawLine(x + k / 4 + k / 4, y + k / 4, x + k / 4 + k / 4, y - k / 4);
  drawLine(x + k - k / 4, y - k / 4, x + k - k / 4, y);
}

void drawVerticalLines(GLdouble x, GLdouble y) {
  drawLine(x, y, x, y + k / 4);
  drawLine(x, y + k / 4, x - k / 4, y + k / 4);
  drawLine(x - k / 4, y + k / 4, x - k / 4, y + k / 4 + k / 4);
  drawLine(x - k / 4, y + k / 4 + k / 4, x + k / 4, y + k / 4 + k / 4);
  drawLine(x + k / 4, y + k / 4 + k / 4, x + k / 4, y + k - k / 4);
  drawLine(x + k / 4, y + k - k / 4, x, y + k - k / 4);
  drawLine(x, y + k - k / 4, x, y + k);
}

void drawLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
  glViewport(0, 0, 800, 800);
  glBegin(GL_LINES);
  {  // рисуем линии
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  }
  glEnd();
}