sc segment 'code'
assume cs:sc, ds:sc
org 256
start proc
mPrint macro string
                               mov      ah, 09h
                               lea      dx, string
                               int      21h
endm
    ; Инициализация сегмента данных
                        mov    ax, @data
                        mov    ds, ax
                        mov    es, ax

    ; Открытие входного файла
                        mov    ah, 3Dh
                        xor    al, al
                        lea    dx, input_file_name
                        int    21h
                        jc     opening_error
                        mov    input_file_ID, ax

    ; Создание выходного файла
                        mov    ah, 3Ch
                        xor    cx, cx
                        lea    dx, output_file_name
                        int    21h
                        jc     creation_error
                        mov    output_file_ID, ax

    file_read_loop:     
    ; Чтение символа из файла
                        mov    ah, 3Fh
                        mov    bx, input_file_ID
                        lea    dx, char_buffer
                        mov    cx, 1                      ; Читаем 1 байт
                        int    21h
                        jc     read_error
                        cmp    ax, 0                      ; Конец файла?
                        je     end_of_file

    ; Проверка на конец строки
                        mov    al, char_buffer            ; Получаем прочитанный символ
                        cmp    al, 0Dh                    ; Возврат каретки?
                        je     end_of_line
                        cmp    al, 0Ah                    ; Перевод строки?
                        je     end_of_line

    ; Сохранение символа в буфер строки
                        lea    di, line_buffer
                        mov    cx, line_length
                        add    di, cx                     ; Указатель на конец строки
                        mov    [di], al                   ; Сохраняем символ
                        inc    word ptr line_length       ; Увеличиваем длину строки
                        jmp    file_read_loop

    end_of_line:        
    ; Добавляем символы конца строки в конец строки
                        lea    di, line_buffer
                        add    di, line_length
                        mov    al, 0Dh
                        stosb
                        mov    al, 0Ah
                        stosb
                        mov al, '$'
                        stosb

    ; Выводим строку на экран
                        lea    dx, line_buffer
                        mPrint line_buffer

    ; Строка завершена, проверяем её чётность
                        mov    ax, line_number
                        test   ax, 1
                        jnz    skip_reverse               ; Нечётная строка — пропускаем

    ; Реверсируем чётную строку
                        lea    si, line_buffer
                        lea    di, reverse_buffer
                        add    si, line_length
                        dec    si
                        mov    cx, line_length
    reverse_loop:       
                        std                               ; Устанавливаем направление
                        lodsb                             ; Читаем символ из строки
                        cld                               ; Меняем направление
                        stosb                             ; Записываем в реверсированный буфер
                        loop   reverse_loop
    
    ; Добавляем символы конца строки (CRLF) в конец строки
                        lea    di, reverse_buffer
                        add    di, line_length
                        mov    al, 0Dh
                        stosb
                        mov    al, 0Ah
                        stosb
                        mov al, '$'
                        stosb

    ; Выводим перевёрнутую строку на экран
                        lea    dx, reverse_buffer
                        mPrint reverse_buffer

    ; Записываем реверсированную строку в выходной файл
                        lea    dx, reverse_buffer
                        mov    cx, line_length
                        call   write_line
                        jmp    continue_processing

    skip_reverse:       
    ; Записываем исходную строку в выходной файл
                        lea    dx, line_buffer
                        mov    cx, line_length
                        call   write_line

    continue_processing:
    ; Увеличение номера строки и сброс длины
                        inc    word ptr line_number
                        mov    word ptr line_length, 0
    ; Добавляем конец строки в файл вручную
                        lea    dx, newline
                        mov    ah, 40h
                        mov    bx, output_file_ID
                        lea    dx, newline
                        mov    cx, 2
                        int    21h
                        jmp    file_read_loop

    end_of_file:        
    ; Закрытие файлов
                        mov    ah, 3Eh
                        mov    bx, input_file_ID
                        int    21h

                        mov    ah, 3Eh
                        mov    bx, output_file_ID
                        int    21h

    ; Успешное завершение
                        mPrint completion_message
                        jmp    end_program

    write_line:         
    ; Записываем строку в файл
                        mov    ah, 40h
                        mov    bx, output_file_ID
                        int    21h
                        jc     write_error
                        ret

    opening_error:      
                        mPrint opening_error_message
                        jmp    end_program

    creation_error:     
                        mPrint creation_error_message
                        jmp    end_program

    read_error:         
                        mPrint read_error_message
                        jmp    end_program
    write_error:        
                        mPrint write_error_message
                        jmp    end_program

    end_program:        
                        mov    ax, 4C00h
                        int    21h

input_file_name        db "infile.txt", 0
    output_file_name       db "outfile.txt", 0

    input_file_ID          dw ?
    output_file_ID         dw ?

    opening_error_message  db "File could not be opened", "$"
    creation_error_message db "File could not be created", "$"
    read_error_message     db "File could not be read", "$"
    write_error_message    db "Error in writing to file", "$"
    completion_message     db "Program completed successfully", "$"

    newline                db 0Dh, 0Ah, 0                              ; Символы конца строки (CRLF)

    char_buffer            db 1 dup(0)                                 ; Буфер для чтения символа
    line_buffer            db 255 dup(0)                               ; Буфер для текущей строки
    line_length            dw 0                                        ; Длина текущей строки
    line_number            dw 1                                        ; Счётчик строк

    reverse_buffer         db 255 dup(0)                               ; Буфер для реверсированной строки
start endp
sc ends
endstart