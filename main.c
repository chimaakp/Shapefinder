#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "RGBtrip.h"
#include "ColorNames.h"
#include <opencv2/highgui/highgui.hpp>
#include <vector>


using namespace std;

//Global variables / Defaults
string filename ="square.png";
string newfilename  = "b.ppm";
string shape = "square";
string color = "orange";
int width;
int height;
vector<RGBtrip>* Pixlist= new vector<RGBtrip>;

//Function Declarations
void flagidentifier(char* arr[],int index);
void replacecolor(vector<RGBtrip>* Pixlist, RGBtrip oldcolor,RGBtrip newcolor);
void stringtoint(int* i,string s);
void writefile(vector<RGBtrip>* P);
int checkforsquare();

int main(int argc, char* argv[]){//argc start at 1(a.out)
		//TODO add error for if file name not included (argc <2) (create must be odd error)
	filename =argv[1];	
	for(int i =2; i<argc;i+=2){
	//TODO add error for when 2nd argument of flag not added  
	flagidentifier(argv, i);//works properly 0 index is a.out, 1 index is first word (file name)
	}
	

	
	cout<<newfilename<<" :this is the name of your new file"<<endl<<color<<endl<<shape<<endl<<filename<<"--------------------------------"<<endl;
	system(("convert "+filename+" -compress none "+newfilename).c_str());//converts file using imagemagick
	
  //PRINTING FILE  
  string line;
  ifstream myfile; 
  myfile.open(newfilename.c_str()); 
  if (myfile.is_open()){
      
      getline (myfile,line);//removes p3/header at top of file
      
      //GRAB HEIGHT AND WIDTH
      string tmp;
      getline(myfile, line, ' ');
      stringtoint(&width, line);
      getline(myfile, line);
      stringtoint(&height,line);

      
      getline(myfile, line);//remove max color value
      
    while ( getline (myfile,line) ){
        if(line.at(0)=='#'){//ignores lines with comments
        }
        else{
            stringstream ss(line);
            int count=1;
            int r,g,b;
            while(getline(ss, line, ' ')){//seperates line by spaces
                stringstream ss2(line);
                while ( getline (ss2,line) ){//removes any remaining whitespace
                //cout<<line<<": line"<<endl;
                if(count>=3){
                    stringtoint(&b,line);
                    Pixlist->push_back(RGBtrip(r,g,b));
                    // printf(" RGB triplets: %d %d %d", r, g, b);
                    // cout<<endl;
                    count=0;
                }

                if(count==2){
                    stringtoint(&g,line);
                }
                if(count==1){
                    stringtoint(&r,line);
                    
                }
                count++;
            }
            }
      
        }
    }
    myfile.close();
  }

  
  //print vector
//   cout<<endl<<endl<<endl<<"Printing vector"<<endl<<"-----------------"<<endl;
//   for(int i=0;i<Pixlist->size();i++){
//       cout<<Pixlist->at(i).qwas()<<endl;
      
//   }

int shapeindex =checkforsquare();
  
  if(shapeindex<height*width){
  
   replacecolor(Pixlist,Pixlist->at(shapeindex),convert(color));
   writefile(Pixlist);

  }
  else{
      cout<<"No shape found"<<endl;
  }



  
  
  //PRINTING ARGUMENTS/INPUTS
	int i;
	for(i=1; i<argc; ++i){//start at 1 to avoid printing a.out
	   
	   printf("Argument %d : %s\n", i, argv[i]);
	}
	return 0;
}

//SETS GLOBAL VARIABLES by reading flags from command line
void flagidentifier(char* arr[],int index){
	string check = "-o";
	if(!strcmp(check.c_str(),arr[index])){//output image

		newfilename= arr[index+1];
	}
		

	  
	  check = "-s";
	  if(!strcmp(check.c_str(),arr[index])){//shape
		shape= arr[index+1];
	}
	  else{
		shape = "square";
	  }
	  
	  
	  check= "-c";
	  if(!strcmp(check.c_str(),arr[index])){//color
		color= arr[index+1];
	}
	  else{
		color ="black";
	  }
	
}



void stringtoint(int* i,string s){
    stringstream w(s);
      w>>*i;
}

void replacecolor(vector<RGBtrip>* Pixlist, RGBtrip oldcolor,RGBtrip newcolor){
    for(int i=0;i<Pixlist->size();i++){
        if(!Pixlist->at(i).compare(oldcolor)){
            newcolor.copy(&Pixlist->at(i));
        }
    }
}

void writefile(vector<RGBtrip>* P){
    ofstream myfile;
    myfile.open (newfilename.c_str());
    myfile << "P3\n";
    char x [50];
    sprintf(x, "%d %d",width, height);
    myfile << x;
    myfile << "\n";
    myfile << "255 \n";
    int j=0;
    for(int i=0;i<Pixlist->size();i++){
        if(j>=width){
            j=0;
            myfile << "\n";
        }
        myfile << Pixlist->at(i).qwas();
        j++;
        
    }
    myfile.close();
}

int checkforsquare(){//Currently working on this
    //cout<<"We got something"<<endl;
     for(int i=0;i<Pixlist->size()-(2*width);i++){//skip last row
     printf("index: %d out of %d \n", i,(int)Pixlist->size());
    //     cout<<"We got something"<<endl;
         int j =i;
        if(!(i+1)%3 || Pixlist->at(i).compare(Pixlist->at(i+1))){
            continue;
        }
        while(!Pixlist->at(j).compare(Pixlist->at(j+1)) && (j+1)%width){//Right
            j++;
        }
        cout<<"DOWN"<<endl;
        printf("%d \n",height*width);
        if(!Pixlist->at(j).compare(Pixlist->at(j+width))){
            j+=2*width;
        while(!Pixlist->at(j).compare(Pixlist->at(j-width)) && j+width<height*width){//shouldnt work what if it doesnt line up with previous
            printf("i: %d j: %d j+width: %d \n",i,j,j+width);
            j+=width;
        }
        
        }
        else{
            continue;
        }
        if(Pixlist->at(j).compare(Pixlist->at(j-width))){//roll it back if values dont match up
            j-=width;
            
        }
        printf(" SWITCHING TO LEFT i: %d j: %d j+width: %d \n",i,j,j+width);
        cout<<"LEFT"<<endl;
        while(!Pixlist->at(j).compare(Pixlist->at(j-1))){//Left TODO: this could be cause of error
            printf("left j: %d  \n",j);
            if(j%width < i%width || (j-1)%width>j%width){
                break;
            }
            j--;
            printf(" j: %d  \n",j);
        }
        printf(" SWITCHING TO UP i: %d j: %d j-width: %d \n",i,j,j-width);
        while(!Pixlist->at(j).compare(Pixlist->at(j-width))){//Up
        cout<<"LOOP"<<endl;
            j-=width;
            if(j==i){
                //return Pixlist->at(i);
                cout<<"We got something"<<endl;
                return i;
            }
            
                
            
        }
        
        
     }
     cout<<"This aint workin"<<endl;
     return height*width;
    
}