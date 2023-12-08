#include "TXLib.h"
#include <cstdlib>

struct Ball{
    int x = 400;
    int y = 250;
    int r = 10;
    int dx = 3 - random(2)*6;
    int dy = 3 - random(2)*6;
    int counter = 0;
    void m0ve();
    void draw();};

struct Bita{
    int x = 0;
    int y = 200;
    int hight = 100;
    int weight = 10;
    int dx = 7;
    int dy = 7;
    void m0veUp();
    void m0veDown();
    void draw();};

struct HP{
    int hp = 3;
    int maxhp = 3;
    int y = 10;
    int r = 10;
    int x = 50;
    int dx = 20;
    void draw();};

bool game = true;

Ball ball;
Bita bitaL;
Bita bitaR;
HP hp1;
HP hp2;


int main(){
    txCreateWindow(800, 500);
    txSetFillColour(TX_BLACK);
    txTextCursor(false);

    hp2.x = 750;
    hp2.dx = -20;
    bitaL.x = 20;
    bitaR.x = 770;

    while (true){
        txSelectFont ("Comic Sans MS", 40);
        txTextOut(320, 200, "БЕЙ МЯЧИ");
        txSelectFont ("Comic Sans MS", 15);
        txTextOut(310, 450, "Нажмите ПРОБЕЛ чтобы начать");
        if (GetAsyncKeyState (VK_SPACE)) break;}


    while(!GetAsyncKeyState (VK_ESCAPE)){

        if (hp1.hp == 0 or hp2.hp == 0){
            txSelectFont ("Comic Sans MS", 30);
            if (hp1.hp == 0) {txTextOut(280, 200, "Игрок справа победил!");}
            if (hp2.hp == 0) {txTextOut(285, 200, "Игрок слева победил!");}
            txSelectFont ("Comic Sans MS", 15);
            txTextOut(310, 450, "Нажмите ESCAPE чтобы выйти");
            txTextOut(290, 430, "Нажмите ПРОБЕЛ чтобы начать заново");
            if (GetAsyncKeyState (VK_SPACE)){
                hp1.hp = (hp1.maxhp);
                hp2.hp = (hp2.maxhp);}}

        if (game==false){
            txSelectFont ("Comic Sans MS", 30);
            txTextOut(350, 200, "ПАУЗА");
            txSelectFont ("Comic Sans MS", 15);
            txTextOut(310, 450, "Нажмите ESCAPE чтобы выйти");
            txTextOut(290, 430, "Нажмите ПРОБЕЛ чтобы продолжить");
            if (GetAsyncKeyState (VK_SPACE)) {
                game = true;
                txClear();}}

        if (game==true and hp1.hp > 0 and hp2.hp > 0){

        if (GetAsyncKeyState ('P')){
            txClear();
            game = false;
            continue;}

        txBegin();

        if (GetAsyncKeyState ('S')){bitaL.m0veDown();}
        if (GetAsyncKeyState ('W')){bitaL.m0veUp();}
        if (GetAsyncKeyState (VK_DOWN)){bitaR.m0veDown();}
        if (GetAsyncKeyState (VK_UP)){bitaR.m0veUp();}

        if (ball.counter == 3){
            ball.dx += 1;
            ball.dy += 1;
            ball.counter = 0;}

        ball.m0ve();

        txClear();

        ball.draw();
        bitaR.draw();
        bitaL.draw();
        hp1.draw();
        hp2.draw();
        txSelectFont ("Comic Sans MS", 15);
        txTextOut(380, 5, "Пауза 'P'");

        if (hp1.hp == 0 or hp2.hp == 0) txClear();

        txEnd();
        txSleep(5);}}

    txClear();
    txSelectFont ("Comic Sans MS", 30);
    if (hp1.hp == 0) txTextOut(280, 200, "Игрок справа победил!");
    if (hp2.hp == 0) txTextOut(285, 200, "Игрок слева победил!");
    if (hp1.hp > 0 and hp2.hp > 0) txTextOut(345, 200, "ВЫХОД");
    txSelectFont ("Comic Sans MS", 15);
    txTextOut(310, 450, "Нажмите ESCAPE чтобы выйти");}

void Ball::m0ve(){

    if (y < 10 or y > 490) dy = -dy;

    if ((x < 780 and x > 760) and y > (bitaR.y - 5) and y < (bitaR.y + 105)){
        dx = -dx;
        x = 760;
        if (dx < 8) counter += 1;}

    if ((x > 20 and x < 40) and y > (bitaL.y - 5) and y < (bitaL.y + 105)){
        dx = -dx;
        x = 40;
        if (dx < 8) counter += 1;}

    if (x < 0){
    hp1.hp -= 1;
    x = 400;
    y = 250;
    dx = 5 - random(2)*10;
    dy = 5 - random(2)*10;}

    if (x > 800){
    hp2.hp -= 1;
    x = 400;
    y = 250;
    dx = 5 - random(2)*10;
    dy = 5 - random(2)*10;}

    x += dx;
    y += dy;}

void Ball::draw(){
    txCircle(x, y, r);}

void Bita::m0veUp(){
    if (y > 2) y -= dy;}

void Bita::m0veDown(){
    if (y < 398) y += dy;}

void Bita::draw(){
    txRectangle(x, y, x + weight, y + hight);}

void HP::draw(){
    int hhp = hp;
    int f = 0;
    while (hhp > 0){
        txCircle(x + (dx * f), y, r);
        f += 1;
        hhp -= 1;}}
