#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
void northFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		northFill(a,b+1,newcolor,oldcolor);
	}
}
void westFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		westFill(a-1,b,newcolor,oldcolor);
	}
}
void southFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		southFill(a,b-1,newcolor,oldcolor);
	}
}
void eastFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		eastFill(a+1,b,newcolor,oldcolor);
	}
}
void northEastFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		northFill(a,b+1,newcolor,oldcolor);
		eastFill(a+1,b,newcolor,oldcolor);
		northEastFill(a+1,b+1,newcolor,oldcolor);
	}
}
void southEastFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		southFill(a,b-1,newcolor,oldcolor);
		eastFill(a+1,b,newcolor,oldcolor);
		southEastFill(a+1,b-1,newcolor,oldcolor);
	}
}
void northWestFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		northFill(a,b+1,newcolor,oldcolor);
		westFill(a-1,b,newcolor,oldcolor);
		northWestFill(a-1,b+1,newcolor,oldcolor);
	}
}
void southWestFill(int a,int b,int newcolor,int oldcolor){
	int current=getpixel(a,b);
	if(current==oldcolor){
		putpixel(a,b,newcolor);
		southFill(a,b-1,newcolor,oldcolor);
		westFill(a-1,b,newcolor,oldcolor);
		southWestFill(a-1,b-1,newcolor,oldcolor);
	}
}
void fillPoint(int x,int y,int color){
	int pixelColor=getpixel(x,y);
	putpixel(x,y,color);
	northFill(x,y+1,color,pixelColor);
	eastFill(x+1,y,color,pixelColor);
	southFill(x,y-1,color,pixelColor);
	westFill(x-1,y,color,pixelColor);
	northEastFill(x+1,y+1,color,pixelColor);
	southEastFill(x+1,y-1,color,pixelColor);
	southWestFill(x-1,y-1,color,pixelColor);
	northWestFill(x-1,y+1,color,pixelColor);
}
void main(){
	int gd = DETECT , gm;
	int x,y;
	initgraph(&gd,&gm,"");
	// circle(320,240,30);
	rectangle(40,40,630,470);
	printf("Enter x,y: ");
	scanf("%d %d",&x,&y);
	fillPoint(x,y,GREEN);
	getch();
	closegraph();
}
