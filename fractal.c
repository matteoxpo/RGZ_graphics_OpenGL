#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init();
void resize(int width, int height);
void display();

void drawTree(double x, double y, double angle, double l);
void drawLeaf(double x, double y, double x1, double y1);
void drawTrunk(double x, double y, double x1, double y1, double p);
void drawLine(double x1, double y1, double x2, double y2);

double createXCoordinate(double bias, double coefficient, double angle);
double createYCoordinate(double bias, double coefficient, double angle);
double createAngle(double angle);
double createLenghtFactor(double length);
int createNumOfBranches();

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int MIN_LENGTH = WINDOW_HEIGHT / 100;
const int MAX_LENGTH = WINDOW_HEIGHT / 5;

int RECURS_COUNTER = 0;
const int RECURS_COUNTER_LIMIT = 30000;

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("RGZ");
  glutReshapeFunc(resize);
  init();

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
  drawTree(0, -WINDOW_HEIGHT / 8, M_PI / 2, WINDOW_HEIGHT / 8);
  glFlush();
}

void drawTree(double x, double y, double angle, double length) {
  RECURS_COUNTER++;

  if (length > MIN_LENGTH && RECURS_COUNTER < RECURS_COUNTER_LIMIT) {
    double x1 = createXCoordinate(x, length, angle);
    double y1 = createYCoordinate(y, length, angle);
    double length_factor = createLenghtFactor(length);
    double new_angle = 0;

    if (length > MAX_LENGTH) length = WINDOW_HEIGHT / 8;

    if (length < WINDOW_HEIGHT / 20)
      drawLeaf(x, y, x1, y1);
    else
      drawTrunk(x, y, x1, y1, length);

    for (int i = 0; i < createNumOfBranches(); i++) {
      new_angle = createAngle(angle);
      x1 = createXCoordinate(x, length_factor, angle);
      y1 = createYCoordinate(y, length_factor, angle);
      drawTree(x1, y1, new_angle, length - 5 - rand() % 30);
    }
  }
}

void drawLeaf(double x, double y, double x1, double y1) {
  if (rand() % 10 > 5) {
    glColor3d(0.5, 1, 0);
  } else {
    glColor3d(0.19, 0.4, 0);
  }

  for (int i = 0; i <= 3; i++) {
    drawLine(x + i, y, x1, y1);
  }
}

void drawTrunk(double x, double y, double x1, double y1, double p) {
  glColor3d(0.5, 0.2, 0.1);
  for (int i = 0; i <= (floor(p / 6)); i++) {
    drawLine(x + i - floor(p / 12), y, x1, y1);
  }
}

void drawLine(double x1, double y1, double x2, double y2) {
  glBegin(GL_LINES);
  {
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  }
  glEnd();
}

double createXCoordinate(double bias, double coefficient, double angle) {
  return ceil(bias + coefficient * cos(angle));
}

double createYCoordinate(double bias, double coefficient, double angle) {
  return ceil(bias + coefficient * sin(angle));
}

int createNumOfBranches() { return (9 - ceil(rand() % 5)); }

double createAngle(double angle) { return angle + 0.1 * (5 - rand() % 10); }

double createLenghtFactor(double length) {
  return (rand() % (int)(length - ceil(length / 6)) + ceil(length / 6));
}