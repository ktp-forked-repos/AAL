/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#ifndef POINT
#define POINT

class MyPoint{
private:
	double x;
	double y;
	bool isMarked;
public:
	MyPoint();
	MyPoint(double, double, bool);
	double getX();
	double getY();
	bool getIsMarked();
};

#endif
