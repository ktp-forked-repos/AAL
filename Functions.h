/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#ifndef FUNCTIONS
#define FUNCTIONS
#include "Vertices.h"
#include "MyPoint.h"
#include <list>
#include <vector>
#include <ctime>

#define PI 3.14159265358979323846 //cmath does not work?!

//calculates convexHull following Jarvis algorithm
Vertices convexHull(Vertices);

//calculates biggest number of vertices covered by convex polygon
Vertices mostCovered(Vertices);

//calculates biggest vertices subset, which belong to convex polygon
Vertices biggestVerticesSet(Vertices v);

//biggestVerticesSet with heuristic
Vertices HEURISTIC_biggestVerticesSet(Vertices v);

//naive approach to biggestVerticesSet
Vertices STUPID_biggestVerticesSet(Vertices);

//part of STUPID_biggestVerticesSet
Vertices STUPID_Delete(int, Vertices);

//calculates angle for middle point according to law of cosines
double angle(MyPoint, MyPoint, MyPoint);

//checks if sets're different
bool areDifferent(Vertices v1, Vertices v2);

void dumpTime(int, int, int);
#endif
