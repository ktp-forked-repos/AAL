/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include "glut.h"
#include "View.h"
#include "Vertices.h"

using namespace std;

Vertices mainVertices;
int problem=0;
int option=0;
extern clock_t timeResult;

void UI();
int complexity(int, int);

int main(int argc, char** argv){
	UI(); // calls user interface
	if(option!=3){
		glutInit( &argc, argv );

		glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );

		glutInitWindowPosition( 0, 0 );
		glutInitWindowSize( 500, 500 );

		glutCreateWindow( "AAL-8-LS Piotr Jastrzêbski" );

		glutDisplayFunc( display );
		glutReshapeFunc( reshape );
		glutMainLoop();
	}
	return 0;
}

void UI(){
	std::cout << "A) Wybierz problem: " << std::endl;
	std::cout << "1. Wielokat wypukly o wierzcholkach wybranych ze zbioru punktow oraz wyroznionego punktu, ktory posiada maksymalna liczbe wierzcholkow" << std::endl;
	std::cout << "2. Wielokat wypukly o wierzcholkach wybranych ze zbioru punktow oraz wyroznionego punktu, ktory pokrywa maksymalna liczba punktow z wejsciowego zbioru" << std::endl;
	while(problem!=1 && problem!=2){
		std::cin >> problem;
	}

	std::cout << "B) Wybierz opcje: " << std::endl;
	std::cout << "1. wg danych dostarczonych z pliku" << std::endl;
	std::cout << "2. wg danych generowanych automatycznie" << std::endl;
	std::cout << "3. wykonanie z generacja danych i pomiarem czasu" << std::endl;
	while(option!=1 && option!=2 && option!=3){
		std::cin >> option;
	}

	switch(option){
	case 1:{ //from file
		bool errorHappened=true;
		std::string path;
		while(errorHappened){
			std::cout << "C) Podaj sciezke do pliku z danymi: ";
			std::cin >> path;
			errorHappened = mainVertices.loadFromFile(path);
		}
		break;
		   }
	case 2:{ //auto
		int x=0;
		std::cout << "C) Podaj liczbe punktow do wygenerowania: ";
		while(x<3)
			std::cin >> x;
		mainVertices.generateRandom(x);
		break;
		   }
	case 3:{ //auto+time
		int x=0;
		std::cout << "C) Podaj liczbe punktow do wygenerowania: ";
		while(x<3)
			std::cin >> x;		
		int mediana = (x+3)/2;
		std::vector<clock_t> times;
			for(int i=3; i<=x;i++){
				mainVertices.generateRandom(i);
				if(problem==1){
					//biggestVerticesSet(mainVertices);
					//STUPID_biggestVerticesSet(mainVertices);
					HEURISTIC_biggestVerticesSet(mainVertices);
				}
				else{
					mostCovered(mainVertices);
				}
				times.push_back(timeResult);
			}
			std::cout << "|\tn\t|" << "|\tt(n)\t|" << "|\tq(n)" << std::endl << std::endl;
			for(int i=0;i<(int)times.size();i++){
				int a=times[i]; //easier debugging
				int b=complexity(problem, mediana);
				int c=complexity(problem, i+3);
				int d=times[mediana-3];
				std::cout << "|\t" << i+3 << "\t||\t" << a << "\t||\t" << 1.0*a*b/c/d << std::endl;
			}

		cin >> x;
			break;
	}
	}
}

int complexity(int type, int n){
	if(type==1) // biggestVerticesSet
		//return pow((n-1)/3.0,n-1.0);
		return n*n;
	else		// mostCovered
		return n*n;
}
