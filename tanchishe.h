#ifndef TANCHISHE_H_INCLUDED
#define TANCHISHE_H_INCLUDED
#include<iostream>
#include<algorithm>
#include<list>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<cstdio>

using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
const int  mapsize = 20;
int smap[mapsize][mapsize]={0};
int x,y,k=0,fx,fy,t=0,time_i=0,time_j=0;
int dir[4]={0,0,0,0};

struct node
{
    int nx,ny;
    node *next;
}*pt,*pw;

void initsnake(int nx,int ny)
{
    pt=new node;
    pw=pt;
    pt->nx=nx;
    pt->ny=ny;
    pt->next=NULL;
    for(int i=1;i<2;i++)
    {
        node *p;
        p=new node;
        p->nx=nx;
        p->ny=ny+i;
        p->next=NULL;
        pt->next=p;
        pt=p;
    }
    x=pt->nx;
    y=pt->ny;
}

void initmap()
{
    for(int i=0;i<mapsize;i++)
        for(int j=0;j<mapsize;j++)
        if(i==0||j==0||i==mapsize-1||j==mapsize-1)
             smap[i][j]=1;//  墙
}

void food()
{
    k=0;
    int kk=1;
    srand(time(0));
    while(kk){
        fx=rand()%(mapsize-1)+1;
        fy=rand()%(mapsize-1)+1;
        if(smap[fx][fy]==0){
            smap[fx][fy]=2;
            kk=0;
        }
    }
    return ;
}

void input()
{
    char ch;
	if(_kbhit())
    {
        ch=_getch();
        if(ch==65||ch==97)//左移
        {
            if(dir[3]==0)
            {
                memset(dir,0,sizeof(dir));
                dir[2]=1;
            }
        }
        else if(ch==68||ch==100)//右移
        {
             if(dir[2]==0)
            {
                memset(dir,0,sizeof(dir));
                dir[3]=1;
            }
        }
        else if(ch==87||ch==119)//上移
        {
             if(dir[1]==0)
            {
                memset(dir,0,sizeof(dir));
                dir[0]=1;
            }
        }
        else if(ch==83||ch==115)//下移
        {
             if(dir[0]==0)
            {
                memset(dir,0,sizeof(dir));
                dir[1]=1;
            }
        }
    }
}

void click()
{
    int f=0;
    node *p;
    p=new node;
    p->nx=x-dir[0]+dir[1];
    if(p->nx<=0||p->nx>=mapsize) t=1;
    p->ny=y-dir[2]+dir[3];
    //if(p->nx==x&&p->ny==y) f=1;
    x=p->nx;
    y=p->ny;
    if(p->ny<=0||p->ny>=mapsize) t=1;
    p->next=NULL;
    if(!f)
    {
        pt->next=p;
        pt=p;
    }
    else{
        pt=p;
    }
    if(t==1) return;
    if(pt->nx==fx&&pt->ny==fy) k=1;
    if(k) {
            food();
            k=0;
    }
    else if(!f) {
        smap[pw->nx][pw->ny]=0;
        pw=pw->next;
    }
    //delete p;
}


/******************************************************
                   可视化界面
*******************************************************/

void gotoxy(int n_y, int n_x) // 获取标准输出设备句柄 SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
{
    COORD pos = {(SHORT)n_x,(SHORT)n_y};
   SetConsoleCursorPosition(hOut,pos);
}

void HideCursor()//隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = {1,0};
    SetConsoleCursorInfo(hOut, &cursor_info);//控制控制台光标大小及可视性
}

void show_for_user()
{
    gotoxy(mapsize+4,2);
    cout<<"W";
    gotoxy(mapsize+5,0);
    cout<<"A S D";
    gotoxy(mapsize+7,0);
    cout<<"按W,A,S,D中任意键开始游戏.";
}

void snake()
{
    node *p;
    p=pw;
    while(p->next!=NULL)
    {
        if(smap[pt->nx][pt->ny]==1||smap[pt->nx][pt->ny]==-1) {t=1;break;}
        else
        {
            smap[p->nx][p->ny]=-1;//蛇身
            p=p->next;
        }
    }
    smap[p->nx][p->ny]=-2;
    //delete p;
}

void reflesh()
{
    snake();
    gotoxy(0,0);
    for(int i=0;i<mapsize;i++)
        for(int j=0;j<mapsize;j++)
    {
        if(smap[i][j]==1)
        {
             SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//绿色
             cout<<"■";
             if(j==mapsize-1) cout<<endl;
        }
        if(smap[i][j]==2||smap[i][j]==-2) {
            SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_RED);//红色
            cout<<"■";
        }
        if(smap[i][j]==-1){
            SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);//白色
            cout<<"■";
        }
        if(smap[i][j]==0) cout<<"  ";
    }
}

#endif // TANCHISHE_H_INCLUDED








