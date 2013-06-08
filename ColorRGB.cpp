#include "ColorRGB.h"
   ColorRGB::ColorRGB(double r,double g,double b):Red(r),Green(g),Blue(b){}
   ColorRGB::ColorRGB():Red(0),Green(0),Blue(0){}
   ColorRGB::ColorRGB(int r, int g,int b):Red((double)r/255),Green((double)g/255),Blue((double)b/255){};
	
	void ColorRGB::HSV2RGB(double h){
		hue2red(h);
		hue2green(h);
		hue2blue(h);
	}

	void ColorRGB::hue2red(double h) {
		double r;
		h = fmod(h, 1);
		if(h < 0) h += 1;
		r = fabs(6*h-3)-1;
		Red = r<0 ? 0:(r>1 ? 1:r);
	}
	void ColorRGB::hue2green(double h){
		h=h+2./3;
		double r;
		h = fmod(h, 1);
		if(h < 0) h += 1;
		r = fabs(6*h-3)-1;
		Green = r<0 ? 0:(r>1 ? 1:r);
	}
	void ColorRGB::hue2blue(double h){
		h=h+1./3;
		double r;
		h = fmod(h, 1);
		if(h < 0) h += 1;
		r = fabs(6*h-3)-1;
		Blue = r<0 ? 0:(r>1 ? 1:r);
	}
