.model small
.stack 100h
.data

	xi    db 0
	a     db 29
	b     db 13h
	c     db 13
	d     db 12
	; x1    db 68
	; x2    db 81h
	; x3    db 252

	summ  db 0
	diff  db 0
	multi dw 1
	all   dw 0
	part  db 0


.code

	start:
	      mov ax,@data
	      mov ds, ax

	;1 часть
	      mov ah, 00
	      mov xi, 68
	;вычитание
	      mov al, xi
	      sub al, a
	      mov diff, al
	;сложение
	      mov summ, al
	      mov al, b
	      add al, summ
	;умножить
	      mul c
	      mov multi, ax
	;делить
	      div d
	      mov byte ptr all, al
	      mov byte ptr part, ah

	;2 часть
	      mov ah, 00
	      mov xi, 81h
	;вычитание
	      mov al, xi
	      sub al, a
	      mov diff, al
	;сложение
	      mov summ, al
	      mov al, b
	      add al, summ
	;умножить
	      mul c
	      mov multi, ax
	;делить
	      div d
	      mov byte ptr all, al
	      mov byte ptr part, ah

	;3 часть
	      mov ah, 00
	      mov xi, 252
	;вычитание
	      mov al, xi
	      sub al, a
	      mov diff, al
	;сложение
	      mov summ, al
	      mov al, b
	      add al, summ
	;умножить
	      mul c
	      mov multi, ax
	;делить
	      mov bl, d
	      div bx
	      mov all, ax
	      mov part, dl
	
	;учет переполнения
	;jnc dop_sum
	;adc word ptr l+2, 0
	;dop_sum:
	      mov ax, 4c00h
	      int 21
end start