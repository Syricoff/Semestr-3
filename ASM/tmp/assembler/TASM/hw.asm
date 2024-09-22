TITLE var_29
.model small
.stack 100h
.386
include func.asm
.data
    matr dw 10 dup(10 dup(0))
    row dw 2
    col dw 2
    buffer db 32 dup(0)
    res_matr dw 10 dup(10 dup(0))
    mrow dw 1
    mcol dw 1
    buf_matr dw 30 dup(0)
    buf_matr2 dw 30 dup(0)
    
    space db 09h, "$"
    endl db 0dh, 0ah, '$'
    input1 db 'matrix[$'
    input3 db '] enter an element -> $'
    input2 db '][$'
    tab db ' $'
    str_sum db 'sum of negative elements -> $'
    str_row db 'rows -> $'
    str_col db 'cols -> $'
    main_menu db 13, 10,'Menu:',13,10, '$'
    m1 db '1 - input matrix',13,10, '$'
    m2 db '2 - print matrix',13,10, '$'
    m3 db '3 - task a',13,10, '$'
    m4 db '4 - task b',13,10, '$'
    m5 db '5 - task c',13,10, '$'
    m6 db '6 - transpose matrix',13,10,'$'
    str_select db 'select -> $'
    str_matrix db 'matrix:',13,10,'$'
    enter_el db "enter vector element -> $"
    
    yes_ans db 13,10,"the second row and column are same$"
    no_ans db 13, 10,"the second row and column aren't same$"
    bel_diag db 13,10,"max element below diagonal - $"
    abov_diag db 13,10,"max element above diagonal - $"
    max_elem dw 0
.code
update_matrix macro
    push ax
    cout str_row
    mReadAX buffer, 4
    mov row, ax
    cout str_col
    mReadAX buffer, 4
    mov col, ax
    mReadMatrix matr, row, col
    pop ax
endm update_matrix

print_menu macro
cout main_menu
cout m1
cout m2
cout m3
cout m4
cout m5
cout m6
endm print_menu

start:
jumps
mov ax, @data
mov ds, ax
mov es, ax
xor ax, ax
mCLS

menu:
print_menu  
cout str_select
mReadAx buffer, 4
cmp ax, 1 
je funk1
cmp ax, 2
je funk2   
cmp ax, 3
je funk3    
cmp ax, 4
je funk4
cmp ax, 5   
je funk5   
cmp ax, 6
je funk6    
jmp exit

funk1:
mCLS
update_matrix
jmp menu
funk2:
mCLS
cout str_matrix
mWriteMatrix matr, row, col, space
cout str_row
mov ax, row
mWriteAX
cout endl
cout str_col
mov ax, col
mWriteAX
jmp menu
funk3:
mCLS
reverse_matrix matr, col, row, buf_matr
jmp menu
funk4:
mCLS
is_similar matr, col, row, buf_matr, buf_matr2
jmp menu
funk5:
mCLS
max_element matr, row, col, max_elem
jmp menu
funk6:
mCLS
mTransposeMatrix matr, row, col, res_matr
mWriteMatrix res_matr, row, col, space
jmp menu
exit:
    mov ax, 4c00h
    int 21h
end start
end