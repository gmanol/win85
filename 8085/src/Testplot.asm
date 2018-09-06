; -------------------------------------0000H
; EPROM (8192 bytes)
; -------------------------------------1FFFH
; -------------------------------------2000H
; USER RAM
; -------------------------------------
; -------------------------------------
; SYSTEM RAM (BUFFERS,ETC. 256 BYTES)
; -------------------------------------
; -------------------------------------
; SYSTEM STACK 256 BYTES
; -------------------------------------3FFFH
;

pusha       %MACRO
            PUSH B
            PUSH D
            PUSH H
            PUSH PSW
            %ENDM

popa        %MACRO
            POP  PSW
            POP  H
            POP  D
            POP  B
            %ENDM


STACK_TOP   EQU    3fffH

; Paraller interface 8255
PIOA     EQU 20H              
PIOB     EQU 21H             
PIOC     EQU 22H             
PIOCTRL  EQU 23H
PIOW1    EQU 91H             
PIOW2    EQU 10000000B
; Timer 8253
TM1      EQU 00H             
TM2      EQU 01H             
TM3      EQU 02H                     
TMCTRL   EQU 03H
; Serial 8251
SIN      EQU 40H              
SOUT     EQU 40H             
SSTAT    EQU 41H              
SCTRL    EQU 41H              
SW1      EQU 0CDH             
SW2      EQU 15H             
SRESET   EQU 40H

; Seiko LCD G1216B1N000 Ports
LCD_CTRL    EQU 80H    ; Instruction Port (in/out)
LCD_DATA    EQU 81H    ; Data Port (in/out)
LCD_CSP     EQU 82H    ; Chip Select Port (output only)

; Seiko LCD G1216B1N000 Variables
LCD_VARS    EQU 3500H
LCD_X       EQU LCD_VARS
LCD_Y       EQU LCD_VARS+1
LCD_Z       EQU LCD_VARS+2
LCD_CS      EQU LCD_VARS+3
LCD_CURSOR  EQU LCD_VARS+4
LCD_BUFFER  EQU LCD_VARS+5
lcd_next    equ lcd_vars+128+5
           ;

            Defseg gmk, absolute
            seg    gmk

            ORG  0000H

BOOT:
            LXI  SP,STACK_TOP

            MVI  A,PIOW2
            OUT  PIOCTRL

            MVI  A,00H
            OUT  SCTRL
            OUT  SCTRL
            OUT  SCTRL
            MVI  A,SRESET
            OUT  SCTRL
            MVI  A,SW1
            OUT  SCTRL
            MVI  A,SW2
            OUT  SCTRL
            ;
            MVI  A,36H
            OUT  TMCTRL
            MVI  A,76H
            OUT  TMCTRL
            MVI  A,64H
            OUT  TM1
            MVI  A,00H
            OUT  TM1
            MVI  A,20H
            OUT  TM2
            MVI  A,4EH
            OUT  TM2

            call    lcd_init

            LXI     H,message
            CALL    FDISPMES


            mvi     E,63
agyy:
            mvi     D,127
agxx:
            call    lcd_pset
            dcr     D
            dcr     D
            jp      agxx
            dcr     E
            dcr     E
            jp      agyy

            hlt

;^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
;                            SUBROUTINE FDISPMES
;  DISPLAYS A MESSAGE WHOSE START IS POINTED AT BY HL AND THE END IS
;  DEFINED BY 0.REGISTERS RETURN UNAFFECTED.
; ---------------------------------------------------------------------

FDISPMES:  PUSH PSW         ;
	   PUSH B           ;
	   PUSH D           ;
	   PUSH H           ;
FDMES1:    MOV  A,M         ;
	   CPI  00H         ;
	   JZ   FDISEND     ;
           CALL lcd_dchar
	   INX  H           ;
	   JMP  FDMES1      ;
FDISEND:   POP  H           ;
	   POP  D           ;
	   POP  B           ;
	   POP  PSW         ;
	   RET              ;
;^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
;                           SUBROUTINE OUTCHAR 
; THIS SUBROUTINE TRANSMITS A CHARACTER CONTAINED IN A TO THE TERMINAL.
; REGISTERS RETURN UNAFFECTED. 
; ---------------------------------------------------------------------

OUTCHAR:   PUSH PSW         ;
           PUSH B           ;
           MOV  B,A         ;
L2OP1:     IN   SSTAT       ;
           ANI  01H         ;
           JZ   L2OP1       ;
           MOV  A,B         ;
           OUT  SOUT        ;
           call lcd_char
           POP  B           ;
	   POP  PSW         ;
	   RET              ;

;^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
;                           SUBROUTINE INCHAR  
; THIS SUBROUTINE RECEIVES A CHARACTER FROM THE KEYBOARD AND LOADS A
; WITH IT.AFFECTS ONLY ACCUMULATOR AND FLAGS.  
; ---------------------------------------------------------------------

INCHAR:    IN   SSTAT       ÿ
           ANI  02H         ÿ
           JZ   INCHAR      ÿ
           IN   SIN         ÿ
           OUT  PIOB        ÿ
           RET              ÿ
;------------------------------- lcd
DELAY:
            push    d
            mvi     d,1
del4:       mvi     e,1
del3:       dcr     e
            jnz     del3
            dcr     d
            jnz     del4
            pop     d
            ret

longdelay:
            push    d
            mvi     d,40
del2:       mvi     e,200
del1:       dcr     e
            jnz     del1
            dcr     d
            jnz     del2
            pop     d
            ret

lcd_busy:
            ret
            push    psw
wait_for_busy:
            in      LCD_CTRL
            ani     10000000B
;            jnz     wait_for_busy

            pop     psw
            ret

lcd_init:
wait_for_reset:
            in      LCD_CTRL
            ani     00010000B
;            jnz     wait_for_reset

            call    lcd_cls

            mvi     a,0
            call    lcd_setCS
            call    lcd_setX
            call    lcd_setY
            call    lcd_setZ

            mvi     d,0
            mvi     e,0
            call    lcd_locate

            MVI     A,00111111B     ; turn on screen
            out     LCD_CTRL
            call    lcd_busy

            ret

lcd_locate:
; change text cursor position
; X=0 ... 15       = D
; Y=0 ... 7        = E
            pusha

            mov     a,e
            ani     00000111B
            rlc
            rlc
            rlc
            rlc
            mov     b,a
            mov     a,d
            ani     00001111B
            add     b

            sta     lcd_cursor

            popa
            ret
lcd_scroll_up:
            pusha
            mvi     b,0
            mvi     d,7
nxt_page_c:
            mvi     a,01B
            call    lcd_setCS

            mov     a,b
            inr     a
            call    lcd_setX
            mvi     a,0
            call    lcd_setY
            in      lcd_DATA        ; dummy read
            call    lcd_busy

            lxi     h,lcd_buffer
            mvi     c,64
nxt_pix_c0:
            in      lcd_DATA
            call    lcd_busy
            mov     M,a
            inx     h
            dcr     c
            jnz     nxt_pix_c0

            mvi     a,10B
            call    lcd_setCS

            mov     a,b
            inr     a
            call    lcd_setX
            mvi     a,0
            call    lcd_setY
            in      lcd_DATA        ; dummy read
            call    lcd_busy

            mvi     c,64
nxt_pix_c1:
            in      lcd_DATA
            call    lcd_busy
            mov     M,a
            inx     h
            dcr     c
            jnz     nxt_pix_c1

            mvi     a,01B
            call    lcd_setCS

            mov     a,b
            call    lcd_setX
            mvi     a,0
            call    lcd_setY

            lxi     h,lcd_buffer
            mvi     c,64
nxt_pix_c2:
            mov     a,M
            out     lcd_DATA
            call    lcd_busy
            inx     h
            dcr     c
            jnz     nxt_pix_c2

            mvi     a,10B
            call    lcd_setCS

            mov     a,b
            call    lcd_setX
            mvi     a,0
            call    lcd_setY

            mvi     c,64
nxt_pix_c3:
            mov     a,M
            out     lcd_DATA
            call    lcd_busy
            inx     h
            dcr     c
            jnz     nxt_pix_c3

            inr     b
            dcr     d
            jnz     nxt_page_c

            mvi     a,00B
            call    lcd_setCS
            mvi     a,7
            call    lcd_setX
            mvi     b,64
            mvi     a,0
nxt_clr:
            out     lcd_data
            call    lcd_busy
            dcr     b
            jnz     nxt_clr
            popa
            ret

lcd_dchar:
            pusha
;input A=char
            mov     b,a
            lda     lcd_cursor
            ani     11111110B
            cpi     0
            jnz     no_upd
            sui     32
            sta     lcd_cursor
            call    lcd_scroll_up
no_upd:
            mov     a,b
            cpi     0dh
            jnz     no_crd
            lda     lcd_cursor
            ani     11100000B
            adi     32
            sta     lcd_cursor
            popa
            ret
no_crd:

            mvi     h,0
            mov     l,a

            dad     h
            dad     h
            dad     h

            lxi     b,dfont0
            dad     b

            lda     lcd_cursor
            ani     00010000B       ;emcl
            jnz     prapd
            mvi     a,10B
            jmp     fofikod
prapd:
            mvi     a,01B
fofikod:
            call    lcd_setCS

            lda     lcd_cursor
            ani     00001111B
            add     a
            add     a
            call    lcd_setY

            lda     lcd_cursor
            ani     11100000B
            rrc
            rrc
            rrc
            rrc
            rrc
            call    lcd_setX

            lda     lcd_cursor
            inr     A
            inr     A
            sta     lcd_cursor

            mvi     b,8
next_vfntd:
            mov     A,M
            out     LCD_DATA
            call    lcd_busy

            inx     h
            dcr     b
            jnz     next_vfntd
            popa
            ret
lcd_char:
            pusha
;input A=char
            mov     b,a
            lda     lcd_cursor
            cpi     0
            jnz     no_up
            sui     32
            sta     lcd_cursor
            call    lcd_scroll_up
no_up:
            mov     a,b
            cpi     0dh
            jnz     no_cr
            lda     lcd_cursor
            ani     11100000B
            adi     32
            sta     lcd_cursor
            popa
            ret
no_cr:

            mvi     h,0
            mov     l,a

            dad     h
            dad     h

            lxi     b,font0
            dad     b

            lda     lcd_cursor
            ani     00010000B
            jnz     prap
            mvi     a,10B
            jmp     fofiko
prap:
            mvi     a,01B
fofiko:
            call    lcd_setCS

            lda     lcd_cursor
            ani     00001111B
            add     a
            add     a
            call    lcd_setY

            lda     lcd_cursor
            ani     11100000B
            rrc
            rrc
            rrc
            rrc
            rrc
            call    lcd_setX

            lda     lcd_cursor
            inr     A
            sta     lcd_cursor

            mvi     b,4
next_vfnt:
            mov     A,M
            out     LCD_DATA
            call    lcd_busy

            inx     h
            dcr     b
            jnz     next_vfnt
            popa
            ret

lcd_CLS:
            pusha

            mvi     a,0
            call    lcd_setCS

            mvi     b,7
nxt_page:
            mov     a,b
            call    lcd_setX

            mvi     d,64
nxt_pixel:
            mvi     a,0
            out     LCD_DATA
            call    lcd_busy
            dcr     d
            jnz     nxt_pixel

            dcr     b
            jp      nxt_page

            popa
            ret

lcd_pset:
; plot pixel : x,y
; X=0 ... 127       = D
; Y=0 ... 63        = E
            pusha

            mov     a,d
            ani     01000000B
            jnz     second_cs

            mvi     a,10b
            jmp     end_cs
second_cs:
            mvi     a,01b
end_cs:
            call    lcd_setCS

            mov     a,d
            ani     00111111B
            push    psw
            call    lcd_setY

            mov     a,e
            rrc
            rrc
            rrc
            ani     00000111B
            push    psw
            call    lcd_setX

            mov     a,e
            ani     00000111B

            lxi     h,pset_prec1
            add     l
            mov     l,a
            mov     b,m

            in      lcd_DATA
            call    lcd_busy
            in      lcd_DATA
            call    lcd_busy

            ora     b
            mov     b,a

            pop     psw
            call    lcd_setX
            pop     psw
            call    lcd_setY

            mov     a,b

            out     lcd_DATA
            call    lcd_busy

            popa
            ret

pset_prec1  db      01,02,04,08,16,32,64,128

lcd_setX:
            push    psw
            ani     00000111B
            sta     LCD_X
            ori     10111000B
            out     LCD_CTRL
            call    lcd_busy
            pop     psw
            ret

lcd_setY:
            push    psw
            ani     00111111B
            sta     LCD_Y
            ori     01000000B
            out     LCD_CTRL
            call    lcd_busy
            pop     psw
            ret

lcd_setZ:
            push    psw
            ani     00111111B
            sta     LCD_Z
            ori     11000000B
            out     LCD_CTRL
            call    lcd_busy
            pop     psw
            ret

lcd_setCS:
; A=CS
            push    psw
            ani     00000011B
            sta     LCD_CS
            out     LCD_CSP
            pop     psw
            ret


            include fonts.inc
            include fonts.big

;0dh=cr
;0ah=lf
message   db 'Seiko G1216B1N0',0dh
          db 196,196,196,196,196,196
          db 196,196,196,196,196,196
          db 196,196,196,196
          db '(c)`93 Seiko Inc'
          db '(c)`98 Gmk Corp ',13,13,13,13,0


          END
;
