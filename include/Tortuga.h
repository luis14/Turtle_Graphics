#ifndef TORTUGA_H
#define TORTUGA_H

#include <winbgim.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <math.h>
#include "LinkedList.h"
#include <fstream>

#define BLACK	0
#define BLUE	1
#define GREEN	2
#define CYAN	3
#define RED	4
#define MAGENTA	5
#define BROWN	6
#define LIGHTGRAY	7
#define DARKGRAY	8
#define LIGHTBLUE	9
#define LIGHTGREEN	10
#define LIGHTCYAN	11
#define LIGHTRED	12
#define LIGHTMAGENTA	13
#define YELLOW	14
#define WHITE	15

using namespace std;

class Tortuga{
private:
    int posX;
    int posY;
    int grosor;
    int direccion;
    bool penDown;
    string colorLinea;
    int colorLineaRGB[3];
public:
    Tortuga(int ancho, int alto){
        posX = 400;
        posY = 300;
        grosor = 1;
        direccion = 0;
        penDown = true;
        colorLinea = "white";
        initwindow(ancho,alto);
        moveto(400,300);
    }
    ~Tortuga(){
    }
    void forward(int unidades){
        posX += cos(direccion*M_PI/180)*unidades;
        posY -= sin(direccion*M_PI/180)*unidades;
        graficador();
    }
    void back(int unidades){
        posX -= cos(direccion*M_PI/180)*unidades;
        posY += sin(direccion*M_PI/180)*unidades;
        graficador();
    }
    void right(int grados){
        direccion = (direccion + 360 - grados) % 360;
    }
    void left(int grados){
        direccion += grados % 360;
    }
    void setpos(int x, int y){
        posX = x;
        posY = y;
        graficador();
    }
    void setx(int x){
        posX = x;
        graficador();
    }
    void sety(int y){
        posY = y;
        graficador();
    }
    void setheading(int grados){
        direccion = grados % 360;
    }
    void home(){
        direccion = 0;
        posX = 400;
        posY = 300;
        graficador();
    }
    void circleFuncion(int radio){
        if(radio<0){
            int tempX, tempY;
            direccion-=90;
            tempX = posX + cos(direccion*M_PI/180)*abs(radio);
            tempY = posY + sin(direccion*M_PI/180)*abs(radio);
            circle(tempX,tempY,abs(radio));
            direccion+=90;
        }
        else{
            int tempX, tempY;
            direccion+=90;
            tempX = posX + cos(direccion*M_PI/180)*abs(radio);
            tempY = posY + sin(direccion*M_PI/180)*abs(radio);
            circle(tempX,tempY,abs(radio));
            direccion-=90;
        }
    }
    void pos(){
        cout<<"\nLa tortuga se encuentra en X = "<<posX<<" y Y = "<<posY<<"\n";
    }
    void xcor(){
        cout<<"\nLa tortuga se encuentra en X = "<<posX<<"\n";
    }
    void ycor(){
        cout<<"\nLa tortuga se encuentra en Y = "<<posY<<"\n";
    }
    void heading(){
        cout<<"\nLa tortuga se encuentra con rumbo de "<<direccion<<" grados\n";
    }
    void pendown(){
        penDown=true;
    }
    void penup(){
        penDown=false;
    }
    void pensize(int pGrosor){
        grosor = pGrosor;
        setlinestyle(1, 1, grosor);
    }
    void colorLineaFuncion(int R, int G, int B){
        colorLinea = "nulo";
        colorLineaRGB[0] = R;
        colorLineaRGB[1] = G;
        colorLineaRGB[2] = B;
    }
    void colorLineaFuncion(string pColor){
        colorLinea = pColor;
        colorLineaRGB[0] = -1;
        colorLineaRGB[1] = -1;
        colorLineaRGB[2] = -1;
    }
    void pen(){
        if(penDown) cout<<"El lapiz se encuentra abajo con grosor "<<grosor<<" y color xxx";
        else cout<<"El lapiz se encuentra arriba con grosor "<<grosor<<" y color xxx";
    }
    void reset(){
        cleardevice();
        posX = 400;
        posY = 300;
        grosor = 1;
        direccion = 0;
        penDown = true;
        colorLinea = "white";
        moveto(400,300);
    }
    void clear(){
        cleardevice();
        moveto(posX,posY);
    }
    void write(string texto, int pSize){
        const char* textoChar = texto.c_str();
        settextstyle(3,0,pSize);
        outtextxy(posX,posY,textoChar);
    }
    void exitProgram(){
        exit(0);
    }
    void crearTortuga(){
        int pRadio = 10;
        setcolor(COLOR(80,200,120));
        circle(posX, posY, pRadio);

        /*Pata Derecha Delantera*/
        int pataDerDelx = cos (((direccion + 60) * M_PI) /180) * (pRadio + 3);
        int pataDerDely = sin(((direccion + 60) * M_PI) /180) * (pRadio + 3);
        circle(posX + pataDerDelx, posY + pataDerDely, 4);

        /*Pata Izquierda Delantera*/
        int pataIzqDelx = cos (((direccion - 60) * M_PI) /180) * (pRadio + 3);
        int pataIzqDely = sin(((direccion - 60) * M_PI) /180) * (pRadio + 3);
        circle(posX + pataIzqDelx, posY + pataIzqDely, 4);

        /*Pata Derecha Tracera*/
        int pataDerTrax = cos (((direccion + 135) * M_PI) /180) * (pRadio + 3);
        int pataDerTray = sin(((direccion + 135) * M_PI) /180) * (pRadio + 3);
        circle(posX + pataDerTrax, posY + pataDerTray, 4);

        /*Pata Izquierda Tracera*/
        int pataIzqTrax = cos (((direccion - 135) * M_PI) /180) * (pRadio + 3);
        int pataIzqTray = sin(((direccion - 135) * M_PI) /180) * (pRadio + 3);
        circle(posX + pataIzqTrax, posY + pataIzqTray, 4);

        /*Cabeza*/
        int cabezax = cos (((direccion) * M_PI) /180) * (pRadio + 3);
        int cabezay = sin(((direccion) * M_PI) /180) * (pRadio + 3);
        circle(posX + cabezax, posY + cabezay, 5);

        if(colorLinea == "nulo") colorLineaFuncion(colorLineaRGB[0],colorLineaRGB[1],colorLineaRGB[2]);
        else colorLineaFuncion(colorLinea);
    }
private:
    void graficador(){
        if(penDown){
            if(colorLinea == "nulo"){
                setcolor(COLOR(colorLineaRGB[0],colorLineaRGB[1],colorLineaRGB[2]));
                line(getx(),gety(),posX,posY);
            }
            else{
                if(colorLinea == "white"){
                    setcolor(WHITE);
                }
                if(colorLinea == "yellow"){
                    setcolor(YELLOW);
                }
                if(colorLinea == "light magenta"){
                    setcolor(LIGHTMAGENTA);
                }
                if(colorLinea == "light red"){
                    setcolor(LIGHTRED);
                }
                if(colorLinea == "light cyan"){
                    setcolor(LIGHTCYAN);
                }
                if(colorLinea == "light green"){
                    setcolor(LIGHTGREEN);
                }
                if(colorLinea == "light blue"){
                    setcolor(LIGHTBLUE);
                }
                if(colorLinea == "dark grey"){
                    setcolor(DARKGRAY);
                }
                if(colorLinea == "light grey"){
                    setcolor(LIGHTGRAY);
                }
                if(colorLinea == "brown"){
                    setcolor(BROWN);
                }
                if(colorLinea == "magenta"){
                    setcolor(MAGENTA);
                }
                if(colorLinea == "red"){
                    setcolor(RED);
                }
                if(colorLinea == "cyan"){
                    setcolor(CYAN);
                }
                if(colorLinea == "green"){
                    setcolor(GREEN);
                }
                if(colorLinea == "blue"){
                    setcolor(BLUE);
                }
                if(colorLinea == "black"){
                    setcolor(BLACK);
                }
                line(getx(),gety(),posX,posY);
            }
        }
        moveto(posX,posY);
    }
};
#endif // TORTUGA_H
