; Supports interrupt-driven keyboard input.
; CSC 225, Assignment 5
; Given code, Winter '20

        .ORIG x1000

; Reads one character, executing a second program while waiting for input:
;  1. Saves the keyboard entry from the IVT.
;  2. Sets the keyboard entry in the IVT to ISR180.
;  3. Enables keyboard interrupts.
;  4. Returns to the second program.
; NOTE: The first program's state must be swapped with the second's.
TRAP26                  ; TODO: Implement this service routine.
ST R1, P1R1            
ST R2, P1R2            
ST R3, P1R3      
ST R4, P1R4         
ST R5, P1R5     
ST R7, P1R7                  ; saves val of Program 1's Registers so they can be restored
; other program 1 saves
LDR R5, R6, #0              ; saves mem[PC](S.S.) into R5
ST R5, P1PC                 ; saves P1's PC pointer in P1PC, saves address to RET back into Program 1
LD R4, P2PC                 ; r4 = address of P2PC
STR R4, R6, #0              ; replaced P1PC in S.S. with P2PC

LDR R5, R6, #1              ; saves mem[PSR] (S>S) into R5
ST R5, P1PSR                ; saves P1's PSR val in P1PSR
LD R4, P2PSR
STR R4, R6, #1              ; replaced P1PSR in S.S. with P2PSR

; store original value at x180
LDI R5, KBIV                 ; R5 = mem[x180], (the value @ the address of the IVT)
ST R5, SAVEIR               ; SAVEIR = R5 = mem[x180]

; change value at x180 to be address of ISRx180
LEA R5, ISR180               ; load address of ISR subroutine into R5  BROKEN
STI R5, KBIV                ; store address of ISRx180 at mem[x180]  WORKS
; need to enable bit 14 of KBSR
LDI R3, KBSR                ; R3 = mem[xFF00] (init = x8000)
ADD R2, R3, #0              ; copy R3 into R2
LD R1, KBIMASK
AND R2, R2, R1
Brnp SkipApplyMask          ; if And makes all 0's, we want to add the mask to the KBSR
STI R1, KBSR                ; KBSR = R1 = x4000
                            ; else KBSR[14] = 1 already
SkipApplyMask
; program 2 register loads
LD R0, P2R0            
LD R1, P2R1            
LD R2, P2R2            
LD R3, P2R3      
LD R4, P2R4         
LD R5, P2R5     
LD R7, P2R7    
RTI                       ; value will get loaded into the PC proper (PC = x4000)

; Responds to a keyboard interrupt:
;  1. Disables keyboard interrupts.
;  2. Restores the original keyboard entry in the IVT.
;  3. Reads the typed character into R0.
;  4. Returns to the caller of TRAP26.
; NOTE: The second program's state must be swapped with the first's.
ISR180                  ; TODO: Implement this service routine. 
ST R0, P2R0
ST R1, P2R1            
ST R2, P2R2            
ST R3, P2R3      
ST R4, P2R4         
ST R5, P2R5     
ST R7, P2R7                 ; saves all of program 2 registers

; other program 2 saves
LDR R5, R6, #0              ; saves mem[PC](S.S.) into R5
ST R5, P2PC                 ; saves P1's PC pointer in P2PC, saves address to RET back into Program 1
LD R4, P1PC                 ; r4 = address of P2PC
STR R4, R6, #0              ; replaced P1PC in S.S. with P1PC

LDR R5, R6, #1              ; saves mem[PSR] (S.S.) into R5
ST R5, P2PSR                ; saves P2's PSR val in P2PSR
LD R4, P1PSR
STR R4, R6, #1              ; replaced P1PSR in S.S. with P1PSR

; store val in KBDR into R0
LDI R0, KBDR                 ; R4 = val at kbdr

; disable interrupt
; LDI R3, KBSR                ; R3 = mem[xFF00] (always = x4000 (or greater)?)
AND R4, R4, #0              ; clear R4
STI R4, KBSR                ; setting  KBSR to 0

; restore/load Keyboard's IVT
LD R5, SAVEIR               ; SAVEIR = R5 = mem[x180]
STI R5, KBIV                ; mem[x180] = R5

; load Program 2's registers
LD R1, P1R1            
LD R2, P1R2            
LD R3, P1R3      
LD R4, P1R4         
LD R5, P1R5     
LD R7, P1R7 
RTI


; Program 1's data:
P1R1    .FILL x0000     ; TODO: Use these memory locations to save and restore
P1R2    .FILL x0000     ;       the first program's state.
P1R3    .FILL x0000
P1R4    .FILL x0000
P1R5    .FILL x0000
P1R7    .FILL x0000
P1PC    .FILL x0000     ; Initially, Program 1's PC is 0x3000, but that doesn't matter,
                        ; return address will be stored in R6
P1PSR   .FILL x0000     ; 

; Program 2's data:
P2R0    .FILL x0000     ; TODO: Use these memory locations to save and restore
P2R1    .FILL x0000     ;       the second program's state.
P2R2    .FILL x0000
P2R3    .FILL x0000
P2R4    .FILL x0000
P2R5    .FILL x0000
P2R7    .FILL x0000
P2PC    .FILL x4000     ; Initially, Program 2's PC is 0x4000, will be stored in R6
P2PSR   .FILL x8002     ; Initially, Program 2 is unprivileged.

; Shared data:
SAVEIR .FILL x2FFF      ; TODO: Use this memory location to save and restore
                        ;       the keyboard's IVT entry.

; Shared constants:
KBIV    .FILL x0180     ; The keyboard's interrupt vector
KBSR    .FILL xFE00     ; The Keyboard Status Register
KBDR    .FILL xFE02     ; The Keyboard Data Register
KBIMASK .FILL x4000     ; The keyboard interrupt bit's mask

        .END
