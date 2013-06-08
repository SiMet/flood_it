#include "macierz.h"

		Macierz::Macierz(){
			cols = 0;
			rows = 0;
			wsk = NULL;
		}
		Macierz::Macierz(int row, int col):rows(row),cols(col){
			wsk = new double[rows*cols];
			for(int i=0;i<rows*cols;i++)
				wsk[i]=0;
		}
		
		Macierz::Macierz(const Macierz &macierz){ // konstruktor kopiujacy
			rows = macierz.rows;
			cols = macierz.cols;
			wsk = new double[macierz.rows*macierz.cols];

			for(int i=0;i<rows*cols;i++)
				wsk[i]=macierz.wsk[i];
		}	
		Macierz::~Macierz(){
			delete [] wsk;
		}
		
		double & Macierz::operator () (int i, int j){
         if(i<rows && j<cols)    
			   return wsk[i*cols+j];
			else 
          throw ("Poza zasiegiem");
		}
		
		std::ostream & operator << (std::ostream &os, Macierz mac){
			for(int i=0;i<mac.getRows();i++){
				for(int j=0;j<mac.getCols();j++)
					os << mac(i,j) << " ";
				os << std::endl;
			}
			return os;
		}

		Macierz & Macierz::operator = (const Macierz & macierz){
			if( &macierz == this )
				return *this;
			delete [] wsk;
		
			rows = macierz.rows;
			cols = macierz.cols;
			wsk = new double[rows*cols];

			for(int i=0;i<rows*cols;i++)
				wsk[i]=macierz.wsk[i];
		}	
		
 Macierz Macierz::operator + (const Macierz macierz){
		Macierz tmp(rows,cols);
			if(cols != macierz.cols || rows != macierz.rows){
				throw("Nie mozna dodac tych macierzy!!");
			}
		else{
				for(int i=0;i<rows*cols;i++)
					tmp.wsk[i]=wsk[i]+macierz.wsk[i];		
			}
			return tmp;
		}
		
 Macierz Macierz::operator - (const Macierz macierz){
			Macierz tmp(rows,cols);
			if(cols != macierz.cols || rows != macierz.rows){
				throw("Nie mozna odjac tych macierzy!!");
			}
			else{
				for(int i=0;i<rows*cols;i++)
					tmp.wsk[i]=wsk[i]-macierz.wsk[i];		
			}
			return tmp;
		}

		Macierz Macierz::operator * (Macierz macierz){
			Macierz tmp(rows,macierz.cols);
			if(cols != macierz.rows)
				throw("Nie mozna pomnozyc tych macierzy!!");
			else{
				for(int i=0;i<tmp.rows;i++)
					for(int j=0;j<tmp.cols;j++)
						for(int k=0;k<cols;k++)
							tmp(i,j)+=(*this)(i,k)*macierz(k,j);
			}
			return tmp;
		}
		bool Macierz::operator == (Macierz macierz){
				if( &macierz == this )	
					return true;
				else if(cols != macierz.cols || rows != macierz.rows)
					return false;
				for(int i=0;i<rows;i++)
					for(int j=0;j<cols;j++)
						if((*this)(i,j)!=macierz(i,j))
							return false;
				return true;
		}
		
Macierz Macierz::odwroc(){
		if(rows!=cols)
			throw("Nie można wyliczyć wyznacznika");
		Macierz A(rows,rows); // macierz pomocnicza
		for(int i=0;i<rows;i++) //ustawienie macierzy A na macierz jednoskowa
			A(i,i)=1;

		Macierz B(*this);
		double tmp;

		for(int i=0;i<rows;i++){ // dla kazdego rzędu
			if(B(i,i)!=1){
			tmp = B(i,i);
				for(int j=0;j<cols;j++){
					B(i,j)/=tmp;
					A(i,j)/=tmp;
				}
			}
			for(int j=0;j<rows;j++){
				if(j==i) continue;
				tmp = B(j,i);
				for(int k=0;k<cols;k++){
					B(j,k)-=B(i,k) * tmp;
					A(j,k)-=A(i,k) * tmp;	
				}
			}
		}	
	return A;
 }
Macierz Macierz::transponuj(){
	Macierz A(cols,rows);
	for(int i=0;i<cols;i++)
		for(int j=0;j<rows;j++)
			A(i,j) = (*this)(j,i);
	return A;
}

