#include <stdio.h>
#include <graphics.h>
#include<stdlib.h>
#include "print.h"
//each level must be bordered by walls

int posx=1, posy=3, endx, endy, map[12][23], face=1, aix[10], aiy[10], maxlevel, currentlevel, levelstatus, flag=0;
FILE *level;

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      Manager Section    //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void printsuitable(int x, int y){
    int intensity, base, layer;
    intensity=map[y][x]/100;
    base=(map[y][x]/10)%10;
    layer=map[y][x]%10;
    if(intensity>=1) {
            if(base==0) printpath(x,y);
            else if(base==1) printdir(x,y,1);
            else if(base==2) printdir(x,y,2);
            else if(base==3) printdir(x,y,3);
            else if(base==4) printdir(x,y,4);
            else if(base==5) printlight(x,y);
            else if(base==6) printinactiveport(x,y);
            else if(base==7) printwall(x,y);

            if(layer==2) printglass(x,y);
            else if(layer==4) printblock(x,y);
            else if(layer==7) printwall(x,y);
    }
    else printdarkness(x, y);
}
void printmap(){
    int meh, reen;
    for(reen=0; reen<12;reen++){
        for(meh=0; meh<23;meh++) printsuitable(meh,reen);
    }
}
void move(char command);
void lightensuitable(int x, int y);


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////     AI Section     ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int aisearch(int x, int y){
    int i;
    for(i=0;i<10;i++){
        if(aix[i]==x&&aiy[i]==y) return 1;
    }
    return 0;
}
void aimap(int i){
    int intensity, base, layer, flag=0;
    if(map[aiy[i]][aix[i]]>=100){
        printai(aix[i], aiy[i]);
        delay(100);
        printsuitable(aix[i],aiy[i]);
        printai2(aix[i], aiy[i]);
        delay(100);
        printai(aix[i], aiy[i]);
        delay(100);
        printsuitable(aix[i],aiy[i]);
        printai2(aix[i], aiy[i]);
        delay(100);
        if(map[aiy[i]-1][aix[i]]<100&&map[aiy[i]-1][aix[i]]%10==0&&aisearch(aix[i],aiy[i]-1)==0){
            readimagefile("AI_up.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aiy[i]--;
        }
        else if(map[aiy[i]+1][aix[i]]<100&&map[aiy[i]+1][aix[i]]%10==0&&aisearch(aix[i],aiy[i]+1)==0){
            readimagefile("AI_down.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aiy[i]++;
        }
        else if(map[aiy[i]][aix[i]-1]<100&&map[aiy[i]][aix[i]-1]%10==0&&aisearch(aix[i]-1,aiy[i])==0){
            readimagefile("AI_left.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aix[i]--;
        }
        else if(map[aiy[i]][aix[i]+1]<100&&map[aiy[i]][aix[i]+1]%10==0&&aisearch(aix[i]+1,aiy[i])==0){
            readimagefile("AI_right.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aix[i]++;
        }
        else if(map[aiy[i]-1][aix[i]-1]<100&&map[aiy[i]-1][aix[i]-1]%10==0&&aisearch(aix[i]-1,aiy[i]-1)==0){
            readimagefile("AI_upleft.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aiy[i]--;
            aix[i]--;
        }
        else if(map[aiy[i]+1][aix[i]-1]<100&&map[aiy[i]+1][aix[i]-1]%10==0&&aisearch(aix[i]-1,aiy[i]+1)==0){
            readimagefile("AI_downleft.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aiy[i]++;
            aix[i]--;
        }
        else if(map[aiy[i]+1][aix[i]+1]<100&&map[aiy[i]+1][aix[i]+1]%10==0&&aisearch(aix[i]+1,aiy[i]+1)==0){
            readimagefile("AI_downright.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aix[i]++;
            aiy[i]++;
        }
        else if(map[aiy[i]-1][aix[i]+1]<100&&map[aiy[i]-1][aix[i]+1]%10==0&&aisearch(aix[i]+1,aiy[i]-1)==0){
            readimagefile("AI_upright.gif",60*aix[i],60*aiy[i], 60*(aix[i]+1), 60*(aiy[i]+1));
            delay(100);
            printsuitable(aix[i],aiy[i]);
            aiy[i]--;
            aix[i]++;
        }
    }
}
void aikill(){
    int i;
    for(i=0;i<10;i++) if(aix[i]>=0) aimap(i);
    for(i=0;i<10;i++)
        if(map[aiy[i]][aix[i]]>=100&&aix[i]>=0) printsuitable(aix[i],aiy[i]);
    for(i=0;i<10;i++)
        if(map[aiy[i]][aix[i]]>=100&&aix[i]>=0) printdeadai(aix[i],aiy[i]);
        delay(500);
    for(i=0;i<10;i++)
        if(map[aiy[i]][aix[i]]>=100&&aix[i]>=0){
            printsuitable(aix[i],aiy[i]);
            aix[i]=-1;
            aiy[i]=-1;
        }
}
void aisilentkill(){
    int i;
    for(i=0;i<10;i++)
        if(map[aiy[i]][aix[i]]%10!=0&&aix[i]>=0){
            aix[i]=-1;
            aiy[i]=-1;
        }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    Lighting Section         ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void lightenup(int x, int y){
    int i, intensity, base, layer;
    for(i=y;i>=0;i--){
        map[i][x]+=100;
        intensity=map[posy][posx]/100;
        base=(map[posy][posx]/10)%10;
        layer=map[posy][posx]%10;
        if(map[i][x]<200)lightensuitable(x,i);
        if(map[i][x]%10==4||map[i][x]%10==7) break;
    }
}
void darkenup(int x, int y){
    int i, intensity, base, layer;
    for(i=y;i>=0;i--){
        intensity=map[posy][posx]/100;
        base=(map[posy][posx]/10)%10;
        layer=map[posy][posx]%10;
        if(map[i][x]>=100)map[i][x]-=100;
        if(map[i][x]<100) printdarkness(x,i);
        if(map[i][x]%10==4||map[i][x]%10==7) break;
    }
}
void lightendown(int x, int y){
    int i;
    for(i=y;i<=12;i++){
        map[i][x]+=100;
        if(map[i][x]<200)lightensuitable(x,i);
        if(map[i][x]%10==4||map[i][x]%10==7) break;
    }
}
void darkendown(int x, int y){
    int i;
    for(i=y+1;i<=12;i++){
        if(map[i][x]>=100)map[i][x]-=100;
        if(map[i][x]<100) printdarkness(x,i);
        if(map[i][x]%10==4||map[i][x]%10==7) break;
    }
}
void lightenleft(int x, int y){
    int i;
    for(i=x;i>=0;i--){
        map[y][i]+=100;
        if(map[y][i]<200)lightensuitable(i,y);
        if(map[y][i]%10==4||map[y][i]%10==7) break;
    }
}
void darkenleft(int x, int y){
    int i;
    for(i=x-1;i>=0;i--){
        if(map[y][i]>=100)map[y][i]-=100;
        if(map[y][i]<100) printdarkness(i,y);
        if(map[y][i]%10==4||map[y][i]%10==7) break;
    }
}
void lightenright(int x, int y){
    int i;
    for(i=x;i<=23;i++){
        map[y][i]+=100;
        if(map[y][i]<200)lightensuitable(i,y);
        if(map[y][i]%10==4||map[y][i]%10==7) break;
    }
}
void darkenright(int x, int y){
    int i;
    for(i=x+1;i<=23;i++){
        if(map[y][i]>=100)map[y][i]-=100;
        if(map[y][i]<100) printdarkness(i,y);
        if(map[y][i]%10==4||map[y][i]%10==7) break;
    }
}

void changelight(char command){
    int intensity, base, layer;
    intensity=map[posy][posx]/100;
    base=(map[posy][posx]/10)%10;
    layer=map[posy][posx]%10;
    if(base==1||base==2||base==3||base==4||base==6){
            if(base==1) darkenup(posx,posy);
            else if(base==2) darkendown(posx,posy);
            else if(base==3) darkenleft(posx,posy);
            else if(base==4) darkenright(posx,posy);
            else if(base==6) map[posy][posx]+=100;
            if(intensity<1) intensity=1;
            if(command=='i') base=1;
            else if(command=='k') base=2;
            else if(command=='j') base=3;
            else if(command=='l') base=4;
            map[posy][posx]=100*intensity+10*base;
            printsuitable(posx,posy);
            printcharacter(posx,posy,face);
            if(base==1) lightenup(posx,posy);
            else if(base==2) lightendown(posx,posy);
            else if(base==3) lightenleft(posx,posy);
            else if(base==4) lightenright(posx,posy);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    Movement Section    //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void moveup(int x, int y){
    printsuitable(x,y);
    printsuitable(x,y-1);
    readimagefile("move_up_1.gif",60*x,60*y-10,60*(x+1), 60*(y+1)-10);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y-1);
    readimagefile("move_up_2.gif",60*x,60*y-20,60*(x+1),60*(y+1)-20);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y-1);
    readimagefile("move_up_3.gif",60*x,60*y-30,60*(x+1),60*(y+1)-30);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y-1);
    readimagefile("move_up_4.gif",60*x,60*y-40,60*(x+1),60*(y+1)-40);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y-1);
    readimagefile("move_up_5.gif",60*x,60*y-50,60*(x+1),60*(y+1)-50);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y-1);
    printcharacter(posx,posy-1,face);
    //readimagefile("move_up_6.gif",60*x,60*y-60,60*(x+1),60*(y+1)-60);
    delay(50);
}
void movedown(int x, int y){
    printsuitable(x,y);
    printsuitable(x,y+1);
    readimagefile("move_down_1.gif",60*x,60*y+10,60*(x+1), 60*(y+1)+10);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y+1);
    readimagefile("move_down_2.gif",60*x,60*y+20,60*(x+1),60*(y+1)+20);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y+1);
    readimagefile("move_down_3.gif",60*x,60*y+30,60*(x+1),60*(y+1)+30);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y+1);
    readimagefile("move_down_4.gif",60*x,60*y+40,60*(x+1),60*(y+1)+40);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y+1);
    readimagefile("move_down_5.gif",60*x,60*y+50,60*(x+1),60*(y+1)+50);
    delay(50);
    printsuitable(x,y);
    printsuitable(x,y+1);
    printcharacter(posx,posy+1,face);
    //readimagefile("move_down_6.gif",60*x,60*y+60,60*(x+1),60*(y+1)+60);
    delay(50);
}
void moveleft(int x, int y){
    printsuitable(x,y);
    printsuitable(x-1,y);
    readimagefile("move_left_1.gif",60*x-10,60*y,60*(x+1)-10, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x-1,y);
    readimagefile("move_left_2.gif",60*x-20,60*y,60*(x+1)-20, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x-1,y);
    readimagefile("move_left_3.gif",60*x-30,60*y,60*(x+1)-30, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x-1,y);
    readimagefile("move_left_4.gif",60*x-40,60*y,60*(x+1)-40, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x-1,y);
    readimagefile("move_left_5.gif",60*x-50,60*y,60*(x+1)-50, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x-1,y);
    printcharacter(posx-1,posy,face);
    //readimagefile("move_down_6.gif",60*x,60*y+60,60*(x+1),60*(y+1)+60);
    delay(50);
}
void moveright(int x, int y){
    printsuitable(x,y);
    printsuitable(x+1,y);
    readimagefile("move_right_1.gif",60*x+10,60*y,60*(x+1)+10, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x+1,y);
    readimagefile("move_right_2.gif",60*x+20,60*y,60*(x+1)+20, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x+1,y);
    readimagefile("move_right_3.gif",60*x+30,60*y,60*(x+1)+30, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x+1,y);
    readimagefile("move_right_4.gif",60*x+40,60*y,60*(x+1)+40, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x+1,y);
    readimagefile("move_right_5.gif",60*x+50,60*y,60*(x+1)+50, 60*(y+1));
    delay(50);
    printsuitable(x,y);
    printsuitable(x+1,y);
    printcharacter(posx+1,posy,face);
    //readimagefile("move_down_6.gif",60*x,60*y+60,60*(x+1),60*(y+1)+60);
    delay(50);
}
void pushup(int layer, int layer2){

            if(layer2==0&&layer==4){
                map[posy-1][posx]-=layer;

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy-2)+50,60*(posx+1)-1,60*(posy-1)+50);
                readimagefile("push_up_1.gif",60*(posx),60*(posy-1)+50,60*(posx-1)+1,60*(posy)+50);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy-2)+40,60*(posx+1)-1,60*(posy-1)+40);
                readimagefile("push_up_2.gif",60*(posx),60*(posy-1)+40,60*(posx-1)-1,60*(posy)+40);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy-2)+30,60*(posx+1)-1,60*(posy-1)+30);
                readimagefile("push_up_3.gif",60*(posx),60*(posy-1)+30,60*(posx+1)-1,60*(posy)+30);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy-2)+20,60*(posx+1)-1,60*(posy-1)+20);
                readimagefile("push_up_4.gif",60*(posx),60*(posy-1)+20,60*(posx+1)-1,60*(posy)+20);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy-2)+10,60*(posx+1)-1,60*(posy-1)+10);
                readimagefile("push_up_5.gif",60*(posx),60*(posy-1)+10,60*(posx+1)-1,60*(posy)+10);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy-2),60*(posx+1)-1,60*(posy-1));
                readimagefile("push_up_2.gif",60*(posx),60*(posy-1),60*(posx+1)-1,60*(posy));

                delay(100);
                map[posy-2][posx]+=layer;
                printsuitable(posx,--posy);
                printsuitable(posx,posy-1);
                printcharacter(posx,posy,face);
            }

            else if(layer2==0&&layer==2){
                map[posy-1][posx]-=layer;

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Glass.gip",60*(posx),60*(posy-2)+50,60*(posx+1)-1,60*(posy-1)+50);
                readimagefile("push_up_1.gif",60*(posx),60*(posy-1)+50,60*(posx-1)+1,60*(posy)+50);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy-2)+40,60*(posx+1)-1,60*(posy-1)+40);
                readimagefile("push_up_2.gif",60*(posx),60*(posy-1)+40,60*(posx-1)-1,60*(posy)+40);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy-2)+30,60*(posx+1)-1,60*(posy-1)+30);
                readimagefile("push_up_3.gif",60*(posx),60*(posy-1)+30,60*(posx+1)-1,60*(posy)+30);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy-2)+20,60*(posx+1)-1,60*(posy-1)+20);
                readimagefile("push_up_4.gif",60*(posx),60*(posy-1)+20,60*(posx+1)-1,60*(posy)+20);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy-2)+10,60*(posx+1)-1,60*(posy-1)+10);
                readimagefile("push_up_5.gif",60*(posx),60*(posy-1)+10,60*(posx+1)-1,60*(posy)+10);
                delay(100);

                printsuitable(posx,posy-2);
                printsuitable(posx,posy-1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy-2),60*(posx+1)-1,60*(posy-1));
                readimagefile("push_up_2.gif",60*(posx),60*(posy-1),60*(posx+1)-1,60*(posy));

                delay(100);
                map[posy-2][posx]+=layer;
                printsuitable(posx,--posy);
                printsuitable(posx,posy-1);
                printcharacter(posx,posy,face);
            }

}
void pushdown(int layer, int layer2){

            if(layer2==0&&layer==4){
                map[posy+1][posx]-=layer;

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy+2)-50,60*(posx+1)-1,60*(posy+1)-50);
                readimagefile("push_down_1.gif",60*(posx),60*(posy+1)-50,60*(posx+1)+1,60*(posy)-50);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy+2)-40,60*(posx+1)-1,60*(posy+1)-40);
                readimagefile("push_down_2.gif",60*(posx),60*(posy+1)-40,60*(posx-1)-1,60*(posy)-40);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy+2)-30,60*(posx+1)-1,60*(posy+1)-30);
                readimagefile("push_down_3.gif",60*(posx),60*(posy+1)-30,60*(posx+1)-1,60*(posy)-30);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy+2)-20,60*(posx+1)-1,60*(posy+1)-20);
                readimagefile("push_down_4.gif",60*(posx),60*(posy+1)-20,60*(posx+1)-1,60*(posy)-20);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy+2)-10,60*(posx+1)-1,60*(posy+1)-10);
                readimagefile("push_down_5.gif",60*(posx),60*(posy+1)-10,60*(posx+1)-1,60*(posy)-10);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx),60*(posy+2),60*(posx+1)-1,60*(posy+1));
                readimagefile("push_down_2.gif",60*(posx),60*(posy+1),60*(posx+1)-1,60*(posy));

                delay(100);
                map[posy+2][posx]+=layer;
                printsuitable(posx,++posy);
                printsuitable(posx,posy+1);
                printcharacter(posx,posy,face);
            }

            else if(layer2==0&&layer==2){
                map[posy+1][posx]-=layer;

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy+2)-50,60*(posx+1)-1,60*(posy+1)-50);
                readimagefile("push_down_1.gif",60*(posx),60*(posy+1)-50,60*(posx+1)+1,60*(posy)-50);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy+2)-40,60*(posx+1)-1,60*(posy+1)-40);
                readimagefile("push_down_2.gif",60*(posx),60*(posy+1)-40,60*(posx-1)-1,60*(posy)-40);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy+2)-30,60*(posx+1)-1,60*(posy+1)-30);
                readimagefile("push_down_3.gif",60*(posx),60*(posy+1)-30,60*(posx+1)-1,60*(posy)-30);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy+2)-20,60*(posx+1)-1,60*(posy+1)-20);
                readimagefile("push_down_4.gif",60*(posx),60*(posy+1)-20,60*(posx+1)-1,60*(posy)-20);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy+2)-10,60*(posx+1)-1,60*(posy+1)-10);
                readimagefile("push_down_5.gif",60*(posx),60*(posy+1)-10,60*(posx+1)-1,60*(posy)-10);
                delay(100);

                printsuitable(posx,posy+2);
                printsuitable(posx,posy+1);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx),60*(posy+2),60*(posx+1)-1,60*(posy+1));
                readimagefile("push_down_2.gif",60*(posx),60*(posy+1),60*(posx+1)-1,60*(posy));

                delay(100);
                map[posy+2][posx]+=layer;
                printsuitable(posx,++posy);
                printsuitable(posx,posy+1);
                printcharacter(posx,posy,face);
            }

}
void pushleft(int layer, int layer2){

            if(layer2==0&&layer==4){
                map[posy][posx-1]-=layer;

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx-1)-10,60*(posy),60*(posx-2)-9,60*(posy-1)+1);
                readimagefile("push_left_1.gif",60*posx-10,60*posy,60*(posx-1)-9,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx-1)-20,60*(posy),60*(posx-2)-19,60*(posy-1)+1);
                readimagefile("push_left_2.gif",60*posx-20,60*posy,60*(posx-1)-19,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx-1)-30,60*(posy),60*(posx-2)-29,60*(posy-1)+1);
                readimagefile("push_left_3.gif",60*posx-30,60*posy,60*(posx-1)-29,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx-1)-40,60*(posy),60*(posx-2)-39,60*(posy-1)+1);
                readimagefile("push_left_4.gif",60*posx-40,60*posy,60*(posx-1)-39,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx-1)-50,60*(posy),60*(posx-2)-49,60*(posy-1)+1);
                readimagefile("push_left_5.gif",60*posx-50,60*posy,60*(posx-1)-49,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx-1)-60,60*(posy),60*(posx-2)-59,60*(posy-1)+1);
                readimagefile("push_left_2.gif",60*posx-60,60*posy,60*(posx-1)-59,60*(posy-1)+1);

                delay(100);
                map[posy][posx-2]+=layer;
                printsuitable(--posx,posy);
                printsuitable(posx-1,posy);
                printcharacter(posx,posy,face);
            }

            else if(layer2==0&&layer==2){
                map[posy][posx-1]-=layer;
                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx-1)-10,60*(posy),60*(posx-2)-9,60*(posy-1)+1);
                readimagefile("push_left_1.gif",60*posx-10,60*posy,60*(posx-1)-9,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx-1)-20,60*(posy),60*(posx-2)-19,60*(posy-1)+1);
                readimagefile("push_left_2.gif",60*posx-20,60*posy,60*(posx-1)-19,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx-1)-30,60*(posy),60*(posx-2)-29,60*(posy-1)+1);
                readimagefile("push_left_3.gif",60*posx-30,60*posy,60*(posx-1)-29,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx-1)-40,60*(posy),60*(posx-2)-39,60*(posy-1)+1);
                readimagefile("push_left_4.gif",60*posx-40,60*posy,60*(posx-1)-39,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx-1)-50,60*(posy),60*(posx-2)-49,60*(posy-1)+1);
                readimagefile("push_left_5.gif",60*posx-50,60*posy,60*(posx-1)-49,60*(posy-1)+1);
                delay(100);

                printsuitable(posx-2,posy);
                printsuitable(posx-1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx-1)-60,60*(posy),60*(posx-2)-59,60*(posy-1)+1);
                readimagefile("push_left_2.gif",60*posx-60,60*posy,60*(posx-1)-59,60*(posy-1)+1);

                delay(100);
                map[posy][posx-2]+=layer;
                printsuitable(--posx,posy);
                printsuitable(posx-1,posy);
                printcharacter(posx,posy,face);
            }
}
void pushright(int layer, int layer2){

            if(layer2==0&&layer==4){
                map[posy][posx+1]-=layer;
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx+1)+10,60*(posy),60*(posx+2)+9,60*(posy+1)-1);
                readimagefile("push_right_1.gif",60*posx+10,60*posy,60*(posx+1)+9,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx+1)+20,60*(posy),60*(posx+2)+19,60*(posy+1)-1);
                readimagefile("push_right_2.gif",60*posx+20,60*posy,60*(posx+1)+19,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx+1)+30,60*(posy),60*(posx+2)+29,60*(posy+1)-1);
                readimagefile("push_right_3.gif",60*posx+30,60*posy,60*(posx+1)+29,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx+1)+40,60*(posy),60*(posx+2)+39,60*(posy+1)-1);
                readimagefile("push_right_4.gif",60*posx+40,60*posy,60*(posx+1)+39,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx+1)+50,60*(posy),60*(posx+2)+49,60*(posy+1)-1);
                readimagefile("push_right_5.gif",60*posx+50,60*posy,60*(posx+1)+49,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Block.jpg",60*(posx+1)+60,60*(posy),60*(posx+2)+59,60*(posy+1)-1);
                readimagefile("push_right_2.gif",60*posx+60,60*posy,60*(posx+1)+59,60*(posy+1)-1);
                delay(100);
                map[posy][posx+2]+=layer;
                printsuitable(++posx,posy);
                printsuitable(posx+1,posy);
                printcharacter(posx,posy,face);
            }

            else if(layer2==0&&layer==2){
                map[posy][posx+1]-=layer;
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx+1)+10,60*(posy),60*(posx+2)+9,60*(posy+1)-1);
                readimagefile("push_right_1.gif",60*posx+10,60*posy,60*(posx+1)+9,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx+1)+20,60*(posy),60*(posx+2)+19,60*(posy+1)-1);
                readimagefile("push_right_2.gif",60*posx+20,60*posy,60*(posx+1)+19,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx+1)+30,60*(posy),60*(posx+2)+29,60*(posy+1)-1);
                readimagefile("push_right_3.gif",60*posx+30,60*posy,60*(posx+1)+29,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx+1)+40,60*(posy),60*(posx+2)+39,60*(posy+1)-1);
                readimagefile("push_right_4.gif",60*posx+40,60*posy,60*(posx+1)+39,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx+1)+50,60*(posy),60*(posx+2)+49,60*(posy+1)-1);
                readimagefile("push_right_5.gif",60*posx+50,60*posy,60*(posx+1)+49,60*(posy+1)-1);
                delay(100);
                printsuitable(posx+2,posy);
                printsuitable(posx+1,posy);
                printsuitable(posx,posy);
                readimagefile("Glass.gif",60*(posx+1)+60,60*(posy),60*(posx+2)+59,60*(posy+1)-1);
                readimagefile("push_right_2.gif",60*posx+60,60*posy,60*(posx+1)+59,60*(posy+1)-1);
                delay(100);
                map[posy][posx+2]+=layer;
                printsuitable(++posx,posy);
                printsuitable(posx+1,posy);
                printcharacter(posx,posy,face);
            }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////      Loading And Saving Section    ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void loadmap(int command){
     int meh, reen;

    level=fopen("status.lvl","r");
    fscanf(level,"%d",&maxlevel);
    fclose(level);

    if(command==1){
        flag=0;
        level=fopen("level1.lvl","r");
        fscanf(level,"%d %d %d",&posx,&posy,&face);
        fscanf(level,"%d %d",&endx,&endy);
        for(meh=0; meh<12;meh++){
            for(reen=0; reen<23;reen++) fscanf(level,"%d",&map[meh][reen]);
        }
        for(meh=0;meh<10;meh++) fscanf(level,"%d %d",&aix[meh],&aiy[meh]);
        fclose(level);
    }
    else if(command==2){
        level=fopen("level2.lvl","r");
        fscanf(level,"%d %d %d",&posx,&posy,&face);
        fscanf(level,"%d %d",&endx,&endy);
        for(meh=0; meh<12;meh++){
            for(reen=0; reen<23;reen++) fscanf(level,"%d",&map[meh][reen]);
        }
        for(meh=0;meh<10;meh++) fscanf(level,"%d %d",&aix[meh],&aiy[meh]);
        fclose(level);
    }
    else if(command==3){
        level=fopen("level3.lvl","r");
        fscanf(level,"%d %d %d",&posx,&posy,&face);
        fscanf(level,"%d %d",&endx,&endy);
        for(meh=0; meh<12;meh++){
            for(reen=0; reen<23;reen++) fscanf(level,"%d",&map[meh][reen]);
        }
        for(meh=0;meh<10;meh++) fscanf(level,"%d %d",&aix[meh],&aiy[meh]);
        fclose(level);
    }
    else if(command==4){
        level=fopen("level4.lvl","r");
        fscanf(level,"%d %d %d",&posx,&posy,&face);
        fscanf(level,"%d %d",&endx,&endy);
        for(meh=0; meh<12;meh++){
            for(reen=0; reen<23;reen++) fscanf(level,"%d",&map[meh][reen]);
        }
        for(meh=0;meh<10;meh++) fscanf(level,"%d %d",&aix[meh],&aiy[meh]);
        fclose(level);
    }
    else if(command==5){
        level=fopen("level5.lvl","r");
        fscanf(level,"%d %d %d",&posx,&posy,&face);
        fscanf(level,"%d %d",&endx,&endy);
        for(meh=0; meh<12;meh++){
            for(reen=0; reen<23;reen++) fscanf(level,"%d",&map[meh][reen]);
        }
        for(meh=0;meh<10;meh++) fscanf(level,"%d %d",&aix[meh],&aiy[meh]);
        fclose(level);
    }
}
void loadsave(){//keep track in which level is the game being played
     int meh, reen;
    level=fopen("status.lvl","r");
    fscanf(level,"%d",&maxlevel);
    fclose(level);
    level=fopen("Savedata.sve","r");
    fscanf(level,"%d\n",&currentlevel);
    fscanf(level,"%d %d %d",&posx,&posy,&face);
    fscanf(level,"%d %d",&endx,&endy);
    for(meh=0; meh<12;meh++){
        for(reen=0; reen<23;reen++) fscanf(level,"%d",&map[meh][reen]);
    }
    for(meh=0;meh<10;meh++) fscanf(level,"%d %d",&aix[meh],&aiy[meh]);
    fclose(level);
}
void savegame(){
    if(currentlevel>maxlevel){
        level=fopen("status.lvl","w");
        fprintf(level,"%d",currentlevel);
        fclose(level);
    }
    int meh, reen;
    level=fopen("Savedata.sve","w");
    fprintf(level,"%d\n",currentlevel);
    fprintf(level,"%d %d\n%d\n",posx,posy,face);
    fprintf(level,"%d %d\n",endx,endy);
    for(meh=0; meh<12;meh++){
        for(reen=0; reen<23;reen++) fprintf(level,"%d ", map[meh][reen]);
        fprintf(level,"\n");
    }
    for(meh=0;meh<10;meh++) fprintf(level,"%d %d\n", aix[meh], aiy[meh]);
    fclose(level);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     Main Function    //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int i,j;
    char command;
    flag=0;
    initwindow(1380,720,"Dodge the Darkness");
    currentlevel=printhome();
    while(1){
        if(currentlevel==1) flag=tutorial(posx,posy,flag);
        if(currentlevel==6) currentlevel=printhome();
        if(currentlevel==-1) loadsave();
        else loadmap(currentlevel);
        if(currentlevel==1) story();
        savegame();
        cleardevice();
        printmap();
        printcharacter(posx,posy,face);
        while(1){
            if(currentlevel==1) flag=tutorial(posx,posy,flag);
            command=getch();
            if(command=='w'||command=='a'||command=='s'||command=='d') move(command);
            else if(command=='i'||command=='j'||command=='k'||command=='l'){
              changelight(command);
              if(currentlevel==1) flag=tutorial(posx,posy,flag);
            }
            else if(command=='m') return 0;
            else if(command=='r'){
                loadmap(currentlevel);
                cleardevice();
                printmap();
                printcharacter(posx,posy,face);
            }
            else if(command=='\b'){
                loadsave();
                printmap();
                printcharacter(posx,posy,face);
            }
            else if(command==9) { //tab
                savegame();
            }
            else if(command==27){//esc
                currentlevel=printhome();
                break;
            }
            while(kbhit()>=1) getch(); //smooth controlling
            aisilentkill();
            aikill();
            printend(endx,endy);
            if(endx==posx&&endy==posy){
                currentlevel++;
                if(currentlevel>maxlevel){
                    readimagefile("Unlock.jpg",0,0,1380,760);
                    getch();
                }
                else {
                    readimagefile("Newlevel.jpg",0,0,1380,760);
                    getch();
                }
                break;
            }
        }
    }

    return 0;
}


//__________________________________________________________________________
//______________________Explanation Section_____________________________________
//__________________________________________________________________________

void lightensuitable(int x, int y){
    int intensity, base, layer;
    intensity=map[y][x]/100;
    base=(map[y][x]/10)%10;
    layer=map[y][x]%10;
    if(intensity>=1) {
            if(base==0) lightenpath(x,y);
            else if(base==1) printdir(x,y,1);
            else if(base==2) printdir(x,y,2);
            else if(base==3) printdir(x,y,3);
            else if(base==4) printdir(x,y,4);
            else if(base==5) printlight(x,y);
            else if(base==6) printinactiveport(x,y);
            else if(base==7) printwall(x,y);

            if(layer==2) printglass(x,y);
            else if(layer==4) printblock(x,y);
            else if(layer==7) printwall(x,y);
    }
    else printdarkness(x, y);
}
void move(char command){
    int base, layer, base2, layer2, i;
    if(command=='w'){
        face=1;
        printsuitable(posx,posy);
        printcharacter(posx,posy,face);
        base=(map[posy-1][posx]/10)%10;
        layer=map[posy-1][posx]%10;
         if(base<=6&&layer==0&&map[posy-1][posx]>=100){
            moveup(posx,posy);
            posy--;
        }
        else if(base<=6&&map[posy-1][posx]>=100&&layer!=5){
            base2=(map[posy-2][posx]/10)%10;
            layer2=map[posy-2][posx]%10;
            pushup(layer,layer2);
        }
    }
    else if (command=='s'){
        face=2;
        printsuitable(posx,posy);
        printcharacter(posx,posy,face);
        base=(map[posy+1][posx]/10)%10;
        layer=map[posy+1][posx]%10;
        if(base<=6&&layer==0&&map[posy+1][posx]>=100){
            movedown(posx,posy);
            posy++;
        }
        else if(base<=6&&map[posy+1][posx]>=100&&layer!=5){
            base2=(map[posy+2][posx]/10)%10;
            layer2=map[posy+2][posx]%10;
            pushdown(layer,layer2);
        }
    }
    else if (command=='a'){
        face=3;
        printsuitable(posx,posy);
        printcharacter(posx,posy,face);
        base=(map[posy][posx-1]/10)%10;
        layer=map[posy][posx-1]%10;
         if(base<=6&&layer==0&&map[posy][posx-1]>=100){
            moveleft(posx,posy);
            posx--;
        }
        else if(base<=6&&map[posy][posx-1]>=100&&layer!=5){
            base2=(map[posy][posx-2]/10)%10;
            layer2=map[posy][posx-2]%10;
            pushleft(layer,layer2);
        }
    }
    else if (command=='d'){
        face=4;
        printsuitable(posx,posy);
        printcharacter(posx,posy,face);
        base=(map[posy][posx+1]/10)%10;
        layer=map[posy][posx+1]%10;
         if(base<=6&&layer==0&&map[posy][posx+1]>=100){
            moveright(posx,posy);
            posx++;
        }
        else if(base<=6&&map[posy][posx+1]>=100&&layer!=5){
            base2=(map[posy][posx+2]/10)%10;
            layer2=map[posy][posx+2]%10;
            pushright(layer,layer2);
        }
    }
}



/*Base list:
//% 0-Regular Grid
//% 2==down
//% 1==up
//% 3==left
//% 4==right
//% 5==light
//% 6==inactive port
//% 7==wall

//Layer list:
//% 1==glass
//% 2== mirror up-left
//% 3==mirror down-left
//% 4==block
//% 7==wall
//< 100 dark*/
