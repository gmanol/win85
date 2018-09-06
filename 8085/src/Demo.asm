; (c) 2000 George Manolaros aka Emc/dEUS
;
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� 0000H
; ROM (8192 bytes)                      1FFFH
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� 2000H
; RAM (8192 bytes)
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� 3FFFH <---- Stack

; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Constants
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

STACK_TOP       EQU     3ff0H

; Parallel interface 8255
PIOA            EQU     20H
PIOB            EQU     21H
PIOC            EQU     22H
PIOCTRL         EQU     23H
PIOW1           EQU     91H
PIOW2           EQU     10000000B
; Timer 8253
TM1             EQU     00H
TM2             EQU     01H
TM3             EQU     02H
TMCTRL          EQU     03H

; Serial 8251
SIN             EQU     40H
SOUT            EQU     40H
SSTAT           EQU     41H
SCTRL           EQU     41H
SW1             EQU     0CDH
SW2             EQU     15H
SRESET          EQU     40H

; Seiko LCD G1216B1N000 Ports
LCD_CTRL        EQU     80H    ; Instruction Port (in/out)
LCD_DATA        EQU     81H    ; Data Port (in/out)
LCD_CS          EQU     82H    ; Chip Select Port (output only)

; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Macros
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

Pusha           %MACRO
                push    B
                push    D
                push    H
                push    PSW

                %ENDM

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Popa            %MACRO
                pop     PSW
                pop     H
                pop     D
                pop     B

                %ENDM

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Locate          %MACRO  Y,X
                push    D
                mvi     D,X
                mvi     E,Y
                call    Seiko_Lcd_Locate
                pop     D

                %ENDM

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

STR             EQU     0
BYTE            EQU     1
WORD            EQU     2

HEX             EQU     0
BIN             EQU     1

NORMAL          EQU     0
WIDE            EQU     1

REG             EQU     0
VAL             EQU     1

Print           %MACRO  type,string,suffix,sourcetype,size
                %LOCAL  labx,strp
                PushA

        %IF     size    EQ      NORMAL

                call    Seiko_SetNormalFonts

        %ELSEIF size    EQ      WIDE

                call    Seiko_SetWideFonts
        %ENDIF

        %IF     type    EQ      STR

                push    H
                jmp     labx
strp:
                db      string
                db      suffix
                db      0
labx:
                lxi     H,strp
                call    Print_String
                pop     H

        %ELSEIF type    EQ      BYTE

                push    PSW

            %IF     suffix  EQ      HEX

                %IF     sourcetype EQ   REG
                mov     A,string
                %ELSEIF sourcetype EQ   VAL
                mvi     A,string
                %ENDIF

                call    Print_Byte
                call    Print_CR
            %ELSEIF suffix  EQ      BIN

                %IF     sourcetype EQ   REG
                mov     A,string
                %ELSEIF sourcetype EQ   VAL
                mvi     A,string
                %ENDIF

                call    Print_Binary_Byte
                call    Print_CR
            %ENDIF

                pop     PSW

        %ELSEIF type    EQ      WORD

                push    string
                push    B

            %IF     suffix  EQ      HEX

                %IF     sourcetype EQ   REG
                push    string
                pop     B
                %ELSEIF sourcetype EQ   VAL
                lxi     B,string
                %ENDIF

                call    Print_Word
                call    Print_CR
            %ELSEIF suffix  EQ      BIN

                %IF     sourcetype EQ   REG
                push    string
                pop     B
                %ELSEIF sourcetype EQ   VAL
                lxi     B,string
                %ENDIF

                call    Print_Binary_Word
                call    Print_CR
            %ENDIF

                pop     B
                pop     string

        %ENDIF


                PopA
                %ENDM

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Cls             %MACRO

                call    Seiko_Lcd_Cls

                %ENDM
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Pset            %MACRO  X,Y
                push    D
                mvi     D,X
                mvi     E,Y
                call    Seiko_Lcd_Pset
                pop     D
                %ENDM
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Sleep           %MACRO  inner,outer
                push    H
                push    B
                lxi     H,inner
                mvi     C,outer
                call    Delay
                pop     B
                pop     H
                %ENDM

; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Start
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

            Defseg gmk, absolute
	    seg    gmk

	    ORG  0000H

BOOT:
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Init Stack
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
        lxi     SP,STACK_TOP
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Init Devices
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

        Call    Init_Devices

; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Main Program
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

        call    Splash_Screen
        call    Clear_Regs

        Cls

        mvi     a,0
        sta     x1
        mvi     a,0
        sta     y1
        mvi     a,127
        sta     x2
        mvi     a,63
        sta     y2

        mvi     c,32
next_random:

        call    Seiko_Lcd_Line

        lda     x1
        inr     a
        inr     a
        inr     a
        inr     a
        sta     x1

        lda     x2
        dcr     a
        dcr     a
        dcr     a
        dcr     a
        sta     x2
        dcr     c
        jnz     next_random


        mvi     a,0
        sta     x1
        mvi     a,0
        sta     y1
        mvi     a,127
        sta     x2
        mvi     a,63
        sta     y2

        mvi     c,16
next_random2:
        call    Seiko_Lcd_Line

        lda     y1
        inr     a
        inr     a
        inr     a
        inr     a
        sta     y1

        lda     y2
        dcr     a
        dcr     a
        dcr     a
        dcr     a
        sta     y2

        dcr     c
        jnz     next_random2


        Sleep   30000,30

        Cls

        mvi     a,0
        sta     x1
        mvi     a,0
        sta     y1
        mvi     a,0
        sta     x2
        mvi     a,63
        sta     y2

        mvi     c,32
next_random3:

        call    Seiko_Lcd_Line

        lda     x1
        inr     a
        inr     a
        inr     a
        inr     a
        sta     x1

        lda     x2
        inr     a
        inr     a
        inr     a
        inr     a
        sta     x2

        dcr     c
        jnz     next_random3


        mvi     a,0
        sta     x1
        mvi     a,0
        sta     y1
        mvi     a,127
        sta     x2
        mvi     a,0
        sta     y2

        mvi     c,16
next_random4:

        call    Seiko_Lcd_Line

        lda     y1
        inr     a
        inr     a
        inr     a
        inr     a
        sta     y1

        lda     y2
        inr     a
        inr     a
        inr     a
        inr     a
        sta     y2

        dcr     c
        jnz     next_random4

        Sleep   30000,30

        Cls

        Call    Draw_Fractal

        Sleep   50000,255

        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        call    Display_Regs_Layout
axx:
        call    Display_Regs
        Sleep   30000,2
        inr     A
        dcx     B
        dcx     D
        inx     H
        dad     D
        jmp     axx

        hlt

; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Subroutines
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Draw Mandelbrot Fractal
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Draw_Fractal            PROC
        Pusha

; X=0 ... 127	    = D
; Y=0 ... 63	    = E

        mvi     e,32
..nextline:
        mvi     d,128
..nextpixel:
        push    d
        dcr     d
        dcr     e


        mov     a,e
        sui     32
        sta     yy
        sta     mandely

        mov     a,d
        sui     80
        sta     xx
        sta     mandelx

        push    d
        mvi     c,255
..loop:
        lda     mandelx
        mov     e,a
        call    Multiply
        shld    realnum

        lda     mandely
        mov     e,a
        call    Multiply
        shld    imagnum

        xchg
        lhld    realnum
        dad     d

        mov     a,h
        cpi     10
        jp      ..exitloop

        lda     mandelx
        mov     e,a
        lda     mandely
        call    Multiply

        call    hl_shr4

        xchg
        mvi     h,0
        lda     yy
        ani     128
        jz      ..abl2
        mvi     h,0ffh
..abl2:
        lda     yy
        mov     l,a
        dad     d

        mov     a,l
        sta     mandely


        lhld    imagnum
        xchg
        lhld    realnum
; hl-de
        mov     a,l
        sub     e
        mov     l,a
        mov     a,h
        sbb     d
        mov     h,a

        call    hl_shr5

        xchg
        mvi     h,0
        lda     xx
        ani     128
        jz      ..abl
        mvi     h,0ffh
..abl:
        lda     xx
        mov     l,a
        dad     d

        mov     a,l
        sta     mandelx


        dcr     c
        jnz     ..loop

..exitloop:

        pop     d


        push    d
        lxi     h,dither
        mvi     d,0
        mvi     a,255
        sub     c
        mov     e,a
        dad     d
        pop     d

        mov     a,m
        cpi     15
        jz      no_draw

        call    Seiko_Lcd_Pset

        push    d
        mvi     a,63
        sub     e
        mov     e,a
        call    Seiko_Lcd_Pset
        pop     d
no_draw:


        pop     d
        dcr     d
        jnz     ..nextpixel

        dcr     e
        jnz     ..nextline


        Popa
        ret

        include dither.inc
Draw_Fractal            ENDPROC

hl_shr1                 PROC
        mov     a,l
        ani     11111110b
        rrc
        mov     l,a
        mov     a,h
        ani     00000001b
        rrc
        ora     l
        mov     l,a

        mov     a,h
        ani     11111110b
        rrc
        mov     h,a

        mov     a,h
        ani     01000000b
        jz      ..soso
        mov     a,h
        ori     11000000b
        mov     h,a
..soso:
        ret
hl_shr1                 ENDPROC

hl_shr2                 PROC
        mov     a,l
        ani     11111100b
        rrc
        rrc
        mov     l,a
        mov     a,h
        ani     00000011b
        rrc
        rrc
        ora     l
        mov     l,a

        mov     a,h
        ani     11111100b
        rrc
        rrc
        mov     h,a

        mov     a,h
        ani     00100000b
        jz      ..soso
        mov     a,h
        ori     11100000b
        mov     h,a
..soso:
        ret
hl_shr2                 ENDPROC

hl_shr3                 PROC
        mov     a,l
        ani     11111000b
        rrc
        rrc
        rrc
        mov     l,a
        mov     a,h
        ani     00000111b
        rrc
        rrc
        rrc
        ora     l
        mov     l,a

        mov     a,h
        ani     11111000b
        rrc
        rrc
        rrc
        mov     h,a

        mov     a,h
        ani     00010000b
        jz      ..soso
        mov     a,h
        ori     11110000b
        mov     h,a
..soso:
        ret
hl_shr3                 ENDPROC

hl_shr4                 PROC
        mov     a,l
        ani     0f0h
        rrc
        rrc
        rrc
        rrc
        mov     l,a
        mov     a,h
        ani     0fh
        rlc
        rlc
        rlc
        rlc
        ora     l
        mov     l,a

        mov     a,h
        ani     0f0h
        rlc
        rlc
        rlc
        rlc
        mov     h,a

        mov     a,h
        ani     00001000b
        jz      ..soso
        mov     a,h
        ori     11111000b
        mov     h,a
..soso:
        ret
hl_shr4                 ENDPROC

hl_shr5                 PROC
        mov     a,l
        ani     11100000b
        rlc
        rlc
        rlc
        mov     l,a
        mov     a,h
        ani     00011111b
        rlc
        rlc
        rlc
        ora     l
        mov     l,a

        mov     a,h
        ani     11100000b
        rlc
        rlc
        rlc
        mov     h,a

        mov     a,h
        ani     00000100b
        jz      ..soso
        mov     a,h
        ori     11111100b
        mov     h,a
..soso:
        ret
hl_shr5                 ENDPROC

hl_shr6                 PROC
        mov     a,l
        ani     11000000b
        rlc
        rlc
        mov     l,a
        mov     a,h
        ani     00111111b
        rlc
        rlc
        ora     l
        mov     l,a

        mov     a,h
        ani     11000000b
        rlc
        rlc
        mov     h,a

        mov     a,h
        ani     00000010b
        jz      ..soso
        mov     a,h
        ori     11111110b
        mov     h,a
..soso:
        ret
hl_shr6                 ENDPROC

hl_shr7                 PROC
        mov     a,l
        ani     10000000b
        rlc
        mov     l,a
        mov     a,h
        ani     01111111b
        rlc
        ora     l
        mov     l,a

        mov     a,h
        ani     10000000b
        rlc
        mov     h,a

        mov     a,h
        ani     00000001b
        jz      ..soso
        mov     a,h
        ori     11111111b
        mov     h,a
..soso:
        ret
hl_shr7                 ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Multiply
; HL=A*E
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Multiply                PROC
        push    D
        push    B
        push    PSW

        mov     d,a

        mvi     b,0
        mov     a,e
        ani     80h
        jz      ..pos1
        mvi     b,1
        mov     a,e
        cma
        inr     a
        mov     e,a
..pos1:

        mvi     c,0
        mov     a,d
        ani     128
        jz      ..pos2
        mvi     c,1
        mov     a,d
        cma
        inr     a
        mov     d,a
..pos2:

        mov     a,d

        lxi     H,0
        mvi     D,0

        %REPT   8
        %LOCAL  NoAdd
        rrc
        jnc     NoAdd
        dad     D
NoAdd:
        xchg
        dad     H
        xchg
        %ENDREPT

        mov     a,b
        xra     c
        jz      ..done
        mov     a,l
        cma
        adi     1
        mov     l,a
        mov     a,h
        cma
        aci     0
        mov     h,a
..done:

        pop     PSW
        pop     B
        pop     D

        ret

Multiply                ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Bresenham Line
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Seiko_Lcd_Line          PROC
        Pusha

        lda     x2
        lxi     h,x1
        sub     m
        jp      ..positive
        cma
        inr     a
..positive:
        sta     deltax
        mov     c,a             ; c=deltax

        lda     y2
        lxi     h,y1
        sub     m
        jp      ..positive2
        cma
        inr     a
..positive2:
        sta     deltay
        mov     b,a             ; b=deltay

        cmp     c
        jp      ..positive3

; deltax>=deltay
        mov     a,c
        inr     a
        sta     numpixels       ; numpixels=deltax+1


        mvi     h,0
        mov     l,b
        dad     h
        shld    dinc1           ; dinc1=2*deltay


        mvi     d,0
        mov     e,c
        mov     a,l
        sub     e
        mov     l,a
        mov     a,h
        sbb     d
        mov     h,a

        shld    delta           ; delta=2*deltay-deltax

        mvi     d,0
        mov     e,c
        mov     a,l
        sub     e
        mov     l,a
        mov     a,h
        sbb     d
        mov     h,a

        shld    dinc2           ; dinc2=2*deltay-2*deltax

        lxi     h,xinc1
        mvi     m,1
        lxi     h,xinc2
        mvi     m,1
        lxi     h,yinc1
        mvi     m,0
        lxi     h,yinc2
        mvi     m,1

        jmp     ..done
..positive3:
; deltax<deltay

        mov     a,b
        inr     a
        sta     numpixels       ; numpixels=deltay+1

        mvi     h,0
        mov     l,c
        dad     h
        shld    dinc1           ; dinc1=2*deltax

        mvi     d,0
        mov     e,b
        mov     a,l
        sub     e
        mov     l,a
        mov     a,h
        sbb     d
        mov     h,a

        shld    delta           ; delta=2*deltax-deltay

        mvi     d,0
        mov     e,b
        mov     a,l
        sub     e
        mov     l,a
        mov     a,h
        sbb     d
        mov     h,a

        shld    dinc2           ; dinc2=2*deltax-2*deltay

        lxi     h,xinc1
        mvi     m,0
        lxi     h,xinc2
        mvi     m,1
        lxi     h,yinc1
        mvi     m,1
        lxi     h,yinc2
        mvi     m,1

..done:

        lxi     h,x1
        mov     a,m
        lxi     h,x2
        cmp     m
        jm      ..noneg

        lda     xinc1
        cma
        inr     a
        sta     xinc1
        lda     xinc2
        cma
        inr     a
        sta     xinc2
..noneg:

        lxi     h,y1
        mov     a,m
        lxi     h,y2
        cmp     m
        jm      ..noneg2

        lda     yinc1
        cma
        inr     a
        sta     yinc1
        lda     yinc2
        cma
        inr     a
        sta     yinc2

..noneg2:

; X=0 ... 127	    = D
; Y=0 ... 63	    = E

        lda     x1
        mov     d,a
        lda     y1
        mov     e,a

        lhld    delta

        lda     numpixels
        mov     c,a
..loop:
        call    Seiko_Lcd_Pset

        mov     a,h
        ani     10000000b
        jz     ..posdelta

        push    d
        xchg
        lhld    dinc1
        xchg
        dad     d
        pop     d

        lda     xinc1
        add     d
        mov     d,a

        lda     yinc1
        add     e
        mov     e,a

        jmp     ..end

..posdelta:
        push    d
        xchg
        lhld    dinc2
        xchg
        dad     d
        pop     d

        lda     xinc2
        add     d
        mov     d,a

        lda     yinc2
        add     e
        mov     e,a

..end:

        dcr     c
        jnz     ..loop


        Popa
        ret

Seiko_Lcd_Line          ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Clear_Regs
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Clear_Regs              PROC

        mvi     b,0
        mvi     c,0
        mvi     d,0
        mvi     e,0
        mvi     h,0
        mvi     l,0
        push    b
        pop     psw
        ret

Clear_Regs              ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Init_Devices
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Init_Devices            PROC
        mvi     A,PIOW2
        out     PIOCTRL

        mvi     A,00H
        out     SCTRL
        out     SCTRL
        out     SCTRL
        mvi     A,SRESET
        out     SCTRL
        mvi     A,SW1
        out     SCTRL
        mvi     A,SW2
        out     SCTRL

        mvi     A,36H
        out     TMCTRL
        mvi     A,76H
        out     TMCTRL
        mvi     A,64H
        out     TM1
        mvi     A,00H
        out     TM1
        mvi     A,20H
        out     TM2
        mvi     A,4EH
        out     TM2

        call    Seiko_Lcd_init

        ret

Init_Devices            ENDPROC
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Splash_Screen
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Splash_Screen           PROC
        Cls
        Locate  7,0
        Print   STR,'Seiko G1216B1N00',0dh,0,WIDE
        Print   STR,"--------------------------------",0dh,0,NORMAL
        Print   STR,'(c) `93 Seiko Instruments Inc.',0dh,0,NORMAL
        Print   STR,'(c) `98 Gmk Corporation',0dh,0,NORMAL
        Print   STR,' ',0dh,0,NORMAL
        Print   STR,'Copyright (c) 2000 G. Manolaros',0dh,0,NORMAL
        Print   STR,'all rights reserved',0dh,0,NORMAL
        Print   STR,' ',0dh,0,NORMAL

        Sleep   50000,9
        ret

Splash_Screen           ENDPROC
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Display_Regs_Layout
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Display_Regs_Layout     PROC
        Pusha
        Cls
        Locate  0,0

        Print   STR,'AF=     BC=    ',0dh,0,WIDE
        Print   STR,'DE=     HL=    ',0dh,0,WIDE
        Print   STR,'SP=            ',0dh,0,WIDE
        Print   STR,'FLAGS=         ',0dh,0,WIDE
        Print   STR,'       SZ5A-PVC',0dh,0,WIDE
        Popa

        ret
Display_Regs_Layout     ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Display_Regs
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Display_Regs            PROC
        Pusha

        Locate  0,22
        Print   WORD,B,HEX,REG,WIDE

        Locate  0,6
        push    PSW
        pop     B
        Print   WORD,B,HEX,REG,WIDE

        Locate  3,14
        mov     A,C
        Print   BYTE,A,BIN,REG,WIDE

        Locate  1,6
        push    D
        pop     B
        Print   WORD,B,HEX,REG,WIDE

        Locate  1,22
        push    H
        pop     B
        Print   WORD,B,HEX,REG,WIDE

        Locate  2,6
        lxi     H,10
        dad     SP
        push    H
        pop     B
        Print   WORD,B,HEX,REG,WIDE

        Popa

        ret
Display_Regs            ENDPROC

Out_Char                PROC
        push    PSW
        push    B
        mov     B,A

        lda     Lcd_Font_Mode
        cpi     0
        jnz     ..wide
        mov     A,B
        call    Seiko_Lcd_Char
        jmp     ..done
..wide:
        mov     A,B
        call    Seiko_Lcd_Wide_Char
..done:



;        call    Serial_Write
        pop     B
        pop     PSW
        ret
Out_Char                ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Print_String
; HL = Offset StringZ
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Print_String            PROC
        Pusha

..next_char:
        mov     A,M
        cpi     0
        jz      ..exit
        out     piob
        call    Out_Char
        inx     H
        jmp     ..next_char
..exit:

        Popa
        ret

Print_String            ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Print_Byte
; A=data
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Print_Byte              PROC
        Pusha
        mvi     B,0

        push    PSW

        ani     11110000b
        rrc
        rrc
        rrc
        rrc
        mov     C,A

        lxi     H,hex_calc
        dad     B

        mov     A,M
        call    Out_Char
        pop     PSW

        ani     00001111b
        mov     C,A

        lxi     H,hex_calc
        dad     B

        mov     A,M
        call    Out_Char

        Popa
        ret
hex_calc  db '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'

Print_Byte              ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Print_Binary_Byte
; A=data
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Print_Binary_Byte       PROC

        Pusha

        mvi     C,8

..next_bit:

        ral
        push    PSW

        jc      ..bit_set
        mvi     A,48

        call    Out_Char

        jmp     ..bit_done
..bit_set:
        mvi     A,49
        call    Out_Char
..bit_done:

        pop     PSW
        dcr     C
        jnz     ..next_bit

        Popa
        ret

        ret
Print_Binary_Byte       ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Print_Word
; BC=data
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Print_Word              PROC

        Pusha
        mov     A,B
        call    Print_Byte
        mov     A,C
        call    Print_Byte
        Popa
        ret

Print_Word              ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Print_Binary_Word
; BC=data
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Print_Binary_Word       PROC

        Pusha
        mov     A,B
        call    Print_Binary_Byte
        mov     A,C
        call    Print_Binary_Byte
        Popa
        ret

Print_Binary_Word       ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Print_CR
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Print_CR                PROC
        push    PSW
        mvi     A,0dh
        call    Out_Char
        pop     PSW
        ret
Print_CR                ENDPROC


; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_SetNormalFonts
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Seiko_SetNormalFonts      PROC
        push    PSW
        mvi     A,0
        sta     Lcd_Font_Mode
        pop     PSW
        ret
Seiko_SetNormalFonts      ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_SetWideFonts
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Seiko_SetWideFonts      PROC
        push    PSW
        mvi     A,1
        sta     Lcd_Font_Mode
        pop     PSW
        ret
Seiko_SetWideFonts      ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Busy
; Wait until Seiko is ready
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Seiko_Lcd_Busy          PROC
        ret
        push    psw
..wait:
        in      LCD_CTRL
        ani     10000000B
        jnz     ..wait

        pop     psw
        ret

Seiko_Lcd_Busy          ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Init
; Initialize Seiko
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Seiko_Lcd_Init          PROC
;..wait_for_reset
;        in      LCD_CTRL
;        ani     00010000B
;        jnz     ..wait_for_reset

        call    Seiko_Lcd_Cls

        mvi     A,0
        call    Seiko_Lcd_SetCS
        call    Seiko_Lcd_SetX
        call    Seiko_Lcd_SetY
        call    Seiko_Lcd_SetZ

        mvi     D,0
        mvi     E,0
        call    Seiko_Lcd_Locate

        mvi     A,0
        sta     Lcd_Font_Mode


        mvi     A,00111111B     ; turn on screen
        out     Lcd_ctrl

        call    Seiko_Lcd_Busy

        ret
Seiko_Lcd_Init          ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Locate
; Locate cursor
; X=0 ... 31	   = D
; Y=0 ... 7	   = E
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Seiko_Lcd_Locate        PROC
        Pusha

        mov     A,E
        ani     00000111B
        rlc
        rlc
        rlc
        rlc
        rlc
        ani     11100000B
        mov     B,A
        mov     A,D
        ani     00011111B
        ora     B               ; A = YYYXXXXX

        sta     Lcd_Cursor
        mvi     a,0
        sta     Lcd_Cursor+1

        Popa
        ret

Seiko_Lcd_Locate        ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Scroll_Up
; Scrolls Screen Up
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Seiko_Lcd_Scroll_Up     PROC

        Pusha
        mvi     B,0
        mvi     D,7
..nxt_page_c:
        mvi     A,01B
        call    Seiko_Lcd_SetCS

        mov     A,B
        inr     A
        call    Seiko_Lcd_SetX
        mvi     A,0
        call    Seiko_Lcd_SetY
        in      Lcd_DATA        ; dummy read
        call    Seiko_Lcd_Busy

        lxi     H,Lcd_buffer
        mvi     C,64
..nxt_pix_c0:
        in      Lcd_DATA
        call    Seiko_Lcd_Busy
        mov     M,A
        inx     H
        dcr     C
        jnz     ..nxt_pix_c0

        mvi     A,10B
        call    Seiko_Lcd_SetCS

        mov     A,B
        inr     A
        call    Seiko_Lcd_SetX
        mvi     A,0
        call    Seiko_Lcd_SetY
        in      Lcd_DATA        ; dummy read
        call    Seiko_Lcd_Busy

        mvi     C,64
..nxt_pix_c1:
        in      Lcd_DATA
        call    Seiko_Lcd_Busy
        mov     M,A
        inx     H
        dcr     C
        jnz     ..nxt_pix_c1

        mvi     A,01B
        call    Seiko_Lcd_SetCS

        mov     A,B
        call    Seiko_Lcd_SetX
        mvi     A,0
        call    Seiko_Lcd_SetY

        lxi     H,Lcd_buffer
        mvi     C,64
..nxt_pix_c2:
        mov     A,M
        out     Lcd_DATA
        call    Seiko_Lcd_Busy
        inx     H
        dcr     C
        jnz     ..nxt_pix_c2

        mvi     A,10B
        call    Seiko_Lcd_SetCS

        mov     A,B
        call    Seiko_Lcd_SetX
        mvi     A,0
        call    Seiko_Lcd_SetY

        mvi     C,64
..nxt_pix_c3:
        mov     A,M
        out     Lcd_DATA
        call    Seiko_Lcd_Busy
        inx     H
        dcr     C
        jnz     ..nxt_pix_c3

        inr     B
        dcr     D
        jnz     ..nxt_page_c

        mvi     A,00B
        call    Seiko_Lcd_SetCS
        mvi     A,7
        call    Seiko_Lcd_SetX
        mvi     B,64
        mvi     A,0
..nxt_clr:
        out     Lcd_data
        call    Seiko_Lcd_Busy
        dcr     B
        jnz     ..nxt_clr
        Popa

        ret
Seiko_Lcd_Scroll_Up     ENDPROC


; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Char
; Displays character stored in A at cursor position
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Seiko_Lcd_Char          PROC

        Pusha
;input A=char
        mov     B,A
        lda     Lcd_Cursor+1
        cpi     0
        jz      ..no_up
        lda     Lcd_Cursor
        sui     32
        sta     Lcd_Cursor
        mvi     a,0
        sta     Lcd_Cursor+1
        call    Seiko_Lcd_Scroll_Up

..no_up:
        mov     A,B
        cpi     0dh
        jnz     ..no_cr
        lhld    Lcd_Cursor

        mov     A,L
        ani     00111111B
        cpi     32
        jnz     ..cr
        Popa
        ret
..cr:

        mov     A,L
        ani     11100000B

        mov     L,A
        lxi     D,32
        dad     D
        shld    Lcd_Cursor

        Popa
        ret
..no_cr:

        mvi     H,0
        mov     L,A

        dad     H
        dad     H

        lxi     B,font0
        dad     B

        lda     Lcd_Cursor
        ani     00010000B
        jnz     ..prap
        mvi     A,10B
        jmp     ..fofiko
..prap:
        mvi     A,01B
..fofiko:
        call    Seiko_Lcd_SetCS

        lda     Lcd_Cursor
        ani     00001111B
        add     A
        add     A
        call    Seiko_Lcd_SetY

        lda     Lcd_Cursor
        ani     11100000B
        rrc
        rrc
        rrc
        rrc
        rrc
        call    Seiko_Lcd_SetX

        push    H
        lhld    Lcd_Cursor
        inx     H
        shld    Lcd_Cursor
        pop     H

        mvi     B,4
..next_vfnt:
        mov     A,M
        out     LCD_DATA
        call    Seiko_Lcd_Busy

        inx     H
        dcr     B
        jnz     ..next_vfnt
        Popa
        ret

Seiko_Lcd_Char          ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Wide_Char
; Displays wide character stored in A at cursor position
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Seiko_Lcd_Wide_Char     PROC

        Pusha
;input A=char
        mov     B,A

        lda     Lcd_Cursor
        ani     11111110B
        sta     Lcd_Cursor

        lda     Lcd_Cursor+1
        cpi     0
        jz      ..no_up
        lda     Lcd_Cursor
        sui     32
        sta     Lcd_Cursor
        mvi     a,0
        sta     Lcd_Cursor+1
        call    Seiko_Lcd_Scroll_Up
..no_up:
        mov     A,B
        cpi     0dh
        jnz     ..no_cr
        lhld    Lcd_Cursor

        mov     A,L
        ani     00111111B
        cpi     32
        jnz     ..cr
        Popa
        ret
..cr:

        mov     A,L
        ani     11100000B

        mov     L,A
        lxi     D,32
        dad     D
        shld    Lcd_Cursor

        Popa
        ret
..no_cr:

        mvi     H,0
        mov     L,A

        dad     H
        dad     H
        dad     H

        lxi     B,dfont0
        dad     B

        lda     Lcd_Cursor
        ani     00010000B
        jnz     ..prap
        mvi     A,10B
        jmp     ..fofiko
..prap:
        mvi     A,01B
..fofiko:
        call    Seiko_Lcd_SetCS

        lda     Lcd_Cursor
        ani     00001111B
        add     A
        add     A
        call    Seiko_Lcd_SetY

        lda     Lcd_Cursor
        ani     11100000B
        rrc
        rrc
        rrc
        rrc
        rrc
        call    Seiko_Lcd_SetX

        push    H
        lhld    Lcd_Cursor
        inx     H
        inx     H
        shld    Lcd_Cursor
        pop     H

        mvi     B,8
..next_vfnt:
        mov     A,M
        out     LCD_DATA
        call    Seiko_Lcd_Busy

        inx     H
        dcr     B
        jnz     ..next_vfnt
        Popa
        ret

Seiko_Lcd_Wide_Char     ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Cls
; Clear Screen
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Seiko_Lcd_Cls           PROC
        pusha

        mvi     A,0
        call    Seiko_Lcd_SetCS

        mvi     B,8
..nxt_page:
        mov     A,B
        dcr     A
        call    Seiko_Lcd_SetX

        mvi     D,64
..nxt_pixel:
        mvi     A,0
        out     LCD_DATA
        call    Seiko_lcd_busy
        dcr     D
        jnz     ..nxt_pixel

        dcr     B
        jnz     ..nxt_page

        Locate  0,0

        popa
        ret
Seiko_Lcd_Cls           ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Pset
; Plot Pixel
; X=0 ... 127	    = D
; Y=0 ... 63	    = E
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Seiko_Lcd_Pset          PROC
        Pusha
        mov     A,D
        ani     10000000B
        jz      ..test1ok
        Popa
        ret
..test1ok:
        mov     A,E
        ani     11000000B
        jz      ..test2ok
        Popa
        ret
..test2ok:

        mov     A,D
        ani     01000000B
        jnz     ..second_cs

        mvi     A,10b
        jmp     ..end_cs
..second_cs:
        mvi     A,01b
..end_cs:
        call    Seiko_Lcd_SetCS

        mov     A,D
        ani     00111111B
        push    psw
        call    Seiko_Lcd_SetY

        mov     A,E
        rrc
        rrc
        rrc
        ani     00000111B
        push    psw
        call    Seiko_Lcd_SetX

        mov     A,E
        ani     00000111B

        lxi     H,pset_prec1
        add     L
        mov     L,A
        mov     B,M

        in      Lcd_DATA
        call    Seiko_Lcd_Busy
        in      Lcd_DATA
        call    Seiko_Lcd_Busy

        ora     B
        mov     B,A

        pop     psw
        call    Seiko_Lcd_SetX
        pop     psw
        call    Seiko_Lcd_SetY

        mov     A,B

        out     Lcd_DATA
        call    Seiko_Lcd_Busy

        Popa
        ret

pset_prec1      db      01,02,04,08,16,32,64,128
Seiko_Lcd_Pset          ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Seiko_Lcd_Set*
; Update internal Seiko registers       (A=source)
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Seiko_Lcd_SetX          PROC
        push    psw
        ani     00000111B
        ori     10111000B
        out     LCD_CTRL
        call    Seiko_Lcd_Busy
        pop     psw
        ret
Seiko_Lcd_SetX          ENDPROC

Seiko_Lcd_SetY          PROC
        push    psw
        ani     00111111B
        ori     01000000B
        out     LCD_CTRL
        call    Seiko_Lcd_Busy
        pop     psw
        ret
Seiko_Lcd_SetY          ENDPROC

Seiko_Lcd_SetZ          PROC
        push    psw
        ani     00111111B
        ori     11000000B
        out     LCD_CTRL
        call    Seiko_Lcd_Busy
        pop     psw
        ret
Seiko_Lcd_SetZ          ENDPROC

Seiko_Lcd_SetCS         PROC
        push    psw
        ani     00000011B
        out     LCD_CS
        pop     psw
        ret
Seiko_Lcd_SetCS         ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Delay
; Small delay
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Delay                   PROC
        Pusha

        mov     D,H
        mov     E,L

..main:
        mov     H,D
..outer:

        mov     L,E
..inner:
        dcr     L
        jnz     ..inner

        dcr     H
        jnz     ..outer

        dcr     C
        jnz     ..main

        Popa
        ret
Delay                   ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Serial_Write
; A=data
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

Serial_Write            PROC

        push    PSW
        push    B
        mov     B,A
..poll:
        in      SSTAT
        ani     01h
        jz      ..poll

        mov     A,B
        out     SOUT
        pop     B
        pop     PSW
        ret

Serial_Write            ENDPROC

; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
; Sub Serial_Read
; Returns: A=data
; 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
Serial_Read             PROC

..poll:
        in      SSTAT
        ani     02h
        jz      ..poll
        in      SIN
        ret

Serial_Read             ENDPROC

; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Static Data
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴

        include fonts.inc
        include fonts.big
;0dh=cr
message         db "0123456789012345",0dh,0
DataStack:


; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
; Variables (RAM)
; 袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴
        org  2000H

; Seiko LCD G1216B1N000 Variables
Lcd_Cursor      ds 2
Lcd_Font_Mode   ds 1
Lcd_Buffer      ds 128

; Bresenham Line Variables
x1              ds 1
y1              ds 1
x2              ds 1
y2              ds 1

numpixels       ds 1

delta           ds 2
dinc1           ds 2
dinc2           ds 2

xinc1           ds 1
yinc1           ds 1

xinc2           ds 1
yinc2           ds 1

deltax          ds 1
deltay          ds 1

; Mandelbrot Fractal Variables

yy              ds 1
xx              ds 1
mandelx         ds 1
mandely         ds 1
realnum         ds 2
imagnum         ds 2

        END
