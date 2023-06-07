#ifndef ARQUITECTURA_COMPUTADORA_H
#define ARQUITECTURA_COMPUTADORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
//output estandar, convierte cualquier numero 
//decimal/Hexa a binario pero al revez (osea 1 = 1000000)
////////////////////Mostrar de la funcion //////////////////////

 void output(unsigned char a) 
{
    const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};
    for(int i=0; i<8; i++)
    {
        if(a%2==0){
            printf("_");
            digitalWrite(led[i], 1);
        }   
        else{
            printf("*");
            digitalWrite(led[i], 0);
        }
    a=a/2;
  }
  printf("\r");
  fflush(stdout); //to clear (or flush) the output buffer and move the buffered data to console
};  */
 

 // Funcion para mostrar en binario
void output(int i) {
    int t;
    system("cls");
    for (t = 128; t > 0; t = t/2) {
        if ( i & t) {
            printf("1");
            //digitalWrite(led[i], 1);
        } else {
            printf("0");
            //digitalWrite(led[i], 0);
        }
    }
} 


#endif
