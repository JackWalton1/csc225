; A program that uses interrupt-driven I/O
; CSC 225, Assignment 5
; Given code, Winter '20
; NOTE: Do not alter this file.

        .ORIG x3000
; this program actually prints the character from R0 that is inputted by user
MAIN    LEA R0, PSTR   
        PUTS
        LEA R0, READ
        PUTS            ; prints "[Program 1] Reading...\n"

        TRAP x26        ; go to trap and put PSR into priv mode, also Gets char
        ADD R1, R0, #0  ; copy R0 to R1

        LEA R0, PSTR    
        PUTS
        LEA R0, WRITE1
        PUTS        
        ADD R0, R1, #0  ; restore R0
        OUT
        LEA R0, WRITE2
        PUTS            ; prints "[Program 1] "Read '<CHAR>".\n"

        HALT

PSTR    .STRINGZ "[Program 1] "
READ    .STRINGZ "Reading...\n"
WRITE1  .STRINGZ "Read '"
WRITE2  .STRINGZ "'.\n"

        .END
