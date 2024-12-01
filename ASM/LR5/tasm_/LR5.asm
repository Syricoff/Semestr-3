include macroses.asm        ; Подключение файла с макросами

.model small
.stack 100h
.data
    mes_n      db 'Enter the size of the array N (max 10): $'
    mes_c      db 'Enter the value of C: $'
    mes_d      db 'Enter the value of D: $'
    mes_num    db 'Enter array element: $'
    mes_pos    db 'Number of positive elements: $'
    mes_neg    db 'Number of negative elements: $'
    mes_zero   db 'Number of zero elements: $'
    new_line   db 13, 10, '$'                                    ; Перевод строки
    buf        db 7 dup(0)                                       ; Буфер для чтения ввода
    n          dw ?                                              ; Переменная для хранения размера массива
    c          dw ?                                              ; Переменная для хранения значения C
    d          dw ?                                              ; Переменная для хранения значения D
    arr        dw 10 dup(?)                                      ; Массив из 10 элементов (слова)
    count_pos  dw 0
    count_neg  dw 0
    count_zero dw 0

.code
    start:            
                      mov       ax, @data
                      mov       ds, ax

    ; Ввод размера массива N
                      mWriteStr mes_n
                      mReadAX   buf, 3               ; Чтение размера массива в регистр AX
                      cmp       ax, 10               ; Проверка, не превышает ли размер массива 10
                      jbe       Valid_N
                      mov       ax, 10               ; Ограничение размера массива значением 10, если введено больше
    Valid_N:          
                      mov       n, ax                ; Сохранение размера массива

    ; Ввод значений C и D
                      mWriteStr new_line
                      mWriteStr mes_c
                      mReadAX   buf, 7               ; Ввод значения C в регистр AX
                      mov       c, ax                ; Сохранение C

                      mWriteStr new_line
                      mWriteStr mes_d
                      mReadAX   buf, 7               ; Ввод значения D в регистр AX
                      mov       d, ax                ; Сохранение D

    ; Ввод массива
                      xor       si, si               ; Обнуление индекса массива
                      xor       cx, cx
                      mov       cx, n                ; Установка счетчика цикла на количество элементов массива
    InputArray:       
                      mWriteStr new_line
                      mWriteStr mes_num
                      mReadAX   buf, 7               ; Ввод элемента массива
                      mov       arr[si], ax          ; Сохранение элемента в массив
                      add       si, 2                ; Переход к следующему элементу массива
                      loop      InputArray           ; Повторение цикла, пока CX != 0

    ; Обработка массива
                      xor       si, si               ; Сброс индекса массива
                      xor       cx, cx
                      mov       cx, n                ; Установка счетчика на количество введенных элементов

    ProcessArray:     
                      mov       ax, arr[si]          ; Загрузка текущего элемента массива
                      cmp       ax, c
                      jl        NextElement          ; Переход к следующему элементу, если меньше С
                      cmp       ax, d
                      jg        NextElement          ; Переход к следующему элементу, если больше D

    ; Условие выполнения: C <= arr[i] <= D
                      cmp       ax, 0
                      jg        IncrementPositive    ; > 0
                      jl        IncrementNegative    ; < 0
                      inc       count_zero           ; = 0
                      jmp       NextElement

    IncrementPositive:
                      inc       count_pos            ; Увеличение счетчика положительных элементов
                      jmp       NextElement
    IncrementNegative:
                      inc       count_neg            ; Увеличение счетчика отрицательных элементов
                      jmp       NextElement

    NextElement:      
                      add       si, 2                ; Переход к следующему элементу массива
                      loop      ProcessArray         ; Повторение цикла обработки массива

    ; Вывод результатов
                      mWriteStr new_line
                      mWriteStr mes_pos
                      mov       ax, count_pos
                      mWriteAX                       ; Вывод количества положительных элементов

                      mWriteStr new_line
                      mWriteStr mes_neg
                      mov       ax, count_neg
                      mWriteAX                       ; Вывод количества отрицательных элементов

                      mWriteStr new_line
                      mWriteStr mes_zero
                      mov       ax, count_zero
                      mWriteAX                       ; Вывод количества нулевых элементов

    ; Завершение программы
                      mov       ax, 4C00h
                      int       21h

end start