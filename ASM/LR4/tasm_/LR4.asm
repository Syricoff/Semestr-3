.model small
.stack 100h
.data
    menu_msg       db '1: Single-digit numbers$', 0Dh, 0Ah, '2: Two-digit numbers$', 0Dh, 0Ah, '3: Three-digit numbers$', 0Dh, 0Ah, 'Choose (1, 2, or 3): $'
    input_msg      db 'Your choice: $', 0
    result_msg     db 'The result is: $', 0
    
    ; Наборы данных для однозначных, двузначных и трёхзначных чисел
    single_digit_a dw -3
    single_digit_b dw 2
    single_digit_c dw 1
    single_digit_x dw 4

    two_digit_a    dw -12
    two_digit_b    dw 15
    two_digit_c    dw 9
    two_digit_x    dw 8

    three_digit_a  dw 100
    three_digit_b  dw 200
    three_digit_c  dw 0
    three_digit_x  dw 50

    result         dw ?
    a              dw ?
    b              dw ?
    c              dw ?
    x              dw ?
    input          db ?
    
.code
main proc
    ; Инициализация сегмента данных
                      mov  ax, @data
                      mov  ds, ax
    
    ; Вывод меню
                      mov  ah, 09h
                      lea  dx, menu_msg
                      int  21h
    
    ; Чтение выбора пользователя
                      lea  dx, input_msg
                      mov  ah, 09h
                      int  21h
    
                      mov  ah, 01h
                      int  21h
                      sub  al, '0'               ; Преобразовать символ в число
                      mov  input, al
    
    ; Загрузка значений переменных в зависимости от выбора
                      cmp  input, 1
                      je   load_single_digit
                      cmp  input, 2
                      je   load_two_digit
                      cmp  input, 3
                      je   load_three_digit

    load_single_digit:
    ; Загрузка однозначных значений
                      mov  ax, single_digit_a
                      mov  [a], ax
                      mov  ax, single_digit_b
                      mov  [b], ax
                      mov  ax, single_digit_c
                      mov  [c], ax
                      mov  ax, single_digit_x
                      mov  [x], ax
                      jmp  calculate

    load_two_digit:   
    ; Загрузка двузначных значений
                      mov  ax, two_digit_a
                      mov  [a], ax
                      mov  ax, two_digit_b
                      mov  [b], ax
                      mov  ax, two_digit_c
                      mov  [c], ax
                      mov  ax, two_digit_x
                      mov  [x], ax
                      jmp  calculate

    load_three_digit: 
    ; Загрузка трёхзначных значений
                      mov  ax, three_digit_a
                      mov  [a], ax
                      mov  ax, three_digit_b
                      mov  [b], ax
                      mov  ax, three_digit_c
                      mov  [c], ax
                      mov  ax, three_digit_x
                      mov  [x], ax
                      jmp  calculate

    calculate:        
    ; Проверка условий и выбор выражения
                      mov  ax, [a]
                      cmp  ax, 0
                      jl   calc_expr1            ; Если a < 0, выполняем выражение 1
    
                      cmp  ax, 0
                      jg   calc_expr2            ; Если a > 0, выполняем выражение 2
    
                      jmp  calc_expr3            ; Иначе выполняем выражение 3

    calc_expr1:       
    ; Выражение 1: ax^2 + bx + c, когда a < 0
    ; Выполнение ax^2 + bx + c
                      mov  ax, [x]
                      imul ax                    ; x * x
                      mov  bx, [a]
                      imul bx                    ; a * x^2
                      mov  result, ax            ; result = a * x^2
    
                      mov  ax, [x]
                      mov  bx, [b]
                      imul bx                    ; bx
                      add  result, ax            ; result += bx
    
                      mov  ax, [c]
                      add  result, ax            ; result += c
                      jmp  print_result

    calc_expr2:       
    ; Выражение 2: -a / (x - c), когда a > 0
    ; Выполнение -a / (x - c)
                      mov  ax, [x]
                      sub  ax, [c]               ; x - c
    
                      mov  bx, [a]
                      neg  bx                    ; -a
                      cwd                        ; Расширение знака для деления
                      idiv ax                    ; -a / (x - c)
                      mov  result, ax
                      jmp  print_result

    calc_expr3:       
    ; Выражение 3: a(x + c), иначе
                      mov  ax, [x]
                      add  ax, [c]               ; x + c
                      mov  bx, [a]
                      imul bx                    ; a * (x + c)
                      mov  result, ax
                      jmp  print_result

    print_result:     
    ; Вывод результата
                      lea  dx, result_msg
                      mov  ah, 09h
                      int  21h
    
                      mov  ax, result
                      call print_number          ; Печать числа
    
                      jmp  done

print_number proc
    ; Печать числа AX
                      push ax
                      push bx
                      push dx
    
                      mov  bx, 10                ; Делитель для преобразования в строку
                      xor  cx, cx                ; Очистить CX
    
    convert_loop:     
                      xor  dx, dx                ; Очистить DX
                      div  bx                    ; AX / BX
                      push dx                    ; Оставшийся остаток (цифра)
                      inc  cx                    ; Увеличить счетчик цифр
                      test ax, ax                ; AX == 0 ?
                      jnz  convert_loop
    
    print_digits:     
                      pop  dx                    ; Получить последнюю цифру
                      add  dl, '0'               ; Преобразовать в символ
                      mov  ah, 02h               ; Вывод символа
                      int  21h
                      loop print_digits
    
                      pop  dx
                      pop  bx
                      pop  ax
                      ret
print_number endp

    done:             
    ; Завершение программы
                      mov  ah, 4Ch
                      int  21h
main endp
end main