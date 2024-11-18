include macroses.asm
.model small
.stack 100h
.data
    buffer   db 5, 0, 5 dup(0)                 ; Буфер для ввода числа (максимум 5 цифр)
    mes_a    db 'Enter the number a: ', '$'
    mes_b    db 'Enter the number b: ', '$'
    mes_c    db 'Enter the number c: ', '$'
    mes_d    db 'Enter the number d: ', '$'
    mes_res1 db 'Result y1: ', '$'
    mes_res2 db 'Result y2: ', '$'
    new_line db 13,10,'$'
    a        dw 10                             ; Переменная для хранения первого числа
    b        dw -20                             ; Переменная для хранения второго числа
    c        dw -15                             ; Переменная для хранения третьего числа
    d        dw 18                           ; Переменная для хранения четвертого числа

.code
    start:
          mov       ax, @data
          mov       ds, ax

    ; ; Ввод переменной a
    ;       xor       ax, ax
    ;       mWriteStr mes_a
    ;       mReadAX   buffer, 5
    ;       mov       a, ax

    ; ; Ввод переменной b
    ;       xor       ax, ax
    ;       mWriteStr mes_b
    ;       mReadAX   buffer, 5
    ;       mov       b, ax

    ; ; Ввод переменной c
    ;       xor       ax, ax
    ;       mWriteStr mes_c
    ;       mReadAX   buffer, 5
    ;       mov       c, ax

    ; ; Ввод переменной d
    ;       xor       ax, ax
    ;       mWriteStr mes_d
    ;       mReadAX   buffer, 5
    ;       mov       d, ax
          

          xor       ax, ax

    
          mCalc_Y1  a, b         ; Пример 1: y = 2*b + 2*a
        ;   mWriteStr mes_res1
		;   mWriteAX
		;   mWriteStr new_line               ; Вывод результата

          xor       ax, ax

          mCalc_Y2  a, b, c      ; Пример 2: y = ((a + 3*b) / c) + 4
        ;   mWriteStr mes_res2
		;   mWriteAX
		;   mWriteStr new_line               ; Вывод результата

    ; Завершение программы
          mov       ax, 4c00h
          int       21h
end start
