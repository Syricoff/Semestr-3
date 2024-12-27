﻿.486
model use16 small
.stack 100h
.data
    const_neg5    dw -5
    n10           dw 1
    const_120     dw 213
    const_240     dw 213
    n2            dw 2
    n6            dw 6
    n3            dw 3
    screen_middle dw 330                                                                                                                                                                                                                         ;
    k1            dw 10                                                                                                                                                                                                                          ;ставим коэффициент K сжатия -
    ;растяжения по оси Ох
    var_x         dw ?
    pi            dw 180                                                                                                                                                                                                                         ;задаѐм число пи в радианах
    var_y         dw ?
    axis_marker   dw ?                                                                                                                                                                                                                           ;задаѐм ось
    scale_y_coeff dw 50                                                                                                                                                                                                                          ;ставим коэффициент K сжатия-
    ;растяжения по оси Оy
    two           dw 2
    music1        dw 2100, 2000, 3000, 2000, 2100, 2000, 2500, 1500, 2500, 2000, 12000, 7000, 8000, 4000, 2217, 2637, 2349, 2093, 3729, 2959, 3729, 2959, 2793, 2637, 2349, 3951, 3322, 3136, 3322, 3136, 2793, 2349, 2637, 2217
    chast         dw 15000
    len_music     dw 29
    music_pointer dw ?
    music2        dw 659, 659, 659, 523, 659, 783, 391, 523, 391, 329, 440, 493, 466, 440, 391, 659, 783, 880, 698, 783, 659, 523, 587, 987, 783, 680, 698, 622, 680, 415, 466, 523, 440, 523, 587, 783, 739, 729, 587, 659, 1046, 1046, 1046
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
                         mov     al, 20h                 ; Зелёный цвет
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
                         mov     al, 21h                 ; Зелёный цвет
                         mov     cx, 639                 ; Количество итераций по X
                         mov     bh, 0h                  ; Номер видеостраницы
                         mov     dx, screen_middle

    draw_horizontal_line:
                         int     10h
                         loop    draw_horizontal_line

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

                         mov     [chast], 300            ; Устанавливаем chast = 300.
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

                         jmp     calculate

    between_zero_and_one:
                         mov     [chast], 10000
                         fld     st(3)
                         fld     st(0)
                         fmul
                         fld     st(0)
                         fmul
                         fld1
                         fadd
                         fsqrt
                         jmp     calculate
    greater_than_one:    
                         mov     [chast], 15000
                         fld     st(3)
                         fld     st(0)
                         fldpi
                         fmul
                         fcos
                         fld1
                         fadd
                         fld     st(1)
                         fild    n6
                         fadd
                         fdiv
                         fxch    st(1)
                         fild    n3
                         fmul
                         fadd
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
                         mov     al, 0                   ; Чёрный цвет
                         int     10h
                         pop     cx
                         
    ; --------------------------------
                         push    cx
                         mov     cx, 1
    d12:                 
                         push    cx
                         xor     cx,cx
    d11:                 
                         nop
                         loop    d11
                         pop     cx
                         loop    d12
                         pop     cx
 

                         mov     al, 10110110b           ;управляющее слово: канал 2, режим 3
                         out     43h, al
                         push    di
                         push    si
                         mov     di, music_pointer
                         add     si, di
                         mov     ax, [si]
                         pop     si
                         pop     di
                         add     di, 2
                         cmp     di, 30
                         jge     di_eq
                         jmp     m_el
    di_eq:               
                         xor     di, di
                         add     si, 2
                         cmp     si, 20
                         je      equl_m
                         jmp     m_el
    equl_m:              
                         mov     si, 0
    m_el:                
                         out     42h, al
                         mov     al, ah
                         out     42h, al
    ;включаем динамик
                         in      al, 61h                 ; читаем порт управления
                         or      al, 00000011b           ;устанавливаем биты для включения канала 2
                         out     61h, al

    ; Проверка нажатия клавиши
                         mov     ah, 01h                 ; Проверка наличия нажатия клавиши (INT 16h, функция 01h)
                         int     16h
                         jz      @skip_keycheck          ; Если клавиша не нажата, пропустить проверку

                         mov     ah, 00h                 ; Чтение символа с клавиатуры (INT 16h, функция 00h)
                         int     16h
                         cmp     al, '0'                 ; Сравнить с символом '0'
                         je      @exit_program           ; Если нажата '0', выйти из программы
                         cmp     al, '1'
                         je      p1_music
                         cmp     al, '2'
                         je      p2_music
    p1_music:            
                         lea     ax, music1
                         mov     music_pointer, ax
                         jmp     @skip_keycheck
    p2_music:            
                         lea     ax, music2
                         mov     music_pointer, ax


@skip_keycheck:
                         dec     cx
                         jnz     draw_graph

@exit_program:
    ; Завершение программы

                         in      al, 61h
                         and     al, 0FCh
                         out     61h, al

                         mov     ah, 4Ch
                         int     21h
end Start
end