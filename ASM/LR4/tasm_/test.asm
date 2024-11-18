include macroses.asm
.model small
.stack 100h
.data
	buffer db 5, 0, 5 dup(0)
	mes_a  db 'Enter the number a: ', '$'
	mes_b  db 'Enter the number b: ', '$'
	mes_c  db 'Enter the number c: ', '$'
	mes_x  db 'Enter the number x: ', '$'
	a      dw 0
	b      dw 0
	c      dw 0
	x      dw 0
	menu1  db '1 - Task', '$',13,10
	menu2  db '0 - Exit','$',13,10
	select db 'Select> $'
	result db 'Result> $'
	task   db 'Your Task:$'
.code
	start:          
	                mov        ax,@data
	                mov        ds,ax
	                mClear
	select_loop:    
	                mSetCursor 10, 34
	                mWriteStr  menu1
	                mSetCursor 11, 34
	                mWriteStr  menu2
	                mSetCursor 12, 34
	                mWriteStr  select

	                mov        ah,01h
	                int        21h

	                cmp        al,'1'
	                je         c1

	                cmp        al,'0'
	                je         exit

	                jmp        select_loop
	exit:           
	                mov        ah, 7h         	; Подготавливает функцию для ожидания нажатия клавиши.
	                int        21h            	; Вызывает прерывание DOS для ожидания нажатия клавиши

	                mov        ax,4c00h
	                int        21h
	c1:             
	                mClear
	                mSetCursor 10, 34
	                mWriteStr  task
	; Ввод переменной a
	                xor        ax, ax
	                mSetCursor 11, 27
	                mWriteStr  mes_a
	                mReadAX    buffer, 5
	                mov        a, ax
	; Ввод переменной b
	                xor        ax, ax
	                mSetCursor 12, 27
	                mWriteStr  mes_b
	                mReadAX    buffer, 5
	                mov        b, ax
	; Ввод переменной c
	                xor        ax, ax
	                mSetCursor 13, 27
	                mWriteStr  mes_c
	                mReadAX    buffer, 5
	                mov        c, ax
	; Ввод переменной x
	                xor        ax, ax
	                mSetCursor 14, 27
	                mWriteStr  mes_x
	                mReadAX    buffer, 5
	                mov        x, ax

	                xor        ax,ax

	                mov        ax,a
	                cmp        ax,0
	                jg         case_pozitive_a
	                jl         case_negative_a
	                jmp        else_case
	case_pozitive_a:                          	; -a / (x-c)

	                xor        ax, ax
	                mov        ax, c
	                cmp        ax, 0
	                jne        else_case

	                xor        ax,ax
	                xor        bx,bx
	                xor        cx,cx
	                xor        dx,dx

	                mov        ax, a
	                neg        ax

	                mov        bx, x
	                sub        bx, c

	                cwd
	                idiv       bx

	                jmp        otvet
	case_negative_a:                          	; ax^2 + bx + c
	                xor        cx, cx
	                mov        cx, c
	                jcxz       else_case

	                xor        ax,ax
	                xor        bx,bx
	                xor        cx, cx

	; Вычисляем x^2
	                mov        ax, x          	; AX = x
	                imul       ax             	; AX = x * x (x^2)
	                mov        bx, ax         	; BX = x^2

	; Вычисляем ax^2
	                mov        ax, a          	; AX = a
	                imul       bx             	; AX = a * x^2
	                mov        cx, ax         	; CX = a * x^2

	; Вычисляем bx
	                mov        ax, b          	; AX = b
	                imul       x              	; AX = b * x
	                add        ax, cx         	; CX += b * x

	; Добавляем c
	                add        ax, c          	; CX += c

	                jmp        otvet
	else_case:                                	; a * (x + c)
	                xor        ax,ax

	                mov        ax, x
	                add        ax, c
	                imul       a
	            
	                jmp        otvet

	otvet:          
	                mSetCursor 16, 27
	                mWriteStr  result
	                mWriteAX
					
	                mov        ah, 7h         	; Подготавливает функцию для ожидания нажатия клавиши.
	                int        21h            	; Вызывает прерывание DOS для ожидания нажатия клавиши
	                
	                mClear
	                jmp        select_loop
end start