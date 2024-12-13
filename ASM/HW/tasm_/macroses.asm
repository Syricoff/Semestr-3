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

mClear macro start           ;Макрос очистки экрана
           push ax
           push bx
           push cx
           push dx

           mov  ah, 10h
           mov  al, 3h
           int  10h          ; Включение режима видеоадаптора с 16-ю цветами

           mov  ax,0600h     ; Подготавливает код для очистки экрана (функция 0).
           mov  bh, 5Ah      ; Устанавливает цвет фона и шрифта
           mov  cx, start    ; Указывает количество строк для очистки (все).
           mov  dx, 184FH    ; Указывает адрес экрана (184FH — адрес видеопамяти).
           int  10h          ; Вызывает прерывание BIOS для выполнения очистки экрана.

           mov  dx, 0        ; dh - строка, dl - столбец
           mov  bh, 0        ; Номер видео-страницы
           mov  ah, 02h      ; 02h - функция установки позиции курсора
           int  10h          ; Устанавливаем курсор на позицию (0, 0)

           pop  dx
           pop  cx
           pop  bx
           pop  ax
endm

mReadMatrix macro matrix, row, col
            local rowLoop, colLoop
            JUMPS ; Директива, делающая возможным большие прыжки
            push bx ; Сохранение регистров, используемых в макросе, в стек
            push cx
            push si

            xor bx, bx ; Обнуляем смещение по строкам
            mov cx, row

            rowLoop: ; Внешний цикл, проходящий по строкам
                    push cx
                    xor si, si ; Обнуляем смещение по столбцам
                    mov cx, col
            colLoop: ; Внутренний цикл, проходящий по столбцам
                    mReadAX buffer 4 ; Макрос ввода значения регистра AX с клавиатуры
                    mov matrix[bx][si], ax
                    add si, 2 ; Переходим к следующему элементу (размером в слово)
                    loop colLoop
            mWriteStr endl ; Макрос вывода строки на экран 
            add bx, col ; Увеличиваем смещение по строкам
            add bx, col ; (дважды, так как размер каждого элемента - слово)
            pop cx
            loop rowLoop
            
            pop si ; Перенос сохранённых значений обратно в регистры
            pop cx
            pop bx
            NOJUMPS ; Прекращение действия директивы JUMPS
endm


mWriteMatrix macro matrix, row, col
    local rowLoop, colLoop
    push ax ; Сохранение регистров, используемых в макросе, в стек
    push bx
    push cx
    push si

    xor bx, bx ; Обнуляем смещение по строкам
    mov cx, row
    rowLoop: ; Внешний цикл, проходящий по строкам
            push cx
            xor si, si ; Обнуляем смещение по столбцам
            mov cx, col
            
    colLoop: ; Внутренний цикл, проходящий по столбцам
            mov ax, matrix[bx][si] ; bx - смещение по строкам, si - по столбцам
            mWriteAX ; Макрос вывода значения регистра AX на экран 
            ; Вывод текущего элемента матрицы
            xor ax, ax
            mWriteStr tab ; Макрос вывода строки на экран
            ; Вывод на экран табуляции, разделяющей элементы строки
            add si, 2 ; Переходим к следующему элементу (размером в слово)
            loop colLoop

    mWriteStr endl ; Макрос вывода строки на экран
    ; Перенос курсора и каретки на следующую строку
    add bx, col ; Увеличиваем смещение по строкам
    add bx, col ; (дважды, так как размер каждого элемента - слово)
    pop cx
    loop rowLoop

    pop si ; Перенос сохранённых значений обратно в регистры
    pop cx
    pop bx
    pop ax
endm

mTransposeMatrix macro matrix, row, col, resMatrix
local rowLoop, colLoop
push ax ; Сохранение регистров, используемых в макросе, в стек
push bx
push cx
push di
push si
push dx
xor di, di ; Обнуляем смещение по строкам
mov cx, row
rowLoop: ; Внешний цикл, проходящий по строкам
push cx
xor si, si ; Обнуляем смещение по столбцам
mov cx, col
colLoop: ; Внутренний цикл, проходящий по столбцам
mov ax, col
mul di ; Устанавливаем смещение по строкам
add ax, si ; Устанавливаем смешение по столбцам
mov bx, ax
mov ax, matrix[bx]
push ax ; Заносим текущий элемент в стек
mov ax, row
mul si ; Устанавливаем смещение по строкам
add ax, di ; Устанавливаем смешение по столбцам
; (смещения по строкам и столбцам меняются 
; местами по сравнению с оригинальной матрицей)
mov bx, ax
pop ax
mov resMatrix[bx], ax ; Заносим в новую матрицу элемент, сохранённый в стеке
add si, 2 ; Переходим к следующему элементу (размером в слово)
loop colLoop
add di, 2 ; Переходим к следующей строке
pop cx
loop rowLoop
pop dx ; Перенос сохранённых значений обратно в регистры
pop si
pop di
pop cx
pop bx
pop ax
endm

mFindMinMaxInRows macro matrix, rows, cols, index, minMaxElement
    local rowLoop, colLoop, skipUpdate, nextRow

    push ax
    push bx
    push cx
    push dx
    push si
    push di

    mov di, 7FFFh         ; Инициализируем минимальный максимум (очень большое значение)
    xor dx, dx            ; Текущий максимум строки
    xor ax, ax            ; Сброс регистра ax
    xor bx, bx            ; Смещение строки
    xor cx, cx            ; Сброс счетчика строк

    mov cx, rows          ; cx = количество строк
    xor si, si            ; si = индекс текущей строки

rowLoop:
    push cx               ; Сохраняем счетчик строк
    mov bx, si            ; bx = номер строки
    imul bx, cols         ; bx = смещение начала строки (учитываем количество столбцов)
    shl bx, 1             ; Умножаем на 2, так как элементы занимают по 2 байта
    mov cx, cols          ; cx = количество столбцов
    mov dx, 8000h         ; Устанавливаем максимум строки в минимальное значение

colLoop:
    mov ax, matrix[bx]    ; Загружаем текущий элемент
    cmp ax, dx            ; Сравниваем с текущим максимумом строки
    jle nextCol           ; Если максимум не обновляется, перейти
    mov dx, ax            ; Обновляем максимум строки

nextCol:
    add bx, 2             ; Переходим к следующему элементу строки
    loop colLoop          ; Повторяем для всех элементов строки

    cmp dx, di            ; Сравниваем максимум строки с минимальным максимумом
    jge skipUpdate        ; Если не меньше, пропускаем обновление
    mov di, dx            ; Обновляем минимальный максимум
    mov [index], si       ; Сохраняем индекс текущей строки

skipUpdate:
    inc si                ; Переход к следующей строке (индекс строки)
    pop cx                ; Восстанавливаем счетчик строк
    loop rowLoop          ; Переход к следующей строке

    mov [minMaxElement], di ; Сохраняем минимальный максимум

    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
endm

mCheckMatrixRange macro matrix, rows, cols, n, k, result
    local rowLoop, colLoop, checkFail, nextElement, endCheck

    push ax
    push bx
    push cx
    push dx
    push si
    push di

    xor si, si            ; si = 0, для работы с индексами матрицы
    xor di, di            ; di = 0, начальный результат (будет 1, если условие выполнено)
    mov di, 1             ; Предполагаем, что матрица соответствует условию

    mov cx, rows          ; cx = количество строк

rowLoop:
    push cx               ; Сохраняем счетчик строк
    mov bx, si            ; bx = номер строки
    imul bx, cols         ; bx = смещение начала строки (учет количества столбцов)
    shl bx, 1             ; Умножаем на 2, так как элементы занимают 2 байта
    mov cx, cols          ; cx = количество столбцов

colLoop:
    mov ax, matrix[bx]    ; Загружаем текущий элемент
    cmp ax, n             ; Сравниваем с n
    jle checkFail         ; Если элемент <= n, условие не выполнено
    cmp ax, k             ; Сравниваем с k
    jge checkFail         ; Если элемент >= k, условие не выполнено

nextElement:
    add bx, 2             ; Переход к следующему элементу строки
    loop colLoop          ; Повторяем для всех элементов строки
    pop cx                ; Восстанавливаем счетчик строк
    inc si                ; Переход к следующей строке
    loop rowLoop          ; Переход к следующей строке
    jmp endCheck          ; Завершаем проверку

checkFail:
    mov di, 0             ; Условие не выполнено
    jmp endCheck          ; Прерываем проверку

endCheck:
    mov [result], di      ; Сохраняем результат: 1 = соответствует, 0 = не соответствует

    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
endm

mRowNegativeSumsCopy macro matrix, rows, cols, result
    local copyMatrix, processRow, processCol, endMacro

    push ax
    push bx
    push cx
    push dx
    push si
    push di

    ; Копируем исходную матрицу в result
    xor si, si             ; si = индекс исходной матрицы
    xor di, di             ; di = индекс для копии
    mov cx, rows           ; cx = количество строк
    imul cx, cols          ; cx = общее количество элементов
    shl cx, 1              ; Умножаем на 2 (размер word)

copyMatrix:
    mov ax, matrix[si]     ; Загружаем элемент исходной матрицы
    mov result[di], ax     ; Копируем в result
    add si, 2              ; Переход к следующему элементу
    add di, 2              ; Переход к следующей ячейке в result
    loop copyMatrix         ; Повторяем для всех элементов

    ; Обрабатываем строки для вычисления сумм отрицательных
    xor si, si             ; Индекс начала текущей строки в result
    xor di, si             ; Индекс записи результата (совпадает с si)
    mov cx, rows           ; cx = количество строк

processRow:
    push cx                ; Сохраняем счётчик строк
    xor dx, dx             ; dx = сумма отрицательных элементов
    mov bx, si             ; bx = начальный адрес текущей строки
    mov cx, cols           ; cx = количество столбцов в строке

processCol:
    mov ax, result[bx]     ; Загружаем элемент текущей строки
    cmp ax, 0              ; Проверяем, является ли элемент отрицательным
    jge skipAdd            ; Если >= 0, пропускаем
    add dx, ax             ; Добавляем к сумме отрицательных

skipAdd:
    add bx, 2              ; Переход к следующему элементу в строке
    loop processCol        ; Повторяем для всех столбцов

    cmp dx, 0
    jz endRow            ; Если сумма отрицательных не ноль, продолжаем обработку
    ; Записываем сумму отрицательных элементов в начало строки
    mov result[si], dx     ; Записываем сумму в начало текущей строки
endRow:
    ; Переход к следующей строке
    add si, cols           ; Смещение для следующей строки
    add si, cols              ; Умножаем на 2 (размер word)

    pop cx                 ; Восстанавливаем счётчик строк
    loop processRow        ; Обрабатываем следующую строку

endMacro:
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
endm