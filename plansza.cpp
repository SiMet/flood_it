#include "Plansza.h"

void glPrintf(float x, float y,int size,	char *fmt, ...){
  char buf[512], *c=buf;
  va_list apt;
  va_start(apt,fmt);
  vsprintf(c, fmt, apt);
  va_end(apt);
  glRasterPos2f(x, y);
  if(size==12)
  while(*c) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c++);
  else if(size==18)
while(*c) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c++);
}

      int Plansza::getMoves(){
         return moves;
      }
      void Plansza::fillRandom(int max){
        for(int i=0;i<getRows();i++)
         for(int j=0;j<getCols();j++)
          (*this)(i,j) = rand()%(max)+1;
      }
      void Plansza::NewGame(int max_rand){
           (*this).fillRandom(max_rand);
           moves = 0;
           (*this)(0,0)=0;
           kolor = 0;
      }
      void Plansza::GLdraw(double begin_x, double begin_y, double end_x, double end_y){

      glPrintf(-1.8,1,12, "Moves: %d", moves);
      
      double h = (end_y - begin_y)/rows;
      double w = (end_x - begin_y)/cols;
      //std::cout << h << " " << w <<std::endl;
      glBegin(GL_QUADS);
        for(int i=0;i<rows;i++)
          for(int j=0;j<cols;j++){
           //std::cout << i << " " << j << std::endl;
           int kolor_pola = (int)(*this)(i,j);
           if(kolor_pola == 0)
            kolor_pola = kolor;
             switch(kolor_pola){
              case 1:
               glColor3d(1,0,0);
               break;
              case 2:
                glColor3d(0,1,0);
                break;
              case 3:
                glColor3d(0,0,1);
                break;
              case 4:
                glColor3d(1,1,0);
                break;
              case 5: 
                 glColor3d(1,0,1);
                 break;
              case 6:
                 glColor3d(0,1,1);
                 break;
              case 7:
                 glColor3d(1,0.61,0);
              case 8:
                 glColor3d(0.38,0.14,0);
             }
            glVertex2d(begin_x+j*w,begin_y+i*h);
            glVertex2d(begin_x+w+j*w,begin_y+i*h);
            glVertex2d(begin_x+w+j*w,begin_y+h+i*h);
            glVertex2d(begin_x+j*w,begin_y+h+i*h);
          }
      
      glEnd();

      }

   bool Plansza::add_to_vec(int wierzcholek){
        for(int i=0;i<vec.size();i++){
           if(vec.at(i)==wierzcholek)
             return false;
        }
        this->wsk[wierzcholek]=0;
        vec.push_back(wierzcholek);
        
        return true;
   }
   
   void Plansza::wybierz_kolor(int kolor){ //DFS
        moves++;
        this->kolor = kolor;
        vec.clear();
        vec.push_back(0);
                
        for(int i=0;i<vec.size();i++){     
           int y = vec[i]/cols;
           int x = vec[i]%cols;
           if((x+1)<cols){
             if((*this)(y,x+1)==0 || (*this)(y,x+1)==kolor)             
             add_to_vec(y*cols + x + 1);
           }
           if(x-1>=0){
              if((*this)(y,x-1)==0 || (*this)(y,x-1)==kolor)
              add_to_vec(y*cols + x - 1);
           }
           if(y+1<rows){
              if((*this)(y+1,x)==0 || (*this)(y+1,x)==kolor)
              add_to_vec((y+1)*cols + x);
           }
           if(y-1>=0){
              if((*this)(y-1,x)==0 || (*this)(y-1,x)==kolor)
              add_to_vec((y-1)*cols + x);
           }
        }// for
        
   }
   bool Plansza::win(){
     for(int i=0;i<rows;i++)
      for(int j=0;j<cols;j++)
       if((*this)(i,j)!=0)
        return false;
     return true;   
   }
      
