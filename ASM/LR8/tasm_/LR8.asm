.486
model use16 small
.stack 100h
.data
    const_neg5    dw -5                                                        ; Константа -5
    const_120     dw 213                                                       ; Константа 120
    const_240     dw 213                                                       ; Константа 240
    const_6       dw 6                                                         ; Константа 6
    const_3       dw 3                                                         ; Константа 3

    screen_middle dw 330                                                       ; Центр экрана по оси Y
    var_x         dw ?                                                         ; Переменная для X
    var_y         dw ?                                                         ; Переменная для Y
    axis_marker   dw ?                                                         ; Метка текущей позиции оси
    scale_y_coeff dw 50                                                        ; Коэффициент масштабирования по оси Y

    music2        dw 2100, 2000, 3000, 2000, 2100, 2000, 2500, 1500, 2500
                  dw 2000, 12000, 7000, 8000, 4000, 2217, 2637, 2349, 2093
                  dw 3729, 2959, 3729, 2959, 2793, 2637, 2349, 3951, 3322
                  dw 3136, 3322, 3136, 2793, 2349, 2637, 2217
                  
    music1        dw 2620, 2940, 3300, 3490, 3920, 4400, 4940, 5230
                  dw 5870, 6590, 6980, 7840, 8800, 9880, 10470, 11750
                  dw 13100, 13970, 15680, 17600, 19750, 20930, 22170, 23490
                  dw 24890, 26370, 27930, 29590, 31360, 33140, 34920, 36700
                  dw 38600

    music_pointer dw ?

    delay_count   dw 1
    melody_end    dw 30
    melody_max    dw 20                                                        ; Указатель на текущую мелодию
.code
    Start:               
    ; Инициализация сегментов данных
                         mov     ax, @data
                         mov     ds, ax

    ; Установим указатель на первую мелодию
                         lea     ax, music1
                         mov     music_pointer, ax

    ; Переключение в графический режим 320x200
                         xor     ax, ax
                         mov     al, 10h
                         int     10h

    ; Заливка экрана белым цветом
                         mov     ax, 0600h               ; Функция прокрутки вверх
                         mov     bh, 15                  ; Белый цвет
                         mov     cx, 0000h               ; Верхний левый угол
                         mov     dx, 184Fh               ; Нижний правый угол
                         int     10h

    ; Рисуем вертикальную линию в центре экрана
                         mov     ah, 0Ch                 ; Установка графической точки
                         mov     al, 10                  ; Зелёный цвет
                         mov     bh, 0h                  ; Номер видеостраницы
                         mov     cx, 400                 ; Количество итераций по Y
    draw_vertical_line:  
                         push    cx
                         mov     axis_marker, cx         ; Сохраняем текущую позицию оси
                         mov     dx, axis_marker
                         mov     cx, 213                 ; Сдвиг оси вправо
                         int     10h
                         pop     cx
                         loop    draw_vertical_line

    ; Рисуем горизонтальную линию в центре экрана
                         mov     ah, 0Ch                 ; Установка графической точки
                         mov     al, 4                   ; Красный цвет
                         mov     cx, 639                 ; Количество итераций по X
                         mov     bh, 0h                  ; Номер видеостраницы
                         mov     dx, screen_middle
    draw_horizontal_line:
                         int     10h
                         loop    draw_horizontal_line
    
    ; стрелка X
                         mov     al, 4                   ; Цвет стрелки (красный)
                         mov     cx, 639
                         mov     dx, 330
                         int     10h

                         mov     dx, 331
                         int     10h

                         mov     dx, 332
                         int     10h

                         mov     cx, 638
                         mov     dx, 329
                         int     10h

                         mov     dx, 333
                         int     10h

                         mov     cx, 637
                         mov     dx, 328
                         int     10h

                         mov     dx, 335
                         int     10h
    ; стрелка Y
                         mov     al, 10                  ; Цвет стрелки (зелёный)
                         mov     cx, 213
                         mov     dx, 1
                         int     10h

                         mov     cx, 214
                         int     10h

                         mov     cx, 215
                         int     10h

                         mov     cx, 212
                         mov     dx, 2
                         int     10h

                         mov     cx, 216
                         int     10h

                         mov     cx, 211
                         mov     dx, 3
                         int     10h

                         mov     cx, 217
                         int     10h
    ; Начинаем расчёт и отрисовку графика
                         mov     cx, 639                 ; Устанавливаем начальное значение X
                         xor     di, di
    draw_graph:          
                         mov     var_x, cx
                         fild    var_x                   ; Загружаем X в стек FPU
                         fild    const_120               ; Загружаем 120 в стек FPU
                         fsub                            ; Вычитаем (X - 120)
                         fild    const_240               ; Загружаем 240 в стек FPU
                         fdiv                            ; Делим на 240 (X - 120) / 240

    ; Условие: если X < 0
                         fld     st(0)
                         fldz                            ; Загружаем 0
                         fcom                            ; Сравниваем X с 0
                         fstsw   ax                      ; Сохраняем результат сравнения
                         sahf                            ; Загружаем флаги
                         ja      less_than_zero          ; Если X < 0, перейти на обработку

    ; Условие: 0 <= X < 1
                         fld     st(1)
                         fld1
                         fsub
                         fldz                            ; Загружаем 0
                         fcom                            ; Сравниваем X с 0
                         fstsw   ax                      ; Сохраняем результат сравнения
                         sahf                            ; Загружаем флаги
                         ja      between_zero_and_one    ; Если X < 0, перейти на обработку

    ; Если X >= 1
                         jmp     greater_than_one

    less_than_zero:      
                         fld     st(1)                   ; Загружаем x из стека.
                         fabs                            ; Берём модуль ST(0) (|x|).

                         fld     st(2)                   ; Загружаем (x - 213) / 213.
                         fld     st(0)                   ; Дублируем вершину стека.
                         fmul                            ; Умножаем (x - 213) / 213 на (x - 213) / 213.

                         fld1                            ; Загружаем константу 1.
                         fadd                            ; Прибавляем 1 к произведению.
                         fdiv                            ; Делим модифицированный результат на (x - 213) / 213.

                         fld     st(2)                   ; Берём (x - 213) / 213.
                         fild    const_neg5              ; Загружаем константу -5.
                         fmul                            ; Умножаем на -5.

                         fldl2e                          ; Загружаем log2(e).
                         fmul                            ; Умножаем результат на log2(e).
                         fld     st                      ; Дублируем вершину стека.

                         frndint                         ; Округляем значение.
                         fsub    st(1), st               ; Вычитаем округлённое значение.
                         fxch    st(1)                   ; Меняем местами ST(0) и ST(1).

                         f2xm1                           ; Вычисляем 2^(ST(0)) - 1.
                         fld1                            ; Загружаем 1.
                         faddp   st(1), st               ; Прибавляем 1 к 2^(ST(0)) - 1.
                         fscale                          ; Умножаем на 2^(целая часть ST(1)).

                         fstp    st(1)                   ; Сохраняем результат.
                         fmul                            ; Умножаем текущий результат на предыдущий.
                         
                         mov     al, 5

                         jmp     calculate
    ; Обработка при 0 <= X <= 1
    between_zero_and_one:
                         fld     st(3)
                         fld     st(0)
                         fmul                            ; X^2
                         fld     st(0)
                         fmul
                         fld1
                         fadd                            ; X^2 + 1
                         fsqrt                           ; sqrt(X^2 + 1)
                         mov     al, 3

                         jmp     calculate

    greater_than_one:    
                         fld     st(3)
                         fld     st(0)
                         fldpi                           ; Загружаем Pi
                         fmul                            ; X * Pi
                         fcos                            ; cos(X * Pi)
                         fld1
                         fadd                            ; cos(X * Pi) + 1
                         fld     st(1)
                         fild    const_6
                         fadd                            ; cos(X * Pi) + 1 + 6
                         fdiv                            ; Нормализация
                         fxch    st(1)
                         fild    const_3
                         fmul                            ; Умножение на 3
                         fadd                            ; Результат

                         mov     al, 10
                         jmp     calculate

    calculate:           
    ; Преобразуем координаты для отображения на экране
                         fimul   scale_y_coeff           ; Умножаем на коэффициент Y
                         fchs                            ; Изменяем знак
                         fiadd   screen_middle           ; Смещаем относительно центра экрана
                         frndint                         ; Округляем до целого
                         fistp   var_y                   ; Сохраняем результат в var_y

    ; Рисуем точку графика
                         push    cx
                         mov     cx, var_x
                         mov     ah, 0Ch                 ; Установка графической точки
                         mov     bh, 0h                  ; Номер видеостраницы
                         mov     dx, var_y
    ;  mov     al, 0                   ; Чёрный цвет
                         int     10h
                         pop     cx

    ; Задержка
                         push    cx
                         mov     cx, delay_count         ; Используем переменную для настраиваемой задержки
    delay:               
                         push    cx
                         xor     cx,cx
    delay_loop:          
                         nop                             ; Минимальная инструкция для задержки
                         loop    delay_loop
                         pop     cx
                         loop    delay
                         pop     cx

    ; Настройка музыкального таймера
                         mov     al, 10110110b           ; Управляющее слово: канал 2, режим 3
                         out     43h, al
                         push    di
                         push    si
                         mov     di, music_pointer       ; Загружаем указатель на текущую мелодию
                         add     si, di
                         mov     ax, [si]                ; Загружаем данные мелодии
                         pop     si
                         pop     di
                         add     di, 2                   ; Смещаем указатель мелодии
                         cmp     di, melody_end          ; Проверяем конец мелодии
                         jge     reset_di_pointer
                         jmp     process_music
    reset_di_pointer:    
                         xor     di, di                  ; Сбрасываем указатель
                         add     si, 2
                         cmp     si, melody_max
                         je      reset_si_pointer
                         jmp     process_music
    reset_si_pointer:    
                         mov     si, 0                   ; Сбрасываем второй указатель
    process_music:       
                         out     42h, al                 ; Отправляем младший байт частоты
                         mov     al, ah                  ; Отправляем старший байт частоты
                         out     42h, al

    ; Включаем динамик
                         in      al, 61h                 ; Читаем порт управления
                         or      al, 00000011b           ; Устанавливаем биты включения канала 2
                         out     61h, al

    ; Проверка ввода с клавиатуры
                         mov     ah, 01h                 ; Проверяем, нажата ли клавиша
                         int     16h
                         jz      skip_key_check          ; Если клавиша не нажата, пропустить проверку

                         mov     ah, 00h                 ; Чтение нажатой клавиши
                         int     16h
                         cmp     al, '0'                 ; Если нажата '0', выйти
                         je      exit_program
                         cmp     al, '1'                 ; Если нажата '1', сменить мелодию на первую
                         je      set_music1
                         cmp     al, '2'                 ; Если нажата '2', сменить мелодию на вторую
                         je      set_music2

    set_music1:          
                         lea     ax, music1
                         mov     music_pointer, ax
                         jmp     skip_key_check
    set_music2:          
                         lea     ax, music2
                         mov     music_pointer, ax

    skip_key_check:      
                         dec     cx
                         jnz     draw_graph

    exit_program:        
    ; Завершаем работу программы
                         in      al, 61h
                         and     al, 0FCh                ; Выключаем динамик
                         out     61h, al

                         mov     ah, 4Ch                 ; Завершение программы
                         int     21h
end Start