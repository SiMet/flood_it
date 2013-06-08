#include <iostream>
#include <cmath>
class ColorRGB{
	public:      
   	double Red;
   	double Green;
   	double Blue;
   
   	ColorRGB(double r,double g,double b);
   	ColorRGB(int r,int g, int b);
   	ColorRGB();
   	void HSV2RGB(double h);

	private:
   	void hue2red(double h);
   	void hue2green(double h);
   	void hue2blue(double h);
};
