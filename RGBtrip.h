#ifndef RGBTRIP_H
#define RGBTRIP_H

#include <iostream>
#include <string>
using namespace std;


struct RGBtrip{//using strings instead of ints so that i dont have to deal with pesky conversion issues
    int red, green, blue;
    RGBtrip(int r, int g, int b){
        red =r;
        green =g;
        blue =b;
        
    }
    
    int compare(RGBtrip O){//working tested
        if(red==O.red && green==O.green && blue==O.blue){//same
            return 0;
        }
        else{//different
            return 1;
        }
    }
    
    void copy(RGBtrip* O){//TODO fix or delete (doesnt work)
        O->red =this->red;
        O->green=this->green;
        O->blue=this->blue;
    }
    
    string qwas(){//working tested
        //printf("%d", red);

        char x [50];
        sprintf(x, "%d %d %d  ",red,green,blue);
        string tmp =x;
        return tmp;

    }

};

#endif 