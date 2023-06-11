//#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//comentar este conio.h

#include <conio.h> // getch para liux usar ncurses.h

//descomentar estos 3 include

//include <termios.h>
//#include <unistd.h>
//#include <ncurses.h>

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

/*  int kbhit()
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
} */ 

 // Funcion para mostrar en binario
void disp_binary(int i) {
    int t;
    const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};
    //system("cls");
    for (t = 128; t > 0; t = t/2) {
        if ( i & t) {
            printf("1");
            //digitalWrite(led[i], 1);
        } else {
            printf("0");
            //digitalWrite(led[i], 0);
        }
    }
     printf("\n");
} 

/////////////////Comprobar Contraseña///////////////////////////
int ingreso(){	

    int intentos = 3;
    char inputPassword[50];
    char caracter;
    int resultado = -1, i;

    while (intentos > 0) {
        printf("Ingrese su password de 5 digitos : \n");
        //fgets(inputPassword, sizeof(inputPassword), stdin);

        //printf("%s", inputPassword);

        //inputPassword[strcspn(inputPassword, "\n")] = 0;

       for (i = 0; i < 50; i++) {
            caracter = getch();

            if (caracter == ENTER) {
                break;
            } else if ( caracter != BACKSPACE) {
                inputPassword[i] = caracter;
                printf("*");
            }
        }

        // inputPassword[i] = '\0';

        // resultado = comparePasswords(inputPassword);

        resultado = strcmp(inputPassword,"admin");

        printf("\n");

        if (resultado == 0) {
            return 1;
        } else {
            printf("Password no valida!\n");
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
 int resultado = 1;
    unsigned int j = 0x2fffff; //raspberry 0x3fffff;
    for (i = 0; i < tiempo; i++) {
        for (j = 0; j < 65535; ++j) {
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    return resultado = 0 ;
                }

                if (input2 == 72) { // si input es up key 
                    resultado = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    resultado = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return resultado = 0;
                }
        }
        //while (j) j--;
    }
    }

    return resultado;
}


/////////////////////Autofantastico Algoritmo ///////////////////////////////////////
void autoFantastico() {
    unsigned char output;
    int input1, input2;
    char t;

    int tiempo = 2000;

    printf("Estas viendo el Auto Fantastico!\n");
    printf("Presione la tecla 'a' si quiere salir!\n");
    printf("Presione la flecha hacia arriba para aumentar la velocidad!\n");
    printf("Presione la flecha hacia abajo para disminuir la velocidad!\n");

    do {

        output = 0x80;
        for (t = 0; t < 8; t++ ) {
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            disp_binary(output);
            delay(tiempo);
            output = output >> 1; // Right shift
        }

        printf("tiempo %d", tiempo);

        output = 0x01;
        for (t = 0; t < 6; t++) {
             if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            output = output << 1;
            disp_binary(output);
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
               if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            disp_binary(valor);
            delay(tiempo);
            } 
        }
};

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
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            disp_binary(valor);
            delay(tiempo);        
        };
    };
}; 

// Secuencia el Monstruo por tabla

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
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            disp_binary(valor);
            delay(tiempo);        
        };
    };


}

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
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            disp_binary(output);
            delay(tiempo);
            output = output >> 1; // Right shift
        }

        output = 0x11;
         for (t = 0; t < 4; t++ ) {
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            disp_binary(output);
            delay(tiempo);
            output = output << 1; // Left shift 
        }

        output = 0x88;
        for (t = 0; t < 5; t++) {
            if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            output = output >> 1; // Right Shift
            disp_binary(output);
            delay(tiempo);
        }

        output = 0x04;

        for (t = 0; t < 4; t++) {
           if (kbhit()) {
                input1 = getch();

                if (input1 == 224){

                input2 = getch();

                if (input2 != 72 && input2 != 80) {
                    printf("ACA");
                    return;
                }

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 1500;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 1500;
                }  

                printf("tiempo %d", tiempo);
                } else {
                    return;
                }

                } 
            output = output << 1; // Left Shift
            disp_binary(output);
            delay(tiempo);
        }


    } while (1);


}

void pressKeyCheck() {

    int input1, input2;
    int tiempo = 100;

    int b = 1;

    while (b) {
     if (kbhit()) {
                input1 = getch();

                printf("INPUT 1: %c", input1);

                if (input1 == 224) {

                input2 = getch();

                if (input2 == 72) { // si input es up key 
                    tiempo = tiempo + 15;
                }

                if (input2 == 80) { // si input es down key
                    tiempo = tiempo - 15;
                }  

                printf("INPUT 2 %c", input2);
                printf("tiempo %d", tiempo);
                }
     }

            }
}




int main()
{
    //pioInit();
    strcpy(password, "admin");

    const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};
    for (int i = 0; i < 8; i++ ){
        // pinMode(led[i], OUTPUT);
    }

    if(ingreso() == 0){
        printf("Haz sido bloqueado del sistema\n");
        return 0;
    }

    printf(" Bienvenido al sistema! \n");

    while(1){
        //system("cls");
        printf("Elija la secuencia que quiere ver: \n");
        printf("1.Autofantastico \n");
        printf("2.Choque\n");
        printf("3.Carrera\n");
        printf("4.Monstruo \n");
        printf("5.Atrapaditas\n");        
        printf("0.Salir\n");

        int opcion;

        scanf("%i", &opcion);
        system("cls");
        
        switch(opcion) {
            case 1 :
                autoFantastico();

                //pressKeyCheck();

                break;
            case 2:
                ChoqueT();
                break;
            case 3:
                Carrera();
                break;
            case 4 :
                Monstruo();
                break;
            case 5 :
                Atrapaditas();
                break;
            case 0 :
                printf("Adios!");
                return 0;
                break;
            default:
                printf("Ingrese una opcion valida!");
                break;
        }
    }
}
