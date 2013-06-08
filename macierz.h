#ifndef CLASS_MACIERZ
#define CLASS_MACIERZ
#include <iostream>
#include <cmath>

class Macierz{
	protected:
		int rows,cols;//wielkosci macierzy
		double *wsk;	
	
	public:
		Macierz();
		Macierz(int row, int col);
		Macierz(const Macierz &macierz);
		~Macierz();
//operatory
		double & Macierz::operator () (int i, int j);
		friend std::ostream & operator << (std::ostream &os, Macierz mac);
		Macierz & operator = (const Macierz & macierz);
		Macierz operator + (const Macierz macierz);
		Macierz operator - (const Macierz macierz);
		Macierz operator * (Macierz macierz);
		bool operator == (Macierz macierz);
		int getRows(){return rows;}	
		int getCols(){return cols;}		
      Macierz odwroc();
      Macierz transponuj();
};



#endif
