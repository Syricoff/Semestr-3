.model small
.stack 100h
include func.asm
.data
CR = 0Dh
LF = 0Ah
FileName db "sentence.txt0", "$" 
FDescr dw ? 
NewFile db "file.txt0", "$"
FDescrNew dw ? 
Buffer dw ? 
String dw 100 dup(0) 
index dw 0 
SumOfWords db "Sum of words in file - ", "$"
MessageError1 db CR, LF, "File was not opened !", "$" 
MessageError2 db CR, LF, "File was not read !", "$"
MessageError3 db CR, LF, "File was not founded!", "$"
MessageError4 db CR, LF, "File was not created!", "$"
MessageError5 db CR, LF, "Error in writing in the file!", "$"
MessageEnd db CR, LF, "Program was successfully finished!",CR, LF, "$"
buf_string dw 40 dup(0)
buf_string2 dw 5 dup(0)
buf_len dw 0
space db " ", "$"
endl dw 0dh, 0ah, '$'
bool_word dw 0
amount_word dw 0
.code
print_string macro
mov ah, 09h
int 21h
endm 
start:
jumps
mov ax, @data
mov ds, ax
mov es, ax
lea DI, string
lea SI, buf_string

mov ah, 3Dh
xor al, al 
mov dx, offset FileName 
xor cx, cx 
int 21h 
mov FDescr, ax 
jnc M1 
jmp Er1 
M1:
 mov ah, 3ch 
 xor cx, cx 
 mov dx, offset NewFile 
 int 21h 
 mov FDescrNew, ax 
 jnc M2 
 jmp Er3 
M2:
 mov ah, 3fh
 mov bx, FDescr  
 mov cx, 1 
 mov dx, offset Buffer
 int 21h  
 jnc M3 
 jmp Er2 
M3:
 cmp ax, 0 
 je M4 
 mov ax, Buffer
 inc index
 stosw
 jmp M2
M4:     ;alles in string and index
mov bx, index
lea si, string
lea di, buf_string
exercise:
    mov cx, 5
    repe movsw
    add buf_len, 5
    add si, 30
    sub bx, 20
    cmp bx, 0
    jg exercise
    jmp exercise2
   
exercise2: 
xor di, di
mov cx, buf_len
print_mas:
    mov dx, buf_string[di]
    mov ah, 02h
    int 21h
    cout space
    add di, 2
    dec cx
    cmp cx, 0
    jne print_mas
    
        
lea si, buf_string
exercise3:
mov ah, 40h
mov bx, FDescrNew
mov cx, 10
mov dx, si
int 21h

mov ah, 40h
mov bx, FDescrNew
mov cx, 2
mov dx, offset endl
int 21h

add si, 10
sub buf_len, 5
cmp buf_len, 0
jg exercise3
    
M5: 
 mov ah, 3eh 
 mov bx, FDescr 
 int 21h 
 mov ah, 3eh 
 mov bx, FDescrNew 
 int 21h
 mov dx, offset MessageEnd
 print_string
 jmp Exit 
 
Er1: 
 cmp ax, 02h
 jne M6
 lea dx, MessageError3
 print_string
 jmp Exit
M6:
 lea dx, MessageError1
 print_string
 jmp Exit
Er2: 
 lea dx, MessageError2
 print_string
 jmp Exit
 
Er3: 
 lea dx, MessageError4
 print_string
 jmp Exit
 
Er4:
lea dx, MessageError5
 print_string
 jmp Exit 
 
nojumps
exit:
 mov ax, 4c00h
 int 21h
end start
end