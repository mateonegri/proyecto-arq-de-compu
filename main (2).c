//#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//comentar este conio.h

//#include <conio.h> // getch para liux usar ncurses.h

//descomentar estos 3 include

#include <termios.h>
#include <unistd.h>
#include <ncurses.h>
#include "EasyPIO.h"

#define ENTER 13
#define BACKSPACE 8

char password[6];
char letra;
    
////Valor global del delay
   // int tiempo = 2000;


////////////////////tablas de datos //////////////////////////////////
unsigned char TablaAf []= {0x01, 0x02, 0x04,0x08,0x10, 0x20, 0x40, 0x80};
unsigned char TablaCh []= {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
unsigned char TablaCa []= {0x01, 0x01 ,0x03, 0x03, 0x05, 0x05, 0x09, 0x09, 0x11,0x12,0x24,0x28,0x50,0x60,0x40,0x80};
unsigned char TP[] = {0x88, 0x48, 0x28, 0x18, 0x14, 0x12, 0x12, 0x14, 0x18,0x28,0x48,0x48, 0x28,0x18,0x14,0x14,0x18,0x28,0x28,0x18,0x18,0x18};
unsigned char TablaMn[] = {0x80, 0x81, 0x82, 0x84, 0x88, 0x90, 0xA0, 0xC0, 0xFF};


//descomentar esta funcion

 int kbhit()
{
    struct termios oldt, newt;
    int ch;
    fd_set readfds;
    struct timeval tv;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    if (FD_ISSET(STDIN_FILENO, &readfds))
    {
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
} 

 // Funcion para mostrar en binario
void disp_binary(int i, int option) {
    int t;
    int n = 0;
    const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};
    //system("cls");
    printf("\033[2J");
    unsigned int k = 10;
    while (k--)
    printf("\033[F");
    
    switch (option) {
  case 1:
    printf("\033[1;30mSECUENCIA:\033[0m \033[1;30mAuto Fantastico\033[0m\n\r\n\r");
    break;
  case 2:
    printf("\033[1;30mSECUENCIA:\033[0m \033[1;30mEl Choque\033[0m\n\r\n\r");
    break;
  case 3:
    printf("\033[1;30mSECUENCIA:\033[0m \033[1;30mLa Carrera\033[0m\n\r\n\r");
    break;
  case 4:
    printf("\033[1;30mSECUENCIA:\033[0m \033[1;30mEl Monstruo\033[0m\n\r\n\r");
    break;
  case 5:
    printf("\033[1;30mSECUENCIA:\033[0m \033[1;30mAtrapaditas\033[0m\n\r\n\r");
    break;
  case 0:
    break;
  }
    
    
    for (t = 128; t > 0; t = t/2) {

        if ( i & t) {
             printf("1");
            digitalWrite(led[n], 1);
        } else {
             printf("0");
            digitalWrite(led[n], 0);
        }

        n++;
    }
    
    printf("\n\r");
    printf("\033[1;30mPresione la tecla A para salir\033[0m\n\r");
    printf("\033[1;30mPresione la flecha para arriba para aumentar la velocidad\033[0m\n\r");
    printf("\033[1;30mPresione la flecha para abajo para disminuir la velocidad\033[0m\n\r");
} 

/////////////////Comprobar Contraseña///////////////////////////
int ingreso(){	

    int intentos = 3;
    char inputPassword[5];
    char caracter;
    int resultado = -1, i = 0;

    while (intentos > 0) {
        printf("Ingrese su password de 5 digitos : \n\r");
        //fgets(inputPassword, sizeof(inputPassword), stdin);

        //printf("%s", inputPassword);

        //inputPassword[strcspn(inputPassword, "\n\r")] = 0;

        for (i = 0; i < 5; i++) {
            caracter = getchar();

            if (caracter == ENTER) {
                break;
            } else if ( caracter != BACKSPACE) {
                inputPassword[i] = caracter;
                printf("*");
            }
        }  

        //inputPassword[i] = '\0';

        //resultado = comparePasswords(inputPassword);
/* 
        while(1) {
            caracter = getchar();

            if ( caracter == '\n\r') {
                inputPassword[i] = '\0';
                break;
            } else if (caracter == 127 || caracter == '\b') {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                } else {
                    if ( i < 5) {
                        printf("*");
                        inputPassword[i] = caracter;
                        i++;
                    }
                }

                if (i == 5) {
                    break;
                }
            }
        } */

        inputPassword[i] = '\0';

        resultado = strcmp(inputPassword,"admin");

        printf("\n\r");

        if (resultado == 0) {
            return 1;
        } else {
            printf("Password no valida!\n\r");
            intentos--;
        }
    }

    if (intentos == 0) {
        return 0;
    }
}


///////////////// Delay de todas las funciones ///////////////////
void delay(int a){
 int i;
    unsigned int j = 0x2fffff; //raspberry 0x3fffff;
    for (i = 0; i < a; i++) {
        for (j = 0; j < 65535; ++j) {
        
        }
        //while (j) j--;
    }
}

///////////////// Delay para las funciones en assembly ///////////////////
int delayAssembly(int tiempo){
 int i;
 int input1, input2;
 int resultado = tiempo;
 
    unsigned int j = 0x3fffff; //raspberry 0x3fffff;
    for (i = 0; i < tiempo; i++) {
        for (j = 0; j < 65535; ++j) {
            /* if (kbhit()) {
                input1 = getch();

                if (KEY_UP == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return resultado = 0 ;
                }

                if (input2 == 72) { // si input es up key 
                    resultado = resultado - 500;
                }

                if (input2 == 80) { // si input es down key
                    resultado = resultado + 500;
                }  

                } else {
                    return resultado = 0;
                } */
               
                }
        }
        //while (j) j--;
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return 0;
                case KEY_UP:
                resultado = tiempo - 500;
                break;
                case KEY_DOWN:
                resultado = tiempo + 500;
                break;
                }
                

    return resultado;
}


/////////////////////Autofantastico Algoritmo ///////////////////////////////////////
void autoFantastico() {
    unsigned char output;
    int input1, input2;
    char t;

    int tiempo = 2000;

    printf("Estas viendo el Auto Fantastico!\n\r");
    printf("Presione la tecla 'a' si quiere salir!\n\r");
    printf("Presione la flecha hacia arriba para aumentar la velocidad!\n\r");
    printf("Presione la flecha hacia abajo para disminuir la velocidad!\n\r");
    printf("\n\r\n\r");
    refresh(); 

    do {

        output = 0x80;
        for (t = 0; t < 8; t++ ) {
            /* if (kbhit()) {
                input1 = getch();

                printf("%d", &input1);

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                   
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  */

                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                
                break;
                }


            
            disp_binary(output, 1);
            delay(tiempo);
            output = output >> 1; // Right shift
        }

   

        output = 0x01;
        for (t = 0; t < 6; t++) {
             /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                   
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  */


                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }

            output = output << 1;
            disp_binary(output, 1);
            delay(tiempo);
        }

    } while (1);

}


/////////////////Funcion Carrera hecha con tabla //////////////////
void Carrera(){

int tiempo = 2000;
int input1, input2;

printf("Estas viendo la carrera!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");
    while(1){
        for (int i = 0; i<16; i++ )
        {
            int valor = TablaCa[i];
              /*  if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
               
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                } */

                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            disp_binary(valor, 3);
            delay(tiempo);
            } 
    }
}

//////////////// choque hecho por tabla (no se puede de otra forma)//////////
void ChoqueT() {

int tiempo = 2000;
int input1, input2;

printf("Estas viendo el choque!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");

    while(1){
        for (int i = 0; i<8; i++ )
        {
            int valor = TablaCh[i];
            /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  */
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            disp_binary(valor, 2);
            delay(tiempo);        
        };
    };
}; 

extern void Monstruo();
extern void Atrapaditas();


// Secuencia el Monstruo por tabla
/*

void Monstruo() {

int tiempo = 2000;
int input1, input2;

printf("Estas viendo el monstruo!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");

    while(1){
        for (int i = 0; i<9; i++ )
        {
            int valor = TablaMn[i];
            /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            disp_binary(valor, 4);
            delay(tiempo);        
        };
    };


}
*/
/*

void Atrapaditas() {

int tiempo = 2000;
int input1, input2;

printf("Estas viendo Atrapaditas!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");

  unsigned char output;
  char t;

 do {
        output = 0x80;
        for (t = 0; t < 4; t++ ) {
            /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            disp_binary(output, 5);
            delay(tiempo);
            output = output >> 1; // Right shift
        }

        output = 0x11;
         for (t = 0; t < 4; t++ ) {
            /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            disp_binary(output, 5);
            delay(tiempo);
            output = output << 1; // Left shift 
        }

        output = 0x88;
        for (t = 0; t < 5; t++) {
            /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            output = output >> 1; // Right Shift
            disp_binary(output, 5);
            delay(tiempo);
        }

        output = 0x04;

        for (t = 0; t < 4; t++) {
           /* if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo - 500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo + 500;
                }  

                } else {
                    return;
                }

                }  
                keypad(stdscr, TRUE);
                nodelay(stdscr, TRUE);
                switch (getch()) {
                case 'a':
                    return;
                case KEY_UP:
                tiempo = tiempo - 500;
                break;
                case KEY_DOWN:
                tiempo = tiempo + 500;
                break;
                }
            output = output << 1; // Left Shift
            disp_binary(output, 5);
            delay(tiempo);
        }


    } while (1);


}
*/


int main()
{
    //setbuf(stdin, NULL);

    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    pioInit();
    //strcpy(password, "admin");

    char input;

    const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};
    for (int i = 0; i < 8; i++ ){
        pinMode(led[i], OUTPUT);
    }

    if(ingreso() == 0){
        printf("Haz sido bloqueado del sistema\n\r");
        return 0;
    }

    printf(" Bienvenido al sistema! \n\r");

    while(1){
        system("clear");
        printf("Elija la secuencia que quiere ver: \n\r");
        printf("1.Autofantastico \n\r");
        printf("2.Choque\n\r");
        printf("3.Carrera\n\r");
        printf("4.Monstruo \n\r");
        printf("5.Atrapaditas\n\r");        
        printf("0.Salir\n\r");

        int opcion;

        //scanf("%i", &opcion);

        input = getchar();

        //system("clear");
        
        switch(input) {
            case '1' :
                autoFantastico();

                //pressKeyCheck();

                break;
            case '2':
                ChoqueT();
                break;
            case '3':
                Carrera();
                break;
            case '4' :
                Monstruo();
                break;
            case '5' :
                Atrapaditas();
                break;
            case '0' :
                printf("Adios!");
                return 0;
                break;
            default:
                printf("Ingrese una opcion valida!");
                break;
        }
    }

    endwin();
}











