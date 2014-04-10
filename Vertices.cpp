/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#include "Vertices.h"

void Vertices::push(MyPoint p){
	myVector.push_back(p);
}

bool Vertices::loadFromFile(std::string path){
	std::string line;
	std::ifstream myfile(path);
	double x=0.0;
	double y=0.0;
	if (myfile.is_open()){
		myfile >> x;
		myfile >> y;
		this->push(MyPoint(x, y, true));
		while (myfile.good()){
			myfile >> x; 
			myfile >> y;
			this->push(MyPoint(x, y, false));
		}
		myfile.close();
	}
	else{
		std::cerr << "Nie znaleziono pliku! Wiecej informacji w pliku 'Readme.txt'."<<std::endl;
		return true;
	}
	return false;
}

std::vector<class MyPoint> Vertices::getMyVector(){
	return myVector;
}

MyPoint Vertices::getMyMarkedPoint(){
	for(int i=0;i<(int)getMyVector().size();i++)
		if(getMyVector()[i].getIsMarked()==true)
			return getMyVector()[i];
	return MyPoint(-6,-9,true); //never called, just in case.
}

void Vertices::setMyVector(std::vector<class MyPoint> v){
	myVector=v;
}

void Vertices::dumpContent(std::string name){
	if(DUMP){
		std::cout << name << std::endl;
		for(int i=0; i<(int)getMyVector().size(); i++){
			std::cout<<i<<": "<< getMyVector()[i].getX() << ", " <<getMyVector()[i].getY() << ", " << (getMyVector()[i].getIsMarked()?" TRUE":" false") << std::endl;
		}
		std::cout << std::endl;
	}
}

bool Vertices::isPointMarked(MyPoint p){
	return ( getMyMarkedPoint().getX()==p.getX() && getMyMarkedPoint().getY()==p.getY() );
}

void Vertices::clearVector(){
	myVector.clear();
}

void Vertices::generateRandom(int n){
	srand ( time(NULL) );
	this->clearVector();
	this->push(MyPoint(rand() % 21 / 10.0 - 1.0, rand() % 21 / 10.0 - 1.0, true));
	for(int i=1;i<n;i++)
		this->push(MyPoint(rand() % 21 / 10.0 - 1.0, rand() % 21 / 10.0 - 1.0, false));

}
