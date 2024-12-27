include macroses.asm        ; Подключение файла с макросами

.model small
.stack 100h
.486 ; Включает сборку инструкций для процессора 80386


;Дана матрица.
;а) В каждой строке матрицы найти максимальный элемент. Найти строку, которая содержит наименьший максимальный элемент.
;б) Проверить, состоит ли матрица только из элементов больших введенного значения n и меньших к (к>0).
;в) Определить сумму отрицательных элементов каждой строки и поместить на место первого элемента.

.data
    buffer            db 20 dup(0)
    endl              db 13, 10, '$'
    tab               db 09, '$'
    space             db ' $'

    mes_rows          db 'Enter the rows of matrix: $'
    mes_cols          db 'Enter the cols of matrix: $'
    mes_inpElements   db 'Enter matrix elements element by element: ', 13, 10, '$'

    mes_menu          db 'To control the menu, press the ', 'corresponding key on the keyboard', 13, 10
                      db '1. Enter matrix from keyboard', 13, 10
                      db '2. Display matrix', 13, 10
                      db '3. View transposed matrix', 13, 10
                      db '4. Find Min of Max elements in rows', 13, 10
                      db '5. Check matrix consists only of elems of larger n and smaller k', 13, 10
                      db '6. Find the sum of the negative elements of line and place it on first element', 13, 10
                      db '0. Exit the program', 13, 10, '$'

    mes_choice        db '>> $'

    mes_matrix        db '>>Matrix<<', 13, 10, '$'
    mes_trans_matrix  db '>>Tronspose Matrix<<', 13, 10, '$'
    mes_edited_matrix db '>>Edited matrix<<', 13, 10, '$'

    mes_minMaxIndex   db 'Min of Max element in rows: $'
    mes_minMaxElement db 'Min of Max elements: $'

    mes_n             db 'Enter n: $'
    mes_k             db 'Enter k: $'
    mes_flag_false    db 'Matrix consists not only of elements of larger entered values n and smaller k$'
    mes_flag_true     db 'Matrix consists only of elements of larger entered values n and smaller k$'



    rows              dw 1
    cols              dw 1
    matrix            dw 100 dup(0)
    trans_matrix      dw 100 dup(0)


    index             dw ?
    minMaxElement     dw ?

    n                 dw ?
    k                 dw ?
    flag              dw ?

    copy_matrix       dw 100 dup(0)


.code
    start:        
    JUMPS  
                    mov                  ax, @data
                    mov                  ds, ax

                    mClear               0000b                                       ; Макрос очистки экрана и установки вида окна
                    mWriteStr            mes_menu                                    ; Макрос вывода строки на экран
                    mWriteStr            endl

    menu:                                                                            ; Вывод на экран меню, а также осуществление выбора следующего пункта программы
                    mov                  ah, 01h
                    int                  16h                                         ; Ожидание нажатия символа и получение его значения в al
                    
                    cmp                  al, "0"
                    je                   exit
                    cmp                  al, "1"
                    je                   consoleInput
                    cmp                  al, "3"
                    je                   transposeMatrix
                    cmp                  al, "4"
                    je                   task1
                    cmp                  al, "5"
                    je                   task2
                    cmp                  al, "6"
                    je                   task3
    writeMatrix:                                                                     ; Вывод элементов матрицы на экран
                    mClear               0000b                                       ; Макрос очистки экрана и установки вида окна
                    mWriteStr            mes_menu                                    ; Макрос вывода строки на экран
                    mWriteStr            endl
                    mov                  ah, 02h
                    mov                  dx, 0900h
                    mov                  bh, 0
                    int                  10h
                    mWriteStr            mes_matrix
                    mWriteMatrix         matrix, rows, cols

                    mov                  ah, 07h                                     ; Задержка экрана
                    int                  21h
                    jmp                  menu

    consoleInput:                                                                    ; Ввод элементов матрицы из консоли
                    mClear               0000b                                       ; Макрос очистки экрана и установки вида окна
                    mWriteStr            mes_rows                                    ; Макрос вывода строки на экран
                    mReadAX              buffer 2                                    ; Макрос ввода значения регистра AX с клавиатуры
                    mov                  rows, ax

                    xor                  ax,ax

                    mWriteStr            mes_cols                                    ; Макрос вывода строки на экран
                    mReadAX              buffer 2
                    mov                  cols, ax

                    mWriteStr            endl                                        ; Макрос вывода строки на экран
                    mWriteStr            mes_inpElements                             ; Макрос вывода строки на экран
                    mReadMatrix          matrix, rows, cols
                    jmp                  writeMatrix

    transposeMatrix:                                                                 ; Получение и вывод транспонированной матрицы
                    mTransposeMatrix     matrix, rows, cols, trans_matrix
                    mWriteStr            endl
                    mWriteStr            mes_trans_matrix
                    mWriteMatrix         trans_matrix, cols, rows

                    mov                  ah, 07h                                     ; Задержка экрана
                    int                  21h
                    jmp                  menu
    task1:                                                                           ; Перемещение нулей в начало строки
                    mFindMinMaxInRows    matrix, rows, cols, index, minMaxElement

                    mWriteStr            endl
                    mWriteStr            mes_minMaxIndex
                    mov                  ax, index
                    mWriteAX

                    xor                  ax, ax

                    mWriteStr            endl
                    mWriteStr            mes_minMaxElement
                    mov                  ax, minMaxElement
                    mWriteAX
                    mWriteStr            endl


                    mov                  ah, 07h                                     ; Задержка экрана
                    int                  21h
                    jmp                  menu
    task2:                                                                           ; Проверка строк на монотонность
                    mWriteStr            mes_n
                    mReadAX              buffer 5
                    mov                  n, ax
                    xor                  ax, ax
                    mWriteStr            mes_k
                    mReadAX              buffer 5
                    mov                  k, ax
                    
                    mCheckMatrixRange    matrix, rows, cols, n, k, flag

                    cmp                  flag, 0
                    jz                   task2False
                    mWriteStr            mes_flag_true
                    mov                  ah, 07h                                     ; Задержка экрана
                    int                  21h
                    jmp                  menu

    task2False:     mWriteStr            mes_flag_false
                    mov                  ah, 07h                                     ; Задержка экрана
                    int                  21h
                    jmp                  menu
    
    task3:                                                                           ; Получение среднего арифметического элементов выше диагоналей
                    mWriteStr            mes_edited_matrix

                    mRowNegativeSumsCopy matrix, rows, cols, copy_matrix

                    mWriteMatrix         copy_matrix, rows, cols

                    mov                  ah, 07h                                     ; Задержка экрана
                    int                  21h
                    jmp                  menu
    ; Завершение программы
    exit:           
                    mov                  ax, 4c00h
                    int                  21h
    NOJUMPS
end Start