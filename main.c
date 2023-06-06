#include "output.h"

    char password[6];
    char letra;
    
////Valor global del delay
    int tiempo = 12;


////////////////////tablas de datos //////////////////////////////////
unsigned char TablaAf []= {0x01, 0x02, 0x04,0x08,0x10, 0x20, 0x40, 0x80};
unsigned char TablaCh []= {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
unsigned char TablaCa []= {0x01, 0x01 ,0x03, 0x03, 0x05, 0x05, 0x09, 0x09, 0x11,0x12,0x24,0x28,0x50,0x60,0x40,0x80};
unsigned char TP[] = {0x88, 0x48, 0x28, 0x18, 0x14, 0x12, 0x12, 0x14, 0x18,0x28,0x48,0x48, 0x28,0x18,0x14,0x14,0x18,0x28,0x28,0x18,0x18,0x18};


/////////////////Comprobar Contraseña///////////////////////////
int ingreso(){	
    initscr(); //determines the terminal type and initialises all implementation data structures
    noecho();  //
    printw("Ingrese clave: ");
    for(int i=0; i<3;i++){
        char c;
        char temp[5];
        for(int i = 0; i < 5; i++){
            c = getch();
            temp[i] = c;
            printw("*");
        }
        printw("\r                      ");
        fflush(stdout);
    if(strcmp(temp, password)==0){
        printw("\r");
        echo();
        endwin();
        return 1; 
    }
    printw("\rPassword no valida! ");
   }
    printw("\r                         ");
    printw("\r");
    fflush(stdout);
    echo();
    endwin();
    return 0;
}

int press_key() {
    //disables line buffering and erase/kill character-processing 
    //making characters typed by the user immediately available to the program
    cbreak(); 
    keypad(stdscr, TRUE);

    //causes getch to be a non-blocking call
    nodelay(stdscr, TRUE); 

    switch (getch()) {
        case 'a':
            return 0;
        case KEY_UP:
            if(tiempo > 0) tiempo--;
            break;
        case KEY_DOWN:
            if(tiempo < 30) tiempo++;
            break;
    }
    return 1;
    nocbreak();
}


///////////////// Delay de todas las funciones ///////////////////
void delay(int a){
  for(int j=0;j<a;j++)
  {
    unsigned int i = 0x2fffff; //raspberry 0x3fffff
    while(i)i--;
  };
};

//////////////////Autofantastico por Tabla /////////////////////
void AutofantasticoT() 
{
    initscr();
    noecho();
    while(1){ 
        for (int i = 0; i<8; i++ )
        {
            int valor = TablaAf[i];
            output(valor);
            delay(tiempo);
            // output = output >> 1; // Mueve el bit a otra pos ?
            if(press_key() == 0){
                echo();
                endwin(); //  restores the terminal after Curses activity
                return;
            } 
        };
        for (int i = 7; i>0; i-- )
        {
            int valor = TablaAf[i];
            output(valor);
            delay(tiempo);
            // output = output << 1; // Mueve el bit a otra pos ?
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
    };
};

/////////////////////Autofantastico Algoritmo ///////////////////////////////////////
void Autofantastico(){

printf("Estas viendo el Auto Fantastico!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");


  while(1){
        initscr();
        noecho();
        for(int i = 1; i<=128; i=i*2) 
        {
            output(i);
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
        for(int i = 64; i>0 ; i=i/2){ 
            output(i);
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
            
        };
    };
};

/////////////////Funcion Carrera hecha con tabla //////////////////
void Carrera()

printf("Estas viendo la carrera!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");


{
    initscr();
    noecho();
    while(1){
        for (int i = 0; i<16; i++ )
        {
            int valor = TablaCa[i];
            output(valor);
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
    };
};

//////////////// choque hecho por tabla (no se puede de otra forma)//////////
void ChoqueT()

printf("Estas viendo el choque!");
printf("Presione la tecla 'a' si quiere salir!");
printf("Presione la flecha hacia arriba para aumentar la velocidad!");
printf("Presione la flecha hacia abajo para disminuir la velocidad!");

{
    initscr();
    noecho();
    while(1){
        for (int i = 0; i<8; i++ )
        {
            int valor = TablaCh[i];
            output(valor);
            delay(tiempo);
            if(press_key() == 0){
                echo();
                endwin();
                return;
            } 
        };
    };
};

int main()
{
    pioInit();
    strcpy(password, "admin");

    const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};
    for (int i = 0; i < 8; i++ ){
        pinMode(led[i], OUTPUT);
    }

    if(!ingreso()){
        printf("Haz sido bloqueado del sistema\n");
        return 0;
    }

    printf(" Bienvenido al sistema! \n");

    while(1){
        system("clear");
        printf("Elija la secuencia que quiere ver: \n");
        printf("1.Autofantastico \n");
        printf("2.Choque\n");
        printf("3.Carrera\n");
        printf("4.Personal1 \n");
        printf("5.Personal2\n");        
        printf("0.Salir\n");

        int opcion;

        scanf("%i", &opcion);
        system("clear");
        
        switch(opcion) {
            case 1 :
                AutofantasticoT();
                break;
            case 2:
                ChoqueT();
                break;
            case 3:
                Carrera();
                break;
            case 4 :
                break;
            case 5 :
                break;
            case 0 :
                printf("Adios!");
                return 1;
                break;
            default:
                printf("Ingrese una opcion valida!");
                break;
        }
    }
}
