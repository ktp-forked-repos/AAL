/********************
* Piotr Jastrzêbski *
* AAL-8-LS          *
********************/
#include "View.h"

#define SIZE 0.05

extern Vertices mainVertices;
extern int problem;

void display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	drawPlot();	//draw plot

	switch(problem){
	case 1:{
		//Vertices check = biggestVerticesSet(mainVertices);
		//Vertices check = STUPID_biggestVerticesSet(mainVertices);
		Vertices check = HEURISTIC_biggestVerticesSet(mainVertices);
		drawPolygon(convexHull(check));
		break;
		   }
	case 2:{
		drawPolygon(convexHull(mostCovered(mainVertices))); //draw convex polygon
		break;
		   }
	}
	drawPoints(SIZE, mainVertices); //draw points
	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	if( h > 0 && w > 0 ) {
		glViewport( 0, 0, w, h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		if( w <= h ) {
			glOrtho( -1.25, 1.25, -1.25*h/w, 1.25*h/w, -10.0, 10.0 );
		}
		else {
			glOrtho( -1.25*w/h, 1.25*w/h, -1.25, 1.25, -10.0, 10.0 );
		}
		glMatrixMode( GL_MODELVIEW );
	}
}

void drawPoints(double size, Vertices v){
	for(int i=0; i<(int)v.getMyVector().size(); i++){
		glPushMatrix();
		glTranslatef( v.getMyVector()[i].getX(), v.getMyVector()[i].getY(), 0.0 ); 
		glColor3f(0.0f, 0.0f, 1.0f);
		glRectf(-size/2.0, -size/2.0, size/2.0, size/2.0);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(v.getMyMarkedPoint().getX(), v.getMyMarkedPoint().getY(), 0.0 ); 
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-size/2.0, -size/2.0, size/2.0, size/2.0);
	glPopMatrix();
}

void drawPolygon(Vertices v){
	v.dumpContent("drawPolygon");

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	for(int i=0; i<(int)v.getMyVector().size(); i++){
		glVertex2f(v.getMyVector()[i].getX(), v.getMyVector()[i].getY());
	}
	glEnd();

	std::cout << std::endl;
}

void drawPlot(){
	glColor3f(0.5f, 0.5f, 0.5f);
	for(int i=-10;i<=10;i++){
		glPushMatrix();
		glTranslatef(i*SIZE*2.0, 0, 0);
		glRotatef(90.0f, 0, 0, 1.0f);
		glRectf(-SIZE*20, -SIZE/10.0, SIZE*20, SIZE/10.0);
		glPopMatrix();
	}
	for(int i=-10;i<=10;i++){
		glPushMatrix();
		glTranslatef(0, i*SIZE*2.0, 0);
		glRectf(-SIZE*20, -SIZE/10.0, SIZE*20, SIZE/10.0);
		glPopMatrix();
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRectf(-SIZE*23, -SIZE/10.0, SIZE*23, SIZE/10.0);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0f, 0, 0, 1.0f);
	glRectf(-SIZE*23, -SIZE/10.0, SIZE*23, SIZE/10.0);
	glPopMatrix();
}
