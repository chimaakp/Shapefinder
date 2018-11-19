#ifndef COLORNAMES_H
#define COLORNAMES_H

#include <iostream>
#include <string>
#include "RGBtrip.h"
using namespace std;


RGBtrip convert(string color){//works
    if(!color.compare("black")){
        return RGBtrip(0,0,0);
    }
    else if(!color.compare("white")){
        return RGBtrip(255,255,255);
    }
    else if(!color.compare("orange")){
        return RGBtrip(255,165,0);
    }
    else{
        cout<<"This color is not supported. Using ORANGE instead"<<endl;
        return RGBtrip(255,165,0);
    }
    

};

#endif 