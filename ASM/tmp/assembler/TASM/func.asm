Clear_screen MACRO
    Push ax
    Push bx
    Push cx 
    Push dx
    mov ax, 0600h 
    mov bh, 07 
    mov cx, 0000h 
    mov dx, 184fh 
    int 10h
    pop ax
    pop bx
    pop cx
    pop dx 
ENDM Clear_screen
Set_cursor MACRO row, col
    Push ax
    Push bx
    Push cx 
    Push dx
    mov ah, 02 
    mov bh, 00 
    mov dh, row 
    mov dl, col 
    int 10h
    pop ax
    pop bx
    pop cx
    pop dx 
ENDM Set_cursor

cout macro string
    push ax
    push dx
    mov ah, 09h
    mov dx, offset string
    int 21h
    pop dx
    pop ax
endm cout

mReadAX macro buffer, sz      
    local input, startOfConvert, endOfConvert
    push bx
    push cx
    push dx
    input:
    mov [buffer], sz
    mov dx, offset [buffer]
    mov ah, 0Ah
    int 21h
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    mov ah, 02h
    mov dl, 0Ah
    int 21h
    xor ah, ah
    cmp ah, [buffer][1]
    jz input
    xor cx, cx
    mov cl, [buffer][1]
    xor ax, ax
    xor bx, bx
    xor dx, dx
    mov bx, offset [buffer][2]
    cmp [buffer][2], '-'
    jne startOfConvert
    inc bx
    dec cl
    startOfConvert:
    mov dx, 10
    mul dx
    cmp ax, 8000h
    jae input
    mov dl, [bx]
    sub dl, '0'
    add ax, dx
    cmp ax, 8000h
    jae input
    inc bx
    loop startOfConvert
    cmp [buffer][2], '-'
    jne endOfConvert
    neg ax
    endOfConvert:
    pop dx
    pop cx
    pop bx
endm mReadAX

mWriteAX macro
    local convert, write
    push ax
    push bx
    push cx
    push dx
    push di
    mov cx, 10
    xor di, di
    or ax, ax
    jns convert
    push ax
    mov dx, "-"
    mov ah, 02h
    int 21h
    pop ax
    neg ax
    convert:
    xor dx, dx
    div cx
    add dl, '0'
    inc di
    push dx
    or ax, ax
    jnz convert
    write:
    pop dx
    mov ah, 02h
    int 21h
    dec di
    jnz write
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
endm mWriteAX

mReadMatrix macro matrix, row, col
local rowLoop, colLoop
jumps
    push bx
    push cx
    push si
    push dx
    xor bx, bx
    mov dx, 1
    mov cx, row
rowLoop:
    push cx
    xor si, si
    mov cx, col
colLoop:
;;;;;;;;;;;;;;;;;;;
    cout_matrix
;;;;;;;;;;;;;;;;;;
    
    mReadAx buffer, 4
    mov matrix[bx][si], ax
    add si, 2
    loop colLoop
    cout endl
;;;;;;;;;;;;;;;
    inc mcol
    mov mrow, 1
;;;;;;;;;;;;;;
    add bx, col
    add bx, col
    pop cx
    loop rowLoop
    
    clearRowCol
    
    pop si
    pop cx
    pop bx
nojumps
endm mReadMatrix

mWriteMatrix macro matrix, row, col, space
local rowLoop, colLoop
    push ax
    push bx
    push cx
    push si
    xor bx, bx
    mov cx, row
rowLoop:
    push cx
    xor si, si
    mov cx, col
colLoop:
    mov ax, matrix[bx][si]
    mWriteAX
    cout space
    xor ax, ax
    add si, 2
    loop colLoop
    cout endl
    add bx, col
    add bx, col
    pop cx
    loop rowLoop
    pop si
    pop cx
    pop bx
    pop ax
endm mWriteMatrix

mSumBelowDiagonal macro matrix, row, col
local rowLoop, colLoop, belowTheDiagonal
    push ax
    push bx
    push cx
    push si
    push di
    push dx
    xor dx, dx
    xor di, di
    xor bx, bx
    mov cx, row
rowLoop:
    push cx
    xor si, si
    mov cx, col
colLoop:
    mov ax, matrix[bx][si]
    cmp si, di
    ja belowTheDiagonal    ;jbe-OhneMainDiagonal ja-BelowDiagonal jb-AboveDiagonal\
    cmp ax, 0
    jg belowTheDiagonal
    add dx, ax
belowTheDiagonal:
    add si, 2
    loop colLoop
    add di, 2
    add bx, col
    add bx, col
    pop cx
    loop rowLoop
    mov ax, dx
    cout str_sum
    mWriteAX
    pop dx
    pop di
    pop si
    pop cx
    pop bx
    pop ax
endm mSumBelowDiagonal

mTransposeMatrix macro matrix, row, col, resMatrix
local rowLoop, colLoop
    push ax
    push bx
    push cx
    push di
    push si
    push dx
    xor di, di
    mov cx, row
rowLoop:
    push cx
    xor si, si
    mov cx, col
colLoop:
    mov ax, col
    mul di
    add ax, si
    mov bx, ax
    mov ax, matrix[bx]
    push ax
    mov ax, row
    mul si
    add ax, di
    mov bx, ax
    pop ax
    mov resMatrix[bx],ax
    add si, 2
    loop colLoop
    add di, 2
    pop cx
    loop rowLoop
    pop dx
    pop si
    pop di
    pop cx 
    pop bx
    pop ax
endm mTransposeMatrix 
    
mCLS macro
    push ax
    push bx
    push cx
    push dx
    mov ah, 10h
    mov al, 3h
    int 10h
    mov ax, 0600h
    mov bh, 00001111b
    mov cx, 0000b
    mov dx, 184Fh
    int 10h
    mov dx, 0
    mov bh, 0
    mov ah, 02h
    int 10h
    pop dx
    pop cx
    pop bx
    pop ax
endm mCLS

cout_matrix macro
   push ax 
   cout input1
   mov ax, mcol
   mWriteAx
   cout input2
   mov ax, mrow
   mWriteAx
   cout input3
   inc mrow
   pop ax
endm cout_matrix1

clearRowCol macro
mov mrow, 0
mov mcol, 0
endm clearRowCol

reverse_matrix macro matrix, col_matr, row_matr, buf_matrix  
local print_matr, exit, buffer_clean, copy, copy_mas
push ax
push bx
push cx
push si
push di
push dx

mov cx, col_matr
xor si, si
buffer_clean:
   mov buf_matrix[si], 0
   add si, 2
   dec cx
   cmp cx, 0
   jne buffer_clean

mov ax, col_matr
imul ax, row_matr
mov cx, ax
imul ax, 02h
sub ax, 02h
mov si, ax
mov dx, ax
xor di, di
print_matr:
    mov ax, matrix[si]
    mov buf_matrix[di], ax
    cout space
    add di, 2
    sub si, 2
    dec cx
    cmp cx, 0
    jne print_matr
    jmp copy

copy:    
    xor si, si
    mov cx, dx
    copy_mas:
    mov ax, buf_matrix[si] 
    mov matrix[si], ax
    add si, 2
    dec cx
    cmp cx, 0
    jne copy_mas
    
exit:  
pop dx
pop di
pop si
pop cx
pop bx
pop ax
nojumps
endm reverse_matrix1

is_similar macro matrix, col_matr, row_matr, buf1, buf2
local buffer_clean, copy_row, copy_col, print_row, is_same, yes, no, exit
push ax
push bx
push cx
push si
push di
push dx

mov cx, col_matr
xor si, si
buffer_clean:
   mov buf1[si], 0
   add si, 2
   dec cx
   cmp cx, 0
   jne buffer_clean
   
xor si, si
mov bx, row_matr 
add bx, bx
mov cx, col_matr
copy_row:
    mov ax, matrix[bx][si]
    mov buf1[si], ax
    add si, 2
    dec cx
    cmp cx, 0
    jne copy_row
      
mov si, 2
xor di, di
xor bx, bx
mov cx, row_matr
copy_col:
    mov ax, matrix[bx][si]
    mov buf2[di], ax
    add di, 2
    add bx, 2
    add bx, 2
    dec cx
    cmp cx, 0
    jne copy_col    
 
mov dx, row_matr
cmp dx, col_matr
jne no  
is_same:
lea si, buf1
lea di, buf2
cld 
mov cx, col_matr
repe cmpsw
jne no

yes:
cout yes_ans
jmp exit 

no:
cout no_ans
jmp exit

exit:
pop dx
pop di
pop si
pop cx
pop bx
pop ax
endm is_similar

max_element macro matrix, row, col, max_el
local rowLoop, colLoop, belowTheDiagonal, rowLoop1, colLoop1, belowTheDiagonal1
jumps    
    push ax
    push bx
    push cx
    push si
    push di
    push dx
    
    xor dx, dx
    xor di, di
    xor bx, bx
    mov cx, row
rowLoop:
    push cx
    xor si, si
    mov cx, col
colLoop:
    mov ax, matrix[bx][si]
    cmp si, di
    ja belowTheDiagonal    ;jbe-OhneMainDiagonal ja-BelowDiagonal jb-AboveDiagonal\
    cmp ax, max_el
    jl belowTheDiagonal
    mov max_el, ax
belowTheDiagonal:
    add si, 2
    loop colLoop
    add di, 2
    add bx, col
    add bx, col
    pop cx
    loop rowLoop
    
    mov ax, max_el
    cout bel_diag
    mWriteAX
    
    xor dx, dx
    xor di, di
    xor bx, bx
    mov cx, row
rowLoop1:
    push cx
    xor si, si
    mov cx, col
colLoop1:
    mov ax, matrix[bx][si]
    cmp si, di
    jb belowTheDiagonal1    
    cmp ax, max_el
    jl belowTheDiagonal1
    mov max_el, ax
belowTheDiagonal1:
    add si, 2
    loop colLoop1
    add di, 2
    add bx, col
    add bx, col
    pop cx
    loop rowLoop1
    
    mov ax, max_el
    cout abov_diag
    mWriteAX   
    
    pop dx
    pop di
    pop si
    pop cx
    pop bx
    pop ax
nojumps
endm MaxElement


