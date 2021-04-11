#include "tanchishe.h"
using namespace std;

DWORD WINAPI fun_time(LPVOID)
{
    while(1)
    {
        Sleep(1000);
        time_i++;
        if(time_i>=60)
        {
            time_j++;
            time_i=0;
        }
    }
}

int main()
{
    CreateThread(NULL, 0,fun_time,NULL, 0,NULL);
    show_for_user();
    initmap();
    food();
    initsnake(mapsize/2,mapsize/2-3);
    reflesh();
    while(1)
    {
        Sleep(100);
        gotoxy(mapsize+2,0);
        if(time_j) cout<<time_j<<"·Ö"<<time_i<<"Ãë";
        else cout <<time_i<<"Ãë";
        HideCursor();
        input();
        click();
        reflesh();
        if(t==1) break;
    }
    MessageBoxA(NULL,"ÓÎÏ·Ê§°Ü","",0);
    system("pause");
    return 0;
}








