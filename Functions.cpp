/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#include "Functions.h"

clock_t timeResult;

Vertices convexHull(Vertices v){ //calculates convexHull following Jarvis algorithm
	Vertices result;
	MyPoint P1 = v.getMyVector()[0];
	MyPoint fin = v.getMyVector()[0];
	MyPoint Q1 = v.getMyVector()[0];
	//P1 = fin - min (x,y) point
	//Q1 - max (x,y) point
	for(int i=1; i< (int)v.getMyVector().size();i++){
		if(v.getMyVector()[i].getY()<=P1.getY()){
			if(v.getMyVector()[i].getY()<P1.getY()){
				P1=v.getMyVector()[i];
				fin=P1;
			}
			else if(v.getMyVector()[i].getX()<=P1.getX()){ //if Y equals, takes one with smaller X
				P1=v.getMyVector()[i];
				fin=P1;
			}
		}
		if(v.getMyVector()[i].getY()>=Q1.getY()){

			if(v.getMyVector()[i].getY()>Q1.getY()){
				Q1=v.getMyVector()[i];

			}
			else if(v.getMyVector()[i].getX()>=Q1.getX()){ //if Y equals, takes one with bigger X
				Q1=v.getMyVector()[i];

			}
		}
	}

	//from bottom to the top on the right side
	MyPoint N;
	while(N.getX() != Q1.getX() || N.getY() != Q1.getY()){
		double minAngle = DBL_MAX;
		for(int i=0; i<(int)v.getMyVector().size(); i++){
			if(v.getMyVector()[i].getY()>=P1.getY()){
				double a = angle(MyPoint(100, P1.getY(), false), P1, v.getMyVector()[i]);
				if(a <= minAngle){
					minAngle = angle(MyPoint(100, P1.getY(), false), P1, v.getMyVector()[i]);
					N = v.getMyVector()[i];

				}
			}
		}
		result.push(N);
		P1=N;
	}

	//from top to the bottom on the left side
	MyPoint M;
	while(M.getX() != fin.getX() || M.getY() != fin.getY()){
		double minAngle = DBL_MAX;
		for(int i=0;i<(int)v.getMyVector().size();i++){
			if(v.getMyVector()[i].getY()<=Q1.getY()){
				double a=angle(MyPoint(-100,Q1.getY(), false),Q1,v.getMyVector()[i]);
				if(a <=minAngle){
					minAngle=angle(MyPoint(-100,Q1.getY(), false),Q1,v.getMyVector()[i]);
					M=v.getMyVector()[i];
				}
			}
		}
		result.push(M);
		Q1=M;
	}
	result.dumpContent("convexHull");
	return result;
}

Vertices mostCovered(Vertices v){ //calculates biggest number of vertices covered by convex polygon
	double xPrime = v.getMyMarkedPoint().getX();
	double yPrime = v.getMyMarkedPoint().getY();
	double x=0.0;
	double y=0.0;
	double a=0.0;
	double b=0.0;
	int setSize=(int)v.getMyVector().size();
	int count=0;
	int maxL=0;
	int maxP=0;
	int max=0;
	std::vector<MyPoint> leftPoints; // local biggest subset of points on the left side
	std::vector<MyPoint> rightPoints; // local biggest subset of points on the right side
	std::vector<MyPoint> maxLeftPoints; // global biggest subset of points on the left side
	std::vector<MyPoint> maxRightPoints; // global biggest subset of points on the right side

	clock_t start= clock();

	for(int i=0; i<setSize; i++){
		leftPoints.clear();
		rightPoints.clear();

		x=v.getMyVector()[i].getX();
		y=v.getMyVector()[i].getY();
		if(abs(x-xPrime) < DBL_EPSILON){ // vertical line divides the set
			a=1.0;
			b=-a*x+y;
			for(int j=0; j<setSize; j++){
				if(v.getMyVector()[j].getX()<=x){
					leftPoints.push_back(v.getMyVector()[j]);
				}
				else if(v.getMyVector()[j].getX()>=x)
				{					
					rightPoints.push_back(v.getMyVector()[j]);
				}
			}
			if(DUMP)
				std::cout<<"("<<x<<", "<<y<<"):\t"<<a<<" * X + "<<b<<" = "<<x
				<<"\tL: " << leftPoints.size() << " P: "<< rightPoints.size() <<std::endl<<std::endl;
			if((int)leftPoints.size() > maxL){
				maxL=leftPoints.size();
				maxLeftPoints = leftPoints;;

			}
			else if((int)rightPoints.size() > maxP){
				maxP = rightPoints.size();
				maxRightPoints = rightPoints;
			}
		}
		else{
			a=((y-yPrime)/(x-xPrime));
			if(abs(a)<DBL_EPSILON){
				a=0.0;	// horizontal line divides
			}
			b=-a*x+y;
			for(int j=0; j<setSize; j++){
				if(a*v.getMyVector()[j].getX()+b <= v.getMyVector()[j].getY()){
					leftPoints.push_back(v.getMyVector()[j]);
				}
				else if(a*v.getMyVector()[j].getX()+b >= v.getMyVector()[j].getY()){
					rightPoints.push_back(v.getMyVector()[j]);
				}
			}
			if(DUMP)
				std::cout<<"("<<x<<", "<<y<<"):\t"<<a<<" * X + "<<b<<" = Y"
				<<"\tL: " << leftPoints.size() << " P: "<< rightPoints.size() <<std::endl<<std::endl;
			if((int)leftPoints.size() > maxL){
				maxL=leftPoints.size();
				maxLeftPoints = leftPoints;
			}
			else if((int)rightPoints.size() > maxP){
				maxP = rightPoints.size();
				maxRightPoints = rightPoints;
			}
		}
	}
	Vertices result;
	if(DUMP)
		std::cout<<"maxL: " << maxL << " maxP: " << maxP;
	if(maxL>maxP){
		max=maxL;
		result.setMyVector(maxLeftPoints);
	}
	else{
		max=maxP;
		result.setMyVector(maxRightPoints);
	}
	result.push(v.getMyMarkedPoint()); //OK!
	if(DUMP)
		std::cout<<" max: " << max << std::endl;
	result.dumpContent("mostCovered");
	timeResult=clock()-start; //TIME finish
	return result;
}

Vertices biggestVerticesSet(Vertices v){ //calculates biggest vertices subset, which belong to convex polygon
	bool isInBoth;
	int setSize=(int)v.getMyVector().size();
	Vertices verticesFromCH;
	Vertices tmp;
	std::vector<Vertices> hulls;
	
	clock_t start= clock();

	while(v.getMyVector().size()>2){
		verticesFromCH = convexHull(v); //takes a convexhull points
		hulls.push_back(verticesFromCH);
		for(int i=0; i<(int)v.getMyVector().size(); i++){
			isInBoth = false;
			for(int j=0; j<(int)verticesFromCH.getMyVector().size(); j++){
				if(v.getMyVector()[i].getX()==verticesFromCH.getMyVector()[j].getX() && v.getMyVector()[i].getY()==verticesFromCH.getMyVector()[j].getY()){
					isInBoth=true;
					if(v.isPointMarked(v.getMyVector()[i])){
						tmp.push(v.getMyVector()[i]);
					}
					break;
				}
			}
			if(!isInBoth)
				tmp.push(v.getMyVector()[i]); //subtract from whole set, push as a tmp for next round
		}
		v=tmp;
		tmp.clearVector();
	}
	v=hulls.back();
	hulls.pop_back();
	v.dumpContent("biggestVerticesSet");
	timeResult=clock()-start; //TIME finish
	return v; //currently those points are those which left
}

Vertices HEURISTIC_biggestVerticesSet(Vertices v){
	v=mostCovered(v); //assumption: more points, more vertices
	int currentlyTotal = 0;
	bool isInBoth;
	int setSize=(int)v.getMyVector().size();
	Vertices verticesFromCH;
	Vertices tmp;
	std::vector<Vertices> hulls;
	clock_t start= clock();

	while(v.getMyVector().size()>2){
		verticesFromCH = convexHull(v); //takes a convexhull points
		hulls.push_back(verticesFromCH);
		for(int i=0; i<(int)v.getMyVector().size(); i++){
			isInBoth = false;
			for(int j=0; j<(int)verticesFromCH.getMyVector().size(); j++){
				if(v.getMyVector()[i].getX()==verticesFromCH.getMyVector()[j].getX() && v.getMyVector()[i].getY()==verticesFromCH.getMyVector()[j].getY()){
					isInBoth=true;
					if(v.isPointMarked(v.getMyVector()[i])){
						tmp.push(v.getMyVector()[i]);
					}
					break;
				}
			}
			if(!isInBoth)
				tmp.push(v.getMyVector()[i]); //subtract from whole set, push as a tmp for next round
		}
		v=tmp;
		tmp.clearVector();
	}
	v=hulls.back();
	hulls.pop_back();

	Vertices currentlyTheBest = v;
	Vertices letsTry;
	while(!hulls.empty()){
		Vertices higherLvlHull = hulls.back();
		hulls.pop_back();
		for(int i=1;i<higherLvlHull.getMyVector().size();i++){
			letsTry = currentlyTheBest;
			letsTry.push(higherLvlHull.getMyVector()[i]);
			letsTry = convexHull(letsTry);
			if(letsTry.getMyVector().size() >= currentlyTheBest.getMyVector().size()){
				if(areDifferent(currentlyTheBest, letsTry))
					i=1;
				currentlyTheBest = letsTry;
			}
		}
		v=currentlyTheBest;
	}
	v.dumpContent("biggestVerticesSet");
	timeResult=clock()-start; //TIME finish
	return v; //currently those points are those which left
}

bool areDifferent(Vertices v1, Vertices v2){
		int size1=v1.getMyVector().size();
		int size2=v2.getMyVector().size();
		if(size1!=size2)
			return true;
		for(int i=0; i<size1;i++)
			if(v1.getMyVector()[i].getX()-v2.getMyVector()[i].getX()>=DBL_EPSILON || v1.getMyVector()[i].getY()-v2.getMyVector()[i].getY()>=DBL_EPSILON)
				return true;
		return false;
}

Vertices STUPID_biggestVerticesSet(Vertices v){
	Vertices maxSet;
	Vertices tmpSet;
	int max=0;

	clock_t start= clock();

	for(int i=0;i<=(int)v.getMyVector().size()-3;i++){
		tmpSet = STUPID_Delete(i, v);
		if(tmpSet.getMyMarkedPoint().getX()!=-6){
			if((int)tmpSet.getMyVector().size()>max){
				max=(int)tmpSet.getMyVector().size();
				maxSet.setMyVector(tmpSet.getMyVector());
			}
		}
	}
	timeResult=clock()-start; //TIME finish
	return maxSet;
}

Vertices STUPID_Delete(int i, Vertices v){
	if(i!=0){
		Vertices maxSet;
		Vertices tmpSet;
		int max=0;
		for(int j=0; j<(int)v.getMyVector().size();j++){
			Vertices vTmp;
			std::vector<class MyPoint> vectorTmp;
			vectorTmp.clear();
			for(int k=0;k<(int)v.getMyVector().size();k++){
				if(k!=j || k == 0)
					vectorTmp.push_back(v.getMyVector()[k]);
			}
			vTmp.setMyVector(vectorTmp);
			tmpSet=STUPID_Delete(i-1, vTmp);
			if(tmpSet.getMyMarkedPoint().getX()!=-6){
				if((int)tmpSet.getMyVector().size()>max){
					max=(int)tmpSet.getMyVector().size();
					maxSet.setMyVector(tmpSet.getMyVector());
				}
			}
		}
		return maxSet;

	}
	else
		return convexHull(v);
}

double angle(MyPoint p1, MyPoint p2, MyPoint p3){ //calculates angle for middle point according to law of cosines
	if(p1.getY()==p2.getY() && p2.getY()==p3.getY() ){ //needed, so NaN error does not happen
		if(p1.getX() > p2.getX() && p3.getX() > p2.getX() || p1.getX() < p2.getX() && p3.getX() < p2.getX()){
			return 0.0;
		}
	}
	double a = sqrt(pow(p1.getY()-p2.getY(),2)+pow(p1.getX()-p2.getX(),2));
	double b = sqrt(pow(p3.getY()-p2.getY(),2)+pow(p3.getX()-p2.getX(),2));
	double c = sqrt(pow(p1.getY()-p3.getY(),2)+pow(p1.getX()-p3.getX(),2));
	return acos((pow(c,2)-pow(a,2)-pow(b,2))/(-2*a*b))*180/3;
}

void dumpTime(int n, int t1, int t2){
	std::cout << "N: " << n << " clicks: " << t2-t1 << " seconds: " << ((float)t2-t1)/CLOCKS_PER_SEC <<std::endl;
}
