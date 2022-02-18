; A program to exploit interrupt-driven I/O
; CSC 225, Assignment 5
; Given code, Winter '20
; NOTE: Do not alter this file.

        .ORIG x4000

MAIN    ADD R2, R2, #1     
        BRnp MAIN       ; infinite loop idk why tho or how the loop breaks

        LEA R0, PSTR
        PUTS
        LEA R0, WRITE1
        PUTS            
        LD  R0, INTOFF  ;
        ADD R0, R0, R1  ; R0 = ASCII_VAL(char)
        OUT             ; print r0
        LEA R0, WRITE2
        PUTS            ; prints "[Program 2] R1: <time>..."

        ADD R1, R1, #1  ; time ++
        BRnzp MAIN

        HALT

PSTR    .STRINGZ "[Program 2] "
WRITE1  .STRINGZ "R1: "
WRITE2  .STRINGZ "...\n"
INTOFF  .FILL x30

        .END
