/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#include "MyPoint.h"

MyPoint::MyPoint(){
	this->x=0.0;
	this->y=0.0;
	this->isMarked=false;
}

MyPoint::MyPoint(double x, double y, bool isMarked){
	this->x=x;
	this->y=y;
	this->isMarked=isMarked;
}

double MyPoint::getX(){
	return x;
}

double MyPoint::getY(){
	return y;
}

bool MyPoint::getIsMarked(){
	return isMarked;
}


