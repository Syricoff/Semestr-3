.model small
.stack 100h
.data

A db ? 
B db ?
C db ?
D db ?

.code ;Открыть сегмент кодов
start: ;Инициализировать

	mov ax, @data
	mov ds, ax

	mov A, 32
	mov B, 0C1h
    mov C, 6
	mov D, 21

	mov al, A
	mov ah, B
	xchg al, ah

	mov bx, 3E10h
	mov cx, bx

	push bx
	push cx
	push ax

	lea si, C
	mov ax, si

	lea di, D
	mov bx, di

	pop ax ;Извлечь из стека значение и поместить его в регистр ax
	pop cx ;Извлечь из стека значение и поместить его в регистр cx
	pop bx ;Извлечь из стека значение и поместить его в регистр bx

	mov bx, ax ;Поместить в регистр bx значение регистра ax
	mov A, al ;Поместить в переменную А значение регистра al
	mov B, ah ;Поместить в переменную B значение регистра ah
	mov C, 0 ;Поместить в переменную C значение 0

	mov ax, 4c00h
	int 21h

end start ;Закрыть процедуру