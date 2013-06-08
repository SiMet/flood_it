#ifndef CLASS_PLANSZA
#define CLASS_PLANSZA
#include "macierz.h"
#include <GL/glut.h>
#include <vector>

void glPrintf(float x, float y,int size,	char *fmt, ...);

class Plansza : public Macierz {

   private:   
      std::vector <int> vec;
      int kolor;
      int moves;
   public:
   
      Plansza(int row,int col):Macierz(row,col),moves(0){};
      int getMoves();
      void fillRandom(int max);
      void NewGame(int max_rand);
      void GLdraw(double begin_x, double begin_y, double end_x, double end_y);
      bool add_to_vec(int wierzcholek);   
      void wybierz_kolor(int kolor); //DFS
      bool win();
      
};



#endif
