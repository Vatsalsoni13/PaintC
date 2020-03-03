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
int shape=4,color=15;

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


			if(o.x.cx>560 && o.x.dx>450 && o.x.cx<610 && o.x.dx<470)
			{
				shape=8;	//exit
				repaint();
				delay(500);
				break;
			}
			if(o.x.cx>595 && o.x.dx>395 && o.x.cx<630 && o.x.dx<430)      //colors button
				color=15;
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

		if(i==0||shape==8)
		{
			rectangle(560,450,610,470);	//outline box
			outtextxy(570,460,"EXIT");		//text
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
		if(o.x.cx>480)
			select();
		if(shape==8)
			break;
	}
}