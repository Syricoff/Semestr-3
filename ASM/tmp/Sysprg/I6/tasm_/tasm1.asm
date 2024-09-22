﻿.model small    ; Определяет модель памяти как "small", где код и данные помещаются в один сегмент.
.stack 100h     ; Определяет стек размером 256 байт (100h).

.data           ; Начало сегмента данных.
message     db  'Hard is the first step','$', 10, 13 
message1    db  'Varro, Mark Ternce','$', 10, 13    
message2    db  '116-27 years. BC','$', 10, 13      
message3    db  'Surikov','$',10,13                 
message4    db  'IUK4-31B','$',10,13                
message5    db  'IUK4','$',10,13                    
message6    db  '!!!!!','$',10,13                  

.code   ; Начало сегмента кода.
start:  ; Метка начала программы.
    mov		ax,@data   ; Загружает адрес сегмента данных в регистр AX.
    mov		ds,ax      ; Устанавливает сегмент данных (DS) в значение AX.

    ; Очистка экрана
	mov 	ax,0600h      ; Подготавливает код для очистки экрана (функция 0).
    mov     bh, 2Dh       ; Устанавливает цвет фона и шрифта
	mov 	cx, 0000      ; Указывает количество строк для очистки (все).
	mov 	dx, 184FH     ; Указывает адрес экрана (184FH — адрес видеопамяти).
	int 	10H           ; Вызывает прерывание BIOS для выполнения очистки экрана.

    ; Вывод информации по углам экрана

    ; Левый верхний угол
	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 0       ; Устанавливает вертикальную позицию курсора (строка 0).
	mov		dl, 0       ; Устанавливает горизонтальную позицию курсора (столбец 0).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки
	mov		dx, offset message3 ; Загружает адрес строки message3 в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

    ; Правый верхний угол
	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 0       ; Устанавливает вертикальную позицию курсора (строка 0).
	mov		dl, 70      ; Устанавливает горизонтальную позицию курсора (столбец 70).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки.
	mov		dx, offset message4 ; Загружает адрес строки message4 в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

    ; Левый нижний угол
	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 24      ; Устанавливает вертикальную позицию курсора (строка 24).
	mov		dl, 0       ; Устанавливает горизонтальную позицию курсора (столбец 0).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки.
	mov		dx, offset message5 ; Загружает адрес строки message5 в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

    ; Правый нижний угол
	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 24      ; Устанавливает вертикальную позицию курсора (строка 24).
	mov		dl, 70      ; Устанавливает горизонтальную позицию курсора (столбец 70).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки.
	mov		dx, offset message6 ; Загружает адрес строки message6 в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

    ; Центральное сообщение
	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 10      ; Устанавливает вертикальную позицию курсора (строка 10).
	mov		dl, 30      ; Устанавливает горизонтальную позицию курсора (столбец 30).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки.
	mov		dx, offset message  ; Загружает адрес строки message в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 11      ; Устанавливает вертикальную позицию курсора (строка 11).
	mov		dl, 30      ; Устанавливает горизонтальную позицию курсора (столбец 30).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки.
	mov		dx, offset message1 ; Загружает адрес строки message1 в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

	mov		ah, 2       ; Подготавливает функцию установки курсора.
	mov		dh, 12      ; Устанавливает вертикальную позицию курсора (строка 12).
	mov		dl, 30      ; Устанавливает горизонтальную позицию курсора (столбец 30).
	mov		bh, 0       ; Указывает страницу экрана (0).
	int		10H         ; Вызывает прерывание BIOS для установки курсора.

	mov		ah, 09h             ; Подготавливает функцию вывода строки.
	mov		dx, offset message2 ; Загружает адрес строки message2 в DX.
	int		21h                 ; Вызывает прерывание DOS для вывода строки.

	mov		ah, 7h      ; Подготавливает функцию для ожидания нажатия клавиши.
	int		21h         ; Вызывает прерывание DOS для ожидания нажатия клавиши.

	mov		ax, 4c00h   ; Завершает программу и возвращает управление операционной системе.
	int		21h         ; Вызывает прерывание DOS для завершения программы.

end	start

; ax регистр аккумулятор жрёт всё
; состоит из ah и al
; ah  старший
; Шаг 1 mov ah, 09h - подготавливает функцию вывода строки
; Шаг 2 mov dx offset message - dx хранит где бутылки пива
; Шаг 3 int 21h вызов прерывания
; 21h - прерывание DOS
; 10h - прерывание BIOS


; mount ~Sysprg/I6/tasm_
; D:
; tasm tasm1 & tlink tasm1 & tasm1