#include <winbgim.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <conio.h>
#include <ctype.h>
#include "include\Tortuga.h"

#define BLACK	0
#define BLUE	1
#define GREEN	2
#define CYAN	3
#define RED	    4
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

LinkedList<string> split(string texto);
int cuentaParametros(string comando);
bool comandoValido(string comando);
string retornaComando(string instruccion, int &indice);
string extraeString(string instruccion, int indice);
bool colorValido(string color);
int retornaParametro(string instruccion, int &indice);
bool parametroValido(string instruccion, int indice, int cantidadParametros);
void ejecutarLista(string lista, Tortuga &tortuguita);
void analizaString(Tortuga &tortuguita, string comando, string instruccion, int indice);
void analizaString2(Tortuga &tortuguita, string comando, string instruccion, int indice);
void menu(Tortuga &tortuguita);

LinkedList<string> historial;
LinkedList<string> memoria;

LinkedList<string> split(string texto){
    unsigned int i=1;
    string instruccionTemporal;
    LinkedList<string> listaTemporal;
    while(i<texto.size()-1){
        if(texto[i] == ' '){
            if(!instruccionTemporal.empty()){
                listaTemporal.append(instruccionTemporal);
                instruccionTemporal.clear();
            }
        }
        else instruccionTemporal+=texto[i];
        i++;
    }
    listaTemporal.append(instruccionTemporal);
    return listaTemporal;
}

int cuentaParametros(string comando){
    if (comando == "home" || comando == "pos" || comando == "xcor" || comando == "ycor" || comando == "heading" || comando == "pendown" || comando == "penup" || comando == "pen" || comando == "reset" || comando == "clear" || comando == "exec" || comando == "history" || comando == "clearhistory" || comando == "exit"){
        return 0;
	}
    else if (comando == "forward" || comando == "back" || comando == "right" || comando == "left" || comando == "setx" || comando == "sety" || comando == "setheading" || comando == "circle" || comando == "pensize"){
        return 1;
    }
    else if (comando == "setpos"){
        return 2;
    }
    else if (comando == "color"){
        return 4;
    }
    else if( comando == "write"){
        return 5;
    }
    else if( comando == "repeat"){
        return 6;
    }
    else if( comando == "loadfile"){
        return 7;
    }
    else return 0;
}

bool comandoValido(string comando){
    if (comando == "forward" || comando == "back" || comando == "right" || comando == "left" || comando == "setpos" || comando == "setx" || comando == "sety" || comando == "setheading" || comando == "home" || comando == "circle" || comando == "pos" || comando == "xcor" || comando == "ycor" || comando == "heading" || comando == "pendown" || comando == "penup" || comando == "pensize" || comando == "color" || comando == "pen" || comando == "reset" || comando == "clear" || comando == "write" || comando == "repeat" || comando == "loadfile" || comando == "exec" || comando == "history" || comando == "clearhistory" || comando == "exit"){
        return true;
    }
    return false;
}

string retornaComando(string instruccion, int &indice){
    string comando;
    while(instruccion[indice] != ' ' && instruccion[indice] != '\0' && instruccion[indice] != '\n'){
            comando+=instruccion[indice];
            indice++;
    }
    return comando;
}

string extraeString(string instruccion, int indice){
    string temporal;
    unsigned int i = indice+1;

    while(i<instruccion.size()){
        temporal+=instruccion[i];
        i++;
    }
    return temporal;
}

bool colorValido(string color){
    if(color == "white" || color == "yellow" || color == "light magenta" || color == "light red" || color == "light cyan" || color == "light green" || color == "light blue" || color == "dark grey" || color == "light grey" || color == "brown" || color == "magenta"|| color == "red" || color == "cyan" || color == "green" ||color == "blue" || color == "black"){
        return true;
    }
    return false;
}

int retornaParametro(string instruccion, int &indice){
    string parametro;
    int retorno;
    indice++;
    while(instruccion[indice] != ' ' && instruccion[indice] != '\0' && instruccion[indice] != '\n'){
        parametro+=instruccion[indice];
        indice++;
    }
    retorno = atoi(parametro.c_str());
    return retorno;
}

bool parametroValido(string instruccion, int indice, int cantidadParametros){
    string parametro;
    unsigned int indiceTemporal = 0;
    if(cantidadParametros == 4){
        if(colorValido(extraeString(instruccion,indice))){
            return true;
        }
        else{
            indice++;
            return parametroValido(instruccion,indice,3);
        }
    }
    else if(cantidadParametros == 5){
        indice++;
        while(instruccion[indice] != ' ' && instruccion[indice] != '\0' && instruccion[indice] != '\n'){
            parametro+=instruccion[indice];
            indice++;
        }
        unsigned int i = 0;
        while(i<parametro.size()){
            if(!(isdigit(parametro[i]))) return false;
            i++;
        }
        if(parametro=="0")return false;
        indice = instruccion.size()+1;
    }
    else if(cantidadParametros == 6){
        indice++;
        while(instruccion[indice] != ' ' && instruccion[indice] != '\0' && instruccion[indice] != '\n'){
            parametro+=instruccion[indice];
            indice++;
        }
        unsigned int i = 0;
        while(i<parametro.size()){
            if(!(isdigit(parametro[i]))) return false;
            i++;
        }
        if(parametro=="0")return false;
        indice = instruccion.size()+1;
    }
    else if(cantidadParametros == 7){
        indice++;
        indice = instruccion.size()+1;
    }
    else if(cantidadParametros == 1 || cantidadParametros == 2 || cantidadParametros == 3 ){
        while(cantidadParametros>0){
            indice++;
            parametro.clear();
            while(instruccion[indice] != ' ' && instruccion[indice] != '\0' && instruccion[indice] != '\n'){
                parametro+=instruccion[indice];
                indice++;
            }
            unsigned int i = 0;
            while(i<parametro.size()){
                if(!(isdigit(parametro[i]))) return false;
                i++;
            }
            cantidadParametros--;
        }
    }
    else if(cantidadParametros == 0){
        indiceTemporal = indice;
        if(instruccion.size()>indiceTemporal) return false;
        else {
            return true;
        }
    }
    indiceTemporal = indice;
    if(instruccion.size() > indiceTemporal) return false;
    return true;
}

void ejecutarLista(string listaString, Tortuga &tortuguita, LinkedList<string> &lista){
    if(listaString == "historial"){
        historial.goToStart();
        int i,indiceTemporal;
        for(i=0; i < historial.getSize(); i++){
            indiceTemporal = 0;
            string instruccionTemporal = historial.getElement();
            string comandoTemporal = retornaComando(instruccionTemporal,indiceTemporal);
            analizaString2(tortuguita, comandoTemporal, instruccionTemporal, indiceTemporal);
            historial.next();
        }
    }
    if(listaString == "memoria"){
        memoria.goToStart();
        int i,indiceTemporal;
        for(i=0; i < memoria.getSize(); i++){
            indiceTemporal = 0;
            string instruccionTemporal = memoria.getElement();
            string comandoTemporal = retornaComando(instruccionTemporal,indiceTemporal);
            analizaString2(tortuguita, comandoTemporal, instruccionTemporal, indiceTemporal);
            memoria.next();
        }
    }
    if(listaString == "repeat"){
        lista.goToStart();
        int i,indiceTemporal;
        for(i=0; i < lista.getSize(); i++){
            indiceTemporal = 0;
            string instruccionTemporal = lista.getElement();
            string comandoTemporal = retornaComando(instruccionTemporal,indiceTemporal);
            analizaString2(tortuguita, comandoTemporal, instruccionTemporal, indiceTemporal);
            lista.next();
        }
    }

}

void agregarAHistorial(string pInstruccion){
    historial.append(pInstruccion);
}

void analizaString(Tortuga &tortuguita, string comando, string instruccion, int indice){
    if(comando == "forward"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.forward(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "back"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.back(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "right"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.right(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "left"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.left(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "setpos"){
        if(parametroValido(instruccion,indice,2)){
            tortuguita.setpos(retornaParametro(instruccion,indice),retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "setx"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.setx(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "sety"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.sety(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "setheading"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.setheading(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "home"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.home();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "circle"){
         if(parametroValido(instruccion,indice,1)){
            tortuguita.circleFuncion(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "pos"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.pos();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "xcor"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.xcor();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "ycor"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.ycor();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "heading"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.heading();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "pendown"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.pendown();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "penup"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.penup();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "pensize"){
        if(parametroValido(instruccion,indice,1)){
            tortuguita.pensize(retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "color"){
        if(parametroValido(instruccion,indice,3)){
            tortuguita.colorLineaFuncion(retornaParametro(instruccion,indice),retornaParametro(instruccion,indice),retornaParametro(instruccion,indice));
            agregarAHistorial(instruccion);
        }
        else{
            string color = extraeString(instruccion,indice);
            if(colorValido(color)){
                tortuguita.colorLineaFuncion(color);
                agregarAHistorial(instruccion);
            }
            else cout << "Color Invalido\n";
        }
    }
    else if(comando == "pen"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.pen();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "reset"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.reset();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "clear"){
        if(parametroValido(instruccion,indice,0)){
           tortuguita.clear();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "write"){
        if(parametroValido(instruccion,indice,5)){
            int tempSize=retornaParametro(instruccion,indice);
            string tempText = extraeString(instruccion,indice);
            if(tempSize == 0) cout<<"Comando Invalido\n";
            else{
                tortuguita.write(tempText,tempSize);
                agregarAHistorial(instruccion);
            }
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "repeat"){
        LinkedList<string> listaRepeat, listaRepeatNoError;
        int tempSize;
        if(parametroValido(instruccion,indice,6)){
            tempSize=retornaParametro(instruccion,indice);
            string tempText = extraeString(instruccion,indice);
            if(tempText[0] == '[' && tempText[tempText.size()-1] == ']'){
                LinkedList<string> listaRepeatTemporal = split(tempText);
                string instruccionTemporal;
                int i;
                for(i=0; i < listaRepeatTemporal.getSize(); i++){
                    string elemento = listaRepeatTemporal.getElement();
                    if(comandoValido(elemento)){
                        if(i != 0){
                            listaRepeat.append(instruccionTemporal);
                            instruccionTemporal.clear();
                            instruccionTemporal += elemento;
                        }
                        else instruccionTemporal += elemento;
                    }
                    else{
                        instruccionTemporal += ' ';
                        instruccionTemporal += elemento;
                    }
                    listaRepeatTemporal.next();
                }
                listaRepeat.append(instruccionTemporal);
            }
            else cout<<"Comando Invalido"<<endl;
        }
        else cout<<"Comando Invalido"<<endl;
        int j,indiceTemporal;
        string instruccionTemporal;
        string comandoTemporal;
        bool sinError = true;

        for(j=0; j < listaRepeat.getSize() && sinError; j++){
            indiceTemporal = 0;
            instruccionTemporal = listaRepeat.getElement();
            comandoTemporal = retornaComando(instruccionTemporal, indiceTemporal);
            if(parametroValido(instruccionTemporal,indiceTemporal,cuentaParametros(comandoTemporal))){
                listaRepeatNoError.append(instruccionTemporal);
                instruccionTemporal.clear();
                comandoTemporal.clear();
            }
            else{
                sinError = false;
            }
            listaRepeat.next();
        }
        if(sinError){
            int contador = 0;
            while(contador < tempSize){
                ejecutarLista("repeat",tortuguita,listaRepeatNoError);
                contador++;
            }
            agregarAHistorial(instruccion);
        }
        else cout<<"Instrucciones invalidas";
    }
    else if(comando == "loadfile"){
        string direccion = extraeString(instruccion,indice);
        string linea;
        bool sinError = true;
        int indiceFile = 0;
        string comandoFile;

        ifstream fe(direccion.c_str());
        if(! (fe.is_open())) {
            cout << "Archivo incorrecto" << endl;
            sinError = false;
        }
        else{
            while (!fe.eof() && sinError){
                getline(fe,linea);
                comandoFile = retornaComando(linea,indiceFile);
                if (comandoValido(comandoFile) && parametroValido(linea,indiceFile,cuentaParametros(comandoFile))){
                    memoria.append(linea);
                    linea.clear();
                    comandoFile.clear();
                    indiceFile = 0;
                }
                else{
                    memoria.clear();
                    cout<<"Las instrucciones en el archivo no son validas\n";
                    sinError=false;
                }
            }
        }
        fe.close();
        if(sinError){
            cout<<"Archivo cargado correctamente\n";
            agregarAHistorial(instruccion);
        }
    }
    else if(comando == "exec"){
        if(parametroValido(instruccion,indice,0)){
            LinkedList<string> vacia;
            ejecutarLista("memoria",tortuguita,vacia);
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "history"){
        if(parametroValido(instruccion,indice,0)){
           historial.imprimir();
            agregarAHistorial(instruccion);
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "clearhistory"){
        if(parametroValido(instruccion,indice,0)){
            historial.clear();
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "exit"){
        if(parametroValido(instruccion,indice,0)) tortuguita.exitProgram();
        else cout<<"Comando Invalido\n";
    }
    else cout<<"Comando Invalido\n";

    tortuguita.reset();
    LinkedList<string> vacia;
    ejecutarLista("historial",tortuguita,vacia);
    tortuguita.crearTortuga();
}

void analizaString2(Tortuga &tortuguita, string comando, string instruccion, int indice){
    if(comando == "forward"){
        tortuguita.forward(retornaParametro(instruccion,indice));
    }
    else if(comando == "back"){
        tortuguita.back(retornaParametro(instruccion,indice));
    }
    else if(comando == "right"){
        tortuguita.right(retornaParametro(instruccion,indice));
    }
    else if(comando == "left"){
        tortuguita.left(retornaParametro(instruccion,indice));
    }
    else if(comando == "setpos"){
        tortuguita.setpos(retornaParametro(instruccion,indice),retornaParametro(instruccion,indice));
    }
    else if(comando == "setx"){
        tortuguita.setx(retornaParametro(instruccion,indice));
    }
    else if(comando == "sety"){
        tortuguita.sety(retornaParametro(instruccion,indice));
    }
    else if(comando == "setheading"){
        tortuguita.setheading(retornaParametro(instruccion,indice));
    }
    else if(comando == "home"){
        tortuguita.home();
    }
    else if(comando == "circle"){
         tortuguita.circleFuncion(retornaParametro(instruccion,indice));
    }
    else if(comando == "pendown"){
        tortuguita.pendown();
    }
    else if(comando == "penup"){
        tortuguita.penup();
    }
    else if(comando == "pensize"){
        tortuguita.pensize(retornaParametro(instruccion,indice));
    }
    else if(comando == "color"){
        string color = extraeString(instruccion,indice);
        if(colorValido(color)) tortuguita.colorLineaFuncion(color);
        else tortuguita.colorLineaFuncion(retornaParametro(instruccion,indice),retornaParametro(instruccion,indice),retornaParametro(instruccion,indice));
    }
    else if(comando == "reset"){
        tortuguita.reset();
    }
    else if(comando == "clear"){
        tortuguita.clear();
    }
    else if(comando == "write"){
        int tempSize;
        string tempText;
        if(parametroValido(instruccion,indice,5)){
            tempSize=retornaParametro(instruccion,indice);
            tempText = extraeString(instruccion,indice);
            if(tempSize == 0) cout<<"Comando Invalido\n";
            else{
                tortuguita.write(tempText,tempSize);
                agregarAHistorial(instruccion);
            }
        }
        else cout<<"Comando Invalido\n";
    }
    else if(comando == "repeat"){
        LinkedList<string> listaRepeat, listaRepeatNoError;
        int tempSize;
        if(parametroValido(instruccion,indice,6)){
            tempSize=retornaParametro(instruccion,indice);
            string tempText = extraeString(instruccion,indice);
            if(tempText[0] == '[' && tempText[tempText.size()-1] == ']'){
                LinkedList<string> listaRepeatTemporal = split(tempText);
                string instruccionTemporal;
                int i;
                for(i=0; i < listaRepeatTemporal.getSize(); i++){
                    string elemento = listaRepeatTemporal.getElement();
                    if(comandoValido(elemento)){
                        if(i != 0){
                            listaRepeat.append(instruccionTemporal);
                            instruccionTemporal.clear();
                            instruccionTemporal += elemento;
                        }
                        else instruccionTemporal += elemento;
                    }
                    else{
                        instruccionTemporal += ' ';
                        instruccionTemporal += elemento;
                    }
                    listaRepeatTemporal.next();
                }
                listaRepeat.append(instruccionTemporal);
            }
            else cout<<"Comando Invalido"<<endl;
        }
        else cout<<"Comando Invalido"<<endl;
        int j,indiceTemporal;
        string instruccionTemporal;
        string comandoTemporal;
        bool sinError = true;

        for(j=0; j < listaRepeat.getSize() && sinError; j++){
            indiceTemporal = 0;
            instruccionTemporal = listaRepeat.getElement();
            comandoTemporal = retornaComando(instruccionTemporal, indiceTemporal);
            if(parametroValido(instruccionTemporal,indiceTemporal,cuentaParametros(comandoTemporal))){
                listaRepeatNoError.append(instruccionTemporal);
                instruccionTemporal.clear();
                comandoTemporal.clear();
            }
            else{
                sinError = false;
            }
            listaRepeat.next();
        }
        if(sinError){
            int contador = 0;
            while(contador < tempSize){
                ejecutarLista("repeat",tortuguita,listaRepeatNoError);
                contador++;
            }
        }
        else cout<<"Instrucciones invalidas";
    }
    else if(comando == "loadfile"){
        string direccion = extraeString(instruccion,indice);
        string linea;
        bool sinError = true;
        int indiceFile = 0;
        string comandoFile;

        ifstream fe(direccion.c_str());
        if(! (fe.is_open())) {
            cout << "Archivo incorrecto" << endl;
            sinError = false;
        }
        else{
            while (!fe.eof() && sinError){
                getline(fe,linea);
                comandoFile = retornaComando(linea,indiceFile);
                if (comandoValido(comandoFile) && parametroValido(linea,indiceFile,cuentaParametros(comandoFile))){
                    memoria.append(linea);
                    linea.clear();
                    comandoFile.clear();
                    indiceFile = 0;
                }
                else{
                    memoria.clear();
                    cout<<"Las instrucciones en el archivo no son validas\n";
                    sinError=false;
                }
            }
        }
        if(sinError) cout<<"Archivo cargado correctamente\n";
    }
    else if(comando == "exec"){
        LinkedList<string> vacia;
        ejecutarLista("memoria",tortuguita,vacia);
    }
    else if(comando == "history"){
        historial.imprimir();
    }
    else if(comando == "clearhistory"){
        tortuguita.clear();
    }
    else if(comando == "exit"){
        tortuguita.exitProgram();
    }
    else cout<<"Comando Invalido\n";
}

void menu(Tortuga &tortuguita){
    string instruccion;
    string comando = "hola mundo";
    int indice;
    while(true){
        indice = 0;
        getline(std::cin,instruccion);
        kbhit();
        comando = retornaComando(instruccion,indice);
        analizaString(tortuguita, comando, instruccion, indice);
        kbhit();
        cout<<"--> ";
    }
}

int main(){
    cout<<"Bienvenido a TORTUGITA!\n-----------------------\nPara comenzar digite una instruccion\n--> ";
    Tortuga tortuguita(800,600);
    tortuguita.crearTortuga();
    menu(tortuguita);
    return 0;
}
