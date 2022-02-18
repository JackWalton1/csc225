; A program that uses interrupt-driven I/O
; CSC 225, Assignment 5
; Given code, Winter '20
; NOTE: Do not alter this file.

        .ORIG x3000

MAIN    LEA R0, PSTR
        PUTS
        LEA R0, READ
        PUTS

        TRAP x26
        ADD R1, R0, #0

        LEA R0, PSTR
        PUTS
        LEA R0, WRITE1
        PUTS
        ADD R0, R1, #0
        OUT
        LEA R0, WRITE2
        PUTS

        BRnzp MAIN
        HALT

PSTR    .STRINGZ "[Program 1] "
READ    .STRINGZ "Reading...\n"
WRITE1  .STRINGZ "Read '"
WRITE2  .STRINGZ "'.\n"

        .END
