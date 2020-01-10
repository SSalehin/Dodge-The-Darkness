#include<stdio.h>
#include<graphics.h>

FILE *lvlstat;
int story()
{
    //while(kbhit()>=0) getch();
    readimagefile("Story1.jpg",0,0,1360,720);
    if(kbhit()>0){
        if(getch()==27) return 0;
    }
    getch();
    cleardevice();

    readimagefile("Story2.jpg",0,0,1360,720);
    if(kbhit()>0){
        if(getch()==27) return 0;
    }
    getch();
    cleardevice();

    readimagefile("Story3.jpg",0,0,1360,720);
    if(kbhit()>0){
        if(getch()==27) return 0;
    }
    getch();
    cleardevice();

    readimagefile("Story4.jpg",0,0,1360,720);
    if(kbhit()>0){
        if(getch()==27) return 0;
    }
    getch();
    cleardevice();

    readimagefile("Story5.jpg",0,0,1360,720);
    if(kbhit()>0){
        if(getch()==27) return 0;
    }
    getch();
    cleardevice();

    readimagefile("Story6.jpg",0,0,1360,720);
    if(kbhit()>0){
        if(getch()==27) return 0;
    }
    getch();
    cleardevice();
    delay(3000);
    return 0;
}

int tutorial(int x, int y, int f){
    if(x==1&&y==6&&f==0){
        readimagefile("Tutorial1.jpg",0,540,300,720);
        getch();
        readimagefile("Tutorial2.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==4&&y==6&&f==1){
        readimagefile("Tutorial3.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==4&&y==6&&f==2){
        readimagefile("Tutorial4.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==7&&y==6&&f==3){
        readimagefile("Tutorial5.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==10&&y==4&&f==4){
        readimagefile("Tutorial6.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==9&&y==5&&f==4){
        readimagefile("Tutorial6.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==9&&y==4&&f==5){
        readimagefile("Tutorial7.jpg",0,540,300,720);
        return ++f;
    }
    else if(x==9&&y==4&&f==6){
        readimagefile("Tutorial8.jpg",0,540,300,720);
        return ++f;
    }
    else return f;
}

void printcharacter(int x, int y, int s){
    if(s==1) readimagefile("Stand_up.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    else if(s==2) readimagefile("Stand_down.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    else if(s==3) readimagefile("Stand_left.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    else if(s==4) readimagefile("Stand_right.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printend(int x, int y){
    readimagefile("Exit.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}

int printselectlevel(){
    cleardevice();
    while (ismouseclick(WM_LBUTTONDOWN)!=0) clearmouseclick(WM_LBUTTONDOWN);
    int level, ind=10000,i,x,y;
    lvlstat=fopen("status.lvl","r");
    fscanf(lvlstat,"%d",&level);
    for(i=0;i<level;i++){
        if(i==0) readimagefile("level1.jpg",700,100,800,200);
        else if(i==1) readimagefile("level2.jpg",700,200,800,300);
        else if(i==2) readimagefile("level3.jpg",700,300,800,400);
        else if(i==3) readimagefile("level4.jpg",700,400,800,500);
        else if(i==4) readimagefile("level5.jpg",700,500,800,600);
    }
    while (ismouseclick(WM_LBUTTONDOWN)!=0) clearmouseclick(WM_LBUTTONDOWN);
    while(1){
        if(ismouseclick(WM_LBUTTONDOWN)!=0){
            x=mousex();
            y=mousey();
            if(x>700&&x<800&&y>100&&y<200) ind= 1;
            else if(x>700&&x<800&&y>200&&y<300) ind=2;
            else if(x>700&&x<800&&y>300&&y<400) ind=3;
            else if(x>700&&x<800&&y>400&&y<500) ind=4;
            else if(x>700&&x<800&&y>500&&y<600) ind=5;
        }
        if(ind<=level) return ind;
    }
}
int printhome(){
    char com;
    int x, y, returnvalue=1000;
    readimagefile("Homescreen.jpg",0,0,1380,720);
    readimagefile("Story_button.jpg",700,390,1300,480);
    readimagefile("Select_button.jpg",700,480,1300,570);
    readimagefile("Exit_button.jpg",700,570,1300,660);

    while (ismouseclick(WM_LBUTTONDOWN)!=0) clearmouseclick(WM_LBUTTONDOWN);

    while(1){
        readimagefile("Homescreen.jpg",0,0,1380,720);
        readimagefile("Story_button.jpg",700,390,1300,480);
        readimagefile("Select_button.jpg",700,480,1300,570);
        readimagefile("Exit_button.jpg",700,570,1300,660);

        if(kbhit()>0){
            com=getch();
            if(com=='c'){
                readimagefile("Credits.jpg",0,0,1360,720);
                while(getch()!=27);
            }
        }

        if(ismouseclick(WM_LBUTTONDOWN)!=0){
            x=mousex();
            y=mousey();
            if(x>700&&x<1300&&y>390&&y<480) return -1;
            else if(x>700&&x<1300&&y>480&&y<570) returnvalue= printselectlevel();
            else if(x>700&&x<1300&&y>570&&y<660) exit(0);
            printf("%d\n",returnvalue);
            if(returnvalue!=1000) return returnvalue;
        }
    }
}


void printpath(int x, int y){
    readimagefile("path.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void lightenpath(int x, int y){
    readimagefile("path4.jpg",60*x+1,60*y+1,60*(x+1)-1,60*(y+1)-1);
    delay(20);
    readimagefile("path.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    delay(10);
}
void printdarkness(int x, int y){
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    bar(60*x,60*y,60*(x+1),60*(y+1));
}
void printdir(int x, int y, int u){
    if(u==1) readimagefile("Up.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    else if(u==2) readimagefile("Down.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    else if(u==3) readimagefile("Left.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    else if(u==4) readimagefile("Right.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printlight(int x, int y){
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    bar(60*x,60*y,60*(x+1),60*(y+1));
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    circle(60*x+30,60*y+30,20);
    //floodfill(70*x+50,70*y+50,BLUE);
}
void printwall(int x, int y){
    readimagefile("Wall.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printblock(int x, int y){
     readimagefile("Block.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printglass(int x, int y){
    readimagefile("Glass.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printinactiveport(int x, int y){
    readimagefile("inactiveport.jpg",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printai(int x, int y){
     readimagefile("AI.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printai2(int x, int y){
     readimagefile("AI2.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
void printdeadai(int x, int y){
    readimagefile("AI_dead.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
    delay(100);
    readimagefile("AI_dead2.gif",60*x,60*y,60*(x+1)-1,60*(y+1)-1);
}
