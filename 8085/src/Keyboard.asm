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



STACK_TOP   EQU     25ffH

; Seiko LCD G1216B1N000 Ports
LCD_CTRL    EQU 80H    ; Instruction Port (in/out)
LCD_DATA    EQU 81H    ; Data Port (in/out)
LCD_CS      EQU 82H    ; Chip Select Port (output only)

KEYB_DATA   EQU 60H

; Seiko LCD G1216B1N000 Variables
LCD_VARS    EQU 2600H
LCD_CURSOR  EQU LCD_VARS
LCD_BUFFER  EQU LCD_VARS+2
lcd_next    equ lcd_vars+2+128
; Seiko LCD G1216B1N000 Static Variables


            Defseg gmk, absolute
            seg    gmk

            ORG   03Ch                 ; Keyboard Handler
            IN    KEYB_DATA
            CALL  LCD_DCHAR
            EI
            RET

            ORG  0
            JMP   0200H

            ORG  0200H

BOOT:
            LXI  SP,STACK_TOP

            call    lcd_init

            LXI     H,message
            CALL    FDISPD
            LXI     H,message2
            CALL    FDISPD
            LXI     H,message3
            CALL    FDISPMES

            mvi     a,8
            sim
            ei

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
           CALL lcd_char
	   INX  H           ;
	   JMP  FDMES1      ;
FDISEND:   POP  H           ;
	   POP  D           ;
	   POP  B           ;
	   POP  PSW         ;
	   RET              ;

;^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
;                            SUBROUTINE FDISPMES
;  DISPLAYS A MESSAGE WHOSE START IS POINTED AT BY HL AND THE END IS
;  DEFINED BY 0.REGISTERS RETURN UNAFFECTED.
; ---------------------------------------------------------------------

FDISPD:    PUSH PSW         ;
           PUSH B           ;
	   PUSH D           ;
	   PUSH H           ;
FDMES1D:   MOV  A,M         ;
	   CPI  00H         ;
           JZ   FDISENDD    ;
           CALL lcd_dchar
	   INX  H           ;
           JMP  FDMES1D     ;
FDISENDD:  POP  H           ;
	   POP  D           ;
	   POP  B           ;
	   POP  PSW         ;
	   RET              ;

;------------------------------- lcd
DELAY:
            push    d
            mvi     d,1
del4:       mvi     e,10
del3:       dcr     e
            jnz     del3
            dcr     d
            jnz     del4
            pop     d
            ret

longdelay:
            push    d
            push    b
            mvi     b,3
del0:
            mvi     d,255
del2:
            mvi     e,255
del1:       dcr     e
            jnz     del1
            dcr     d
            jnz     del2
            dcr     b
            jnz     del0
            pop     b
            pop     d
            ret

lcd_busy:
            ret
            push    psw
wait_for_busy:
            in      LCD_CTRL
            ani     10000000B
            jnz     wait_for_busy

            pop     psw
            ret

lcd_init:
wait_for_reset:
;            in      LCD_CTRL
;            ani     00010000B
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
            out     lcd_ctrl
            call    lcd_busy

            ret

lcd_locate:
; change text cursor position
; X=0 ... 31       = D
; Y=0 ... 7        = E
            pusha

            mov     a,e
            ani     00000111B
            rlc
            rlc
            rlc
            rlc
            rlc
            mov     b,a
            mov     a,d
            ani     00011111B
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

lcd_CLS:
            pusha

            mvi     a,0
            call    lcd_setCS

            mvi     b,8
nxt_page:
            mov     a,b
            dcr     a
            call    lcd_setX

            mvi     d,64
nxt_pixel:
            mvi     a,0
            out     LCD_DATA
            call    lcd_busy
            dcr     d
            jnz     nxt_pixel

            dcr     b
            jnz     nxt_page


            popa
            ret

lcd_tpset:
            mvi     b,64
nxll:
            mvi     c,128
nxzz:
            mov     d,c
            dcr     d
            mov     e,b
            dcr     e
            call    lcd_pset
            dcr     c
            jnz     nxzz
            dcr     b
            jnz     nxll
            ret

lcd_pset:
; plot pixel : x,y
; X=0 ... 127       = D
; Y=0 ... 63        = E
            pusha
            mov     a,d
            ani     10000000B
            jz      test1ok
            popa
            ret
test1ok:
            mov     a,e
            ani     11000000B
            jz      test2ok
            popa
            ret
test2ok:

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
            ori     10111000B
            out     LCD_CTRL
            call    lcd_busy
            pop     psw
            ret

lcd_setY:
            push    psw
            ani     00111111B
            ori     01000000B
            out     LCD_CTRL
            call    lcd_busy
            pop     psw
            ret

lcd_setZ:
            push    psw
            ani     00111111B
            ori     11000000B
            out     LCD_CTRL
            call    lcd_busy
            pop     psw
            ret

lcd_setCS:
; A=CS
            push    psw
            ani     00000011B
            out     LCD_CS
            pop     psw
            ret

            include fonts.inc
            include fonts.big
;0dh=cr
;0ah=lf
message   db 'Seiko G1216B1N00',0
message2  db 196,196,196,196,196,196
          db 196,196,196,196,196,196
          db 196,196,196,196,0
message3  db '(c) `93 Seiko Instruments Inc.',0dh
          db '(c) `98 Gmk Corporation Ltd AEBE'
          db '(c) `98 Deus Inc',0dh,0dh,0dh,0dh,0

bitmap db 0ffh,83h,0bfh,0bfh,0bfh,0bfh,0bfh,0ffh

   END
;
