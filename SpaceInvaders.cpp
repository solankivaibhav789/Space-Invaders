#include <iostream>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;
int y=30,m=y*2;
//int shipPts[8] = {320,410,350,460,290,460,320,410};
int shipPts[24]={330,419,340,429,350,429,360,479,350,479,340,450,320,450,310,479,300,479,310,429,320,429,330,419};
/*int objectPts[80] = {40,100,70,100,100,100,130,100,160,100,190,100,220,100,250,100,280,100,310,100,340,100,370,100,400,100,430,100,460,100,490,100,520,100,
        40,100-y,70,100-y,100,100-y,130,100-y,160,100-y,190,100-y,220,100-y,250,100-y,280,100-y,310,100-y,340,100-y,370,100-y,400,100-y,430,100-y,460,100-y,490,100-y,520,100-y};
*/
int objectPts[81] = {40,100,70,100-y,100,100,130,100-y,160,100,190,100-y,220,100,250,100-y,280,100,310,100-y,340,100,370,100-y,400,100,430,100-y,460,100,490,100-y,520,100,
                        280,50,
        40,100-y*3-20,70,100-y*4-20,100,100-y*3-20,130,100-y*4-20,160,100-y*3-20,190,100-y*4-20,220,100-y*3-20,250,100-y*4-20,280,100-y*3-20,310,100-y*4-20,340,100-y*3-20,370,100-y*4-20,400,100-y*3-20,430,100-y*4-20,460,100-y*3-20,490,100-y*4-20,520,100-y*3-20};


int shipSpeed = 4;
int bulletSpeed = 5;
int isRunnig=0;
int score = 0;
int n_bullet = 0;
int bulletPts[1024];
int firePts[1024];
int n_fire = 0;
int fireSpeed = 5;
int keyPressed = 0;
int objectSpeed = 4;
int temp=0;
int safeLine = 410;
int totalObj = 17*2+1;
int isGameOver = 0;
int boss_hit = 5;
int gunPts[1024];
int n_Gun = 0;
int gunSpeed = 5;
int life = 5;
void drawShip(){
    fillpoly(12,shipPts);
}
void showPts(int score){
    char msg[10];
    setcolor(YELLOW);
    settextstyle(9,HORIZ_DIR,1);
    snprintf(msg,sizeof(msg),"Score:%d",score);
    outtextxy(500,5,msg);
}
void drawBullets(){
    setcolor(BLUE);
    for(int i = 0,j=0 ; i < n_bullet ; i ++,j=j+2){
        rectangle(bulletPts[j]-3,bulletPts[j+1],bulletPts[j]+3,bulletPts[j+1]+10);
        bulletPts[j+1] -= bulletSpeed;
    }
}
void drawFire(){
    setcolor(YELLOW);
    for(int i = 0,j=0 ; i < n_fire ; i ++,j=j+2){
        circle(firePts[j],firePts[j+1],5);
        firePts[j+1] += fireSpeed;
    }
}
void drawGun(){
    if(objectPts[35]>0){
    int length = shipPts[1] - 20;
                        float del_X = shipPts[0] - 280 ;
                        del_X = del_X/length;
                        int del_Y = 1;

    for(int i = 0,j=0 ; i < n_Gun ; i ++,j=j+2){
        setcolor(RED);
       // floodfill(gunPts[j],gunPts[j+1],RED);
        circle(gunPts[j],gunPts[j+1],5);
        gunPts[j] += del_X*5;
        gunPts[j+1] += del_Y*5;
    }
    }
}


void drawObject(){
    for(int i = 0,j=0 ; i < 17*2+1; i++,j = j + 2){
            if(i==17){
        bar(objectPts[j],objectPts[j+1],objectPts[j]+40,objectPts[j+1]+40);//for filled rectangle
            }
            else{
        bar(objectPts[j],objectPts[j+1],objectPts[j]+20,objectPts[j+1]+20);//for filled rectangle
            }
        if(temp==20){
                if(i!=17){
        objectPts[j+1] += objectSpeed;}
        }
    }
    if(temp==20){temp=0;}
    temp++;
}


void checkCollision(){
    int width = 20;
    if(totalObj<=0){
        isGameOver = 1;
    }
    for(int i = 0,a=0 ; i < 17*2+1 ;i++,a=a+2){
        if(objectPts[a+1]>=safeLine-20){
                isGameOver=2;
        }
        for(int j = 0,k=0 ; j < n_bullet ; j++,k=k+2){
            if(bulletPts[k+1]>0){
                    if(a==34){
                        width = 40;
                    }else{width = 20;}
                if(objectPts[a]<=bulletPts[k] && bulletPts[k]<=objectPts[a]+width){
                    if(objectPts[a+1]<=bulletPts[k+1] && bulletPts[k+1]<=objectPts[a+1]+width){
                        if(a==34 && boss_hit!=0){
                            score=score+10;
                            boss_hit--;
                            bulletPts[k+1]=-1000;
                            // objectPts[a+1]=-1000;
                        }
                        else{
                        PlaySoundA(TEXT("invaderkilled.wav"),NULL,SND_ASYNC);
                        objectPts[a+1] = -1000;
                        bulletPts[k+1] = -1000;
                        score = score + 10;
                        totalObj--;
                        }

                    }
                }
            }
        }
    }
}
void drawLife()
{
    setcolor(YELLOW);
    outtextxy(10,5,"Life: ");
    setfillstyle(SOLID_FILL,RED);
    bar(70,5,70+life*20,25);
}
void checkCollisionShip(){

        for(int j = 0,k=0 ; j < n_Gun ; j++,k=k+2){
            if(gunPts[k+1]>0){

                if(shipPts[16]<=gunPts[k] && gunPts[k]<=shipPts[6]){
                    if(shipPts[1]<=gunPts[k+1] && gunPts[k+1]<=shipPts[7]){
                        life--;
                        gunPts[k+1]=1000;

                        if(life==0)
                            isGameOver = 2;
                    }
                }
            }
        }
        for(int j = 0,k=0 ; j < n_fire ; j++,k=k+2){
            if(firePts[k+1]>0){

                if(shipPts[16]<=firePts[k] && firePts[k]<=shipPts[6]){
                    if(shipPts[1]<=firePts[k+1] && firePts[k+1]<=shipPts[7]){
                        life--;
                        firePts[k+1]=1000;

                        if(life==0)
                            isGameOver = 2;
                    }
                }
            }
        }
}

int main()
{
    int gd=DETECT,gm;
    char msg[20];
    initgraph(&gd,&gm,"");
    setbkcolor(0);
     //PlaySoundA(TEXT("game.wav"),NULL,SND_ASYNC);
    while(1){

            if(isGameOver){
                break;
            }
            //line(0,safeLine,640,safeLine);
            if(isRunnig == 0){
                outtextxy(200,200,"Press Any Key To Start Game.");
                getch();
                isRunnig = 1;
            }

            if(GetAsyncKeyState(VK_RIGHT)){
                if(shipPts[6] < 630){
                    for(int i = 0 ; i < 24 ; i = i + 2){
                        shipPts[i]+=shipSpeed;
                    }
                }
            }else if(GetAsyncKeyState(VK_LEFT)){
                if(shipPts[16] > 0){
                    for(int i = 0 ; i < 24 ; i = i + 2){
                        shipPts[i]-=shipSpeed;
                    }
                }
            }else if(GetAsyncKeyState(VK_SPACE)){

                    PlaySoundA(TEXT("shoot.wav"),NULL,SND_ASYNC);
                    //Beep(800,100);
                    if(keyPressed==0){
                        bulletPts[n_bullet*2] = shipPts[0]; //x-coordinate same as ship center pt
                        bulletPts[n_bullet*2+1] = shipPts[1];//y-coordinate
                        n_bullet++;
                        n_bullet = n_bullet%1024;
                        keyPressed = 1;
                    }

            }else if(GetKeyState(VK_SPACE)>=0){ //for key unpressed
                keyPressed=0;
            }
            int r = rand()%100;
            if(r>95){
                    r = rand()%81;
                        if(objectPts[r]>0){
                        firePts[n_fire*2] = objectPts[r]; //x-coordinate
                        firePts[n_fire*2+1] = objectPts[r+1];//y-coordinate
                        n_fire++;
                        n_fire = n_fire%1024;
                        }

            }
            //Boss Firing Gun
            if(objectPts[35]>0)
            {r = rand()%100;
                if(r>95){
                        gunPts[n_Gun*2] = 300; //x-coordinate same as ship center pt
                        gunPts[n_Gun*2+1] = 60;//y-coordinate
                        n_Gun++;
                        n_Gun = n_Gun%1024;
                }
            }


            drawShip();
            drawBullets();
            drawFire();
            drawGun();
            drawObject();
            checkCollision();
            checkCollisionShip();
            setfillstyle(SOLID_FILL,BLACK);
            bar(0,0,640,30);
            showPts(score);
            drawLife();
             setfillstyle(SOLID_FILL,WHITE);

            delay(40);
            cleardevice();
    }

    if(isGameOver==1){
    snprintf(msg,sizeof(msg),"Your Score:%d",score);
    while(1){

    setcolor(GREEN);
    settextstyle(8,HORIZ_DIR,1);
    outtextxy(240,200,"You Won");
    setcolor(WHITE);
    outtextxy(240,220,msg);

    outtextxy(240,240,"Press ESC to Exit");
        if(GetAsyncKeyState(VK_ESCAPE)){
            return 0;
        }
        delay(40);
         cleardevice();
    }}
    else{
        snprintf(msg,sizeof(msg),"Your Score:%d",score);
    while(1){
    //PlaySoundW(TEXT(""),NULL,SND_NOWAIT);
    setcolor(RED);
    settextstyle(8,HORIZ_DIR,1);
    outtextxy(240,200,"Game Over");
    setcolor(WHITE);

    outtextxy(240,220,msg);
    outtextxy(240,240,"Press ESC to Exit");
        if(GetAsyncKeyState(VK_ESCAPE)){
            return 0;
        }
        delay(60);
         cleardevice();
    }
    }
    return 0;
}
