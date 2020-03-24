#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>


struct pixel
{
	int x,y,c;
}pix;


union REGS i,o;
int shape=4,prevColor=15,color=15,oldColor=0;

			//shape for selecting button for shape
			//color for selecting button for color
void show();
void save();
void select();
void repaint();
void square();
void cirlce();
void lin();
void pencil();
void fill();

void show()
{

	FILE *fp;
	fp= fopen("GRAPHICS.bin","rb");
	while(!feof(fp))
	{
		fread(&pix,sizeof(struct pixel),1,fp);
		putpixel(pix.x,pix.y,pix.c);
	}
	fclose(fp);
}

void save()
{

	FILE *fp;
	int a,b,c;
	i.x.ax=2;
	int86(0X33,&i,&o);
	fp= fopen("GRAPHICS.bin","wb");
	for(a=0;a<479;a++)
	{
		for(b=0;b<479;b++)
		{
			c=getpixel(a,b);
			if(c!=0)
			{
				pix.x=a;
				pix.y=b;
				pix.c=c;
				fwrite(&pix,sizeof(struct pixel),1,fp);
			}
		}
	}
	fclose(fp);
	i.x.ax=1;
	int86(0X33,&i,&o);
}

void select()
{
	int y=1;
	while(1)
	{
		i.x.ax=3;
		int86(51,&i,&o);
		if(o.x.bx==1&&y==1)
		{
			y=0;
		}
		if(o.x.bx==0&&y==0)
		{
			y=1;
			if(o.x.cx>520 && o.x.dx>10 && o.x.cx<600 && o.x.dx<30)
			{
				shape=0;	//clear
				repaint();
				delay(500);
				break;
			}
			if(o.x.cx>490 && o.x.dx>40 && o.x.cx<560 && o.x.dx<110)
				shape=1;	//rectangle

			if(o.x.cx>560 && o.x.dx>40 && o.x.cx<630 && o.x.dx<110)
				shape=2;	//circle

			if(o.x.cx>490 && o.x.dx>110 && o.x.cx<560 && o.x.dx<180)
				shape=3;              //line

			if(o.x.cx>560 && o.x.dx>110 && o.x.cx<630 && o.x.dx<180)
				shape=4;	//pencil
			if(o.x.cx>510 && o.x.dx>450 && o.x.cx<560 && o.x.dx<470)
				shape=7;	//fill

			if(o.x.cx>560 && o.x.dx>450 && o.x.cx<610 && o.x.dx<470)
			{
				shape=8;	//exit
				repaint();
				delay(500);
				break;
			}
			if(o.x.cx>490 && o.x.dx>290 && o.x.cx<525 && o.x.dx<325){ prevColor=color;     //colors button
				color=0;                                             }
			if(o.x.cx>525 && o.x.dx>290 && o.x.cx<560 && o.x.dx<325){ prevColor=color;     //colors button
				color=1;                                             }
			if(o.x.cx>560 && o.x.dx>290 && o.x.cx<595 && o.x.dx<325){ prevColor=color;	  //colors button
				color=2;                                            }
			if(o.x.cx>595 && o.x.dx>290 && o.x.cx<630 && o.x.dx<325){ prevColor=color;	  //colors button
				color=3;                                            }
			if(o.x.cx>490 && o.x.dx>325 && o.x.cx<525 && o.x.dx<360){ prevColor=color;	  //colors button
				color=4;                                            }
			if(o.x.cx>525 && o.x.dx>325 && o.x.cx<560 && o.x.dx<360){ prevColor=color;	  //colors button
				color=5;                                            }
			if(o.x.cx>560 && o.x.dx>325 && o.x.cx<595 && o.x.dx<360){ prevColor=color;	  //colors button
				color=6;                                            }
			if(o.x.cx>595 && o.x.dx>325 && o.x.cx<630 && o.x.dx<360){ prevColor=color;	  //colors button
				color=7;                                            }
			if(o.x.cx>490 && o.x.dx>360 && o.x.cx<525 && o.x.dx<395){ prevColor=color;	  //colors button
				color=8;                                            }
			if(o.x.cx>525 && o.x.dx>360 && o.x.cx<560 && o.x.dx<395) { prevColor=color;	 //colors button
				color=9;                                             }
			if(o.x.cx>560 && o.x.dx>360 && o.x.cx<595 && o.x.dx<395){ prevColor=color;	  //colors button
				color=10;                                           }
			if(o.x.cx>595 && o.x.dx>360 && o.x.cx<630 && o.x.dx<395){ prevColor=color;	  //colors button
				color=11;                                           }
			if(o.x.cx>490 && o.x.dx>395 && o.x.cx<525 && o.x.dx<430){ prevColor=color;	  //colors button
				color=12;                                           }
			if(o.x.cx>525 && o.x.dx>395 && o.x.cx<560 && o.x.dx<430){ prevColor=color;	  //colors button
				color=13;                                           }
			if(o.x.cx>560 && o.x.dx>395 && o.x.cx<595 && o.x.dx<430){ prevColor=color;	  //colors button
				color=14;		                                    }
			if(o.x.cx>595 && o.x.dx>395 && o.x.cx<630 && o.x.dx<430){ prevColor=color;	 //colors button
				color=15;                                           }
			repaint();
			setcolor(color);
		}
		if(o.x.cx<480)
			break;
	}
}

void repaint()
{
	int i=0;
	setviewport(0,0,479,479,0);
	setcolor(15);
	line(480,0,480,480);         //separate tools and worksheet
	while(i<2)
	{
		if(i==0||shape==0)
		{
			rectangle(520,10,600,30);	//clear
			outtextxy(540,20,"Clear");
		}
		if(i==0||shape==1)
		{
			rectangle(490,40,560,110);   //outline box
			rectangle(510,60,540,90);	//rectangle
		}
		if(i==0||shape==2)
		{
			rectangle(560,40,630,110);    //outline box
			circle(595,75,20);	//circle
		}
		if(i==0||shape==3)
		{
			rectangle(490,110,560,180);    //outline box
			line(510,130,540,160);              //line
		}
		if(i==0||shape==4)
		{
			rectangle(560,110,630,180);	//outline box
			rectangle(590,120,600,160);	//pencil
			line(590,160,595,170);
			line(600,160,595,170);
		}
		if(i==0||shape==7)
		{
			rectangle(510,450,560,470);	//button
			outtextxy(520,460,"FILL");		//text
		}

		if(i==0||shape==8)
		{
			rectangle(560,450,610,470);	//outline box
			outtextxy(570,460,"EXIT");		//text
		}

		if(i==0||color==0)
		{
			rectangle(490,290,525,325);      //colors button
			setfillstyle(SOLID_FILL,0);
			if(i==0)
			floodfill(491,291,WHITE);
			else
			floodfill(491,291,1);
		}
		if(i==0||color==1)
		{
			rectangle(525,290,560,325);      //colors button
			setfillstyle(SOLID_FILL,1);
			if(i==0)
			floodfill(526,291,WHITE);
			else
			floodfill(526,291,1);
		}
		if(i==0||color==2)
		{
			rectangle(560,290,595,325);      //colors button
			setfillstyle(SOLID_FILL,2);
			if(i==0)
			floodfill(561,291,WHITE);
			else
			floodfill(561,291,1);
		}
		if(i==0||color==3)
		{
			rectangle(595,290,630,325);      //colors button
			setfillstyle(SOLID_FILL,3);
			if(i==0)
			floodfill(596,291,WHITE);
			else
			floodfill(596,291,1);
		}
		if(i==0||color==4)
		{
			rectangle(490,325,525,360);      //colors button
			setfillstyle(SOLID_FILL,4);
			if(i==0)
			floodfill(491,326,WHITE);
			else
			floodfill(491,326,1);
		}
		if(i==0||color==5)
		{
			rectangle(525,325,560,360);      //colors button
			setfillstyle(SOLID_FILL,5);
			if(i==0)
			floodfill(526,326,WHITE);
			else
			floodfill(526,326,1);
		}
		if(i==0||color==6)
		{
			rectangle(560,325,595,360);      //colors button
			setfillstyle(SOLID_FILL,6);
			if(i==0)
			floodfill(561,326,WHITE);
			else
			floodfill(561,326,1);
		}
		if(i==0||color==7)
		{
			rectangle(595,325,630,360);      //colors button
			setfillstyle(SOLID_FILL,7);
			if(i==0)
			floodfill(596,326,WHITE);
			else
			floodfill(596,326,1);
		}
		if(i==0||color==8)
		{
			rectangle(490,360,525,395);      //colors button
			setfillstyle(SOLID_FILL,8);
			if(i==0)
			floodfill(491,361,WHITE);
			else
			floodfill(491,361,1);
		}
		if(i==0||color==9)
		{
			rectangle(525,360,560,395);      //colors button
			setfillstyle(SOLID_FILL,9);
			if(i==0)
			floodfill(526,361,WHITE);
			else
			floodfill(526,361,1);
		}
		if(i==0||color==10)
		{
			rectangle(560,360,595,395);      //colors button
			setfillstyle(SOLID_FILL,10);
			if(i==0)
			floodfill(561,361,WHITE);
			else
			floodfill(561,361,1);
		}
		if(i==0||color==11)
		{
			rectangle(595,360,630,395);      //colors button
			setfillstyle(SOLID_FILL,11);
			if(i==0)
			floodfill(596,361,WHITE);
			else
			floodfill(596,361,1);
		}
		if(i==0||color==12)
		{
			rectangle(490,395,525,430);      //colors button
			setfillstyle(SOLID_FILL,12);
			if(i==0)
			floodfill(491,396,WHITE);
			else
			floodfill(491,396,1);
		}
		if(i==0||color==13)
		{
			rectangle(525,395,560,430);      //colors button
			setfillstyle(SOLID_FILL,13);
			if(i==0)
			floodfill(526,396,WHITE);
			else
			floodfill(526,396,1);
		}
		if(i==0||color==14)
		{
			rectangle(560,395,595,430);      //colors button
			setfillstyle(SOLID_FILL,14);
			if(i==0)
			floodfill(561,396,WHITE);
			else
			floodfill(561,396,1);
		}
		if(i==0||color==15)
		{
			rectangle(595,395,630,430);      //colors button
			setfillstyle(SOLID_FILL,15);
			if(i==0)
			floodfill(596,396,WHITE);
			else
			floodfill(596,396,1);
		}
		i++;
		setcolor(1);
	}

}

void cirlce()
{
	int y=1,m,n,oi,s,p,a;
	setviewport(0,0,479,479,1);
	save();
	while(1)
	{
		i.x.ax=3;
		int86(0X33,&i,&o);
		if(o.x.bx==1&&y==1)
		{
			m=o.x.cx;
			n=o.x.dx;
			y=0;
		}
		if(o.x.bx==1&&y==0)
		{
			i.x.ax=3;
			int86(0X33,&i,&o);
			oi=o.x.cx;
			p=o.x.dx;
			a=(oi-m)/2;
			a=a>=0?a:-a;
			s=(p-n)/2;
			s=s>=0?s:-s;
			clearviewport();
			show();
			ellipse((m+oi)/2,(n+p)/2,0,360,a,s);
			delay(60);

			i.x.ax=3;
			int86(0X33,&i,&o);
			if(o.x.bx==0)
			{
				y=1;
				save();
			}
		}
		if(o.x.cx>480&&y==1)
		{
			break;
		}
	}
}

void square()
{
	int y=1,m,n,oi,p;
	setviewport(0,0,479,479,1);
	save();
	while(1)
	{
		i.x.ax=3;
		int86(0X33,&i,&o);
		if(o.x.bx==1&&y==1)
		{
			m=o.x.cx;
			n=o.x.dx;
			y=0;
			i.x.ax=2;
			int86(0X33,&i,&o);
		}
		if(o.x.bx==1&&y==0)
		{
			i.x.ax=3;
			int86(0X33,&i,&o);
			oi=o.x.cx;
			p=o.x.dx;
			clearviewport();
			show();
			rectangle(m,n,oi,p);
			delay(60);

			i.x.ax=3;
			int86(0X33,&i,&o);
			if(o.x.bx==0)
			{
				y=1;
				save();
				i.x.ax=1;
				int86(0X33,&i,&o);
			}
		}
		if(o.x.cx>480&&y==1)
		{
			break;
		}
	}
}

void lin()
{
	int y=1,m,n,oi,p;
	setviewport(0,0,479,479,1);
	save();
	while(1)
	{
		i.x.ax=3;
		int86(0X33,&i,&o);
		if(o.x.bx==1&&y==1)
		{
			m=o.x.cx;
			n=o.x.dx;
			y=0;
			i.x.ax=2;
			int86(0X33,&i,&o);
		}
		if(o.x.bx==1&&y==0)
		{
			i.x.ax=3;
			int86(0X33,&i,&o);
			oi=o.x.cx;
			p=o.x.dx;
			clearviewport();
			show();
			line(m,n,oi,p);
			delay(60);

			i.x.ax=3;
			int86(0X33,&i,&o);
			if(o.x.bx==0)
			{
				y=1;
				save();
				i.x.ax=1;
				int86(0X33,&i,&o);
			}
		}
		if(o.x.cx>480&&y==1)
		{
			break;
		}
	}
}

void pencil()
{
	int m,n,a,b;
	setviewport(0,0,479,479,1);
	while(1)
	{
		i.x.ax=3;
		int86(0X33,&i,&o);
		if(o.x.bx==1)
		{
			m=o.x.cx;
			n=o.x.dx;
			delay(50);
			i.x.ax=2;
			int86(0X33,&i,&o);
			i.x.ax=3;
			int86(0X33,&i,&o);
			line(m,n,o.x.cx,o.x.dx);

		}
		else
		{
			i.x.ax=1;
			int86(0X33,&i,&o);
			i.x.ax=3;
			int86(0X33,&i,&o);
		}
		if(o.x.cx>480&&o.x.bx==0)
		{
			break;
		}
	}

}



int readwrite(char c[20],char ch[20],int k)
{

	FILE *fp,*f;
	register int i,j;
	int r=1;
	fp= fopen(c,"rb");
	f=fopen(ch,"wb");
	if(fgetc(fp)!=EOF)
	{
		fp=freopen(c,"rb",fp);
		while(!feof(fp))
		{
			fread(&pix,sizeof(struct pixel),1,fp);
			i=pix.x;
			j=pix.y;
			if(getpixel(i+1,j)==k&& i>-1 &&i<640 && j>-1 &&j<480)
			{
				putpixel(i+1,j,color);
				pix.x=i+1;
				pix.y=j;
				fwrite(&pix,sizeof(struct pixel),1,f);
			}
			if(getpixel(i,j+1)==k&& i>-1 &&i<640 && j>-1 &&j<480)
			{
				putpixel(i,j+1,color);
				pix.x=i;
				pix.y=j+1;
				fwrite(&pix,sizeof(struct pixel),1,f);
			}
			if(getpixel(i-1,j)==k&& i>-1 &&i<640 && j>-1 &&j<480)
			{
				putpixel(i-1,j,color);
				pix.x=i-1;
				pix.y=j;
				fwrite(&pix,sizeof(struct pixel),1,f);
			}
			if(getpixel(i,j-1)==k&& i>-1 &&i<640 && j>-1 &&j<480)
			{
				putpixel(i,j-1,color);
				pix.x=i;
				pix.y=j-1;
				fwrite(&pix,sizeof(struct pixel),1,f);
			}
		}
	}
	else
		r=0;
	fclose(f);
	fclose(fp);
	return r;
}

void fill()
{
	int a,b,y=1,m,n,seed;
	FILE *x;
	setviewport(0,0,479,479,1);
	while(1)
	{
		i.x.ax=3;
		int86(0X33,&i,&o);
		if(o.x.bx==1&&y==1)
		{
			y=0;
		}
		if(o.x.bx==0&&y==0)
		{
			y=1;
			x=fopen("FP1.bin","wb");
			pix.x=m=o.x.cx;
			pix.y=n=o.x.dx;
			fwrite(&pix,sizeof(struct pixel),1,x);
			i.x.ax=2;
			int86(0X33,&i,&o);
			seed=getpixel(m,n);
			fclose(x);
			if(color!=seed)
			{
				do
				{
					a=readwrite("FP1.bin","FP2.bin",seed);
					b=readwrite("FP2.bin","FP1.bin",seed);
				}while(a==1||b==1);

			}
			i.x.ax=1;
			int86(0X33,&i,&o);

		}
		if(o.x.cx>480&&o.x.bx==0)
		{
			break;
		}
	}
}




void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
	i.x.ax=1;
	int86(51,&i,&o);
	repaint();
	setcolor(color);
	while(1)
	{
		i.x.ax=3;
		int86(51,&i,&o);
		if(shape==0)
		{
			cleardevice();
			shape=4;
			color=15;
			repaint();
			setcolor(color);
		}
		if(shape==1)
			square();
		if(shape==2)
			cirlce();
		if(shape==3)
			lin();
		if(shape==4)
			pencil();
		if(shape==7)
			fill();
		if(o.x.cx>480)
			select();
		if(shape==8)
			break;
	}
}