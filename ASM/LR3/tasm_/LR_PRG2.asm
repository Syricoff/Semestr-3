title prog4             ; LR_2, Surikov, IUK4
.model small			; Количество сегментов в программе - 2
.stack 200h				; Размер стека - 512б
.data                             ; Сегмент данных
    day   db 26                   ; День рождения - 26
    qwer  dw 4321h                ; Число qwer
    month dw 01                   ; Месяц рождения - январь
    year  dw 7D5H                 ; Год рождения - 2005
    min   db 68                   ; Минимальная оценка - 68
    max   db 100                  ; Максимальная оценка - 97
    age   db 19                   ; Возраст - 19
    mas_1 db 01 dup(19)           ; Массив длиной 01, каждый символ = 19
    mas_2 dw 68 dup(97 dup(?))    ; Двумерный массив, число строк - min, столбцов - max
    mes   db 'Surikov', '$'       ; Фамилия

.code                            ; Сегмент кода
    start:
          mov  ax, @data         ; Инициализировать
          mov  ds, ax            ; сегментный регистр ds

          xor  ax, ax            ; Очистка ригистра ax

          mov  di, year          ; Переместить значение переменной year в регистр DI
          mov  al, day           ; Переместить значение переменной day в регистр al
          mov  cx, month         ; Переместить значение переменной month в регистр cx
          mov  es, cx            ; Переместить значение переменной month в регистр es

          push ax                ; Поместить в стек значение регистра ax
          push cx                ; Поместить в стек значение регистра cx

          mov  ax, month
          xchg ax, qwer          ; Обмен содержимого переменных qwer и mes
          mov  month, ax

          lea  si, day           ; Поместить в регистр SI адрес переменной day

    ; mov cs, ds			Сегментный регистр может быть только приёмником!

          pop  dx                ; Извлечь из стека значение и переместить его в регистр dx
          pop  cx                ; Извлечь из стека значение и поместить его в регистр cx

          mov  ah, 09h           ; Вывод строки на экран
          mov  dx, offset mes    ; Поиск адреса первого символа строки
          int  21h               ; Прерывание DOS

          mov  ax, 4c00h         ; Завершить программу
          int  21h               ; с помощью DOS
end start				; Закрыть процедуру