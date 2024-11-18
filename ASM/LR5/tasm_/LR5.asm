include macroses.asm
.model small
.stack 100h
.data
  N          db 0
  c          dw 0
  d          dw 0
  numbers    db 10 dup(0)            ; массив для 10 чисел
  posCount   db 0                    ; счетчик положительных
  negCount   db 0                    ; счетчик отрицательных
  zeroCount  db 0                    ; счетчик нулевых
  promptN    db 'Enter N (1-10): $'
  promptC    db 'Enter c: $'
  promptD    db 'Enter d: $'
  promptNum  db 'Enter number: $'
  resultMsg  db 'Positive: $'
  resultPos  db 0
  resultNeg  db 0
  resultZero db 0
  newline    db 0Dh, 0Ah, '$'

.code
  main:         
                mov       ax, @data
                mov       ds, ax

  ; Ввод N
                mWriteStr promptN
                call      mReadByte
                sub       al, '0'             ; преобразуем символ в число
                mov       N, al               ; сохраняем N
                cmp       al, 1
                jb        exit                ; если N < 1, выход
                cmp       al, 10
                ja        exit                ; если N > 10, выход

  ; Ввод c
                mWriteStr promptC
                call      mReadAX
                mov       c, ax

  ; Ввод d
                mWriteStr promptD
                call      mReadAX
                mov       d, ax

  ; Ввод чисел
                mov       cl, N               ; CL = N
                xor       si, si              ; SI = 0 (индекс массива)

  input_loop:   
                mWriteStr promptNum
                mReadAX
                mov       numbers[si], al     ; сохраняем число в массив
                inc       si                  ; увеличиваем индекс

  ; Проверка условия c <= a[i] <= d
                cmp       ax, c
                jb        not_in_range
                cmp       ax, d
                ja        not_in_range

  ; Увеличиваем счетчики
                cmp       ax, 0
                je        zero_case
                jg        positive_case
                jmp       negative_case

  positive_case:
                inc       posCount
                jmp       next_input

  negative_case:
                inc       negCount
                jmp       next_input

  zero_case:    
                inc       zeroCount
                jmp       next_input

  not_in_range: 
  ; просто переходим к следующему числу
                jmp       next_input

  next_input:   
                loop      input_loop          ; уменьшаем CL и повторяем, если не 0

  ; Вывод результата
                mWriteStr resultMsg
                mov       al, posCount
                call      mWriteByte
                mWriteStr newline
                mWriteStr 'Negative: $'
                mov       al, negCount
                call      mWriteByte
                mWriteStr newline
                mWriteStr 'Zero: $'
                mov       al, zeroCount
                call      mWriteByte
                mWriteStr newline

  exit:         
                mov       ax, 4c00h
                int       21h

  ; Подпрограммы для ввода/вывода
mReadByte proc
                mov       ah, 01h
                int       21h
                ret
mReadByte endp

mReadAX proc
                mov       ah, 0
                int       16h
                ret
mReadAX endp

mWriteStr proc
                mov       dx, offset promptN  ; пример, нужно передать строку
                mov       ah, 09h
                int       21h
                ret
mWriteStr endp

mWriteByte proc
                add       al, '0'             ; преобразуем число в символ
                mov       ah, 02h
                int       21h
                ret
mWriteByte endp

end main
