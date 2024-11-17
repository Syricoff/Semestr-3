.model small
.stack 100h
.data
    buffer db 5, 0, 5 dup(0)                 ; Буфер для ввода числа (максимум 5 цифр)
    mes_a  db 'Enter the number a: ', '$'
    mes_b  db 'Enter the number b: ', '$'
    mes_c  db 'Enter the number c: ', '$'
    mes_d  db 'Enter the number d: ', '$'
    a      dw 0                              ; Переменная для хранения первого числа
    b      dw 0                              ; Переменная для хранения второго числа
    c      dw 0                              ; Переменная для хранения третьего числа
    d      dw 0                              ; Переменная для хранения четвертого числа

.code
    ; Макрос для вычисления y = 2*b + 2*a
    mCalc_Y1 MACRO a, b
                    push bx        ; Данные в стек
                    push cx
                    push dx

                    mov  ax, a     ; загрузить a в ax
                    mov  bx, b     ; загрузить b в bx
                    shl  ax, 1     ; ax = 2*a
                    shl  bx, 1     ; bx = 2*b
                    add  ax, bx    ; ax = 2*a + 2*b

                    pop  dx
                    pop  cx
                    pop  bx
    ENDM

    ; Макрос для вычисления y = ((a + 3*b) / c) + 4
    mCalc_Y2 MACRO a, b, c
                    push bx             ; Данные в стек
                    push cx
                    push dx

                    mov  bx, a          ; загрузить a в bx
                    mov  ax, b          ; загрузить b в ax
                    mov  cx, 3          ; загрузить 3 в cx

                    imul cx            ; ax = b * 3 (ax = 3*b)
                    add  ax, bx        ; ax = a + 3*b

                    xor  dx, dx         ; очистить для деления
                    xor  cx,cx

                    mov  cx, c          ; загрузить c в cx
                    cmp  cx, 0

                    je   DIV_BY_ZERO    ; если c = 0, переход к обработке деления на ноль
                    cwd
                    idiv cx             ; деление ax на c, результат в ax/dx
                    add  ax, 4          ; добавить 4 к результату
                    jmp  END_CALC_Y2
        DIV_BY_ZERO:  
                    xor  ax, ax         ; если деление на ноль, сохранить 0 в res
        END_CALC_Y2:  
                    pop  dx
                    pop  cx
                    pop  bx
    ENDM

    mReadAX macro buffer, sizee                                   ;Макрос ввода 10-чного числа в регистр АХ
                    local input, startOfConvert, endOfConvert
                    push  bx                                     ;Данные в стек
                    push  cx
                    push  dx
        input:         
                    mov   [buffer], sizee                        ;Задаём размер буфера
                    mov   dx, offset [buffer]                    ;Поместить в регистр dx строку по адресу buffer
                    mov   ah, 0Ah                                ;Чтение строки из консоли
                    int   21h                                    ;Прерывание DOS

                    mov   ah, 02h                                ;Вывод символа на экран
                    mov   dl, 0Dh                                ;Перевод каретки на новую строку
                    int   21h                                    ;Прерывание DOS

                    mov   ah, 02h                                ;Вывод символа на экран
                    mov   dl, 0Ah                                ;Чтение строки из консоли
                    int   21h                                    ;Прерывание DOS

                    xor   ah, ah                                 ;Очистка регистра ah
                    cmp   al, [buffer][1]                        ;Проверка на пустую строку
                    jz    input                                  ;Переход, если строка пустая

                    xor   cx, cx                                 ;Очистка регистра cx
                    mov   cl, [buffer][1]                        ;инициализация переменной-счётчика

                    xor   ax, ax                                 ;Очистка регистра ax
                    xor   bx, bx                                 ;Очистка регистра bx
                    xor   dx, dx                                 ;Очистка регистра dx

                    mov   bx, offset [buffer][2]                 ;Поместить начало строки в регистр bx
                    cmp   [buffer][2], '-'                       ;Проверка на знак числа
                    jne   startOfConvert                         ;Переход, если число неотрицательное
                    inc   bx                                     ;Инкремент регистра bx
                    dec   cl                                     ;Декремент регистра-счетчика cl
        startOfConvert:
                    mov   dx, 10                                 ;Поместить в регистр ax число 10
                    mul   dx                                     ;Умножение на 10 перед сложением с младшим разрядом
                    cmp   ax, 8000h                              ;Проверка числа на выход за границы
                    jae   input                                  ;Переход, если число выходит за границы
                    mov   dl, [bx]                               ;Поместить в регистр dl следующий символ
                    sub   dl, '0'                                ;Перевод его в числовой формат
                    add   ax, dx                                 ;Прибавляем его к конечному результату
                    cmp   ax, 8000h                              ;Проверка числа на выход за границы
                    jae   input                                  ;Переход, если число выходит за границы
                    inc   bx                                     ;Переход к следующему символу
                    loop  startOfConvert                         ;Цикл
                    cmp   [buffer][2], '-'                       ;Проверка на знак числа
                    jne   endOfConvert                           ;Переход, если число неотрицательное
                    neg   ax                                     ;Инвертирование числа
        endOfConvert:  
                    pop   dx                                     ;Данные из стека
                    pop   cx
                    pop   bx
    endm

    mWriteAX macro                       ;Макрос вывода 10-чного числа из регистра AX
                local convert, write
                push  ax                ;Данные в стек
                push  bx
                push  cx
                push  dx
                push  di
                
                mov   cx, 10            ;cx - основание системы счисления
                xor   di, di            ;di - количество цифр в числе
                or    ax, ax            ;Проверка числа на ноль
                jns   convert           ;Переход, если число положительное
                push  ax                ;Регистр ax в стек
                mov   dx, '-'           ;Поместить в регистр dx символ '-'
                mov   ah, 02h           ;Вывод символа на экран
                int   21h               ;Прерывание DOS
                pop   ax                ;Регистр ax из стека
                neg   ax                ;Инвертирование отрицательного числа
        convert:   
                xor   dx, dx            ;Очистка регистра dx
                div   cx                ;После деления dl = остатку от деления ax на cx
                add   dl, '0'           ;Перевод в символьный формат
                inc   di                ;Увеличение количества цифр в числе на 1
                push  dx                ;Регистр dx в стек
                or    ax, ax            ;Проверка числа на ноль
                jnz   convert           ;Переход, если число не равно нулю
        write:     
                pop   dx                ;dl = очередной символ
                mov   ah, 02h           ;Вывод символа на экран
                int   21h               ;Прерывание DOS
                dec   di                ;Повторение, пока di != 0
                jnz   write

                pop   di                ;Данные из стека
                pop   dx
                pop   cx
                pop   bx
                pop   ax
    endm

    mWriteStr macro string                  ;Макрос вывода строки
                push ax
                push dx

                mov  ah, 09h
                mov  dx, offset string
                int  21h

                pop  dx
                pop  ax
    ENDM

    start:
          mov           ax, @data
          mov           ds, ax

    ; Ввод переменной a
          xor           ax, ax
          mWriteStr     mes_a
          mReadAX     buffer, 5
          mov           a, ax

    ; Ввод переменной b
          xor           ax, ax
          mWriteStr     mes_b
          mReadAX     buffer, 5
          mov           b, ax

    ; Ввод переменной c
          xor           ax, ax
          mWriteStr     mes_c
          mReadAX     buffer, 5
          mov           c, ax

    ; Ввод переменной d
          xor           ax, ax
          mWriteStr     mes_d
          mReadAX     buffer, 5
          mov           d, ax
          

          xor           ax, ax

    
          mCalc_Y1  a, b ; Пример 1: y = 2*b + 2*a
          mWriteAX; Вывод результата

          xor           ax, ax
          mWriteStr '/'
      
          mCalc_Y2 a, b, c ; Пример 2: y = ((a + 3*b) / c) + 4
          mWriteAX    ; Вывод результата

    ; Завершение программы
          mov           ax, 4c00h
          int           21h
end start
