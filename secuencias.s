// prj.s
// 23 de Mayo de 2022
// Arqui I UCC

.text
.extern delayAssembly
.extern disp_binary


.global Monstruo
Monstruo:
      STMFD SP!, {R4,R5,R6,R7,LR}
monstruo_start: 
      MOV R4,#0 
      MOV R7, #255
      ADD R7, R7, R7   
      LDR R5, =array // load base address of a into R5
;
loop:
      LDRB R6,[R5, R4]
      MOV R0,R6
      MOV R1,#4
      BL disp_binary //Cambiar el dispbinary xq los leds son active low
      ADD R4,R4,#1
      MOV R0, R7
      BL delayAssembly;
;
      CMP R0, #0
      BEQ FINAL
      MOV R7, R0
 
      CMP R4, #9
      BEQ monstruo_start
      B loop
;

 FINAL:     
 POP {R4,R5,R6,R7,PC}
 
 .global Atrapaditas
Atrapaditas: 

      PUSH {R4, R5, R6, R7, LR}
      
start: MOV R5, #0x80
      MOV R7, #3  
      MOV R4, #255
      ADD R4, R4, R4
      MOV R1,#5

loop1: MOV R6, R5
      LSR R5, R5, #1
      MOV R0, R6
      BL disp_binary
      MOV R0, R4
      BL delayAssembly
      CMP R0, #0
      BEQ TERMINO
      MOV R4, R0

      SUBS R7,R7,#1
      BNE loop1

      MOV R7, #3
      MOV R5, #0x11

loop2: MOV R6, R5
      LSL R5, R5, #1
      MOV R0, R6
      MOV R1,#5
      BL disp_binary
      MOV R0, R4
      BL delayAssembly
      CMP R0, #0
      BEQ TERMINO
      MOV R4, R0

      SUBS R7,R7,#1
      BNE loop2

      MOV R7, #4
      MOV R5, #0x88

loop3: MOV R6, R5
      LSL R5, R5, #1
      MOV R0, R6
      MOV R1,#5
      BL disp_binary
      MOV R0, R4
      BL delayAssembly
      CMP R0, #0
      BEQ TERMINO
      MOV R4, R0

      SUBS R7,R7,#1
      BNE loop3

      MOV R7, #4
      MOV R5, #0x04

loop4: MOV R6, R5
      LSL R5, R5, #1
      MOV R0, R6
      MOV R1,#5
      BL disp_binary
      MOV R0, R4
      BL delayAssembly
      CMP R0, #0
      BEQ TERMINO
      MOV R4, R0

      SUBS R7,R7,#1
      BNE loop4

      BL delayAssembly
      CMP R0, #0
      BNE start

 TERMINO: POP {R4, R5, R6, R7, PC}
 

.data
array:
      .byte 0x80
      .byte 0x81
      .byte 0x82
      .byte 0x84
      .byte 0x88
      .byte 0x90
      .byte 0xA0
      .byte 0xC0
      .byte 0xFF
.end
