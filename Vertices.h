/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#ifndef VERTICES
#define VERTICES

#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "MyPoint.h"
#include "glut.h"

#define DUMP false //if true, dumps some extra info

class Vertices{
private:
	std::vector<class MyPoint> myVector;
public:
	void push(MyPoint);
	bool loadFromFile(std::string);
	std::vector<MyPoint> getMyVector();
	MyPoint getMyMarkedPoint();
	void setMyVector(std::vector<MyPoint>);
	void dumpContent(std::string name);
	bool isPointMarked(MyPoint);
	void clearVector();
	void generateRandom(int);
};

#endif

