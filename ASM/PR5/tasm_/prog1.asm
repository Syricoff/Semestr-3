.model small    ; Определяет модель памяти как "small", где код и данные помещаются в один сегмент.
.stack 100h     ; Определяет стек размером 256 байт (100h).

; Начало сегмента данных.
.data
	message  db 'Hard is the first step','$', 10, 13
	message1 db 'Varro, Mark Ternce','$', 10, 13
	message2 db '116-27 years. BC','$', 10, 13
	message3 db 'Surikov','$',10,13
	message4 db 'IUK4-31B','$',10,13
	message5 db 'IUK4','$',10,13

.code   
    Set_cursor MACRO row, col ;Макрос установки курсора
        push ax
        push bx
        push cx
        push dx

        mov ah, 02  ; Установка курсора
        mov dh, row ; номер строки в DH
        mov dl, col ; номер столбца в DL
        mov bh, 0   ; Указывает страницу экрана (0).
        int 10h

        pop dx
        pop cx
        pop bx
        pop ax
    ENDM

    mWriteStr macro string ;Макрос вывода строки
        push ax
        push dx

        mov ah, 09h
        mov dx, offset string
        int 21h

        pop dx
        pop ax
    ENDM

    Clear macro ;Макрос очистки экрана
        push ax
        push bx
        push cx
        push dx

        mov ax,0600h           	; Подготавливает код для очистки экрана (функция 0).
        mov bh, 2Ch            	; Устанавливает цвет фона и шрифта
        mov cx, 0000           	; Указывает количество строк для очистки (все).
        mov dx, 184FH          	; Указывает адрес экрана (184FH — адрес видеопамяти).
        int 10h                	; Вызывает прерывание BIOS для выполнения очистки экрана.

        pop dx
        pop cx
        pop bx
        pop ax
    ENDM

	start:                      ; Метка начала программы.
	    mov ax,@data           	; Загружает адрес сегмента данных в регистр AX.
	    mov ds,ax              	; Устанавливает сегмент данных (DS) в значение AX.

	    Clear	                	

	; Центральное сообщение
	      
		Set_cursor 10, 30
	    mWriteStr message

		Set_cursor 11, 30
	    mWriteStr message1

		Set_cursor 12, 30
	    mWriteStr message2

	; Вывод информации по углам экрана

	; Левый верхний угол
	    Set_cursor 0, 0
	    mWriteStr message3

	; Правый верхний угол
		Set_cursor 0, 72
	    mWriteStr message4
	   
	; Левый нижний угол
		Set_cursor 24, 0
	    mWriteStr message5

	; Правый нижний угол
	    Set_cursor 24, 75

	    mov ah, 09h            	; Подготавливает функцию вывода строки.
	    mov al, '!'            	; Выводимый символ
	    mov bl, 10101100b      	; Атрибут(цвет, фон, мерцание)
	    mov cx, 5              	; Коэффицент повторения
	    int 10h                	; Вызывает прерывание BIOS для установки курсора.

	    mov ah, 7h             	; Подготавливает функцию для ожидания нажатия клавиши.
	    int 21h                	; Вызывает прерывание DOS для ожидания нажатия клавиши.

	    mov ax, 4c00h          	; Завершает программу и возвращает управление операционной системе.
	    int 21h                	; Вызывает прерывание DOS для завершения программы.

end	start