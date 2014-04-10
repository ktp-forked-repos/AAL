/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#ifndef VIEW
#define VIEW

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "Vertices.h"
#include "Functions.h"

void drawPoints(double, Vertices);
void drawPlot();
void drawPolygon(Vertices);
void display();
void maxCovered();
void reshape(GLsizei, GLsizei);

#endif
