.486
.386
_data segment use16
tmp dw ?
ot dd ?
tmpx dw ?
ctr dw 0
fin db 0
old_int_1c dw 2 dup (?)
_data ends
_code segment use16
    assume  cs:_code, ds:_data
@Start:
    mov ax, _data
    mov ds, ax
    xor ax, ax
    mov al, 10h
    int 10h
    mov ax, 0600h
    mov bh, 15
    xor cx, cx
    mov dx, 184Fh
    int 10h
    mov cx, 350
    mov ax, 0c07h
    xor bh, bh


@draw_vert_l:                        ; X = -1
    push cx
    mov dx, cx
    dec dx
    mov cx, 320
    sub cx, 32
    int 10h
    pop cx
    loop @draw_vert_l
    mov cx, 382
    mov ax, 0c02h
    xor bh, bh

@draw_vert_r:                        ; X = 1
    push cx
    mov dx, cx
    dec dx
    mov cx, 320
    add cx, 32
    int 10h
    pop cx
    loop @draw_vert_r
    mov cx, 640
    mov dx, 300
    mov al, 1

@draw_horiz:                         ; X axis
    dec cx
    int 10h
    inc cx
    loop @draw_horiz
    finit
    fstcw tmp
    mov ax, tmp
    or ah, 00001100b
    mov tmp, ax
    fldcw tmp
    fld1                            ; ST(0) = 1
    mov tmp, 3
    fild tmp                        ; ST(0) = tmp, ST(1) = 1
    fdiv                            ; ST(0) = 1 / tmp
    fstp ot                         ; ot = 1 / tmp 
    mov ax, 351ch
    int 21h
    mov old_int_1c, bx
    mov [old_int_1c+2], es
    mov dx, offset @new_int_1c
    push ds
    push cs
    pop ds
    mov ax, 251ch
    int 21h
    pop ds

@infl:
    mov al, fin
    cmp al, 0
    je @infl

    mov ax, 251ch
    mov dx, old_int_1c
    mov ds, [old_int_1c+2]
    int 21h

    mov ah, 8h
    int 21h

    mov ax, 4c00h
    int 21h

@new_int_1c proc far

    pusha
    push ds

    mov ax, _data
    mov ds, ax

    mov ax, ctr
    inc ctr
    cmp ax, 640
    jge @exit_timer_fin

    push ax
    and ax, 1
    jz @left_part

    pop ax
    shr ax, 1

    add ax, 320
    
    cmp ax, 352
    jge @right_part
    
    mov bx, 0c04h
    push bx
    
@mid_left:
    mov tmp, ax
    fild tmp                        ; ST(0) = ax
    mov tmp, 32
    fild tmp                        ; ST(0) = 32, ST(1) = ax
    fdiv                            ; ST(0) = ax / 32
    mov tmp, 10
    fild tmp                        ; ST(0) = 10, ST(1) = ax / 32
    fsub                            ; ST(0) = (ax / 32) - 10           - X value
    fld1    
    jmp @draw_point
    
@right_part:
    mov bx, 0c02h
    push bx

    mov tmp, ax
    fild tmp                        ; ST(0) = ax
    mov tmp, 32
    fild tmp                        ; ST(0) = 32, ST(1) = ax
    fdiv                            ; ST(0) = ax / 32
    mov tmp, 10
    fild tmp                        ; ST(0) = 10, ST(1) = ax / 32
    fsub     ; ST(0) = (ax / 32) - 10           - X value

    fld st(0)
    fmul
    mov tmp, 4
    fild tmp
    fdiv st(0), st(2)
    jmp @draw_point
    
@left_part:
    pop ax
    shr ax, 1

    mov bx, 319
    sub bx, ax
    mov ax, bx
    
    cmp ax, 288
    jle @left_left
    
    mov bx, 0c04h
    push bx
    
    mov tmp, ax
    fild tmp                        ; ST(0) = ax
    mov tmp, 32
    fild tmp                        ; ST(0) = 32, ST(1) = ax
    fdiv                            ; ST(0) = ax / 32
    mov tmp, 10
    fild tmp                        ; ST(0) = 10, ST(1) = ax / 32
    fsub                            ; ST(0) = (ax / 32) - 10           - X value
    fld ST(0)
    fld ST(0)
    fsub
    fxch ST(1)
    fsub   
    fld1
    jmp @draw_point
    
@left_left:
    mov bx, 0c05h
    push bx
    
    mov tmp, ax
    fild tmp
    mov tmp, 32
    fild tmp
    fdiv
    mov tmp, 10
    fild tmp
    fsub                            ; ST(0) = X
    fld ST(0)
    fld ST(0)
    fsub
    fxch ST(1)
    fsub
    ffree st(1)
    
    fld st(0)
    fldl2e
    fmul
    fld     st
    frndint
    fsub    st(1), st
    fxch    st(1)
    f2xm1
    fld1
    fadd
    fscale
    fstp    st(1)
    fdiv
    jmp @draw_point 
    
@draw_point:
    mov tmp, -14
    fild tmp                        ; ST(0) = -14, ST(1) = res
    fmul                            ; ST(0) = -14res
    mov tmp, 280
    fild tmp                        ; ST(0) = 280, ST(1) = -14res
    fadd                            ; ST(0) = 280 - 14res
    frndint
    fistp tmp                       ; tmp -> int(280 - 14res)
    mov bh, 0                       ; Window #0
    mov dx, tmp                     ; Result row
    mov cx, ax                      ; Column
    pop ax                          ; Color + graphic point
    int 10h
    jmp @exit_timer

@exit_timer_fin:
    inc fin
@exit_timer:
    pop ds
    popa
    iret

endp @new_int_1c

_code   ends
end @Start
