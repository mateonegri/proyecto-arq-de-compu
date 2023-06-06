# Arquitectura-de-Computadora-1
Programa en C que busca simular los drivers de 8 leds.
concignas:
Descomponer el archivo.
Main.c --> deberia generar un main.o (objeto)
Funcion_1.c --> deberia convertirse en funcion_1.o
.
.
.
comando linuk
con $ gcc se linkea --> 
1) $gcc -g -c <<archivo de.c>>
-g// informacion para debugear
-c// genera.0
-o// cambia de nombre
 
 2) hacer lo mismo para todos los .c
 
 3)$ gcc -g <<archivo1>> <<archivo2>> <<archivo3>> ... -o proyecto
  
  
  EasyPIO.h --> se puede incluir o generar un objeto y linkearlo todo junto

pioInit --> sirve para acceder a puerto de memoria para el sistema operativo --> se necesita utilizar el SUDO porque esta protegido


void delayMillis(int millis); //(1000 = 1 seg)
void digitalWrite(int pin,int val); --> pin es que puero prendo // valo 0 apagado, 1 prendido
para llamar a la funcion se necesita B <<rotulo>>
 
 
 
 //comentario//
 . text
. global main
.type main, %function

main:
    push{r3,lr}
                                    ;;;;; Funcion Main
    MOV R2, #0                      ; seteo caso base
    SUB R1, R1, #1                  ; empezar con posición 0
    LSL R1, #2                      ; multiplica por 4 - lsl multiplica por 2 y #2 determina 
    LDR PC, [R2,R1, LSL #2]         ;Posicion a buscar
    

    
    MOV R1,#1 ; VALOR DE R1 a graficar
    BL game ;llamado de la funcion
    pop {r3,pc}


.data
.l3:
    .word 0x08
    .word 0x10
    .word 0xff
    
.end

