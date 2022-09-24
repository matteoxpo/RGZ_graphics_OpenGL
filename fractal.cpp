#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cmath>

void init();
void resize(int width, int height);
void display();
void drawTree(double x, double y, double angle, double l);
void drawLeaf();
double createXCoordinate(double bias, double coefficient, double angle);
void drawLine(double x1, double y1, double x2, double y2);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int recursionStopCounter = 0;

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(800, 800);
  glutCreateWindow("RGZ");
  glutReshapeFunc(resize);
  init();

  glColor3d(1, 1, 0);

  srand(time(NULL));
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
  drawTree(0, -100, M_PI / 2, WINDOW_HEIGHT / 8);
  glFlush();
}

void drawTree(double x, double y, double angle, double length) {
  double p;
  double x1, y1;
  double s, new_angle, i;

  recursionStopCounter++;
  if (recursionStopCounter >= 25000) return;
  if (length > 8) {
    x1 = ceil(x + length * cos(angle));
    y1 = ceil(y + length * sin(angle));
    if (length > 150) {
      p = 100;
    } else {
      p = length;
    }
    if (p < 30) {
      if (rand() % 10 > 5) {
        glColor3d(0.5, 1, 0);
      } else {
        glColor3d(0.19, 0.4, 0);
      }

      for (i = 0; i <= 3; i++) {
        drawLine(x + i, y, x1, y1);
      }

    } else {
      glColor3d(0.5, 0.2, 0.1);
      for (i = 0; i <= (floor(p / 6)); i++) {
        drawLine(x + i - floor(p / 12), y, x1, y1);
      }
    }
    int recursionDown = (9 - ceil(rand() % 5));

    for (i = 0; i < recursionDown; i++) {
      s = (rand() % (int)(length - ceil(length / 6)) + ceil(length / 6));
      new_angle = angle + 0.1 * (5 - rand() % 10);
      x1 = ceil(x + s * cos(angle));
      y1 = ceil(y + s * sin(angle));
      drawTree(x1, y1, new_angle, p - 5 - rand() % 30);
    }
  }
}

double createXCoordinate(double bias, double coefficient, double angle) {
  return ceil(bias + coefficient * cos(angle));
}

void drawLine(double x1, double y1, double x2, double y2) {
  glBegin(GL_LINES);
  {
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  }
  glEnd();
}