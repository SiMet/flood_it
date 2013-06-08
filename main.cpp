//==========================//
// Autor: Marek Szkowron    //
// Data: 30 VI 2008	        //
// Projekt: Flood it!       //
// wersja: 1.0              //
// =========================//


#include <iostream>
#include <GL/glut.h>
#include "Plansza.h"
#include "ColorRGB.h"
namespace ustawienia{
   int wielkosc = 2;
}

static const double M_PI = 3.141592653589793238462643383279502884197169399375;

   using namespace std;
      
Plansza plansza(20,20);
vector<ColorRGB*> vec_kolor(10);

void Menu();
void MouseButton (int button, int state, int x, int y);
void Selection(int x,int y);
double st2rad(double kat);
void DrawCircle(double r, double x,double y,int name);
static void init();

void GLdisplay(){
     
 	glInitNames();
	glPushName(0);    
   glColor3f(1,1,1);
     
	glClear (GL_COLOR_BUFFER_BIT);
	 plansza.GLdraw(0,0,6,6);
	 	 
   glColor3d(1,0,0);
	DrawCircle(0.25,-1.5,5.5,1); 
 
   glColor3d(0,1,0);
	DrawCircle(0.25,-0.5,5.5,2);
 
   glColor3d(0,0,1);
	DrawCircle(0.25,-1.5,4.5,3);
		 
   glColor3d(1,1,0);
   DrawCircle(0.25,-0.5,4.5,4); 

   glColor3d(1,0,1);
	DrawCircle(0.25,-1.5,3.5,5);	

   glColor3d(0,1,1);
	DrawCircle(0.25,-0.5,3.5,6);
   

   if(plansza.win()){
      glColor3f(0.9,0.9,0.9);    
      glBegin(GL_QUADS);
       glVertex2f(-0.7,2.5);
       glVertex2f(5.4,2.5);
       glVertex2f(5.4,3.5);
       glVertex2f(-0.7,3.5);
      glEnd();           
      glColor3f(1,0,0);
      glPrintf(-0.6,3,12,"Gratulacje! Zwyciestwo po %d ruchach", plansza.getMoves());
      
      glLoadName(7);
      
      glColor3f(0.9,0.9,0.9);
      glBegin(GL_QUADS);
       glVertex2f(0.5,1.0);
       glVertex2f(4,1.0);
       glVertex2f(4,2.0);
       glVertex2f(0.5,2.0);
      glEnd();
      glColor3f(0,0,0);
       glPrintf(1,1.4,12,"Jeszcze raz :D");
      glEnd();     
   }	
	
	glFlush();
	glutSwapBuffers();
};

int main(int argc, char **argv){
    
    srand(time(NULL));
    plansza.NewGame(6);

    //cout << plansza << endl;    
    
  		glutInit(&argc,argv);
		glutInitWindowSize(300,225);
		glutInitWindowPosition(60,60);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutCreateWindow("Flood it!");
      init();
		glutMouseFunc(MouseButton);
		glutDisplayFunc(GLdisplay);
		glutMainLoop();
      
    return 0;
}

static void init(void){
  glClearColor(0,0,0,0);
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D(-2,6,0,6);
  glMatrixMode(GL_MODELVIEW);
}
double st2rad(double kat){
	return kat/360.0*2*M_PI;
}
void DrawCircle(double r, double x,double y, int name){

   glLoadName(name);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x,y);
	for(int i=0;i<=360;i++){
		glVertex2f(x+r*cos(st2rad(i)),y+r*sin(st2rad(i)));
	}		
	glEnd();
}
void Menu(){
   glInitNames();
	glPushName(0);
   
   glColor3f(0.9,0,0);
   glPrintf(1,5,18,"Flood it!");
   glBegin(GL_TRIANGLES);
     glLoadName(100);
     glVertex2f(1,3);
     glVertex2f(1.2,3.2);
     glVertex2f(1.2,2.8);
     
     glLoadName(101);
     glVertex2f(3,3);
     glVertex2f(2.8,3.2);
     glVertex2f(2.8,2.8);
   glEnd();
   glPrintf(-0.5,2.9,12,"Wielkosc: ");
   switch(ustawienia::wielkosc){
      case 1:
         glPrintf(1.4,2.9,12,"Mala");
         break;
      case 2:
         glPrintf(1.4,2.9,12,"Srednia");
         break;
      case 3:
         glPrintf(1.4,2.9,12,"Duza");      
         break;
   }
   glColor3f(0.5,0.5,0.5);
   glBegin(GL_QUADS);
     glLoadName(200);
     glVertex2f(0,1.2);
     glVertex2f(4,1.2);
     glVertex2f(4,1.9);
     glVertex2f(0,1.9);
   glEnd();
   glColor3f(0.9,0,0);
   glPrintf(1.6,1.5,12,"Play!");
	glFlush();
	glutSwapBuffers();
}
void Selection(int x,int y){
	//BUFOR SELEKCJI
	const int BUFFER_LENGTH = 32;
    GLuint select_buffer[BUFFER_LENGTH];
    glSelectBuffer (BUFFER_LENGTH,select_buffer);

	// pobranie obszaru rozmiaru renderingu
    int viewport[4];
    glGetIntegerv (GL_VIEWPORT,viewport);
    int width = viewport [2];
    int height = viewport [3];

    // wybór macierzy rzutowania
    glMatrixMode (GL_PROJECTION);
    glPushMatrix ();
	 glLoadIdentity();

    // parametry bry³y obcinania - jednostkowa kostka dooko³a punktu wskaŸnika
    // myszy (x,y) rozci¹gaj¹cej siê na dwa piksele w poziomie i w pionie
    gluPickMatrix (x,height-y,1,1,viewport); //page 593

    // rzutowanie prostok¹tne
    init();

    // w³¹czenie trybu selekcji
    glRenderMode (GL_SELECT);
    // generowanie sceny 3D
    GLdisplay();

    // zliczenie iloœci rekordów trafieñ, powrót do domyœlnego trybu renderingu
    GLint hits = glRenderMode(GL_RENDER);
    // wybór macierzy rzutowania
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();

	if(hits>0){//w cos trafilismy :D
         int wyb_kolor = select_buffer[(hits-1)*4+3];         
			cout << "Trafilem:" << wyb_kolor << endl;
			if(wyb_kolor==7 && plansza.win()){
           plansza.NewGame(6);
         }
			else if(wyb_kolor!=0 && !plansza.win())
   			plansza.wybierz_kolor(wyb_kolor);
         else if(wyb_kolor==100)
            if(ustawienia::wielkosc>1) ustawienia::wielkosc--;
         else if(wyb_kolor==101)
            if(ustawienia::wielkosc<3) ustawienia::wielkosc++;
         else if(wyb_kolor==200){
            glutDisplayFunc(GLdisplay);
         }   
	}
}

void MouseButton (int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		Selection(x,y);
		glutPostRedisplay();
	}
}
