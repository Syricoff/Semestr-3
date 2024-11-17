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

                imul cx             ; ax = b * 3 (ax = 3*b)
                add  ax, bx         ; ax = a + 3*b

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

; Макрос ввода 10-чного числа в регистр АХ
mReadAX macro buffer, sizee
                   local input, startOfConvert, endOfConvert
                   push  bx                                     ; Данные в стек
                   push  cx
                   push  dx
    input:         
                   mov   [buffer], sizee                        ; Задаём размер буфера
                   mov   dx, offset [buffer]                    ; Поместить в регистр dx строку по адресу buffer
                   mov   ah, 0Ah                                ; Чтение строки из консоли
                   int   21h                                    ; Прерывание DOS

                   mov   ah, 02h                                ; Вывод символа на экран
                   mov   dl, 0Dh                                ; Перевод каретки на новую строку
                   int   21h                                    ; Прерывание DOS

                   mov   ah, 02h                                ; Вывод символа на экран
                   mov   dl, 0Ah                                ; Чтение строки из консоли
                   int   21h                                    ; Прерывание DOS

                   xor   ah, ah                                 ; Очистка регистра ah
                   cmp   al, [buffer][1]                        ; Проверка на пустую строку
                   jz    input                                  ; Переход, если строка пустая

                   xor   cx, cx                                 ; Очистка регистра cx
                   mov   cl, [buffer][1]                        ; инициализация переменной-счётчика

                   xor   ax, ax                                 ; Очистка регистра ax
                   xor   bx, bx                                 ; Очистка регистра bx
                   xor   dx, dx                                 ; Очистка регистра dx

                   mov   bx, offset [buffer][2]                 ; Поместить начало строки в регистр bx
                   cmp   [buffer][2], '-'                       ; Проверка на знак числа
                   jne   startOfConvert                         ; Переход, если число неотрицательное
                   inc   bx                                     ; Инкремент регистра bx
                   dec   cl                                     ; Декремент регистра-счетчика cl
    startOfConvert:
                   mov   dx, 10                                 ; Поместить в регистр ax число 10
                   mul   dx                                     ; Умножение на 10 перед сложением с младшим разрядом
                   cmp   ax, 8000h                              ; Проверка числа на выход за границы
                   jae   input                                  ; Переход, если число выходит за границы
                   mov   dl, [bx]                               ; Поместить в регистр dl следующий символ
                   sub   dl, '0'                                ; Перевод его в числовой формат
                   add   ax, dx                                 ; Прибавляем его к конечному результату
                   cmp   ax, 8000h                              ; Проверка числа на выход за границы
                   jae   input                                  ; Переход, если число выходит за границы
                   inc   bx                                     ; Переход к следующему символу
                   loop  startOfConvert                         ; Цикл
                   cmp   [buffer][2], '-'                       ; Проверка на знак числа
                   jne   endOfConvert                           ; Переход, если число неотрицательное
                   neg   ax                                     ; Инвертирование числа
    endOfConvert:  
                   pop   dx                                     ; Данные из стека
                   pop   cx
                   pop   bx
endm

; Макрос вывода 10-чного числа из регистра AX
mWriteAX macro
             local convert, write
             push  ax                ; Данные в стек
             push  bx
             push  cx
             push  dx
             push  di
                
             mov   cx, 10            ; cx - основание системы счисления
             xor   di, di            ; di - количество цифр в числе
             or    ax, ax            ; Проверка числа на ноль
             jns   convert           ; Переход, если число положительное
             push  ax                ; Регистр ax в стек
             mov   dx, '-'           ; Поместить в регистр dx символ '-'
             mov   ah, 02h           ; Вывод символа на экран
             int   21h               ; Прерывание DOS
             pop   ax                ; Регистр ax из стека
             neg   ax                ; Инвертирование отрицательного числа
    convert: 
             xor   dx, dx            ; Очистка регистра dx
             div   cx                ; После деления dl = остатку от деления ax на cx
             add   dl, '0'           ; Перевод в символьный формат
             inc   di                ; Увеличение количества цифр в числе на 1
             push  dx                ; Регистр dx в стек
             or    ax, ax            ; Проверка числа на ноль
             jnz   convert           ; Переход, если число не равно нулю
    write:   
             pop   dx                ; dl = очередной символ
             mov   ah, 02h           ; Вывод символа на экран
             int   21h               ; Прерывание DOS
             dec   di                ; Повторение, пока di != 0
             jnz   write

             pop   di                ; Данные из стека
             pop   dx
             pop   cx
             pop   bx
             pop   ax
endm

; Макрос вывода строки
mWriteStr macro string
              push ax
              push dx

              mov  ah, 09h
              mov  dx, offset string
              int  21h

              pop  dx
              pop  ax
endm